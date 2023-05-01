# Return Oriented Programming: Today
Suppose a hacker has found a buffer overflow exploit in the program to hijack control flow by overwriting the return address on the stack with the start of a ROP chain. Below are fragments from the program in question. 

Build a ROP chain that invokes the a malicious function `today` with one argument `2023`, this will print `The year is 2023!`.

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
    113e:	e8 35 ff ff ff       	callq  1078 <__cxa_finalize@plt>
..
0000000000001160 <frame_dummy>:
    1160:	e9 7b ff ff ff       	jmpq   10e0 <register_tm_clones>
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
0000000000001234 <main>:
    1234:	55                   	push   %rbp
    1235:	48 89 e5             	mov    %rsp,%rbp
    1238:	48 83 ec 10          	sub    $0x10,%rsp
    123c:	89 7d fc             	mov    %edi,-0x4(%rbp)
    123f:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1243:	83 7d fc 02          	cmpl   $0x2,-0x4(%rbp)
    1247:	74 0a                	je     1253 <main+0x1f>
    1249:	bf 00 00 00 00       	mov    $0x0,%edi
    124e:	e8 1d fe ff ff       	callq  1070 <exit@plt>
    1253:	48 8b 05 8e 2d 00 00 	mov    0x2d8e(%rip),%rax        # 3fe8 <exit@GLIBC_2.2.5>
    125a:	48 89 c6             	mov    %rax,%rsi
...
```
