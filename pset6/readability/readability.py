from cs50 import get_string
import string
import re

letters = 0
sentences = 0
text = get_string("Enter text: ")
words = text.split()
for i in range(len(words)):
    for j in range(len(words[i])):
        if words[i][j].isalpha():
            letters += 1
        if words[i][j] in ['.', '?', '!']:
            sentences += 1
words = len(words)
L = (letters / words) * 100
S = (sentences / words) * 100
index = round(0.0588 * L - 0.296 * S - 15.8)
if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")