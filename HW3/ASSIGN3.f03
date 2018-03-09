PROGRAM assignment3
  !variables
  character(len=:), allocatable :: inputFile
  character(len=:), allocatable :: outputFile
  integer arglen, a
  integer :: rowNumber,columnNumber
  real, dimension(:,:), allocatable :: x
  integer :: iostat

  !Get input and output files
  call GET_COMMAND_ARGUMENT(1,length=arglen)
  allocate(character(arglen) :: inputFile)
  call GET_COMMAND_ARGUMENT(1,value=inputFile)
  call GET_COMMAND_ARGUMENT(2,length=arglen)
  allocate(character(arglen) :: outputFile)
  call GET_COMMAND_ARGUMENT(2,value=outputFile)
  print*, inputFile," " ,outputFile

  !Read from input file for
  open(unit=1, file=inputFile, action='read')
  read(1, *) rowNumber, columnNumber
  print*, "Rows: ",rowNumber, "Columns: ",columnNumber

  allocate(x(rowNumber,columnNumber))
  do I=1,n,1
   read(1,*,IOSTAT=iostat) x(I,:)
   print*,(int(x(I,:)))
   if(iostat>0)then
    stop
   end if
  enddo

  !array for storing the matrix
  !integer :: A()
end
