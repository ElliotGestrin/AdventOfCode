import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag12.txt")
lines = [(line.strip()) for line in file.readlines()]

class ship:
    def northMove(self, distance):
        self.waypointY += distance
    def eastMove(self, distance):
        self.waypointX += distance
    def southMove(self, distance):
        self.waypointY -= distance
    def westMove(self, distance):
        self.waypointX -= distance
    def rotateR(self, distance):
        direction = int(distance/90)
        for rot in range(0, direction):
            temp = self.waypointY
            self.waypointY = -self.waypointX
            self.waypointX = temp
    def rotateL(self, distance):
        direction = int(distance/90)
        for rot in range(0, direction):
            temp = self.waypointY
            self.waypointY = self.waypointX
            self.waypointX = -temp
    def forwardMove(self, distance):
        for i in range(0, distance):
            self.xpos += self.waypointX
            self.ypos += self.waypointY

    def __init__(self):
        self.xpos = 0
        self.ypos = 0
        self.directions = {0:"N", 1:"E", 2:"S", 3:"W"}
        self.directionsMoves = {"N": self.northMove, "E":self.eastMove, \
                                "S":self.southMove, "W":self.westMove, \
                                "R":self.rotateR, "L":self.rotateL, \
                                "F":self.forwardMove}
        self.waypointX = 10
        self.waypointY = 1

    def move(self, instruction):
        direction = instruction[0]
        distance = int(instruction[1:])
        self.directionsMoves[direction](distance)

    def manhattanDistance(self):
        return abs(self.xpos) + abs(self.ypos)

    def __str__(self):
        return str(self.xpos) + ", " + str(self.ypos) + \
               " (" + str(self.waypointX) + ", " + str(self.waypointY) + ")"

def main():
    boat = ship()
    for instruction in lines:
        boat.move(instruction)
        print(boat)
    print(boat.manhattanDistance())

main()
