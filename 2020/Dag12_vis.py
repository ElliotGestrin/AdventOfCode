import single_line_reader as slr
import elliot_standard_library as es
import time
from graphics import *

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
            if self.drawMode and i%2 == 0:
                self.updateWindow()
                time.sleep(0.015)

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
        self.positions = [((self.xpos,self.ypos),\
                          (self.waypointX,self.waypointY))]
        self.drawMode = False

    def move(self, instruction):
        direction = instruction[0]
        distance = int(instruction[1:])
        self.directionsMoves[direction](distance)
        boatPos = (self.xpos, self.ypos)
        wayPos = (self.waypointX, self.waypointY)
        self.positions.append((boatPos, wayPos))
        if self.drawMode:
            self.updateWindow()

    def manhattanDistance(self):
        return abs(self.xpos) + abs(self.ypos)

    def __str__(self):
        return str(self.xpos) + ", " + str(self.ypos) + \
               " (" + str(self.waypointX) + ", " + str(self.waypointY) + ")"

    def updatePoints(self):
        boatWidth = 5
        xpos = self.xpos * self.boatScaling
        ypos = self.ypos * self.boatScaling
        TL = Point(xpos - boatWidth, ypos -boatWidth)
        TR = Point(xpos +boatWidth, ypos -boatWidth)
        BL = Point(xpos -boatWidth, ypos +boatWidth)
        BR = Point(xpos +boatWidth, ypos +boatWidth)
        self.points = [TL, TR, BL, BR]
        triOff = 10
        TM = Point(xpos, ypos -triOff)
        RM = Point(xpos +triOff, ypos)
        BM = Point(xpos, ypos +triOff)
        LM = Point(xpos -triOff, ypos)
        self.tripoints = [TM, RM, BM, LM]
        wayPointX = self.xpos  * self.boatScaling  + self.waypointX * self.wayScaling
        wayPointY = self.ypos  * self.boatScaling + self.waypointY * self.wayScaling
        self.wayPoint = Point(wayPointX, wayPointY)

    def decideTriPoints(self):
        if self.waypointY <= 0:
            if abs(self.waypointY) >= abs(self.waypointX):
                return[self.points[0], self.points[1], self.tripoints[0]]
            elif self.waypointX >= 0:
                return[self.points[1], self.points[3], self.tripoints[1]]
            else:
                return[self.points[0], self.points[2], self.tripoints[3]]
        else:
            if abs(self.waypointY) >= abs(self.waypointX):
                return[self.points[2], self.points[3], self.tripoints[2]]
            elif self.waypointX >= 0:
                return[self.points[1], self.points[3], self.tripoints[1]]
            else:
                return[self.points[0], self.points[2], self.tripoints[3]]

    def updateWindow(self):
        for item in self.window.items[:]:
            item.undraw()
        self.updatePoints()
        self.boat = Rectangle(self.points[0], self.points[3])
        tripoints = self.decideTriPoints()
        self.tri = Polygon(tripoints)
        self.circle = Circle(self.wayPoint, 2)
        self.boat.setFill("Red")
        self.tri.setFill("Red")
        self.circle.setFill("Red")
        self.boat.draw(self.window)
        self.tri.draw(self.window)
        self.circle.draw(self.window)

    def setupCanvas(self, xsize, ysize, boatScaling, wayScaling):
        self.boatScaling = boatScaling
        self.wayScaling = wayScaling
        self.window = GraphWin("Ocean", xsize*boatScaling, ysize*boatScaling)
        self.window.setBackground("Blue")
        self.updatePoints()
        self.boat = Rectangle(self.points[0], self.points[3])
        tripoints = self.decideTriPoints()
        self.tri = Polygon(tripoints)
        self.circle = Circle(self.wayPoint, 2)
        self.boat.setFill("Red")
        self.tri.setFill("Red")
        self.circle.setFill("Red")
        self.boat.draw(self.window)
        self.tri.draw(self.window)
        self.circle.draw(self.window)
        self.drawMode = True

def main():
    boat = ship()
    for instruction in lines:
        boat.move(instruction)

    boatPositions = [boatPos for boatPos, wayPos in boat.positions]
    wayPositions = [wayPos for boatPos, wayPos in boat.positions]
    boatX = [x for x,y in boatPositions]
    boatY = [y for x,y in boatPositions]
    xAdjust = -min(boatX) + 3000
    yAdjust = -min(boatY) + 4000
    es.add_to_list(boatX, xAdjust)
    es.add_to_list(boatY, yAdjust)
    xBoundary = max(boatX) + 6000
    yBoundary = max(boatY) + 8000

    boat = ship()
    boat.xpos += xAdjust
    boat.ypos += yAdjust
    boat.setupCanvas(xBoundary, yBoundary, 0.01, 1)
    for instruction in lines:
        print(instruction)
        boat.move(instruction)
        time.sleep(0.2)

main()
