.name "zork"
.comment "just a basic living prog"
		
l2:	sti	r1,%:lve,%0
	and	r1,%0,r1
lve:	live	%1
	zjmp	%:live
