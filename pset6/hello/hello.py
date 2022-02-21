import sys

name = input("What is your name?\n")
for c in name:
    if c.isdigit():
        print("Letters Only")
        exit(1)
print(f"hello, {name}")

