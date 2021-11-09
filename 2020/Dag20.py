import elliot_standard_library as es

file = open("Filer\Dag20.txt")
lines = [(line.strip()) for line in file.readlines()]

def generateTile(lines):
    tile = {}
    tile["A0"] = lines[0]
    tile["B1"] = ""
    tile["B0"] = ""
    for index in range(0, len(lines)):
        if not lines[index]:
            index -= 1
            break
        tile["B1"] += lines[index][0]
        tile["B0"] += lines[index][-1]
    tile["A1"] = lines[index]
    return tile

def printTile(tile):
    print(tile["A0"])
    for index in range(1, len(tile["B1"]) - 1):
        print(f"{tile['B1'][index]}        {tile['B0'][index]}")
    print(tile["A1"])

def rotateTile(tile):
    tempA0 = tile["A0"]
    tile["A0"] = tile["B1"][::-1]
    tile["B1"] = tile["A1"]
    tile["A1"] = tile["B0"][::-1]
    tile["B0"] = tempA0
    return tile

def flipTile(tile, axis):
    if axis == "A":
        noAxis = "B"
    if axis == "B":
        noAxis = "A"
    tile[axis + '0'] = tile[axis + "0"][::-1]
    tile[axis + '1'] = tile[axis + "1"][::-1]
    tempN0 = tile[noAxis + '0']
    tile[noAxis + '0'] = tile[noAxis + '1']
    tile[noAxis + '1'] = tempN0
    return tile

def main():
    tiles = {}
    for line in lines:
        if line[0:4] == "Tile":
            tileId = int(line.split(" ")[1][:-1])
            tileTitleIndex = lines.index(line)
            tiles[tileId] = generateTile(lines[tileTitleIndex + 1:])
            tiles[tileId]["NumFits"] = 0 #ConnectionId, selfDirection, isReversed
    for tileId in tiles:
        print(f"\n{tileId}: ")
        printTile(tiles[tileId])
    for firstId in tiles.keys():
        break
    for mainId, mainTile in tiles.items():
        numFits = 0
        print(f"Analysing tile num {mainId}")
        for mainDirection in mainTile:
            if mainDirection == "NumFits":
                continue
            subDirection = mainDirection[0]
            if mainDirection[1] == "0":
                subDirection += "1"
            if mainDirection[1] == "1":
                subDirection += "0"
            for subId, subTile in tiles.items():
                subTile = subTile.copy()
                if mainTile == subTile:
                    continue
                for flipPhase in range(0,5):
                    if flipPhase == 1: #Flip A only
                        flipTile(subTile, "A")
                    if flipPhase == 2: #Flip B only
                        flipTile(subTile, "A")
                        flipTile(subTile, "B")
                    if flipPhase == 3: #Flip A & B
                        flipTile(subTile, "B")
                        flipTile(subTile, "A")
                        flipTile(subTile, "B")
                    if flipPhase == 4: #Flip B & A
                        flipTile(subTile, "B")
                        flipTile(subTile, "A")
                        flipTile(subTile, "B")
                        flipTile(subTile, "A")
                    for rotation in range(0,4):
                        if subTile[subDirection] == mainTile[mainDirection]:
                            numFits += 1
                            print(f"    {mainDirection} matched with {subId} ({rotation}, {flipPhase})")
                            break
                        rotateTile(subTile)
                    else:
                        continue
                    break
                else:
                    continue
                break
            print(f"    After direction {mainDirection} there are: {numFits} fits")
        mainTile["NumFits"] = numFits
    cornerTiles = []
    mult = 1
    for tileId, tile in tiles.items():
        if tile["NumFits"] == 2:
            cornerTiles.append(tileId)
            mult *= tileId
    print(f"The corner tiles are: {cornerTiles}")
    print(f"The multiplication thereof is: \n{mult}")


main()
