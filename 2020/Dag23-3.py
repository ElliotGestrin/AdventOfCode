import elliot_standard_library as es

file = open("Filer\Dag23.txt")
lines = [(line.strip()) for line in file.readlines()]

class Cups:
    def __init__(self, cup_line):
        self.cups = {}
        for position in range(0, len(cup_line)):
            self.cups[position + 1] = int(cup_line[position])
        self.currentCup = self.cups[1]
        self.currentPos = 1
        self.smallestUntracked = len(self.cups) + 1
        self.untrackedIndex = len(self.cups) + 1
        self.max = 1000000

    def play(self, rounds):
        for round in range(0, rounds):
            #print(f"\nBefore round {round + 1}\nCurrent: {self.currentCup} ({self.currentPos})")
            self.printCups()
            pickedUp = self.pickUp()
            #print(f"Pickup: {pickedUp}")
            self.printCups()
            destination = self.chooseDestination()
            #print(f"Destination: {self.cupValue(destination)} ({destination})")
            self.place(destination, pickedUp)
            self.printCups()
            self.currentPos += 1
            if self.currentPos > self.max:
                self.currentPos -= self.max
            self.currentCup = self.cupValue(self.currentPos)
            #print(f"NewCurrent: {self.currentCup} ({self.currentPos})")

    def printCups(self, interrupt = False):
        if not interrupt:
            pass
            return True
        toPrint = ""
        positions = [pos for pos in self.cups.keys()]
        for pos in sorted(positions):
            toPrint += f"({pos}): {self.cups[pos]}, "
        print(f"Cups ({self.max}, ({self.untrackedIndex}: {self.smallestUntracked})) : " + toPrint)

    def cupValue(self, index):
        if index in self.cups.keys():
            return self.cups[index]
        elif index <= self.max:
            value = self.smallestUntracked + index - self.untrackedIndex
            self.printCups()
            #print(f"The value at {index} was requested. {value} calculated ({index}, {self.untrackedIndex})")
            return value
        else:
            return self.cupValue(self, index - self.max)

    def removeCups(self, toRemove):
        #self.printCups()
        #print(f"   Removing cups from {toRemove}")
        for index in toRemove:
            if index in self.cups.keys():
                del self.cups[index]
                self.max -= 1
                self.adjustDown(index)
            elif index <= self.max:
                self.max -= 1
                pass
            else:
                self.removeCups([index - self.max])


    def adjustUp(self, fromIndex):
        toLoop = []
        for loopy in [999998,999999,1000000]:
            if loopy in self.cups:
                toLoop.append(self.cups[loopy])
                del self.cups[loopy]
        newCups = {}#self.cups.copy()
        for pos in range(1, len(toLoop) + 1):
            #print(f"    Looped {toLoop[pos-1]} to {pos}")
            newCups[pos] = toLoop[pos-1]
        sortedPositions = sorted([pos for pos in self.cups.keys()])
        for index in sortedPositions:
            if toLoop:
                if index < fromIndex - 4 or index >= fromIndex:
                    newCups[index + 3] = self.cups[index]
                    #print(f"    Moved {self.cups[index]}    {index} -> {index+3}")
                    #if not index - 3 in self.cups and not index == 3:
                #        del newCups[index]
                else:
                    newCups[index] = self.cups[index]
            else:
                if index >= fromIndex:
                    newCups[index + 3] = self.cups[index]
                    #print(f"    Moved {self.cups[index]}    {index} -> {index+3}")
                    #if not index - 3 in self.cups and not index == 3:
                    #    del newCups[index]
                else:
                    newCups[index] = self.cups[index]
        self.cups = newCups


    def adjustDown(self, fromIndex):
        newCups = self.cups.copy()
        #print(f"    Adjusting down from {fromIndex}")
        sortedPositions = sorted([pos for pos in self.cups.keys()])
        for index in sortedPositions:
            if index > fromIndex:
                newCups[index - 1] = self.cups[index]
                #print(f"    {self.cups[index]} {index} -> {index - 1}")
                del newCups[index]
        self.untrackedIndex -= 1
        self.cups = newCups

    def pickUp(self):
        pickedUp = []
        adjustmentFromCurrent = 0
        adjustmentFromZero = 0
        for offset in [1,2,3]:
            pickedUp.append(self.cupValue(self.currentPos + offset))
            while self.currentPos + offset >= self.untrackedIndex:
                self.untrackedIndex += 1
                self.smallestUntracked += 1
        self.removeCups([self.currentPos + 1, self.currentPos + 1, self.currentPos + 1])
        return pickedUp

    def chooseDestination(self):
        destinationVal = self.currentCup - 1
        if destinationVal < 1:
            destinationVal = self.max
        #print(f"I think we should go with dest: {destinationVal}")
        if destinationVal in self.cups.values():
            destinationPos = [pos for pos, value in self.cups.items() if value == destinationVal][0]
        else:
            strangeCupsAbove = len([label for pos, label in self.cups.items() if label < destinationVal and pos > destinationVal])
            destinationPos = destinationVal - strangeCupsAbove
        return destinationPos

    def place(self, pos, toPlace):
        offset = 0
        self.adjustUp(pos + 1)
        for cup in toPlace:
            pos += 1
            #print(f"    Placing {cup}")
            #self.printCups()
            if pos + offset*1000000 in self.cups:
                #print(f"    Placing {cup} at {pos + offset}")
                self.cups[pos + offset*1000000] = cup
            elif pos + offset <= 1000000:
                #print(f"    {pos + offset} not in cups")
                #print(f"    Placing {cup} at {pos + offset}")
                self.cups[pos + offset*1000000] = cup
            else:
                #print(f"    {pos + offset} too big")
                #print(f"    Placing {cup} at {pos + offset}")
                offset -= 1
                if pos + offset*1000000 in self.cups:
                    self.cups[pos + offset * 1000000] = cup
                elif pos + offset*1000000 <= 1000000:
                    self.cups[pos + offset * 1000000] = cup
            self.max += 1
        while self.untrackedIndex in self.cups:
            #print(f"Increased untracked")
            self.untrackedIndex += 1

    def score(self):
        OnePos = [pos for pos, val in self.cups.items() if val == 1][0]
        First = self.cupValue(OnePos + 1)
        Second =  self.cupValue(OnePos + 2)
        Score = First * Second
        return (Score, First, Second)

def main():
    cups = Cups(lines[0])
    cups.play(10000)
    cups.printCups(True)
    print(cups.score())

main()
