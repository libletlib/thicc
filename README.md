# ThicC

[![Tests](https://github.com/libletlib/thicc/actions/workflows/tests.yml/badge.svg)](https://github.com/libletlib/thicc/actions/workflows/tests.yml)

Simple ducktyping in ANSI C/ISO C89. Adheres strictly to the standard and tested on three major compiler vendors (Clang, GCC, MSVC)
on three platforms (Mac OS, Ubuntu, Windows).

## Types

In order of ascending priority:
* boolean -> `unsigned int/_Bool`
* character -> `char`
* natural -> `unsigned long/unsigned long long`
* integer -> `long/long long`
* real -> `long double`
* complex -> `struct { Real real; Real imaginary };`
* string -> `struct { char* string; MutableNatural length; }`
* function -> `Var (*function)(Var self, Var args)`
* array -> `struct { Var* array; MutableNatural length; }`
* object -> `void*` (can be `NULL`)

## Typedefs and macros

### Useful typedefs
* Var -> `struct thicc_struct_let`
* Let -> `struct thicc_struct_let const`

Every instance of the below typedefs has a mutable variant with the `Mutable` prefix, like `MutableBoolean`.
* Boolean
* Character
* Natural
* Integer
* Real
* Complex
* String
* Function
* Array
* Object

For the object type, there is also a more `const`-qualified type with the `Immutable` prefix.
* ImmutableObject -> `void const* const`

### Macros

* `THICC_FUNCTION(name)` for writing thicc function signatures easier.
```c
#define THICC_FUNCTION(_name) Var _name(Var self, Var args)
```
* `THICC_1ST`, `THICC_2ND`, `THICC_3RD`, and `THICC_4TH` for accessing thicc function arguments easier.
```c
#define THICC_1ST (array_view(args)[0])
#define THICC_2ND (array_view(args)[1])
#define THICC_3RD (array_view(args)[2])
#define THICC_4TH (array_view(args)[3])
```

## Functions

A basic thicc functions has the signature:
```c
Var function_name(Var self, Var args);
```
where
* `self` is a Function to the function itself, allowing anonymous recursion.
* `args` is a Array to the arguments of the function.
  * Functions invoked via objects take the object as the first argument.
* All function must return something, hence exists the `unit` macro.

## Strings
Strings are structs of a `char*` pointer and its known length.

## Arrays
Arrays are structs of a pointer to Var (C array) and its known length.

## Objects
Object representation is an array with length of 2. Both elements of the `members`-array are arrays themselves, first
one holds the keys and the second one the values of a dictionary.
 
## Recurse you a factorial
```c
#include <thicc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static THICC_FUNCTION(factorial) {
    if (less_than(THICC_1ST, let_integer(2))) {
        return let_integer(1);
    } else {
        Let minus = difference(THICC_1ST, let_integer(1));
        return product(THICC_1ST, invoke(self, 1, &minus));
    }
}

static THICC_FUNCTION(println) {
    Let string_type = move_string(as_string(THICC_1ST));
    printf("%s", string_view(string_type));
    unlet(string_type);
    return let_empty();
}

int main(void) {
    Let number = let_integer(5);
    Let factorial_result = invoke(let_function(factorial), 1, &number);
    assert(equal(factorial_result, let_integer(120)));
    invoke(let_function(println), 1, &factorial_result);
    return EXIT_SUCCESS;
}
```