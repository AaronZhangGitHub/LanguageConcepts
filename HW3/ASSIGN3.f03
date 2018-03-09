PROGRAM assignment3
  implicit none
  !variables
  character(len=:), allocatable :: inputFile
  character(len=:), allocatable :: outputFile
  integer arglen, a
  integer :: rowNumber,columnNumber
  integer, dimension(:,:), allocatable :: x
  integer, dimension(:), allocatable :: tmpRow
  integer, dimension(:), allocatable :: tmpColumn
  integer :: iostat, irow, krow, i, j, k, m, temp, icolumn, kcolumn

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
  allocate(tmpRow(columnNumber))

  do i = 1, rowNumber
    read(1,*) x(i,:)
  end do

  !sort rows
  do j = 1, rowNumber
    do k = 1, columnNumber
      print*,x(j,k)
    end do
    print*,"New Row"
  end do
  print*,x(1,:)
  print*,x(2,:)
  print*,x(3,:)
  print*,x(4,:)
  print*,x(5,:)
  print*,x(6,:)
  !Sort columns
  do irow = 1, rowNumber
    krow = minloc(x(irow:rowNumber,1),dim=1)+irow-1 !location of minimum value
    tmpRow(:) = x(irow,:)
    x( irow,:) = x(krow,:)
    x( krow,:) = tmpRow(:)
  end do
  print*,"======"
  print*,x(1,:)
  print*,x(2,:)
  print*,x(3,:)
  print*,x(4,:)
  print*,x(5,:)
  print*,x(6,:)
end
