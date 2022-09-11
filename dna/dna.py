import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    csv_file = sys.argv[1]
    text_file = sys.argv[2]

    large = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
    small = ["AGATC", "AATG", "TATC"]

    csv_list = []
    # Read database file into a variable
    with open(csv_file, "r") as f:
        csv_reader = csv.DictReader(f)
        for row in csv_reader:
            if csv_file == "databases/large.csv":
                for i in large:
                    row[i] = int(row[i])
                    csv_list.append(row)
            else:
                for i in small:
                    row[i] = int(row[i])
                    csv_list.append(row)

    # Read DNA sequence file into a variable
    with open(text_file, "r") as file:
        text_reader = file.read()

    subsequences = {}

    # Find longest match of each STR in DNA sequence
    if csv_file == "databases/large.csv":
        for i in large:
            subsequences[i] = longest_match(text_reader, i)

    else:
        for i in small:
            subsequences[i] = longest_match(text_reader, i)

    # Check database for matching profiles
    flag = True
    for person in csv_list:
        if csv_file == "databases/large.csv":
            for i in large:
                if person[i] == subsequences[i]:
                    flag = True
                    continue
                else:
                    flag = False
                    break
            if flag == False:
                continue
            else:
                flag == True
                print(person["name"])
                break
        else:
            for i in small:
                if person[i] == subsequences[i]:
                    flag = True
                    continue
                else:
                    flag = False
                    break
            if flag == False:
                continue
            else:
                flag == True
                print(person["name"])
                break

    if flag == False:
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
