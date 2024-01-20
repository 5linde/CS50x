from cs50 import get_int

height = -1

# Prompt user for height
while not (height > 0 and height <= 8):
    height = get_int("Height: ")

padding = height - 1
for i in range(height):
    # Prints left side of pyramid
    print(' ' * (padding) + '#' * (i + 1), end="")
    # Print space between halves
    print('  ', end="")
    # Prints right side of pyramid
    print('#' * (i + 1))
    padding -= 1

# Idea of char arithmetics based on the explanation
# about char and * operator from
# https://java2blog.com/print-character-n-times-python/
