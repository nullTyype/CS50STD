import csv
import sys


def main():

    # TODO: Check for command-line usage
    # ensure proper usage;
    if len(sys.argv) != 3:
        sys.exit("Usage: python ./dna.py DATABASE SEQUENCE")

    # TODO: Read database file into a variable
    # open and stores each csv row at the data array of hashes;
    data = []
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            data.append(row)

    # gets column names;
    with open(sys.argv[1], 'r') as file:
        reader = csv.reader(file)
        row = next(reader)

        columnNames = row[1:]

    # TODO: Read DNA sequence file into a variable
    # store sequence data;
    sequence = ""
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    matches = {}
    for i in columnNames:
        matches[i] = longest_match(sequence, i)

    # TODO: Check database for matching profiles
    # compare matches values with each data STR value,
    # if match, we found the people;
    match = ""
    for person in data:
        if checkData(person, matches, columnNames):
            match = person['name']
            break
        else:
            continue

    if match == "":
        print("No match")
    else:
        print(f"{match}")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run

def checkData(person, matches, columnNames):
    length = len(person)
    count = 0
    for i in range(0, length-1):
        if int(person[columnNames[i]]) == int(matches[columnNames[i]]):
            count += 1
        else:
            break

    if count == length-1:
        return True
    else:
        return False

main()

