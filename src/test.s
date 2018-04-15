.name "zork"
.comment "I'M ALIIIIVE"

l2: sti r99, :liv, %1 ;0b(opcode of sti) 78 01 00 0a 00 01

fork %:l2 ;0c(fork) ff f9

liv: live %4294967294 ;01(live) 00 00 00 01
