import sys
import csv
from cs50 import SQL

# Sanitize input
if len(sys.argv) != 2:
    print("Wrong # of arguments")
    sys.exit(1)

# Create db
open("students.db", "w").close()

db = SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")
with open(sys.argv[1], "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        temp = row['name'].split()
        if len(temp) == 3:
            middle = temp[1]
        else:
            middle = None
        db.execute("INSERT INTO students (first, middle, last, house, birth) Values(?,?,?,?,?)", temp[0], middle, temp[-1], row['house'], row['birth'])