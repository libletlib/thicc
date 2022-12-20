# ThicC

[![Tests](https://github.com/libletlib/thicc/actions/workflows/tests.yml/badge.svg)](https://github.com/libletlib/thicc/actions/workflows/tests.yml)

Simple ducktyping in ANSI C/ISO C89. Adheres strictly to the standard

## Types

In order of ascending priority:
* boolean -> `unsigned int/_Bool`
* character -> `char`
* natural -> `unsigned long/unsigned long long`
* integer -> `long/long long`
* real -> `long double`
* complex -> `struct { Real real; Real imaginary };`
* string -> `char*`
* function -> `Var (*function)(Var self, Var args)`
* array -> `Var*`
* object -> `void*`

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

For the pointer types, there is also a more `const`-qualified type with the `Immutable` prefix.
* ImmutableString -> `char const* const`
* ImmutableArray -> `Var const* const`
* ImmutableObject -> `void const* const`

### Macros

* `function(name)` for writing thicc function signatures easier.
```c
#define function(name) Var name(Var self, Var args)
```
* `st`, `nd`, `rd`, and `th` for accessing thicc function arguments easier.
```c
#define st (array_view(args)[0])
#define nd (array_view(args)[1])
#define rd (array_view(args)[2])
#define th (array_view(args)[3])
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

## Arrays
Arrays are merely pointers to C arrays of Vars. Arrays are 

## Objects

 
## Recurse you a factorial
```c
#include <thicc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

function(factorial) {
    if (less_than(st, let_integer(2))) {
        return let_integer(1);
    } else {
        Let minus = difference(st, let_integer(1));
        return product(st, invoke(self, 1, &minus));
    }
}

function(println) {
    Let string_type = move_string(as_string(st));
    printf("%s", string_view(string_type));
    unlet(string_type);
    return unit;
}

int main(void) {
    Let number = let_integer(5);
    Let factorial_result = invoke(let_function(factorial), 1, &number);
    assert(equal(factorial_result, let_integer(120)));
    invoke(let_function(println), 1, &factorial_result);
    return EXIT_SUCCESS;
}
```