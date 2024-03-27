# CUNIT
Simple unit test framework for c-libraries.

## Usage
### Prerequisites

- __Cunit__ frame work should be in your project directory.
- Full name of your library should match pattern *lib__name__.so*.
- You should compile your library by your own.
- __Cunit__ searchs tests by pattern
	- for files name should match `test_*.c` or `*_test.c`
	- for path name should match `*/test[s]/*.c`
- all files in `test[s]` folder considered contains tests.
- Header files `.h` are searched in `include` directory in _root_ of your _projecti_
- For now `Test` shold return `pass` on success and `fail` atherwise. But this behavior should be replaced with `pass` and `fail` keywords.

### Tests examples

```C
#include "cunit.h"

Test(Suit, Name) {
	/*
		some test logic
	/*
	return fail;
}
```

### Run tests
```Bash
make -C cunit test lib=[lib_name] path=[path_to_your_project] lib_dir=[lib_lir]
```

For example we want to test library with name `libft` so command will be like

```Bash
make -C cunit test lib=ft path=$PWD lib_dir=lib
```

This command force __cunit__ search librari with full name `libft.so` in directory `lib` in your project.

## TODO

- Asserts
- Test helpers files
- Usage functions
- Sutes
- make test -> cunit
- External files (project ralated files like configurations, that project need to read)
- Tests subforlders and non uniq file names
- Different outputs
	- json
	- yaml
	- tap
- Output conclusion with failed tests information by defaulti.
- Memmory leaks tests
- Tests and Tested files shoule compiled in debug mode by default.
- Skip tests and perform only user defined tests (`cunit --skip='[test_name_pattern]'` and `cunit --tests='[test_name_pattern]`)
