#include <thicc_fortran_prelude.h>

module thicc_boilerplate

    use, intrinsic :: iso_c_binding

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

    type, bind(C) :: thicc_struct_opaque
        type(c_ptr) :: variable = c_null_ptr
    end type opaque

    type, bind(C) :: thicc_struct_string
        type(c_char), pointer :: string(:)
        type(c_size_t) :: length
    end type thicc_struct_string

    type, bind(C) :: thicc_struct_array
        type(c_ptr) :: array
        type(c_size_t) :: length
    end type thicc_struct_array

    interface
        type(c_int) function rank(_opaque) bind(C, name="opaque_rank")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function rank

        type(thicc_struct_opaque) function cast(_opaque, _rank) bind(C, name="opaque_cast")
            type(thicc_struct_opaque), intent(in) :: _opaque
            type(c_int), intent(in) :: _rank
        end function cast

        type(c_bool) function requires_free(_opaque) bind(C, name="opaque_requires_free")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function requires_free

        subroutine unlet(_opaque) bind(C, name="opaque_unlet")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end subroutine unlet

        subroutine unlet_if_required(_opaque) bind(C, name="opaque_unlet")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end subroutine unlet_if_required

        type(c_ptr) function string_view(_opaque) bind(C, name="opaque_string_view")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function string_view

        type(c_ptr) function array_view(_opaque) bind(C, name="opaque_array_view")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function array_view

        type(c_ptr) function object_view(_opaque) bind(C, name="opaque_object_view")
            type(thicc_struct_opque), intent(in) :: _opaque
        end function object_view

        type(c_bool) function as_boolean(_opaque) bind(C, name="opaque_as_boolean")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_boolean

        type(c_char) function as_character(_opaque) bind(C, name="opaque_as_character")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_character

        type(THICC_FORTRAN_INTEGER) function as_integer(_opaque) bind(C, name="opaque_as_integer")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_integer

        type(c_long_double) function as_real(_opaque) bind(C, name="opaque_as_real")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_real

        type(c_long_double_complex) function as_complex(_opaque) bind(C, name="opaque_as_complex")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_complex

        type(thicc_struct_string) function as_string(_opaque) bind(C, name="opaque_as_string")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_string

        type(thicc_struct_array) function as_array(_opaque) bind(C, name="opaque_as_array")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_array

        type(c_ptr) function as_object(_opaque) bind(C, name="opaque_as_object")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function as_object

        type(thicc_struct_opaque) function weak_string(_string) bind(C, name="opaque_weak_string")
            type(c_ptr), intent(in), value :: _string
        end function weak_string

        type(thicc_struct_opaque) function call(_opaque) bind(C, name="opaque_call")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function call

        type(thicc_struct_opaque) function member(_object, _member) bind(C, name="opaque_member")
            type(thicc_struct_opaque), intent(in) :: _object
            type(thicc_struct_opaque), intent(in) :: _member
        end function member

        type(thicc_struct_opaque) function sum(_left, _right) bind(C, name="opaque_sum")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function sum

        type(thicc_struct_opaque) function difference(_left, _right) bind(C, name="opaque_difference")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function difference

        type(thicc_struct_opaque) function quotient(_left, _right) bind(C, name="opaque_quotient")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function quotient

        type(thicc_struct_opaque) function modulo(_left, _right) bind(C, name="opaque_modulo")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function modulo

        type(thicc_struct_opaque) function product(_left, _right) bind(C, name="opaque_product")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function product

        type(thicc_struct_opaque) function bit_and(_left, _right) bind(C, name="opaque_bit_and")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function bit_and

        type(thicc_struct_opaque) function bit_or(_left, _right) bind(C, name="opaque_bit_or")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function bit_or

        type(thicc_struct_opaque) function bit_xor(_left, _right) bind(C, name="opaque_bit_xor")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function bit_xor

        type(thicc_struct_opaque) function index_of(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function index_of

        type(thicc_struct_opaque) function bit_not(_opaque) bind(C, name="opaque_bit_not")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function bit_not

        type(thicc_struct_opaque) function bit_complement(_opaque) bind(C, name="opaque_bit_complement")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function bit_complement

        type(thicc_struct_opaque) function indirection(_opaque) bind(C, name="opaque_indirection")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function indirection

        type(thicc_struct_opaque) function negative(_opaque) bind(C, name="opaque_negative")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function negative

        type(thicc_struct_opaque) function positive(_opaque) bind(C, name="opaque_positive")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function positive

        type(c_int) function compare(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function compare

        type(c_bool) function equal(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function equal

        type(c_bool) function greater_than(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function greater_than

        type(c_bool) function less_than(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function less_than

        type(c_bool) function not_equal(_left, _right) bind(C, name="opaque_index_of")
            type(thicc_struct_opaque), intent(in) :: _left
            type(thicc_struct_opaque), intent(in) :: _right
        end function not_equal

        type(c_size_t) function length(_opaque) bind(C, name="opaque_length")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function length

        type(c_bool) function is_character(_opaque) bind(C, name="opaque_is_character")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_character

        type(c_bool) function is_numeric(_opaque) bind(C, name="opaque_is_numeric")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_numeric

        type(c_bool) function is_integral(_opaque) bind(C, name="opaque_is_integral")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_integral

        type(c_bool) function is_unsigned(_opaque) bind(C, name="opaque_is_unsigned")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_unsigned

        type(c_bool) function is_signed(_opaque) bind(C, name="opaque_is_signed")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_signed

        type(c_bool) function is_floating_point(_opaque) bind(C, name="opaque_is_floating_point")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_floating_point

        type(c_bool) function is_string(_opaque) bind(C, name="opaque_is_string")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_string

        type(c_bool) function is_invokable(_opaque) bind(C, name="opaque_is_invokable")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_invokable

        type(c_bool) function is_array(_opaque) bind(C, name="opaque_is_array")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_array

        type(c_bool) function is_object(_opaque) bind(C, name="opaque_is_object")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_object

        type(c_bool) function is_indexable(_opaque) bind(C, name="opaque_is_indexable")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function is_indexable

        type(thicc_struct_opaque) function let_init() bind(C, name="opaque_let_init")
        end function let_init

        type(thicc_struct_opaque) function let_boolean(_value) bind(C, name="opaque_let_boolean")
            type(c_bool), intent(in) :: _value
        end function let_boolean

        type(thicc_struct_opaque) function let_character(_value) bind(C, name="opaque_let_character")
            type(c_char), intent(in) :: _value
        end function let_character

        type(thicc_struct_opaque) function let_natural(_value) bind(C, name="opaque_let_natural")
            type(THICC_FORTRAN_INTEGER), intent(in) :: _value
        end function let_natural

        type(thicc_struct_opaque) function let_integer(_value) bind(C, name="opaque_let_integer")
            type(THICC_FORTRAN_INTEGER), intent(in) :: _value
        end function let_integer

        type(thicc_struct_opaque) function let_real(_value) bind(C, name="opaque_let_real")
            type(c_long_double), intent(in) :: _value
        end function let_real

        type(thicc_struct_opaque) function let_complex(_value) bind(C, name="opaque_let_complex")
            type(c_long_double_complex), intent(in) :: _value
        end function let_complex

        type(thicc_struct_opaque) function move_string(_value) bind(C, name="opaque_move_string")
            type(thicc_struct_string), intent(in) :: _value
        end function move_string

        type(thicc_struct_opaque) function let_string(_value) bind(C, name="opaque_let_string")
            type(thicc_struct_string), intent(in) :: _value
        end function let_string

        type(thicc_struct_opaque) function let_function(_value) bind(C, name="opaque_let_function")
            type(c_funptr), intent(in) :: _value
        end function let_function

        type(thicc_struct_opaque) function move_array(_value) bind(C, name="opaque_move_array")
            type(thicc_struct_array), intent(in) :: _value
        end function move_array

        type(thicc_struct_opaque) function let_array(_value) bind(C, name="opaque_let_array")
            type(thicc_struct_array), intent(in) :: _value
        end function let_array

        type(thicc_struct_opaque) function move_object(_value) bind(C, name="opaque_move_object")
            type(c_ptr), intent(in) :: _value
        end function move_object

        type(thicc_struct_opaque) function let_object(_value) bind(C, name="opaque_let_object")
            type(c_ptr), intent(in) :: _value
        end function let_object

        type(thicc_struct_opaque) function let_copy(_opaque) bind(C, name="opaque_let_copy")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function let_copy

        type(thicc_struct_opaque) function let_move(_opaque) bind(C, name="opaque_let_move")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function let_move

        type(thicc_struct_opaque) function let_empty() bind(C, name="opaque_let_empty")
        end function let_empty

        type(c_bool) function let_is_empty(_opaque) bind(C, name="opaque_let_is_empty")
            type(thicc_struct_opaque), intent(in) :: _opaque
        end function let_is_empty

    end interface

end module thicc_boilerplate