   .data
0x10010020
a:  .word   42         // int x = 42
+4
0x10010024
b:  .space  4         //malloc(4) -> 4 bytes of uninitialised space
+4
0x10010028
c:  .asciiz "abcde"   // space: "abcde \0"
+6
0123456789ABCDEF
0x1001002E
c2:
    .align  2     // next label (d) must be 2^2 - aligned
// d must be at next address divisible by 4
0x10010030
d:  .byte   1, 2, 3, 4    char x[4] = {1, 2, 3, 4}
+4
0x10010034
e:  .word   1, 2, 3, 4    int  x[4] = {1, 2, 3, 4}
+16
0x10010044
f:  .space  1