import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Wrong Usage!!!")
        print("Execute program: python dna.py some_database.csv dna_sequence.txt")

    # TODO: Read database file into a variable
    peopleDNA = []
    names = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        STRList = reader.fieldnames
        STRList = STRList[1:len(STRList)]
        for row in reader:
            names.append(row['name'])
            peopleDNA.append(row)
        file.close()

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dnaSequence = file.readline()
        file.close()

    # TODO: Find longest match of each STR in DNA sequence
    longestMatchSTR = {}
    for STR in STRList:
        longestMatchSTR[STR] = longest_match(dnaSequence, STR)

    # TODO: Check database for matching profiles
    idx = 0
    for name in names:
        matches = 0
        for STR in STRList:
            temp = int(peopleDNA[idx][STR])
            temp2 = longestMatchSTR[STR]
            if (int(peopleDNA[idx][STR]) == longestMatchSTR[STR]):
                matches += 1
                if (matches == len(STRList)):
                    print(name)
                    return
            else:
                idx += 1
                break

    print("No match")

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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
