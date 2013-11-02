
program main
    use omp_lib
    implicit none

    integer :: n, i
    integer :: threadID

    n = 10

    !$omp parallel do shared(n) private(i)
    do i=1, n
        threadID = omp_get_thread_num()
        write (*,*) "thread:", threadID, "i:", i
    end do
    !$omp end parallel do
end program
