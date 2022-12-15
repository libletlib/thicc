# ThicC

Simple ducktyping in ANSI C/ISO C89.

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