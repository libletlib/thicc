#include <thicc_fortran_prelude.h>

module thicc_fortran
    implicit none
    use, intrinsic :: iso_c_binding, only: c_ptr, c_null_ptr
    use thicc_boilerplate

    public :: var
    public :: move_var

    type var
        type(thicc_struct_opaque) :: opaque

    contains
        final :: var_destructor
        procedure :: print => var_print
    end type var

    contains

        type(var) function var(_value)
            class(*), intent(in), value :: _value
            type(thicc_struct_opaque), intent(out) :: opaque
            type(mut), intent(out) :: result

            select type(_value)
                class is(thicc_struct_opaque)
                    opaque = opaque_let_copy(_value)
                type is(logical)
                    opaque = opaque_let_boolean(_value)
                type is(character)
                    opaque = opaque_let_character(_value)
                type is(integer)
                    opaque = opaque_let_integer(_value)
                type is(real)
                    opaque = opaque_let_real(_value)
                type is(complex)
                    opaque = opaque_let_complex(_value)
                type is(character(:))
            end select

            result%opaque = opaque
            return result
        end function var

        subroutine var_destructor(self)
            type(mut), intent(in) :: self

            interface
                subroutine opaque_unlet(opaque) bind(C)
                    type(thicc_struct_opaque), intent(in) :: opaque
                end subroutine opaque_unlet
            end interface

            call opaque_unlet(self%value)
        end subroutine var_destructor

        subroutine var_print(_var)
            type(var) string = as_string(_var%opaque)
        end subroutine var_print

end module thicc_fortran