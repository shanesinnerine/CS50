from cs50 import get_int

num = get_int("Number: ")
Sum = 0
i = 1
for k in range(2):
    while i < len(str(num)):
        temp = num
        for j in range(i):
            temp = int(temp / 10)
        if k == 0:
            double = 2 * (temp % 10)
            Sum += (double % 10) + int(double / 10)
        else:
            Sum += temp % 10
        i += 2
    i = 0
if Sum % 10 != 0:
    print("INVALID")
else:
    for i in range((len(str(num))) - 2):
        num = int(num / 10)
    if num == 34 or num == 37:
        print("AMEX")
    elif num > 50 and num < 56:
        print("MASTERCARD")
    elif int(num / 10) == 4:
        print("VISA")