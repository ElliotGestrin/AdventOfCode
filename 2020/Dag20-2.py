import elliot_standard_library as es
import math

file = open("Filer\Dag20.txt")
lines = [(line.strip()) for line in file.readlines()]

def generateTile(lines):
    tile = {}
    tile["A0"] = lines[0]
    tile["B1"] = lines[0][0]
    tile["B0"] = lines[0][-1]
    tile["C"] = []
    for index in range(1, len(lines) - 1):
        if not lines[index + 1]:
            index -= 1
            break
        tile["B1"] += lines[index][0]
        tile["B0"] += lines[index][-1]
        tile["C"].append(lines[index][1:-1])
    index += 1
    tile["B1"] += lines[index][0]
    tile["B0"] += lines[index][-1]
    tile["A1"] = lines[index]
    tile["Neighbors"] = []
    return tile

def printTile(tile):
    print(tile["A0"])
    for index in range(1, len(tile["B1"]) - 1):
        print(f"{tile['B1'][index] + tile['C'][index - 1] + tile['B0'][index]}")
    print(tile["A1"], "\n")

def rotateTile(tile, center = False):
    tempA0 = tile["A0"]
    tile["A0"] = tile["B1"][::-1]
    tile["B1"] = tile["A1"]
    tile["A1"] = tile["B0"][::-1]
    tile["B0"] = tempA0
    if center == True:
        tile["C"] = rotateCenter(tile["C"])
    return tile

def rotateCenter(center):
    numRows = len(center)
    rotatedCenter = ["" for i in range(0,numRows)]
    row_len = len(center[0])
    for rotatedRow in range(0,numRows):
        for offset in range(0,row_len):
            rotatedCenter[rotatedRow] = rotatedCenter[rotatedRow][0:offset] + center[row_len - 1 - offset][rotatedRow] + rotatedCenter[rotatedRow][offset:]
    return rotatedCenter

def flipTile(tile, axis, center = False):
    if axis == "A":
        noAxis = "B"
    if axis == "B":
        noAxis = "A"
    tile[axis + '0'] = tile[axis + "0"][::-1]
    tile[axis + '1'] = tile[axis + "1"][::-1]
    tempN0 = tile[noAxis + '0']
    tile[noAxis + '0'] = tile[noAxis + '1']
    tile[noAxis + '1'] = tempN0
    if center == True:
        tile["C"] = flipCenter(tile["C"], axis)
    return tile

def flipCenter(center, axis):
    numRows = len(center)
    flippedCenter = ["" for i in range(0,numRows)]
    row_len = len(center[0])
    if axis == "A":
        for rowNum in range(0, numRows):
            flippedCenter[rowNum] = center[rowNum][::-1]
    if axis == "B":
        for rowNum in range(0, numRows):
            flippedCenter[rowNum] = center[numRows - 1 - rowNum]
    return flippedCenter

def findTileNeighbors(tiles):
    for mainId, mainTile in tiles.items():
        numFits = 0
        for mainDirection in mainTile:
            if not mainDirection in ["A0", "A1", "B0", "B1"]:
                continue
            subDirection = mainDirection.translate("".maketrans({"0":"1","1":"0"}))
            for subId, subTile in tiles.items():
                subTile = subTile.copy()
                if mainTile == subTile:
                    continue
                for flipPhase in range(0,2):
                    if flipPhase == 1: #Flip A only
                        flipTile(subTile, "A")
                    for rotation in range(0,4):
                        if subTile[subDirection] == mainTile[mainDirection]:
                            numFits += 1
                            flipDirection = "A" if flipPhase == "1" else ""
                            mainTile["Neighbors"].append((mainDirection,subId))
                            break
                        rotateTile(subTile)
                    else:
                        continue
                    break
                else:
                    continue
                break
        mainTile["NumFits"] = numFits

def findSideArrangement(originCorner, tiles, offset = 0, aboveControlId = None, leftControlId = None):
    arrangement = {}
    for direction in ["A1", "B0"]:
        x = offset
        y = offset
        if direction == "A1":
            if aboveControlId == None:
                lastTileID = originCorner
                neighbordirections = [direction for direction, neighborID in tiles[originCorner]["Neighbors"]]
                nextTileId = tiles[originCorner]["Neighbors"][0][1]
                arrangement[(offset,offset)] = (originCorner, "A0")
            else:
                lastTileID = originCorner
                nextTileId, originalTileTop = chooseNextTile(aboveControlId, tiles[originCorner])
                arrangement[(offset,offset)] = (originCorner, originalTileTop)
        if direction == "B0":
            if leftControlId == None:
                lastTileID = originCorner
                nextTileId = tiles[originCorner]["Neighbors"][1][1]
            else:
                lastTileID = originCorner
                nextTileId, nextTileTop = chooseNextTile(leftControlId, tiles[originCorner])
        while nextTileId:
            currentTileID = nextTileId
            nextTileId, currentTileComingFrom = chooseNextTile(lastTileID, tiles[currentTileID])
            if direction == "A1":
                currentTileTop = currentTileComingFrom
                y += 1
            if direction == "B0":
                if currentTileComingFrom == "B1":
                    currentTileTop = "A0"
                if currentTileComingFrom == "A0":
                    currentTileTop = "B0"
                if currentTileComingFrom == "A1":
                    currentTileTop = "B1"
                if currentTileComingFrom == "B0":
                    currentTileTop = "A1"
                x += 1
            arrangement[(x,y)] = (currentTileID, currentTileTop)
            lastTileID = currentTileID
    try:
        rightID = arrangement[(offset + 1, offset)][0]
        belowID = arrangement[(offset, offset + 1)][0]
        rightsNeighborIDs = [neighborID for direction, neighborID in tiles[rightID]["Neighbors"]]
        belowsNeighborIDs = [neighborID for direction, neighborID in tiles[belowID]["Neighbors"]]
        nextOriginId = [neighborID for neighborID in rightsNeighborIDs if neighborID in belowsNeighborIDs and neighborID != originCorner][0]
        followingArrangements = findSideArrangement(nextOriginId, tiles, offset + 1, rightID, belowID)
        for position, ID in followingArrangements.items():
            arrangement[position] = ID
        return arrangement
    except KeyError: #Will happen on the final, where there is no rightID
        return arrangement

def chooseNextTile(lastTileID, currentTile):
    #print(f"Analysing {currentTile}")
    comingFrom = [direction for direction, neighborID in currentTile["Neighbors"] if neighborID == lastTileID][0]
    goingTo = comingFrom.translate("".maketrans({"0":"1", "1":"0"}))
    nextTileId = [neighborID for direction, neighborID in currentTile["Neighbors"] if direction == goingTo]
    if len(nextTileId) == 1:
        nextTileId = nextTileId [0]
    #print(f"{lastTileID} -> ? -> {nextTileId}")
    return nextTileId, comingFrom

def fixArrangementRotation(arrangement, tiles):
    pos_max = int(math.sqrt(len(arrangement)))
    for x in range(0, pos_max):
        for y in range(0, pos_max):
            currentTileID, wantUp = arrangement[(x,y)]
            currentTile = tiles[currentTileID]
            if wantUp == "A0":
                rotations = 0
            if wantUp == "B0":
                rotations = 3
            if wantUp == "A1":
                rotations = 2
            if wantUp == "B1":
                rotations = 1
            for rot in range(0, rotations):
                rotateTile(currentTile, True)

def fixArrangementFlip(arrangement, tiles):
    originTile = tiles[arrangement[(0,0)][0]]
    rightTile = tiles[arrangement[(1,0)][0]]
    rightEdgesExtended = [rightTile["B0"], rightTile["B1"], rightTile["B0"][::-1], rightTile["B1"][::-1]]
    belowTile = tiles[arrangement[(0,1)][0]]
    belowEdgesExtended =  [belowTile["B0"], belowTile["B1"], belowTile["B0"][::-1], belowTile["B1"][::-1]]
    if not originTile["B0"] in rightEdgesExtended:
        flipTile(originTile, "A", True)
    if not originTile["A1"] in belowEdgesExtended:
        flipTile(originTile, "B", True)

    pos_max = int(math.sqrt(len(arrangement)))
    for y in range(0, pos_max):
        if y != 0:
            activeTile = tiles[arrangement[(0,y)][0]]
            aboveTile = tiles[arrangement[(0,y-1)][0]]
            aboveEdgeExtended = [aboveTile["A1"], aboveTile["A1"][::-1]]
            rightTile = tiles[arrangement[(1,y)][0]]
            rightEdgesExtended = [rightTile["B0"], rightTile["B1"], rightTile["B0"][::-1], rightTile["B1"][::-1]]
            if not activeTile["A0"] in aboveEdgeExtended:
                flipTile(activeTile, "B", True)
            if not activeTile["B0"] in rightEdgesExtended:
                flipTile(activeTile, "A", True)
        for x in range(1, pos_max):
            if y == x == 0:
                continue
            activeTile = tiles[arrangement[(x,y)][0]]
            leftTile = tiles[arrangement[(x-1,y)][0]]
            leftEdgeExtended = [leftTile["B0"], leftTile["B0"][::-1]]
            if not activeTile["B1"] in leftEdgeExtended:
                flipTile(activeTile, "A", True)
            if not activeTile["B1"] == leftTile["B0"]:
                flipTile(activeTile, "B", True)

def printArrangement(arrangement, tiles):
    pos_max = int(math.sqrt(len(arrangement)))
    tile_size = len(tiles[arrangement[(0,0)][0]]["A0"])
    for y in range(0, pos_max):
        for subRow in range(0, tile_size):
            row = ""
            for x in range(0, pos_max):
                tile = tiles[arrangement[(x,y)][0]]
                if subRow == 0:
                    row += tile["A0"] + "  "
                elif subRow == tile_size - 1:
                    row += tile["A1"] + "  "
                else:
                    row += tile["B1"][subRow] + tile["C"][subRow - 1] + tile["B0"][subRow] + "  "
            print(row)
        print()

def createTrueImage(arrangement, tiles):
    pos_max = int(math.sqrt(len(arrangement)))
    num_centerlines = len(tiles[arrangement[(0,0)][0]]["C"])
    trueImage = ["" for i in range(0, pos_max * num_centerlines)]
    for y in range(0, pos_max):
        for subRow in range(0, num_centerlines):
            for x in range(0, pos_max):
                trueImage[y*num_centerlines + subRow] += tiles[arrangement[(x,y)][0]]["C"][subRow]
    return trueImage

def findSeaMonsters(trueImage):
    seaMonster = [(0,0), (1,1), (4,1), (5,0), (6,0), (7, 1), (10, 1), (11,0), (12,0), (13,1), (16,1), (17,0), (18,-1), (18,0), (19,0)]
    print("\nA demo seamonster:")
    for y in [-1,0,1]:
        row = ""
        for x in range(0,20):
            if (x,y) in seaMonster:
                row += "#"
            else:
                row += " "
        print(row)
    numMonsters = 0
    for flipPhase in range(0,2):
        if flipPhase == 1: #Flip A
            trueImage = flipCenter(trueImage, "A")
        if flipPhase == 2: #Flip B
            trueImage = flipCenter(trueImage, "A")
            trueImage = flipCenter(trueImage, "B")
        if flipPhase == 3: #Flip A-B
            trueImage = flipCenter(trueImage, "B")
            trueImage = flipCenter(trueImage, "A")
            trueImage = flipCenter(trueImage, "B")
        if flipPhase == 4: #Flip B-A
            trueImage = flipCenter(trueImage, "B")
            trueImage = flipCenter(trueImage, "A")
            trueImage = flipCenter(trueImage, "B")
            trueImage = flipCenter(trueImage, "A")
        for rotation in range(0,4):
            for y in range(1, len(trueImage) - 1):
                for x in range(0, len(trueImage[0]) - 19):
                    for monsterPart in seaMonster:
                        if trueImage[y + monsterPart[1]][x + monsterPart[0]] != "#":
                            break
                    else:
                        numMonsters += 1
                        for monsterPart in seaMonster:
                            trueImage[y + monsterPart[1]] = es.stringExchange(trueImage[y + monsterPart[1]], "O", x + monsterPart[0])
            if numMonsters != 0:
                break
            trueImage = rotateCenter(trueImage)
        else:
            continue
        break
    print(f"There are: {numMonsters} sea monsters!")
    return trueImage

def main():
    tiles = {}
    for line in lines:
        if line[0:4] == "Tile":
            tileId = int(line.split(" ")[1][:-1])
            tileTitleIndex = lines.index(line)
            tiles[tileId] = generateTile(lines[tileTitleIndex + 1:])
            tiles[tileId]["NumFits"] = 0
    findTileNeighbors(tiles)
    cornerTiles = []
    for tileId, tile in tiles.items():
        if tile["NumFits"] == 2:
            cornerTiles.append(tileId)
    print(f"The corner tiles are: {cornerTiles}")
    originCorner = cornerTiles[0]
    arrangement = findSideArrangement(originCorner, tiles)
    fixArrangementRotation(arrangement, tiles)
    fixArrangementFlip(arrangement, tiles)
    print("After fixing the arrangements flip:")
    printArrangement(arrangement, tiles)
    trueImage = createTrueImage(arrangement, tiles)
    print("The true image:")
    es.printlist(trueImage)
    seamonsterMap = findSeaMonsters(trueImage)
    print("\nThe seamonster map!")
    es.printlist(seamonsterMap)
    seaRougness = 0
    for row in seamonsterMap:
        seaRougness += row.count("#")
    print(f"The roughness in this sea is: {seaRougness}")

testList = ["1234","5678","8901"]
es.printlist(testList)
testList = flipCenter(testList, "A")
print()
es.printlist(testList)

main()
