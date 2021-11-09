import elliot_standard_library as es

file = open("Filer\Dag24.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    black = {}

    for line in lines:
        last = ""
        x = 0
        y = 0
        for char in line:
            if char == "e":
                if last not in ["n", "s"]:
                    x += 1
                elif last == "n":
                    x += 0.5
                    y += 1
                elif last == "s":
                    x += 0.5
                    y -= 1
            if char == "w":
                if last not in ["n", "s"]:
                    x -= 1
                elif last == "n":
                    x -= 0.5
                    y += 1
                elif last == "s":
                    x -= 0.5
                    y -= 1
            last = char
        if (x,y) in black:
            del black[(x,y)]
        else:
            black[(x,y)] = True
    print(f"The black tiles: {black}")
    print(f"There are {len(black)}")
    neighbors = [(-1,0), (-0.5,1), (0.5,1), (1,0),(0.5,-1),(-0.5,-1)]
    for day in range(0,100):
        newBlack = {}
        blackNeighbors = {}
        for blackTileX, blackTileY in black.keys():
            #print(f"  Tile: ({blackTileX}, {blackTileY})")
            for x_dif, y_dif in neighbors:
                #print(f"     Neighbor: ({blackTileX + x_dif}, {blackTileY + y_dif})")
                try:
                    blackNeighbors[blackTileX + x_dif, blackTileY + y_dif] += 1
                except KeyError:
                    blackNeighbors[blackTileX + x_dif, blackTileY + y_dif] = 1
        #print(f"BlackNeighbors:\n   {blackNeighbors}")
        for tile, numBlackNeighbors in blackNeighbors.items():
            if tile in black:
                if numBlackNeighbors == 0 or numBlackNeighbors > 2:
                    pass
                else:
                    newBlack[tile] = True
            if not tile in black:
                if numBlackNeighbors == 2:
                    newBlack[tile] = True
        black = newBlack
        print(f"Day {day + 1}: {len(black)}")
    #print(f"The black tiles: {black}")
    print(f"There are {len(black)}")


main()
