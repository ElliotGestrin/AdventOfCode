import elliot_standard_library as es
import math
import time

file = open("Filer\Dag17.txt")
lines = [(line.strip()) for line in file.readlines()]

def extractCoordinates(cubes):
    Ws = es.list_remove_duplicates([cube[0] for cube in cubes])
    Zs = es.list_remove_duplicates([cube[1] for cube in cubes])
    Ys = es.list_remove_duplicates([cube[2] for cube in cubes])
    Xs = es.list_remove_duplicates([cube[3] for cube in cubes])
    return (Ws, Zs, Ys, Xs)

def printCubes(cubes):
    Ws, Zs, Ys, Xs = extractCoordinates(cubes)

    for w in range(min(Ws), max(Ws) + 1):
        print("W = ", w)
        for z in range(min(Zs), max(Zs) + 1):
            print("   Z = ", z)
            for y in range(min(Ys), max(Ys) + 1):
                y_text = "     "
                for x in range(min(Xs), max(Xs) + 1):
                    y_text += cubes[(w,z,y,x)]
                print(y_text)
    print()

def countActiveNeighbors(coordinates, cubes):
    active_neighbors = 0
    w, z, y, x = coordinates
    for w_dif in [-1,0,1]:
        for z_dif in [-1,0,1]:
            for y_dif in [-1,0,1]:
                for x_dif in [-1,0,1]:
                    if w_dif == z_dif == y_dif == x_dif == 0:
                        continue
                    checked_cube = cubes.get((w+w_dif, z+z_dif, y+y_dif, x+x_dif), ".")
                    if checked_cube == "#":
                        active_neighbors += 1
    return active_neighbors

def updateCubes(cubes):
    original_cubes = es.deep_copy_dict(cubes)
    Ws, Zs, Ys, Xs = extractCoordinates(cubes)
    for w in range(min(Ws) - 1, max(Ws) + 2):
        for z in range(min(Zs) - 1, max(Zs) + 2):
            for y in range(min(Ys) - 1, max(Ys) + 2):
                for x in range(min(Xs) - 1, max(Xs) + 2):
                    active_cube = cubes.get((w, z, y, x), ".")
                    active_neighbors = countActiveNeighbors((w,z,y,x), original_cubes)
                    if active_cube == "#":
                        if active_neighbors in [2,3]:
                            cubes[(w,z,y,x)] = "#"
                        else:
                            cubes[(w,z,y,x)] = "."
                    if active_cube == ".":
                        if active_neighbors == 3:
                            cubes[(w,z,y,x)] = "#"
                        else:
                            cubes[(w,z,y,x)] = "."
    return cubes

def main():
    cubes = {}
    w = 0
    z = 0
    y = -math.floor(len(lines)/2)
    x = -math.floor(len(lines[0])/2)
    for line in lines:
        for char in line:
            cubes[(w,z,y,x)] = char
            x += 1
        x = -math.floor(len(lines[0])/2)
        y += 1
    "Starting setup: "
    printCubes(cubes)

    for i in range(0,6):
        updateCubes(cubes)
        print("\nAfter step ", i + 1)
        #printCubes(cubes)

    active_cubes = 0
    Ws, Zs, Ys, Xs = extractCoordinates(cubes)
    for w in range(min(Ws), max(Ws) + 1):
        for z in range(min(Zs), max(Zs) + 1):
            for y in range(min(Ys), max(Ys) + 1):
                for x in range(min(Xs), max(Xs) + 1):
                    if cubes[(w,z,y,x)] == "#":
                        active_cubes += 1
    print("Total number of cubes: ", len(cubes))
    print("Number of active cubes:\n", active_cubes)

t1 = time.time()
main()
t2 = time.time()
print("Elapsed time: ", t2-t1)
