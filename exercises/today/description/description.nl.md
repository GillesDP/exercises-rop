# Return Oriented Programming: Vandaag
Stel dat een hacker een bufferoverloopexploit in het programma heeft gevonden om de controlestroom te kapen door het retouradres op de stapel te overschrijven met het begin van een ROP-keten. Hieronder staan ​​fragmenten uit het programma in kwestie.

Bouw een ROP-keten die de schadelijke functie `today` aanroept met één argument `2023`, dit zal afdrukken `The year is 2023!`.

```
0000000000001120 <__do_global_dtors_aux>:
    1120:	80 3d 21 2f 00 00 00 	cmpb   $0x0,0x2f21(%rip)        # 4048 <__TMC_END__>
    1127:	75 2f                	jne    1158 <__do_global_dtors_aux+0x38>
    1129:	55                   	push   %rbp
    112a:	48 83 3d c6 2e 00 00 	cmpq   $0x0,0x2ec6(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1131:	00 
    1132:	48 89 e5             	mov    %rsp,%rbp
...
0000000000001160 <frame_dummy>:
    1160:	e9 7b ff ff ff       	jmpq   10e0 <register_tm_clones>
...
0000000000001165 <today>:
    1165:	55                   	push   %rbp
    1166:	48 89 e5             	mov    %rsp,%rbp
    1169:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    116d:	48 83 ec 10          	sub    $0x10,%rsp
    1171:	89 7c 24 0c          	mov    %edi,0xc(%rsp)
    1175:	8b 44 24 0c          	mov    0xc(%rsp),%eax
    1179:	89 c6                	mov    %eax,%esi
    117b:	48 8d 3d 82 0e 00 00 	lea    0xe82(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    1182:	b8 00 00 00 00       	mov    $0x0,%eax
    1187:	e8 a4 fe ff ff       	callq  1030 <printf@plt>
    118c:	b8 00 00 00 00       	mov    $0x0,%eax
    1191:	c9                   	leaveq 
    1192:	c3                   	retq   
...
0000000000001193 <helpful>:
    1193:	55                   	push   %rbp
    1194:	48 89 e5             	mov    %rsp,%rbp
    1197:	bf e7 07 00 00       	mov    $0x7e7,%edi
    119c:	90                   	nop
    119d:	5d                   	pop    %rbp
    119e:	c3                   	retq   
...
0000000000001240 <main>:
    1240:	55                   	push   %rbp
    1241:	48 89 e5             	mov    %rsp,%rbp
    1244:	48 83 ec 10          	sub    $0x10,%rsp
    1248:	89 7d fc             	mov    %edi,-0x4(%rbp)
    124b:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    124f:	83 7d fc 02          	cmpl   $0x2,-0x4(%rbp)
    1253:	74 0a                	je     125f <main+0x1f>
    1255:	bf 00 00 00 00       	mov    $0x0,%edi
    125a:	e8 11 fe ff ff       	callq  1070 <exit@plt>
...
```