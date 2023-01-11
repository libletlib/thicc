function fortran_function(self, args) bind(C)
    use thicc_fortran
    type(thicc_struct_var), value, intent(in) :: self, args
    type(thicc_struct_var) :: fortran_function
end function

program thicc_fortran_demo
    use, intrinsic :: iso_c_binding
    use thicc_fortran
    implicit none

    type(var) :: x
    x = var("kek")

end program thicc_fortran_demo