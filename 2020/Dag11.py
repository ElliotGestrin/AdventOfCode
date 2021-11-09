import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag11.txt")
lines = [(line.strip()) for line in file.readlines()]

def seatOccupied(seatY, seatX, seats):
    try:
        if seatY < 0 or seatX < 0:
            return False
        if seats[seatY][seatX] == "#":
            return True
        else:
            return False
    except IndexError:
        return False

def seatType(seatY, seatX, seats):
    try:
        if seatY < 0 or seatX < 0:
            return "L"
        if seats[seatY][seatX] == "#":
            return "#"
        if seats[seatY][seatX] == "L":
            return "L"
        if seats[seatY][seatX] == ".":
            return "."
    except IndexError:
        return "L"

def updateSeatVisible(seatY, seatX, seats):
    if seats[seatY][seatX] == ".":
        return "."
    occupiedSurrounding = 0
    #print("   ", seatY, ",", seatX)
    for yslope in range(-1, 2):
        for xslope in range(-1,2):
            if yslope == 0 and xslope == 0:
                continue
            xpos = seatY
            ypos = seatX
            seatFound = False
            while(not seatFound):
                xpos += yslope
                ypos += xslope
                if seatType(xpos, ypos, seats) != ".":
                    #print("     Slope", yslope, ",", xslope, "=>", xpos, ",", ypos, "=", seatType(xpos, ypos, seats))
                    seatFound = True
                    if seatType(xpos, ypos, seats) == "#":
                        occupiedSurrounding += 1
    if seats[seatY][seatX] == "#":
        if occupiedSurrounding >= 5:
            return "L"
        else:
            return "#"
    if seats[seatY][seatX] == "L":
        if occupiedSurrounding == 0:
            return "#"
        else:
            return "L"

def updateSeat(seatY, seatX, seats):
    if seats[seatY][seatX] == ".":
        return "."
    occupiedSurrounding = 0
    for y_dif in range(- 1, + 2):
        for x_dif in range(- 1, + 2):
            if y_dif == 0 and x_dif == 0:
                continue
            if seatOccupied(seatY + y_dif, seatX + x_dif, seats):
                occupiedSurrounding += 1
    if seats[seatY][seatX] == "#":
        if occupiedSurrounding >= 4:
            return "L"
        else:
            return "#"
    if seats[seatY][seatX] == "L":
        if occupiedSurrounding == 0:
            return "#"
        else:
            return "L"
    return None




def main():
    seats = []
    for line in lines:
        row = []
        for char in line:
            row.append(char)
        seats.append(row)
    updated = True
    count = 0
    while(updated):
        updated = False
        originalSeats = es.copy_double_list(seats)
        #es.printlist(seats)
        #print("")
        for seatY in range(0,len(seats)):
            for seatX in range(0, len(seats[seatY])):
                if updateSeatVisible(seatY, seatX, originalSeats) != seats[seatY][seatX]:
                    seats[seatY][seatX] = updateSeatVisible(seatY, seatX, originalSeats)
                    updated = True

        count += 1
        if count == 2:
            pass
            #break
    occupiedSeats = 0
    for seatY in range(0,len(seats)):
        for seatX in range(0, len(seats[seatY])):
            if seatOccupied(seatY, seatX, seats):
                occupiedSeats += 1
    es.printlist(seats)
    print("Occupied seats: ", occupiedSeats)

main()
