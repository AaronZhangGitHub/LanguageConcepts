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
  integer :: iostat, irow, krow, i, j, k, m, temp, icolumn, kcolumn, lowestVal, lowestIndex
  lowestVal = 10000
  !Get input and output files
  call GET_COMMAND_ARGUMENT(1,length=arglen)
  allocate(character(arglen) :: inputFile)
  call GET_COMMAND_ARGUMENT(1,value=inputFile)
  call GET_COMMAND_ARGUMENT(2,length=arglen)
  allocate(character(arglen) :: outputFile)
  call GET_COMMAND_ARGUMENT(2,value=outputFile)

  !Read from input file for
  open(unit=1, file=inputFile, action='read')
  read(1, *) rowNumber, columnNumber

  allocate(x(rowNumber,columnNumber))
  allocate(tmpRow(columnNumber))

  do i = 1, rowNumber
    read(1,*) x(i,:)
  end do

  !sort rows
  do j = 1, rowNumber
    do k = 1, columnNumber
    lowestVal = x(j,k)
    lowestIndex = k
      do m = k, columnNumber
        if(x(j,m)<lowestVal) then
          lowestVal = x(j,m)
          lowestIndex = m
        end if
      end do
      !swap
      temp = x(j,k)
      x(j,k) = lowestVal
      x(j,lowestIndex) = temp
    end do
  end do
  !Sort columns
  do irow = 1, rowNumber
    krow = minloc(x(irow:rowNumber,1),dim=1)+irow-1 !location of minimum value
    tmpRow(:) = x(irow,:)
    x( irow,:) = x(krow,:)
    x( krow,:) = tmpRow(:)
  end do
  !open to write
  open(unit=2, file=outputFile, action='write', status="replace")
  do i =1, rowNumber
    write(2,*) x(i,:)
  end do
end
