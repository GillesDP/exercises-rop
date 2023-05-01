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
    1135:	74 0c                	je     1143 <__do_global_dtors_aux+0x23>
    1137:	48 8b 3d 02 2f 00 00 	mov    0x2f02(%rip),%rdi        # 4040 <__dso_handle>
    113e:	e8 35 ff ff ff       	call   1078 <__cxa_finalize@plt>
    1143:	e8 68 ff ff ff       	call   10b0 <deregister_tm_clones>
...

0000000000001160 <frame_dummy>:
    1160:	e9 7b ff ff ff       	jmp    10e0 <register_tm_clones>

0000000000001165 <today>:
    1165:	55                   	push   %rbp
    1166:	48 89 e5             	mov    %rsp,%rbp
    1169:	48 83 ec 10          	sub    $0x10,%rsp
    116d:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1170:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1173:	89 c6                	mov    %eax,%esi
    1175:	48 8d 3d 88 0e 00 00 	lea    0xe88(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    117c:	b8 00 00 00 00       	mov    $0x0,%eax
    1181:	e8 aa fe ff ff       	call   1030 <printf@plt>
    1186:	b8 00 00 00 00       	mov    $0x0,%eax
    118b:	c9                   	leave  
    118c:	c3                   	ret
...
000000000000122e <main>:
    122e:	55                   	push   %rbp
    122f:	48 89 e5             	mov    %rsp,%rbp
    1232:	48 83 ec 10          	sub    $0x10,%rsp
    1236:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1239:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    123d:	83 7d fc 02          	cmpl   $0x2,-0x4(%rbp)
    1241:	74 0a                	je     124d <main+0x1f>
    1243:	bf 00 00 00 00       	mov    $0x0,%edi
    1248:	e8 23 fe ff ff       	call   1070 <exit@plt>
...
```