.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r1,%:1,%0
	and	r1,%0,r1
1:	live	%1
	zjmp	%:1
