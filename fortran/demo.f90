subroutine playground()
    use, intrinsic :: iso_c_binding
    use thicc_fortran
    implicit none

    type(let) :: x, y, z
    character(:, c_char), allocatable :: s

    x = 6
    y = "3"
    z = x .mod. y
    s = z%as_string()
    print *, s
    deallocate(s)

end subroutine playground


program thicc_fortran_demo
    implicit none

    call playground()

end program thicc_fortran_demo