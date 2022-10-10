import csv
import sys


# pseudocode
# Open Db file(csv), load it into people as [[],[],...]
# open sequences file, into string sequence
# Find longest match (compute STR count)
#   for each sub in seq
#   longestMatch = longest_match (sequence[],sub) -> sub is the first line in csv file without the name (header variable)

def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    dbFilename = sys.argv[1]
    people = []
    with open(dbFilename) as file:
        reader = csv.reader(file)
        for row in reader:
            people.append(row)

    # Columns names
    header = people[0][1:]
    # print(header)

    # People with no header
    people = people[1:]
    # print(people)

    # just the numbers(str vlues) with no names or str: as header
    lst2 = []
    for i in people:
        lst2.append(i[1:])
    # print(lst2)

    # TODO: Read DNA sequence file into a variable
    sequence = ""
    seqFilename = sys.argv[2]
    with open(seqFilename, "r") as file:
        content = file.read()
        sequence = content
    # print(sequence)

    # TODO: Find longest match of each STR in DNA sequence
    # print(f"people {people}")
    countLongest = []
    for i in header:

        num = longest_match(sequence, i)
        num = str(num)
        countLongest.append(num)

    #print (countLongest)

    # TODO: Check database for matching profiles
    theMatch = "no match"

    for index, item in enumerate(lst2):
        if item == countLongest:
            theMatch = people[index][0]
            #print(index, item)
    # print(people[18][0])

    print(theMatch)

    # for i in lst2:
    #     if i == countLongest:
    #         print(index(i))

    # for i in range(len(people)):
    #     for j in range(len(people) + 1):
    #         if j == 0:
    #             continue
    #         for k in range(len(countLongest)):
    #             #print(f"{k} {countLongest[k]}")
    #             count = 0
    #             if people [i][j] == countLongest[k]:
    #                 count +=1
    #             if count == len(countLongest):
    #                 theMatch = people [i][0]
    #                 return theMatch

    # print(f" [{i}][{j}] {people[i][j]}")
    #         if j == i:
    #             return people["name"]


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)
    #print(f"seq {sequence} sub {subsequence}")
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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
