#Created by Aaron Zhang

def fibbonaci(sequenceNum)
  if sequenceNum == 0
    return 0
  end
  @val0 = 0
  @val1 = 1
  while sequenceNum>1 do
    @temp = @val1
    @val1 = @val0+@val1
    @val0 = @temp
    sequenceNum-=1
  end
  return @val1
end

def receiveUserInputIntegersOnly
  #Take in input
  @input = gets
  #Strip everything but the numbers
  @numbersFromInput = @input.gsub(/[^\d]/, '')
  #Test to see if there is an integer
  if @numbersFromInput.empty?
    return -1
  end
  #Convert to integer
  @numericalFibNumber = @numbersFromInput.to_i
  return @numericalFibNumber
end

def fib(fibNum)
  #Print the result of the fibonacci number for that sequence
  puts fibbonaci(fibNum)
end

#Main method is not used
def main
  #Get the user inputted fibonaci sequence number
  fibSequenceNumber = receiveUserInputIntegersOnly
  #Validate the input
  if(fibSequenceNumber==-1)
    raise 'Illegal argument'
  else
    #Print the result of the fibonacci number for that sequence
    puts fibbonaci fibSequenceNumber
  end
end
