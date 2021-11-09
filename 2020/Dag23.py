import elliot_standard_library as es

file = open("Filer\Dag23.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    cups = []
    currentCup = int(lines[0][0])
    for char in lines[0]:
        cups.append(int(char))
    print(f"Cups: {cups}")
    for move in range(0,100):
        print(f"\nMove {move}\nCups: {cups}\nCurrent: {currentCup}")
        pickedUp = []
        currentIndex = cups.index(currentCup)
        for pickUp in [1,1,1]:
            try:
                pickedUp.append(cups.pop(currentIndex + pickUp))
            except IndexError:
                pickedUp.append(cups.pop(0))
        print(f"Pickup: {pickedUp}")
        DestinationCup = False
        offset = 0
        while not DestinationCup:
            offset += 1
            if currentCup - offset <= 0:
                offset = - max(cups)
            if currentCup - offset in cups:
                DestinationCup = currentCup - offset
        DestinationIndex = cups.index(DestinationCup)
        print(f"Destination: {DestinationCup} ({DestinationIndex})")
        cups = cups[0:DestinationIndex + 1] + pickedUp + cups[DestinationIndex + 1:]
        currentIndex = cups.index(currentCup)
        try:
            currentCup = cups[currentIndex + 1]
        except IndexError:
            currentCup = cups[0]
    print(f"Cups {cups}")
    answer = ""
    startingPos = cups.index(1)
    for offest in range(1,len(cups)):
        try:
            answer += str(cups[currentIndex + pickUp])
        except IndexError:
            answer += str(cups[currentIndex + pickUp - len(cups)])
    print(f"Answer: {answer}")
main()
