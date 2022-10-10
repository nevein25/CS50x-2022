from cs50 import get_int


def main():

    sum = 0
    secPart = 0

    # Prompt user for credit card number 4012888888881881
    number = get_int("enter number: ")

    # Get the first two digits of the credit card number
    fisrtDigits = firstTwoDigits(number)
    # Calculate the length of credit card numbers
    theLength = length(number)
    # Cut the credit card number into two parts
    while number != 0:
        # First part
        n = number % 10
        # Sum the of the first part
        sum = sum + n
        number = number // 10
        # Second part
        r = number % 10
        r = r * 2
        secPart = secPart * 10 + r
        number = number // 10
        
    # Sum of the second part
    n2 = 0
    sum2 = 0
    while secPart != 0:
        n2 = secPart % 10
        sum2 = sum2 + n2
        secPart = secPart // 10

    # Sum of the two parts
    final = sum + sum2

    if final % 10 != 0:
        print("INVALID")

    else:
        if (theLength == 15) and ((fisrtDigits == 34) or (fisrtDigits == 37)):
            print("AMEX")
        elif ((theLength == 16) and (fisrtDigits >= 51 and fisrtDigits <= 55)):
            print("MASTERCARD")
        elif (((theLength == 13) or (theLength == 16)) and ((fisrtDigits >= 40) and (fisrtDigits <= 49))):
            print("VISA")
        else:
            print("INVALID")


def firstTwoDigits(numb):
    while numb >= 100:
        numb = numb // 10
    return numb


def length(num):
    counter = 0
    while num != 0:
        num = num // 10
        counter = counter + 1
    return counter


main()