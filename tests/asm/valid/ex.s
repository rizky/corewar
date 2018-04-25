.name "zork"
.comment "just a basic living prog"
		
l2:	st	r1,r2
	sti	r2,%:live,%20
	and	r1,%0,r2
live:	live	%1
	zjmp	%:l2
