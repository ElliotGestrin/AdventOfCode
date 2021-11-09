import elliot_standard_library as es
import math

file = open("Filer\Dag17.txt")
lines = [(line.strip()) for line in file.readlines()]

def updateCube(cube, cube_state, original_cubes, z):
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

def printCubes(cubes):
    zWidth = int((len(cubes) - 1)/2)
    xWidth = int()
    for z in range(-zWidth, zWidth + 1):
        print("Z = ", z)
        strings = {}
        for cube, cube_state in cubes[z].items():
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
    cubes[z] = {}
    for line in lines:
        for char in line:
            if char == ".":
                cubes[z][(x,y)] = 0
            if char == "#":
                cubes[z][(x,y)] = 1
            x += 1
        x = -math.floor(len(lines[0])/2)
        y += 1
    print(cubes)
    print("CUBES: ")
    printCubes(cubes)
    for i in range(0,6):
        minZ = min(cubes.keys())
        maxZ = max(cubes.keys())
        cubes[minZ-1] = {}
        cubes[maxZ+1] = {}
        maxDif = 0
        for cube in cubes[0].keys():
            if abs(cube[0]) > maxDif:
                maxDif = abs(int(cube[0]))
        for z in cubes.keys():
            for x in range(-maxDif - 1, maxDif + 2):
                for y in range(-maxDif - 1, maxDif + 2):
                    if not (x,y) in cubes[z].keys():
                        cubes[z][(x,y)] = 0
        original_cubes = es.deep_copy_dict(cubes)
        for z in cubes.keys():
            for cube, cube_state in cubes[z].items():
                cubes[z][cube] = updateCube(cube, cube_state, original_cubes, z)
        print("After ", i + 1)
        printCubes(cubes)
        print()
    active_cubes = 0
    for z in cubes.keys():
        for cube, cube_state in cubes[z].items():
            if cube_state == 1:
                active_cubes += 1
    print(active_cubes)



main()
