import elliot_standard_library as es

file = open("Filer\Dag23.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    cups = {}
    for index in range(0, len(lines[0])-1):
        cups[int(lines[0][index])] = int(lines[0][index + 1])
    highest =  max(cups.values())
    print(cups)
    nextInLine = int(lines[0][len(lines[0])-1])
    while highest < 1000000:
        cups[nextInLine] = highest + 1
        highest += 1
        nextInLine = highest
    cups[highest] = int(lines[0][0])
    currentCup = int(lines[0][0])
    for round in range(0, 10000000):
        firstInMove = cups[currentCup]
        middleInMove = cups[firstInMove]
        lastInMove = cups[middleInMove]
        toMove = [firstInMove, middleInMove, lastInMove]
        behindMove = cups[lastInMove]
        destination = currentCup - 1
        while destination in toMove or destination <= 0:
            destination -= 1
            if destination <= 0:
                destination = len(cups)
        afterDestination = cups[destination]
        cups[currentCup] = behindMove
        cups[destination] = firstInMove
        cups[lastInMove] = afterDestination
        currentCup = cups[currentCup]
    first = cups[1]
    second = cups[first]
    print(f"First: {first}\nSecond: {second}\nMult: {first*second}")

main()
