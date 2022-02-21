import sys
import csv

# Check for correct input
if len(sys.argv) != 3:
    print("Wrong input")
    sys.exit(1)

# Initialize database
database = []

# Open dna database(csv)
with open(sys.argv[1], 'r') as file:
    data = csv.DictReader(file)

    # Read csv file into database as dictionary
    for row in data:
        database.append(row)

# Store keys for database in array
keys = list(database[0].keys())

# Open dna sequence(txt)
with open(sys.argv[2], 'r') as text:

    # Read txt file into string
    sequence = text.read()

# Initialize variables
max = [0] * (len(keys) - 1)
counter = 0
i = 0

# Iterate through each dna type
while i < len(max):

    # Skip first column(name)
    i += 1

    # Reset counter and gap
    counter = 0
    gap_length = len(keys[i])

    # Create gap to search for dna type
    gap_start = 0
    gap_end = gap_length

    # Iterate through dna sequence
    while gap_end < len(sequence):

        # Check if gap = dna type
        if sequence[gap_start: gap_end] == keys[i]:

            # If true, increment counter and check for repetition
            counter += 1
            gap_start += gap_length
            gap_end += gap_length
        else:

            # Check if current counter is the biggest one so far
            if counter > max[i - 1]:
                # Set as max if true
                max[i - 1] = counter

            # Reset counter and check next gap
            counter = 0
            gap_start += 1
            gap_end += 1

for i in range(len(database)):
    j = 0

    # Check if dna repetition matches person in row
    while j < (len(keys) - 1):
        j += 1
        if int(database[i][keys[j]]) == max[j - 1]:
            counter += 1

            # If all equal in row, print name and exit
            if counter == len(max):
                print(f"{database[i][keys[0]]}")
                sys.exit(0)
            continue

        # dna doesn't match person, move to next row
        counter = 0
        break

# No matching dna sequence in database
print("No Match")
sys.exit(1)