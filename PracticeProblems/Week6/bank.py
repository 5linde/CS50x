# Make input case-insensitive and remove leading whitespace
# as per https://docs.python.org/3/library/stdtypes.html?highlight=lstrip#str.lstrip
greeting = input("Greeting: ").lower().lstrip()

# Check if greeting starts with "hello"
if greeting[0:5] == "hello":
    print("$0", end="")
elif "h" in greeting[0] and greeting[0:5] != "hello":
    print("$20", end="")
else:
    print("$100", end="")
