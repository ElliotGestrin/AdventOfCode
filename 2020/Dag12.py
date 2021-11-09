import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag12.txt")
lines = [(line.strip()) for line in file.readlines()]

class ship:
    def northMove(self, distance):
        self.ypos += distance
    def eastMove(self, distance):
        self.xpos += distance
    def southMove(self, distance):
        self.ypos -= distance
    def westMove(self, distance):
        self.xpos -= distance

    def __init__(self):
        self.xpos = 0
        self.ypos = 0
        self.direction = 1
        self.directionsMoves = {0: self.northMove, 1:self.eastMove, 2:self.southMove, 3:self.westMove}
        self.waypointX = 10
        self.waypointXY = 1

    def move(self, instruction):
        direction = instruction[0]
        distance = int(instruction[1:])

        if direction == "N":
            direction = 0
        if direction == "E":
            direction = 1
        if direction == "S":
            direction = 2
        if direction == "W":
            direction = 3
        if direction == "F":
            direction = self.direction
        if isinstance(direction, (int, float)):
            self.directionsMoves[direction](distance)

        if direction == "L":
            direction = self.direction - distance/90
            if direction < 0:
                direction = direction + 4
            self.direction = direction
        if direction == "R":
            direction = self.direction + distance/90
            if direction > 3:
                direction = direction - 4
            self.direction = direction

    def manhattanDistance(self):
        return abs(self.xpos) + abs(self.ypos)

def main():
    boat = ship()
    for instruction in lines:
        boat.move(instruction)
        print(boat.xpos, ",",boat.ypos, "(", boat.direction, ")")
    print(boat.manhattanDistance())

main()
