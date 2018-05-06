.name "zork"
.comment "I'M ALIIIIVE"


#r_asm accept no whitespace between operation and param
#our_asm reject it

live:live%1
sti	r1,%:live,%0
	
