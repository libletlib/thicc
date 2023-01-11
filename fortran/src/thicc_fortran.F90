#include "thicc_fortran_prelude.h"

module thicc_fortran
    use, intrinsic :: iso_c_binding, only: &
    c_ptr, c_null_ptr, c_size_t, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
    implicit none

    private

    integer, parameter, public :: c_integer = kind(int(0, THICC_FORTRAN_INTEGER))
    integer, parameter, public :: c_real = kind(real(0.0, THICC_FORTRAN_REAL))
    integer, parameter, public :: c_complex = kind(cmplx(0.0, 0.0, THICC_FORTRAN_COMPLEX))

    private :: var_destructor

    enum, bind(C)
        enumerator :: boolean_rank = 0
        enumerator :: character_rank = 1
        enumerator :: natural_rank = 2
        enumerator :: integer_rank = 3
        enumerator :: real_rank = 4
        enumerator :: complex_rank = 5
        enumerator :: string_rank = 6
        enumerator :: function_rank = 7
        enumerator :: array_rank = 8
        enumerator :: object_rank = 9
    end enum

    type, bind(C) :: thicc_struct_string
        type(c_ptr) :: string = c_null_ptr
        integer(c_size_t) :: length = 0
    end type thicc_struct_string

    type, bind(C) :: thicc_struct_array
        type(c_ptr) :: array = c_null_ptr
        integer(c_size_t) :: length = 0
    end type thicc_struct_array

    type, public, bind(C) :: thicc_struct_var
        type(c_ptr) :: value = c_null_ptr
        type(c_ptr) :: behaviour = c_null_ptr
    end type thicc_struct_var

    type, public :: var
        private
        type(thicc_struct_var) :: variable
    contains
        final :: var_destructor
    end type var

    interface var
        module procedure :: let
    end interface var

    interface

        function let_boolean(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_bool, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            logical(c_bool), value, intent(in) :: value
            type(thicc_struct_var) :: let_boolean
        end function let_boolean

        function let_character(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_char, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            character(c_char), value, intent(in) :: value
            type(thicc_struct_var) :: let_character
        end function let_character

        function let_natural(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_INTEGER, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(thicc_struct_var) :: let_natural
        end function let_natural

        function let_integer(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_INTEGER, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(thicc_struct_var) :: let_integer
        end function let_integer

        function let_real(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_REAL, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            real(THICC_FORTRAN_REAL), value, intent(in) :: value
            type(thicc_struct_var) :: let_real
        end function let_real

        function let_complex(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_COMPLEX, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            complex(THICC_FORTRAN_COMPLEX), value, intent(in) :: value
            type(thicc_struct_var) :: let_complex
        end function let_complex

        function let_string(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_char, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            type(c_ptr), value, intent(in) :: value
            type(thicc_struct_var) :: let_string
        end function let_string

        function let_function(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_funptr, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            type(c_funptr), value, intent(in) :: value
            type(thicc_struct_var) :: let_function
        end function let_function

        function let_array(value) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            type(c_ptr), value, intent(in) :: value
            type(thicc_struct_var) :: let_array
        end function let_array

        function as_string(var) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr, c_size_t
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            type, bind(C) :: thicc_struct_string
                type(c_ptr) :: string = c_null_ptr
                integer(c_size_t) :: length = 0
            end type thicc_struct_string

            type(thicc_struct_var), value, intent(in) :: var
            type(thicc_struct_string) :: as_string
        end function as_string

        subroutine unlet(var) bind(C)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr
            implicit none

            type, bind(C) :: thicc_struct_var
                type(c_ptr) :: value = c_null_ptr
                type(c_ptr) :: behaviour = c_null_ptr
            end type thicc_struct_var

            type(thicc_struct_var), value, intent(in) :: var
        end subroutine unlet

    end interface

    contains

        function thicc_string(f_string)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_char, c_loc
            implicit none

            character(*), intent(in) :: f_string
            character(len=len(f_string) + 1), target :: to_c

            type(c_ptr) :: c_string
            type(thicc_struct_var) :: thicc_string

            to_c = f_string
            to_c(len(to_c):len(to_c)) = c_null_char
            c_string = c_loc(to_c)

            thicc_string = let_string(c_string)
        end function thicc_string

        function thicc_function_prototype(self, args) bind(C)
            type(thicc_struct_var), value, intent(in) :: self, args
            type(thicc_struct_var) :: thicc_function_prototype
        end function thicc_function_prototype

        function thicc_function(f_function)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_funloc, c_funptr
            procedure(thicc_function_prototype), pointer, intent(in) :: f_function
            type(thicc_struct_var) :: thicc_function
            thicc_function = let_function(c_funloc(f_function))
        end function thicc_function

        function let(value)
            use, intrinsic :: iso_c_binding, only: &
            c_bool, c_char, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
            implicit none
            class(*) :: value
            type(var) :: let

            select type(value)
                type is(logical)
                    let%variable = let_boolean(logical(value, c_bool))
                type is(character(*))
                    if(len(value) == 1) then
                        let%variable = let_character(value)
                    else
                        let%variable = thicc_string(value)
                    end if
                type is(integer)
                    let%variable = let_integer(int(value, c_integer))
                type is(real)
                    let%variable = let_real(real(value, c_real))
                type is(complex)
                    let%variable = let_complex(cmplx(value, kind=c_complex))
            end select
        end function let

        subroutine var_destructor(self)
            implicit none

            type(var), intent(in) :: self
            call unlet(self%variable)
        end subroutine var_destructor

end module thicc_fortran