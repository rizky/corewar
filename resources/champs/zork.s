.comment "just a basic living prog"
.name "truc"


l2:		sti r1,%:live,%1
		and r1,%0,r1
live:   live %1
		zjmp %:live
