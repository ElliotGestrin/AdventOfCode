import elliot_standard_library as es
import math

file = open("Filer\Dag17.txt")
lines = [(line.strip()) for line in file.readlines()]

def updateCube(cube, cube_state, original_cubes, z, w):
    active_neighbors = 0
    x,y = cube
    for w_dif in [-1,0,1]:
        w_slice = original_cubes.get(w + w_dif, {})
        if not w_slice:
            continue
        active_neighbors += w_neighbors(cube, cube_state, w_slice, z)
    if cube_state == 1:
        if active_neighbors in [2,3]:
            return 1
        else:
            return 0
    if cube_state == 0:
        if active_neighbors == 3:
            return 1
        else:
            return 0

def w_neighbors(cube, cube_state, original_cubes, z):
    active_neighbors = 0
    x,y = cube
    for z_dif in [-1,0,1]:
        z_slice = original_cubes.get(z + z_dif, {})
        if not z_slice:
            continue
        for x_dif in [-1,0,1]:
            for y_dif in [-1,0,1]:
                if z_dif == x_dif == y_dif == 0:
                    continue
                if z_slice.get((x+x_dif, y+y_dif), 0) == 1:
                    active_neighbors += 1
    return active_neighbors

def printCubes(cubes):
    wWidth = math.floor(len(cubes)/2)
    print(cubes.keys())
    for w in range(-wWidth, wWidth + 1):
        zWidth = math.floor(len(cubes[0])/2)
        print()
        print("W = ", w)
        for z in range(-zWidth, zWidth + 1):
            print("Z = ", z)
            strings = {}
            for cube, cube_state in cubes[w][z].items():
                x, y = cube
                x = int(x)
                y = int(y)
                if y in strings.keys():
                    strings[y][x] = str(cube_state)
                else:
                    strings[y] = {x: str(cube_state)}
            xWidth = int((len(strings[0]) - 1)/2)
            yWidth = int((len(strings) - 1)/2)
            for y in range(-yWidth, yWidth + 1):
                string = ""
                for x in range(-xWidth, xWidth + 1):
                    if strings[y][x] == "1":
                        string += "#"
                    else:
                        string += "."
                print(string)

def main():
    cubes = {}
    x = -math.floor(len(lines[0])/2)
    y = -math.floor(len(lines[0])/2)
    z = 0
    w = 0
    cubes[w] = {z:{}}
    for line in lines:
        for char in line:
            if char == ".":
                cubes[w][z][(x,y)] = 0
            if char == "#":
                cubes[w][z][(x,y)] = 1
            x += 1
        x = -math.floor(len(lines[0])/2)
        y += 1
    print(cubes)
    print("CUBES: ")
    printCubes(cubes)
    for i in range(0,6):
        minW = min(cubes.keys())
        maxW = max(cubes.keys())
        cubes[minW-1] = {}
        cubes[maxW+1] = {}
        maxDif = 0
        for cube in cubes[0][0].keys():
            if abs(cube[0]) > maxDif:
                maxDif = abs(int(cube[0]))
        minZ = min(cubes[0].keys())
        maxZ = max(cubes[0].keys())
        for w in cubes.keys():
            cubes[w][minZ-1] = {}
            cubes[w][maxZ+1] = {}
            for z in cubes[w].keys():
                for x in range(-maxDif - 1, maxDif + 2):
                    for y in range(-maxDif - 1, maxDif + 2):
                        if not (x,y) in cubes[w][z].keys():
                            cubes[w][z][(x,y)] = 0
        original_cubes = es.deep_copy_dict(cubes)
        for w in cubes.keys():
            for z in cubes[w].keys():
                for cube, cube_state in cubes[w][z].items():
                    cubes[w][z][cube] = updateCube(cube, cube_state, original_cubes, z, w)
        print()
        print()
        print("After ", i + 1)
        printCubes(cubes)
    active_cubes = 0
    for w in cubes.keys():
        for z in cubes[w].keys():
            for cube, cube_state in cubes[w][z].items():
                if cube_state == 1:
                    active_cubes += 1
    print(active_cubes)



main()
