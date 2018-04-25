.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r2,%:live,%10
	and	r1,%0,r1
live:	live	%1
	zjmp	%:l2
