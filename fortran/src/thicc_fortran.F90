#include "thicc_fortran_prelude.h"

module thicc_fortran
    use, intrinsic :: iso_c_binding, only: &
    c_ptr, c_null_ptr, c_size_t, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
    implicit none

    private

    integer, parameter, public :: c_integer = kind(int(0, THICC_FORTRAN_INTEGER))
    integer, parameter, public :: c_real = kind(real(0.0, THICC_FORTRAN_REAL))
    integer, parameter, public :: c_complex = kind(cmplx(0.0, 0.0, THICC_FORTRAN_COMPLEX))

    public :: var_print
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

    type, public :: var
        type(c_ptr) :: opaque
    contains
        final :: var_destructor
        procedure :: print => var_print
    end type var

    interface var
        module procedure :: let
    end interface var

    interface

        function let_boolean(value) bind(C, name="opaque_let_boolean")
            use, intrinsic :: iso_c_binding, only: c_ptr, c_bool
            implicit none

            logical(c_bool), value, intent(in) :: value
            type(c_ptr) :: let_boolean
        end function let_boolean

        function let_character(value) bind(C, name="opaque_let_character")
            use, intrinsic :: iso_c_binding, only: c_ptr, c_char
            implicit none

            character(c_char), value, intent(in) :: value
            type(c_ptr) :: let_character
        end function let_character

        function let_natural(value) bind(C, name="opaque_let_natural")
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_INTEGER
            implicit none

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(c_ptr) :: let_natural
        end function let_natural

        function let_integer(value) bind(C, name="opaque_let_integer")
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_INTEGER
            implicit none

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(c_ptr) :: let_integer
        end function let_integer

        function let_real(value) bind(C, name="opaque_let_real")
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_REAL
            implicit none

            real(THICC_FORTRAN_REAL), value, intent(in) :: value
            type(c_ptr) :: let_real
        end function let_real

        function let_complex(value) bind(C, name="opaque_let_complex")
            use, intrinsic :: iso_c_binding, only: c_ptr, THICC_FORTRAN_COMPLEX
            implicit none

            complex(THICC_FORTRAN_COMPLEX), value, intent(in) :: value
            type(c_ptr) :: let_complex
        end function let_complex

        function let_string(value) bind(C, name="opaque_let_string")
            use, intrinsic :: iso_c_binding, only: c_ptr, c_char
            implicit none

            type(c_ptr), value, intent(in) :: value
            type(c_ptr) :: let_string
        end function let_string

        function as_string(opaque) bind(C, name="opaque_as_string")
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr, c_size_t
            implicit none

            type, bind(C) :: thicc_struct_string
                type(c_ptr) :: string = c_null_ptr
                integer(c_size_t) :: length = 0
            end type thicc_struct_string
            type(c_ptr), value, intent(in) :: opaque
            type(thicc_struct_string) :: as_string
        end function as_string

        subroutine unlet_if_required(opaque) bind(C, name="opaque_unlet_if_required")
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr
            implicit none

            type(c_ptr), value, intent(in) :: opaque
        end subroutine unlet_if_required

        subroutine print(printable) bind(C, name="print")
            use, intrinsic :: iso_c_binding, only: c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: printable
        end subroutine print

    end interface

    contains

        function thicc_string(f_string)
            use, intrinsic :: iso_c_binding, only: c_ptr, c_null_char, c_loc
            implicit none

            character(*), intent(in) :: f_string
            character(len=len(f_string) + 1), target :: to_c

            type(c_ptr) :: c_string
            type(c_ptr) :: thicc_string

            to_c = f_string
            to_c(len(f_string) + 1:len(f_string) + 1) = c_null_char
            c_string = c_loc(to_c)

            thicc_string = let_string(c_string)

        end function thicc_string

        function let(value)
            use, intrinsic :: iso_c_binding, only: &
            c_bool, c_char, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
            implicit none
            class(*) :: value
            type(var) :: let

            select type(value)
                type is(logical)
                    let%opaque = let_boolean(logical(value, c_bool))
                type is(character(*))
                    if(len(value) == 1) then
                        let%opaque = let_character(value)
                    else
                        let%opaque = thicc_string(value)
                    end if
                type is(integer)
                    let%opaque = let_integer(int(value, c_integer))
                type is(real)
                    let%opaque = let_real(real(value, c_real))
                type is(complex)
                    let%opaque = let_complex(cmplx(value, kind=c_complex))
            end select
        end function let

        subroutine var_destructor(self)
            implicit none

            type(var), intent(in) :: self
            call unlet_if_required(self%opaque)
        end subroutine var_destructor

        subroutine var_print(printable)
            use, intrinsic :: iso_c_binding, only: c_ptr
            implicit none

            class(var) :: printable
            type(thicc_struct_string) :: string

            string = as_string(printable%opaque)
            call print(string%string)
        end subroutine var_print
end module thicc_fortran