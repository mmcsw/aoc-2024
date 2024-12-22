# Advent of Code 2024

Solutions by Matthew McSweeney

Solved in C, making use of the [STC]() library.

## Compiling

clone the STC library to a location of your choosing, then make a symbolic link to `lib/stc`.

```sh
$ cd where_you_put_libs
$ git clone https://github.com/stclib/STC.git
$ cd aoc-2024
$ ln -s where_you_put_libs/STC/include/stc lib/stc
```

Then, assuming you have clang, just `make`.

```sh
$ make clean
$ make
```

This will produce an executable named `main`.

## Running

The solution program is monolithic, and you specify a problem number and input file via options.

```sh
$ ./main -m <PROBLEM_NUMBER> -f <FILE>
```
