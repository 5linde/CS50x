from cs50 import get_string

input = get_string("Text: ").lower()

letters, words, sentences = 0, 0, 0

for i in input:
    if i.isalpha():
        letters += 1
    if i == " ":
        words += 1
    elif i in [".", "!", "?"]:
        sentences += 1

# Add one more words since I only count spaces
words += 1

# Calculate Coleman-Liau index
L = letters / words * 100
S = sentences / words * 100
CLindex = 0.0588 * L - 0.296 * S - 15.8

# Round to nearest integer
grade = int(CLindex + 0.5)

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")
