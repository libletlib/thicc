program thicc_fortran_demo
    use, intrinsic :: iso_c_binding
    use thicc_fortran
    implicit none

    type(var) :: x
    x = var("kek")
    call x%print ! 1

end program thicc_fortran_demo