import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Usage : python dna.py databases/<file>.csv sequences/<file>.txt")
        return
        
    # TODO: Read database file into a variable
    rows = []
    with open(argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    # print(rows) 
    # list of dictionaries
    # [{'name': 'Alice', 'AGATC': '2', 'AATG': '8', 'TATC': '3'}, {'name': 'Bob', 'AGATC': '4', 'AATG': '1', 'TATC': '5'}, {'name': 'Charlie', 'AGATC': '3', 'AATG': '2', 'TATC': '5'}]
    
    # TODO: Read DNA sequence file into a variable
    with open(argv[2],'r') as dnafile:
        dna = dnafile.read()
    #print(dna) GGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAA

    # TODO: Find longest match of each STR in DNA sequence
    dictstrs = {}
    dictstrs["name"] = ""
    for key in rows[0]:
        if key == "name":
            continue
        dictstrs[key] = str(longest_match(dna,key))

    #print(dictstrs)

    # TODO: Check database for matching profiles
    for dict in rows:
        dictstrs["name"] = dict["name"]
        #print(dictstrs)
        if dictstrs == dict:
            print(dict["name"])
            return
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

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
