from cs50 import get_string
import re

# Get input from user
n = get_string("Number: ")
sum = 0

# Check if user input contains only numbers and is of appropriate length
if re.fullmatch(r"\d+", n) and (len(n) >= 13 and len(n) <= 16):
    # Loop through user input in reverse order
    for i in range(len(n)):
        if i == 0:
            # Get last digit of string
            tempDigit = int(n[len(n) - 1])
        # Get every second digit starting from the second-to-last digit
        elif i % 2 == 1:
            tempDigit = int(n[len(n) - (i + 1)]) * 2

            # If tempDigit > 9 add products digits,
            # (same as subtracting 9 from resulting product ex. 12 => 1+2=3 / 12-9=3)
            if (tempDigit > 9):
                tempDigit -= 9
        # Get every second digit starting from the last digit
        else:
            tempDigit = int(n[len(n) - (i + 1)])

        sum += tempDigit
else:
    print("Input must be a numeric value between 13-16 numbers!")

if sum % 10 != 0:
    print("INVALID")
elif len(n) == 15 and (int(n[0]) == 3 and int(n[1]) in [4, 7]):
    print("AMEX")
elif len(n) == 16 and (int(n[0]) == 5 and int(n[1]) in [1, 2, 3, 4, 5]):
    print("MASTERCARD")
elif len(n) in [13, 16] and int(n[0]) == 4:
    print("VISA")
else:
    print("INVALID")
