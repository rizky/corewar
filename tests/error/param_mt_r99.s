.name "zork"
.comment "just a basic living prog"

l2:
		sti r99,%:live,%1
		and r101,%0,r100
live:   live %1
		zjmp %:live
