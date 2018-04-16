Manage GIT Submodule

git pull && git submodule init && git submodule update && git submodule status
git submodule update --recursive --remote

Run Test

`./asm resources/champs/ex1.s && hexdump -C resources/champs/ex1.cor`
`./resources/vm_champs/asm resources/champs/ex1.s && hexdump -C resources/champs/ex1.cor`

`./asm resources/valid/bigzork.s && hexdump -C resources/valid/bigzork.cor`
`./resources/vm_champs/asm resources/valid/bigzork.s && hexdump -C resources/valid/bigzork.cor`