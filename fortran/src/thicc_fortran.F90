!
!   ___       ___       ___       ___       ___
!  /\  \     /\__\     /\  \     /\  \     /\  \
!  \:\  \   /:/__/_   _\:\  \   /::\  \   /::\  \
!  /::\__\ /::\/\__\ /\/::\__\ /:/\:\__\ /:/\:\__\
! /:/\/__/ \/\::/  / \::/\/__/ \:\ \/__/ \:\ \/__/
! \/__/      /:/  /   \:\__\    \:\__\    \:\__\
!            \/__/     \/__/     \/__/     \/__/
!
! Copyright 2022 - 2023 Ville Rissanen
!
! Redistribution and use in source and binary forms, with or without
! modification, are permitted provided that the following conditions are met:
!
! 1.   Redistributions of source code must retain the above copyright notice,
!      this list of conditions and the following disclaimer.
!
! 2.   Redistributions in binary form must reproduce the above copyright notice,
!      this list of conditions and the following disclaimer in the documentation
!      and/or other materials provided with the distribution.
!
! THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
! AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
! IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
! DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
! FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
! DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
! SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
! CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
! OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
! OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "thicc_fortran_prelude.h"

module thicc_fortran
    use, intrinsic :: iso_c_binding, only : &
            c_ptr, c_null_ptr, c_size_t, c_funptr, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
    implicit none

    private

    integer, parameter, public :: c_integer = kind(int(0, THICC_FORTRAN_INTEGER))
    integer, parameter, public :: c_real = kind(real(0.0, THICC_FORTRAN_REAL))
    integer, parameter, public :: c_complex = kind(cmplx(0.0, 0.0, THICC_FORTRAN_COMPLEX))

    private :: let_destructor
    private :: let_as_boolean
    private :: let_as_character
    private :: let_as_integer
    private :: let_as_real
    private :: let_as_complex
    private :: let_as_string
    private :: let_as_function
    private :: let_as_array
    private :: let_as_object
    private :: let_call

    public :: thiccify_procedure

    type, public :: thicc_procedure
        type(c_funptr) :: procedure_pointer
    end type thicc_procedure

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

    type, public :: let
        private
        type(c_ptr) :: variable = c_null_ptr
    contains
        procedure :: let_assignment
        procedure :: let_sum
        procedure :: let_difference
        procedure :: let_product
        procedure :: let_quotient
        procedure :: let_modulo
        procedure :: let_power
        procedure :: let_equal
        procedure :: let_not_equal
        procedure :: let_greater_than
        procedure :: let_less_than
        procedure :: let_greater_or_equal
        procedure :: let_less_or_equal
        generic, public :: assignment(=) => let_assignment
        generic, public :: operator(+) => let_sum
        generic, public :: operator(-) => let_difference
        generic, public :: operator(*) => let_product
        generic, public :: operator(/) => let_quotient
        generic, public :: operator(.mod.) => let_modulo
        generic, public :: operator(**) => let_power
        generic, public :: operator(==) => let_equal
        generic, public :: operator(.ne.) => let_not_equal
        generic, public :: operator(>) => let_greater_than
        generic, public :: operator(<) => let_less_than
        generic, public :: operator(>=) => let_greater_or_equal
        generic, public :: operator(<=) => let_less_or_equal
        procedure, public :: as_boolean => let_as_boolean
        procedure, public :: as_character => let_as_character
        procedure, public :: as_integer => let_as_integer
        procedure, public :: as_real => let_as_real
        procedure, public :: as_complex => let_as_complex
        procedure, public :: as_string => let_as_string
        procedure, public :: as_function => let_as_function
        procedure, public :: as_array => let_as_array
        procedure, public :: as_object => let_as_object
        procedure, public :: call => let_call
        final :: let_destructor
    end type let

    interface let
        module procedure :: var
    end interface let

    abstract interface
        function thicc_function(self, args) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), intent(in) :: self
            type(c_ptr), intent(in) :: args
            type(c_ptr) :: thicc_function
        end function thicc_function
    end interface

    interface
        function let_move(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: value
            type(c_ptr) :: let_move
        end function let_move

        function let_copy(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: value
            type(c_ptr) :: let_copy
        end function let_copy

        function let_boolean(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            logical(c_bool), value, intent(in) :: value
            type(c_ptr) :: let_boolean
        end function let_boolean

        function let_character(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_char
            implicit none

            character(c_char), value, intent(in) :: value
            type(c_ptr) :: let_character
        end function let_character

        function let_natural(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_INTEGER
            implicit none

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(c_ptr) :: let_natural
        end function let_natural

        function let_integer(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_INTEGER
            implicit none

            integer(THICC_FORTRAN_INTEGER), value, intent(in) :: value
            type(c_ptr) :: let_integer
        end function let_integer

        function let_real(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_REAL
            implicit none

            real(THICC_FORTRAN_REAL), value, intent(in) :: value
            type(c_ptr) :: let_real
        end function let_real

        function let_complex(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_COMPLEX
            implicit none

            complex(THICC_FORTRAN_COMPLEX), value, intent(in) :: value
            type(c_ptr) :: let_complex
        end function let_complex

        function let_string(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_char
            implicit none

            type(c_ptr), value, intent(in) :: value
            type(c_ptr) :: let_string
        end function let_string

        function let_function(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_funptr
            implicit none

            type(c_funptr), value, intent(in) :: value
            type(c_ptr) :: let_function
        end function let_function

        function let_array(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t
            implicit none

            type, bind(C) :: thicc_struct_array
                type(c_ptr) :: array
                integer(c_size_t) :: length
            end type thicc_struct_array

            type(thicc_struct_array), value, intent(in) :: value
            type(c_ptr) :: let_array
        end function let_array

        function let_object(value) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: value
            type(c_ptr) :: let_object
        end function let_object

        function as_boolean(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            type(c_ptr), value, intent(in) :: let
            logical(c_bool) :: as_boolean
        end function as_boolean

        function as_character(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_char
            implicit none

            type(c_ptr), value, intent(in) :: let
            character(c_char) :: as_character
        end function as_character

        function as_integer(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_INTEGER
            implicit none

            type(c_ptr), value, intent(in) :: let
            integer(THICC_FORTRAN_INTEGER) :: as_integer
        end function as_integer

        function as_real(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_REAL
            implicit none

            type(c_ptr), value, intent(in) :: let
            real(THICC_FORTRAN_REAL) :: as_real
        end function as_real

        function as_complex(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, THICC_FORTRAN_COMPLEX
            implicit none

            type(c_ptr), value, intent(in) :: let
            complex(THICC_FORTRAN_COMPLEX) :: as_complex
        end function as_complex

        function as_string(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_null_ptr, c_size_t
            implicit none

            type, bind(C) :: thicc_struct_string
                type(c_ptr) :: string = c_null_ptr
                integer(c_size_t) :: length = 0
            end type thicc_struct_string

            type(c_ptr), value, intent(in) :: let
            type(thicc_struct_string) :: as_string
        end function as_string

        function as_function(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_funptr
            implicit none

            type(c_ptr), value, intent(in) :: let
            type(c_funptr) :: as_function
        end function as_function

        function as_array(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_null_ptr, c_size_t
            implicit none

            type, bind(C) :: thicc_struct_array
                type(c_ptr) :: array = c_null_ptr
                integer(c_size_t) :: length = 0
            end type thicc_struct_array

            type(c_ptr), value, intent(in) :: let
            type(thicc_struct_array) :: as_array
        end function as_array

        function as_object(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: let
            type(c_ptr) :: as_object
        end function as_object

        subroutine unlet(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: let
        end subroutine unlet

        function array_from_booleans(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_bool
            implicit none

            integer(c_size_t), value, intent(in) :: size
            logical(c_bool), intent(in) :: array(size)
            type(c_ptr) :: array_from_booleans
        end function array_from_booleans

        function array_from_characters(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char
            implicit none

            integer(c_size_t), value, intent(in) :: size
            character(c_char), intent(in) :: array(size)
            type(c_ptr) :: array_from_characters
        end function array_from_characters

        function array_from_integers(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, THICC_FORTRAN_INTEGER
            implicit none

            integer(c_size_t), value, intent(in) :: size
            integer(THICC_FORTRAN_INTEGER), intent(in) :: array(size)
            type(c_ptr) :: array_from_integers
        end function array_from_integers

        function array_from_reals(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, THICC_FORTRAN_REAL
            implicit none

            integer(c_size_t), value, intent(in) :: size
            real(THICC_FORTRAN_REAL), intent(in) :: array(size)
            type(c_ptr) :: array_from_reals
        end function array_from_reals

        function array_from_complex(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, THICC_FORTRAN_COMPLEX
            implicit none

            integer(c_size_t), value, intent(in) :: size
            complex(THICC_FORTRAN_COMPLEX), intent(in) :: array(size)
            type(c_ptr) :: array_from_complex
        end function array_from_complex

        function array_from_strings(size, array) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_size_t, c_char
            implicit none

            integer(c_size_t), value, intent(in) :: size
            character(:, c_char), pointer, intent(in) :: array(:)
            type(c_ptr) :: array_from_strings
        end function array_from_strings

        function call(let) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: let
            type(c_ptr) :: call
        end function call

        function sum(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            type(c_ptr) :: sum
        end function sum

        function difference(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            type(c_ptr) :: difference
        end function difference

        function product(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            type(c_ptr) :: product
        end function product

        function quotient(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            type(c_ptr) :: quotient
        end function quotient

        function modulo(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            type(c_ptr) :: modulo
        end function modulo

        function equal(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            logical(c_bool) :: equal
        end function equal

        function not_equal(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            logical(c_bool) :: not_equal
        end function not_equal

        function greater_than(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            logical(c_bool) :: greater_than
        end function greater_than

        function less_than(left, right) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr, c_bool
            implicit none

            type(c_ptr), value, intent(in) :: left, right
            logical(c_bool) :: less_than
        end function less_than

        subroutine free(pointer) bind(C)
            use, intrinsic :: iso_c_binding, only : c_ptr
            implicit none

            type(c_ptr), value, intent(in) :: pointer
        end subroutine free
    end interface

contains

    function thiccify_procedure(procedure)
        use, intrinsic :: iso_c_binding, only : c_funptr, c_funloc
        implicit none

        interface
            function foo(self, args) bind(C)
                use, intrinsic :: iso_c_binding, only : c_ptr
                implicit none

                type(c_ptr), value, intent(in) :: self
                type(c_ptr), value, intent(in) :: args
                type(c_ptr) :: foo
            end function foo
        end interface

        procedure(foo), pointer, intent(in) :: procedure
        type(thicc_procedure) :: thiccify_procedure
        thiccify_procedure%procedure_pointer = c_funloc(procedure)
    end function thiccify_procedure

    function thiccify_string(f_string)
        use, intrinsic :: iso_c_binding, only : c_ptr, c_null_char, c_loc
        implicit none

        character(*), intent(in) :: f_string
        character(len = len(f_string) + 1), target :: to_c

        type(c_ptr) :: c_string
        type(c_ptr) :: thiccify_string

        to_c = f_string
        to_c(len(to_c):len(to_c)) = c_null_char
        c_string = c_loc(to_c)

        thiccify_string = let_string(c_string)
    end function thiccify_string

    function var(value)
        use, intrinsic :: iso_c_binding, only : c_funptr, c_null_ptr, &
                c_bool, c_char, THICC_FORTRAN_INTEGER, THICC_FORTRAN_REAL, THICC_FORTRAN_COMPLEX
        implicit none
        class(*) :: value
        type(let) :: var

        select type(value)
        class is(let)
            var%variable = value%variable
            value%variable = c_null_ptr
        type is(logical)
            var%variable = let_boolean(logical(value, c_bool))
        type is(character(*))
            if(len(value) == 1) then
                var%variable = let_character(value)
            else
                var%variable = thiccify_string(value)
            end if
        type is(integer)
            var%variable = let_integer(int(value, c_integer))
        type is(real)
            var%variable = let_real(real(value, c_real))
        type is(complex)
            var%variable = let_complex(cmplx(value, kind = c_complex))
        type is(thicc_procedure)
            var%variable = let_function(value%procedure_pointer)
        end select
    end function var

    subroutine let_assignment(left, right)
        use, intrinsic :: iso_c_binding, only : c_bool, c_null_ptr
        implicit none

        class(let), intent(inout) :: left
        class(*), intent(in) :: right

        call unlet(left%variable)
        select type(right)
        class is(let)
            left%variable = right%variable
        type is(logical)
            left%variable = let_boolean(logical(right, c_bool))
        type is(character(*))
            if(len(right) == 1) then
                left%variable = let_character(right)
            else
                left%variable = thiccify_string(right)
            end if
        type is(integer)
            left%variable = let_integer(int(right, c_integer))
        type is(real)
            left%variable = let_real(real(right, c_real))
        type is(complex)
            left%variable = let_complex(cmplx(right, kind = c_complex))
        type is(thicc_procedure)
            left%variable = let_function(right%procedure_pointer)
        end select
    end subroutine let_assignment

    subroutine let_destructor(self)
        implicit none

        type(let), intent(in) :: self
        call unlet(self%variable)
    end subroutine let_destructor

    function let_as_boolean(self)
        use, intrinsic :: iso_c_binding, only : c_bool
        implicit none

        class(let), intent(in) :: self
        logical(c_bool) :: let_as_boolean
        let_as_boolean = as_boolean(self%variable)
    end function let_as_boolean

    function let_as_character(self)
        use, intrinsic :: iso_c_binding, only : c_char
        implicit none

        class(let), intent(in) :: self
        character(c_char) :: let_as_character
        let_as_character = as_character(self%variable)
    end function let_as_character

    function let_as_integer(self)
        use, intrinsic :: iso_c_binding, only : THICC_FORTRAN_INTEGER
        implicit none

        class(let), intent(in) :: self
        integer(THICC_FORTRAN_INTEGER) :: let_as_integer
        let_as_integer = as_integer(self%variable)
    end function let_as_integer

    function let_as_real(self)
        use, intrinsic :: iso_c_binding, only : THICC_FORTRAN_REAL
        implicit none

        class(let), intent(in) :: self
        real(THICC_FORTRAN_REAL) :: let_as_real
        let_as_real = as_real(self%variable)
    end function let_as_real

    function let_as_complex(self)
        use, intrinsic :: iso_c_binding, only : THICC_FORTRAN_COMPLEX
        implicit none

        class(let), intent(in) :: self
        complex(THICC_FORTRAN_COMPLEX) :: let_as_complex
        let_as_complex = as_complex(self%variable)
    end function let_as_complex

    function let_as_string(self)
        use, intrinsic :: iso_c_binding, only : c_f_pointer, c_char
        implicit none

        class(let), intent(in) :: self
        type(thicc_struct_string) :: thicc_string
        character(:, c_char), allocatable :: let_as_string
        character(c_char), pointer :: c_string(:)
        integer :: index

        thicc_string = as_string(self%variable)
        call c_f_pointer(thicc_string%string, c_string, [thicc_string%length + 1])
        allocate(character(thicc_string%length) :: let_as_string)

        do index = 0, thicc_string%length
            let_as_string(index:index) = c_string(index)
        end do

        call free(thicc_string%string)
    end function let_as_string

    function let_as_function(self)
        use, intrinsic :: iso_c_binding, only : c_funptr
        implicit none

        class(let), intent(in) :: self
        type(c_funptr) :: let_as_function
        let_as_function = as_function(self%variable)
    end function let_as_function

    function let_as_array(self)
        implicit none

        class(let), intent(in) :: self
        type(thicc_struct_array) :: let_as_array
        let_as_array = as_array(self%variable)
    end function let_as_array

    function let_as_object(self)
        use, intrinsic :: iso_c_binding, only : c_ptr
        implicit none

        class(let), intent(in) :: self
        type(c_ptr) :: let_as_object
        let_as_object = as_object(self%variable)
    end function let_as_object

    function let_call(self)
        use, intrinsic :: iso_c_binding, only : c_ptr
        implicit none

        class(let), intent(in) :: self
        type(c_ptr) :: let_call
        let_call = call(self%variable)
    end function let_call

    function let_sum(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_sum, right_let

        select type(right)
        class is(let)
            let_sum%variable = sum(left%variable, right%variable)
        class default
            right_let = let(right)
            let_sum%variable = sum(left%variable, right_let%variable)
        end select
    end function let_sum

    function let_difference(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_difference, right_let

        select type(right)
        class is(let)
            let_difference%variable = difference(left%variable, right%variable)
        class default
            right_let = let(right)
            let_difference%variable = difference(left%variable, right_let%variable)
        end select
    end function let_difference

    function let_product(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_product, right_let

        select type(right)
        class is(let)
            let_product%variable = product(left%variable, right%variable)
        class default
            right_let = let(right)
            let_product%variable = product(left%variable, right_let%variable)
        end select
    end function let_product

    function let_quotient(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_quotient, right_let

        select type(right)
        class is(let)
            let_quotient%variable = quotient(left%variable, right%variable)
        class default
            right_let = let(right)
            let_quotient%variable = quotient(left%variable, right_let%variable)
        end select
    end function let_quotient

    function let_modulo(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_modulo, right_let

        select type(right)
        class is(let)
            let_modulo%variable = modulo(left%variable, right%variable)
        class default
            right_let = let(right)
            let_modulo%variable = modulo(left%variable, right_let%variable)
        end select
    end function let_modulo

    function let_power(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_power, right_let, temporary

        temporary%variable = product(left%variable, left%variable)
        select type(right)
        class is(let)
            let_power%variable = product(temporary%variable, right%variable)
        class default
            right_let = let(right)
            let_power%variable = product(temporary%variable, right_let%variable)
        end select
    end function let_power

    function let_equal(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_equal, right_let

        select type(right)
        class is(let)
            let_equal%variable = let_boolean(equal(left%variable, right%variable))
        class default
            right_let = let(right)
            let_equal%variable = let_boolean(equal(left%variable, right_let%variable))
        end select
    end function let_equal

    function let_not_equal(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_not_equal, right_let

        select type(right)
        class is(let)
            let_not_equal%variable = let_boolean(not_equal(left%variable, right%variable))
        class default
            right_let = let(right)
            let_not_equal%variable = let_boolean(not_equal(left%variable, right_let%variable))
        end select
    end function let_not_equal

    function let_greater_than(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_greater_than, right_let

        select type(right)
        class is(let)
            let_greater_than%variable = let_boolean(greater_than(left%variable, right%variable))
        class default
            right_let = let(right)
            let_greater_than%variable = let_boolean(greater_than(left%variable, right_let%variable))
        end select
    end function let_greater_than

    function let_less_than(left, right)
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: let_less_than, right_let

        select type(right)
        class is(let)
            let_less_than%variable = let_boolean(less_than(left%variable, right%variable))
        class default
            right_let = let(right)
            let_less_than%variable = let_boolean(less_than(left%variable, right_let%variable))
        end select
    end function let_less_than

    function let_greater_or_equal(left, right)
        use, intrinsic :: iso_c_binding, only : c_bool
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: gt, eq, let_greater_or_equal, right_let
        logical(c_bool) :: result

        select type(right)
        class is(let)
            gt = left > right
            eq = left == right
        class default
            right_let = let(right)
            gt = left > right_let
            eq = left == right_let
        end select

        result = gt%as_boolean() .or. eq%as_boolean()
        let_greater_or_equal = let(result)
    end function let_greater_or_equal

    function let_less_or_equal(left, right)
        use, intrinsic :: iso_c_binding, only : c_bool
        implicit none

        class(let), intent(in) :: left
        class(*), intent(in) :: right
        type(let) :: lt, eq, let_less_or_equal, right_let
        logical(c_bool) :: result

        select type(right)
        class is(let)
            lt = left < right
            eq = left == right
        class default
            right_let = let(right)
            lt = left < right_let
            eq = left == right_let
        end select

        result = lt%as_boolean() .or. eq%as_boolean()
        let_less_or_equal = let(result)
    end function let_less_or_equal

end module thicc_fortran