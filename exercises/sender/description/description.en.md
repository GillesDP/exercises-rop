# Return Oriented Programming: Today
Suppose a hacker has found a buffer overflow exploit in the program to hijack control flow by overwriting the return address on the stack with the start of a ROP chain. Below are fragments from the program in question. 

Build a ROP chain that invokes the a malicious function `sender(5, 8, 1)` which are passed in the `%edi`, `%esi`, and `%edx` registers respectively. This function will print `sender(5, 8, 1) called!`.

```
0000000000001120 <__do_global_dtors_aux>:
    1120:	80 3d 21 2f 00 00 00 	cmpb   $0x0,0x2f21(%rip)        # 4048 <__TMC_END__>
    1127:	75 2f                	jne    1158 <__do_global_dtors_aux+0x38>
    1129:	55                   	push   %rbp
    112a:	48 83 3d c6 2e 00 00 	cmpq   $0x0,0x2ec6(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1131:	00 
    1132:	48 89 e5             	mov    %rsp,%rbp
...
0000000000001165 <sender>:
    1165:	55                   	push   %rbp
    1166:	48 89 e5             	mov    %rsp,%rbp
    1169:	48 83 ec 10          	sub    $0x10,%rsp
    116d:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1170:	89 75 f8             	mov    %esi,-0x8(%rbp)
    1173:	89 55 f4             	mov    %edx,-0xc(%rbp)
    1176:	8b 4d f4             	mov    -0xc(%rbp),%ecx
    1179:	8b 55 f8             	mov    -0x8(%rbp),%edx
    117c:	8b 45 fc             	mov    -0x4(%rbp),%eax
    117f:	89 c6                	mov    %eax,%esi
    1181:	48 8d 3d 7c 0e 00 00 	lea    0xe7c(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    1188:	b8 00 00 00 00       	mov    $0x0,%eax
    118d:	e8 9e fe ff ff       	callq  1030 <printf@plt>
    1192:	b8 00 00 00 00       	mov    $0x0,%eax
    1197:	c9                   	leaveq 
    1198:	c3                   	retq
...
0000000000001199 <generate_payload>:
    1199:	55                   	push   %rbp
    119a:	48 89 e5             	mov    %rsp,%rbp
    119d:	c7 45 fc 05 00 00 00 	movl   $0x5,-0x4(%rbp)
    11a4:	c7 45 f8 01 00 00 00 	movl   $0x1,-0x8(%rbp)
    11ab:	eb 0e                	jmp    11bb <generate_payload+0x22>
    11ad:	8b 45 f8             	mov    -0x8(%rbp),%eax
    11b0:	0f af 45 fc          	imul   -0x4(%rbp),%eax
    11b4:	01 45 f8             	add    %eax,-0x8(%rbp)
    11b7:	83 6d fc 01          	subl   $0x1,-0x4(%rbp)
    11bb:	83 7d fc 00          	cmpl   $0x0,-0x4(%rbp)
    11bf:	7f ec                	jg     11ad <generate_payload+0x14>
    11c1:	5f                   	pop    %rdi
    11c2:	5e                   	pop    %rsi
    11c3:	41 5b                	pop    %r11
    11c5:	41 5c                	pop    %r12
    11c7:	90                   	nop
    11c8:	5d                   	pop    %rbp
    11c9:	c3                   	retq   
00000000000011ca <spoof_mac_address>:
    11ca:	55                   	push   %rbp
    11cb:	48 89 e5             	mov    %rsp,%rbp
    11ce:	5b                   	pop    %rbx
    11cf:	41 5c                	pop    %r12
    11d1:	5a                   	pop    %rdx
    11d2:	41 5d                	pop    %r13
    11d4:	90                   	nop
    11d5:	5d                   	pop    %rbp
    11d6:	c3                   	retq 
...
0000000000001278 <main>:
    1278:	55                   	push   %rbp
    1279:	48 89 e5             	mov    %rsp,%rbp
    127c:	48 83 ec 10          	sub    $0x10,%rsp
    1280:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1283:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1287:	83 7d fc 02          	cmpl   $0x2,-0x4(%rbp)
    128b:	74 0a                	je     1297 <main+0x1f>
    128d:	bf 00 00 00 00       	mov    $0x0,%edi
    1292:	e8 d9 fd ff ff       	callq  1070 <exit@plt>
...
```
