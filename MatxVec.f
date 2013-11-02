module mxv
    implicit none

    contains

    subroutine mxvSeq(m, n, a, b, c)
        implicit none
        integer, intent(in)     :: m, n
        real,    intent(in)     :: b(1:m,1:n), c(1:n)
        real,    intent(inout)  :: a(1:m)

        integer :: i, j

        do i=1, m
            a(i) = 0.0
            do j=1, n
                a(i) = a(i) + b(i,j) * c(j)
            end do
        end do
    end subroutine

    subroutine mxvOpenMP(m, n, a, b, c)
        implicit none
        integer, intent(in)     :: m, n
        real,    intent(in)     :: b(1:m,1:n), c(1:n)
        real,    intent(inout)  :: a(1:m)

        integer :: i, j

        !$omp parallel do default(none) shared(m,n,a,b,c) private(i,j)
        do i=1, m
            a(i) = 0.0
            do j=1, n
                a(i) = a(i) + b(i,j) * c(j)
            end do
        end do
        !$omp end parallel do
    end subroutine
end module


program main
    use mxv
    implicit none

    real, allocatable :: a(:), b(:,:), c(:)
    integer :: m, n, i, memstat

    write (*,*) "Please give me m and n:"
    read (*,*) m, n

    allocate(a(1:m), stat=memstat)
    if (memstat .ne. 0) then
        stop "Error in memory allocation for 'a'"
    end if

    allocate(b(1:m, 1:n), stat=memstat)
    if (memstat .ne. 0) then
        stop "Error in memory allocation for 'b'"
    end if

    allocate(c(1:n), stat=memstat)
    if (memstat .ne. 0) then
        stop "Error in memory allocation for 'c'"
    end if

    ! initialize matrix B and vector C
    c(1:n) = 1.0
    do i=1, m
        b(i, 1:n) = i
    end do

    call mxvSeq(m, n, a, b, c)

    if (allocated(a)) deallocate(a, stat=memstat)
    if (allocated(b)) deallocate(b, stat=memstat)
    if (allocated(c)) deallocate(c, stat=memstat)
end program
