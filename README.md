# Corewar Unit-Tests

Corewar Unit-Tests is a unit test-suite to check whether your asm and corewar have the same behaviour as zaz's asm and corewar. In order to use most of the tests, some options are expected to be implemented by your asm and corewar. By default unit-tests will use `-v 30`, but you can configure the options inside Makefile in the config section.

Option| Makefile Variable |Description|
|---------- |---------- |---------- |
|./asm -a| OPT_A | Prints a stripped and annoted version of the code|
|./corewar -v 30 | OPT_V | Verbosity levels: 2  : Show cycles, 4  : Show operations, 8  : Show deaths, 16 : Show PC movements (Except for jumps)|
|./corewar -dump {nbr_cycles} | OPT_DUMP | Dump the memory after nbr_cycles|

## Source

https://github.com/rizkyario/42-corewar/tree/unit-tests

## Installation

```
git clone https://github.com/rizkyario/42-corewar.git && cd 42-corewar && git checkout unit-tests && make tests
```

or

```
curl --silent "https://api.github.com/repos/rizkyario/42-corewar/releases/latest" | grep '"tarball_url":' | sed -E 's/.*"([^"]+)".*/\1/' | xargs curl -L | tar zx
```

## Instruction

- Add asm binary path to ASM_PATH inside Makefile
- Add corewar binary path to VM_PATH inside Makefile
- Run Comprehensive test using `make tests`

## Test Descriptions
### General Tests
| Test syntax | Description |
| ---------- | ----------- |
| `make tests` | Run comprehensive test on asm and vm |
| `make tests_leaks` | Run leak test on asm and vm |
| `make tests_asm_leaks` | Run leak test on asm |
| `make tests_vm_leaks` | Run leak test on vm |
| `make tests_asm` | Run comprehensive test on asm |
| `make tests_vm` | Run comprehensive test on vm |
### Assembler Tests
| Test syntax|Description|
|---------- |---------- |
| `make tests_asm_error` | Run error test case on asm, by comparing return value from main. Expected value is -1 for exit with error |
| `make tests_asm_valid` | Run valid test case on asm, by comparing the output of option -a e.g `./asm -a 42.s`|
| `make tests_asm_bin` | Run valid test case on asm, by comparing binaries (.cor) |
### Corewar Tests
|Test syntax|Description|
|---------- |---------- |
| `make tests_vm_error` | Run error test case on vm, by comparing return value from main. Expected value is -1 for exit with error |
| `make tests_vm_op` | Run test case focused on simple operation by comparing -v 30|
| `make tests_vm_ocp` | Run test case focused on different ocp by comparing -v 30|
| `make tests_vm_dump` | Run test case focused on simple operation by comparing memory dumps using option -dump |
| `make tests_vm_op_champs` | Run test case focused on operation used by champs by comparing -v 30 |
| `make tests_vm_dump_champs` | Run test case focused on operation used by champs by comparing memory dumps using option -dump|
| `make tests_vm_op_overflow` | Run test case focused on overflow by comparing -v 30 |
| `make tests_vm_dump_overflow` | Run test case focused on overflow by comparing memory dumps using option -dump|
| `make tests_vm_battle` | Run test case focus battle between two champs by comparing -v 30|
