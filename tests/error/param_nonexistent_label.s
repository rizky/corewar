.name    "sebc"
.comment "sebc"

	st	r1, :truc #truc label doesn't exist
	ld	%4, r3 
l1:	live	%1
	ld	%:l1, r2
l3:	ldi	%:bla, r2, r4 #bla label doesn't exist
	sti	r4, %:l2, r2
	add	r2, r3, r2
live:	zjmp	%:l1
	zjmp	%:l3
l2:
