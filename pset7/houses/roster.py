import sys
from cs50 import SQL
if len(sys.argv) != 2:
    print("Wrong # of arguments")
    sys.exit(1)
house = sys.argv[1]
db = SQL("sqlite:///students.db")
students = list(db.execute("SELECT first, middle, last, birth FROM students WHERE house LIKE ? ORDER BY last asc", house))
i = 0
while i < len(students):
    first = students[i]['first']
    middle = students[i]['middle']
    last = students[i]['last']
    birth = students[i]['birth']
    if middle != None:
        print(f"{first} {middle} {last}, born {birth}")
    else:
        print(f"{first} {last}, born {birth}")
    i += 1