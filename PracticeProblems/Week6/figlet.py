from pyfiglet import Figlet
import random
import sys

figlet = Figlet()
fontList = figlet.getFonts()

if len(sys.argv) == 1:
    randomFontIndex = random.randint(0, len(fontList) - 1)
    randomFont = fontList[randomFontIndex]
    figlet.setFont(font=randomFont)

    s = input("Input: ")

    print("Output: ")
    print(figlet.renderText(s))

elif len(sys.argv) == 3:
    if sys.argv[1] not in ["-f", "--font"] or sys.argv[2] not in fontList:
        print("Error: Wrong Command Line Arguments (CLA) Definition!!!")
        print("1. (No CLA) python figlet.py")
        print("2. (With CLA) python figlet.py -f/--font fontname")
        sys.exit(1)

    figlet.setFont(font=sys.argv[2])
    s = input("Input: ")

    print("Output: ")
    print(figlet.renderText(s))
else:
    print("Error: Wrong Command Line Arguments (CLA) Definition!!!")
    print("1. (No CLA) python figlet.py")
    print("2. (With CLA) python figlet.py -f/--font fontname")
    sys.exit(1)
