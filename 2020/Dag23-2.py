import elliot_standard_library as es

file = open("Filer\Dag23.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    cups = []
    currentCup = int(lines[0][0])
    for char in lines[0]:
        cups.append(int(char))
    print(f"Cups: {cups}")
    for i in range(len(cups), 1000000):
        cups.append(i)
    print(f"Final cup: {cups[-1]}")
    for move in range(0,10000000):
        if move % 100000 == 0:
            print(move)
        #print(f"\nMove {move}\nCups: {cups}\nCurrent: {currentCup}")
        pickedUp = []
        currentIndex = cups.index(currentCup)
        for pickUp in [1,1,1]:
            try:
                pickedUp.append(cups.pop(currentIndex + pickUp))
            except IndexError:
                pickedUp.append(cups.pop(0))
        #print(f"Pickup: {pickedUp}")
        DestinationCup = False
        offset = 0
        while not DestinationCup:
            offset += 1
            if currentCup - offset <= 0:
                offset = - max(cups)
            if currentCup - offset in cups:
                DestinationCup = currentCup - offset
        DestinationIndex = cups.index(DestinationCup)
        #print(f"Destination: {DestinationCup} ({DestinationIndex})")
        cups = cups[0:DestinationIndex + 1] + pickedUp + cups[DestinationIndex + 1:]
        if DestinationIndex < currentIndex:
            currentIndex += 3
        try:
            currentCup = cups[currentIndex + 1]
        except IndexError:
            currentCup = cups[0]
    oneIndex = cups.index(1)
    try:
        first = cups[oneIndex + 1]
    except IndexError:
        first = cups[0]
        oneIndex = -1
    second = cups[oneIndex + 2]
    print(f"Cups by one: 1, {first}, {second}")
    print(f"Mult: {first*second}")


main()
