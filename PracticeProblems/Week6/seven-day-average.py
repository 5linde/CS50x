import csv
import requests
import sys


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    maxRecentDaysData = 14
    new_cases = {}
    previous_cases = {}

    for row in reader:
        state = row['state']
        cases = int(row['cases'])

        # Add states to dicts if not already there
        if state not in new_cases:
            new_cases[state] = [cases]
            previous_cases[state] = [0]
        else:
            # Remove first element from list and add new value to the back
            if len(previous_cases[state]) == maxRecentDaysData:
                new_cases[state].pop(0)
                previous_cases[state].pop(0)

                # Calculate daily new cases
                newCases = cases - int(new_cases[state][len(new_cases[state]) - 1])

                new_cases[state].append(cases)
                previous_cases[state].append(newCases)
            else:
                newCases = cases - int(new_cases[state][len(new_cases[state]) - 1])
                new_cases[state].append(cases)
                previous_cases[state].append(newCases)

    return previous_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    percentChange = 0
    for state in new_cases:
        if state in states:
            print(new_cases[state])
            print(new_cases[state][0:7])
            print(new_cases[state][7:14])
            prevWeekAverage = sum(new_cases[state][0:7]) / 7
            thisWeekAverage = sum(new_cases[state][7:14]) / 7
            try:
                percentChange = 100 * ((thisWeekAverage - prevWeekAverage) / prevWeekAverage)
            except ZeroDivisionError:
                print("Error: Division with zero!")
                sys.exit(1)

            if percentChange > 0:
                change = "an increase"
            else:
                change = "a decrease"

            print(state + f" had a 7-day average of {round(thisWeekAverage)} and {change} of {round(abs(percentChange))}%.")

main()
