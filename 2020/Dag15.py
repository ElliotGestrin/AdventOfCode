import elliot_standard_library as es

file = open("Filer\Dag15.txt")
lines = [(line.strip()) for line in file.readlines()]

def nextNumber(new_number, old_numbers, current_round):
    if not new_number in old_numbers:
        return 0
    else:
        return current_round - old_numbers[new_number]

def main():
    startNum = [int(num) for num in lines[0].split(",")]
    old_numbers = {}
    for round in range(len(startNum) - 1):
        old_numbers[startNum[round]] = round + 1
    new_number = startNum[-1]
    for round in range(len(startNum),30000000):
        #print("Round ", round, ": ", new_number)
        next_number = nextNumber(new_number, old_numbers, round)
        old_numbers[new_number] = round
        new_number = next_number
    print(new_number)


main()
