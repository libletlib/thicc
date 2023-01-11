#include <thicc.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static THICC_FUNCTION(foo_sum) {
  return let_real(as_real(THICC_1ST) + as_real(THICC_2ND));
}

static THICC_FUNCTION(factorial) {
  if (less_than(THICC_1ST, let_integer(2))) {
	return let_integer(1);
  } else {
	Let* minus = difference(THICC_1ST, let_integer(1));
	return product(THICC_1ST, invoke(self, 1, minus));
  }
}

static THICC_FUNCTION(println) {
  Let* string = move_string(as_string(THICC_1ST));
  printf("%s", string_view(string));
  unlet(string);
  return let_empty();
}

static void playground(void) {
  Let* foo_key		   = let_string("real");
  Let* foo_value		   = let_real(2.5);
  Let* foo_sum_key	   = let_string("+");
  Let* foo_sum_function = let_function(foo_sum);
  Let* object1		   = object_of(4, foo_key, foo_value, foo_sum_key, foo_sum_function);
  Let* object2		   = let_copy(object1);
  Let* result		   = sum(object1, object2);
  Let* number           = let_integer(5);
  Let* factorial_result;
  assert(equal(result, number));

  unlet(object1);
  unlet(object2);

  factorial_result = invoke(let_function(factorial), 1, number);
  assert(equal(factorial_result, let_integer(120)));
  invoke(let_function(println), 1, factorial_result);
}

int main(void) {
  playground();
  return EXIT_SUCCESS;
}
