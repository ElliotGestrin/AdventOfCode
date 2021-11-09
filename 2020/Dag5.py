file = open("Filer\Dag5.txt")
import math

def findRow(instruction, lowerY, upperY, lowerX, upperX):
    if instruction[0] == "F":
        upperY = math.floor((lowerY + upperY)/2)
    if instruction[0] == "B":
        lowerY = math.ceil((lowerY + upperY)/2)
    if instruction[0] == "L":
        upperX = math.floor((lowerX + upperX)/2)
    if instruction[0] == "R":
        lowerX = math.ceil((lowerX + upperX)/2)
    if len(instruction) == 1:
        return lowerY, lowerX
    return findRow(instruction[1:], lowerY, upperY, lowerX, upperX)

def main():
    seat_instructions = file.readlines()
    seats = [findRow(seat_instruction, 0, 127, 0, 7) for seat_instruction in seat_instructions]
    IDs = [Y*8 + X for Y,X in seats]
    print(max(IDs))
    for ID in range(min(IDs), max(IDs)):
        if ID in IDs:
            continue
        else:
            print("Pretty sure yours is: " + str(ID))

main()
