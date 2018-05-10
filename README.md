# Corewar

## Installation:

`git clone --recurse-submodules https://github.com/rizkyario/42-corewar.git && cd 42-corewar && make`

## Usage:

### Assembler:

```
usage: ./asm [-a] sourcefile.s
       ./asm [-a] [-m] sourcefile.s ...
    -a : Prints a stripped and annoted version of the code
    -m : Allows processing of multiple files
```

![asm_usage_gif](http://g.recordit.co/aYceeeTGbA.gif)

`make assemble`: compile every player within subdirectory *tests/*

### Virtual Machine:

```
usage: ./corewar [options] [-n number] champion1.cor ...

OPTIONS
       -dump  nbr_cycles  : Dump the memory after nbr_cycles
       -dumpc nbr_cycles  : Colorized -dump
       -v N : Verbosity levels, can be added together to enable several
                - 2  : Show cycles
                - 4  : Show operations
                - 8  : Show deaths
                - 16 : Show PC movements (Except for jumps)
       -u : Decompile .cor back to .s
       -g : Printf  visualization
       -G : Ncurses visualization
  ```
  
![vm_usage_gif](http://g.recordit.co/ibcjoLsOtW.gif)

### In action:

#### Visualizer using printf:
![corewar in action_printf](https://github.com/rizkyario/42-corewar/blob/assets/corewar_in_action.gif)

#### Visualizer using ncurses:
![corewar_in_action_ncurses](https://github.com/rizkyario/42-corewar/blob/assets/corewar_in_action2.gif)

### Test Suite:

`make tests`: run an extensive set of tests of both the assembler and virtual machine\
`make tests_asm`: test only the assembler\
`make tests_vm` : test only the virtual machine

#### All test cases:

<img src="https://github.com/rizkyario/42-corewar/blob/assets/make_tests_large.png" width=80%>

## Code snippets:

### Assembler:

Parsing with our own regex library:

```C
int asm_get_paramtype(int opcode, t_param *param)
{
	if (ft_re_match("^r\\d+$", (*param).str) == 0)
	{
		(*param).value = asm_get_paramval((*param).str, "\\d+");
		(*param).size = 1;
		return (T_REG);
	}
	else if (ft_re_match("^%:[\\w_\\d]+$", (*param).str) == 0 ||
                     ft_re_match("^%-?\\d+$", (*param).str) == 0)
	{
		(ft_re_match("^%:[\\w_\\d]+$", (*param).str) == 0) ?
			(*param).is_label = 1 : 0;
		(*param).value = asm_get_paramval((*param).str, "-?\\d+");
		(*param).size = g_op_dict[opcode].d_size;
		return (T_DIR);
	}
	else if (ft_re_match("^:[\\w_\\d]+$", (*param).str) == 0 ||
			ft_re_match("^-?\\d+$", (*param).str) == 0)
	{
		!ft_re_match(":[\\w_\\d]+$", (*param).str) ? (*param).is_label = 1 : 0;
		(*param).value = asm_get_paramval((*param).str, "-?\\d+");
		(*param).size = 2;
		return (T_IND);
	}
	else
		return (-1);
}
```

### Virtual Machine:

Main function:

```C
int         main(int ac, char **av)
{
    t_vm            vm;
    time_t          start;
    static t_array  processes = NEW_ARRAY(t_process);

    ft_bzero(&vm, sizeof(t_vm));
    vm.processes = processes;
    if (ac < 2 || vm_options(av, &vm) == -1)
        return (vm_print_usage(av, -1));
    if (vm_get_champions(av, &vm) == -1)
        return (vm_error(vm.champ_size < 1 ? CHAMP_MIN : CHAMP_MAX, -1, NULL));
    if (vm_read_binaries(vm.players, &vm) == -1)
        return (-1);
    vm_load_champs(&vm);
    while (vm_checker(&vm))
    {
        vm_executor(&vm);
        if ((vm.dump && vm.cycles == g_cycles) ||
            (vm.option_g[VISU_2] && vm_start_ncurses(&start, vm) == -1))
            break ;
    }
    (!vm.dump || g_cycles < vm.cycles) ?
    ft_printfln("Contestant %d, \"%s\", has won !",
        vm.winner + 1, vm.champ[vm.winner].header.prog_name) : 0;
    vm_free(&vm);
    return (0);
}
```

For a closer look at the project's development history, refer to the branches 'feature/assembler' and 'feature/virtual-machine'

## Credits

Collaboration between

|<img src="https://avatars0.githubusercontent.com/u/6814254" width="75px;"/>|<img src="https://avatars0.githubusercontent.com/u/34797639" width="75px;"/>|<img src="https://avatars3.githubusercontent.com/u/38225561" width="75px;"/>|<img src="https://avatars0.githubusercontent.com/u/17133333" width="75px;"/>|
| --------- | --------- | --------  | --------- | 
| [Rizky Ario](https://github.com/rizkyario) |[Fabian Petras](https://github.com/fpetras)|[Julianto Yeo](https://github.com/juliantoyeo)|[Martin Jozan](https://github.com/mjozan)|
