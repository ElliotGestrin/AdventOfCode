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
                    y_text += cubes.get((w,z,y,x), ".")
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

def updateCubes(active_cubes):
    active_neighbors = {}
    new_active_cubes = {}
    for w,z,y,x in active_cubes:
        for w_dif in [-1,0,1]:
            for z_dif in [-1,0,1]:
                for y_dif in [-1,0,1]:
                    for x_dif in [-1,0,1]:
                        if w_dif == z_dif == y_dif == x_dif == 0:
                            continue
                        try:
                            active_neighbors[(w+w_dif, z+z_dif, y+y_dif, x+x_dif)] += 1
                        except KeyError:
                            active_neighbors[(w+w_dif, z+z_dif, y+y_dif, x+x_dif)] = 1
    for current_cube in active_neighbors:
        if active_neighbors[current_cube] in [2,3]:
            if current_cube in active_cubes:
                new_active_cubes[current_cube] = "#"
            elif active_neighbors[current_cube] == 3:
                new_active_cubes[current_cube] = "#"
    return new_active_cubes

def main():
    activeCubes = {}
    w = 0
    z = 0
    y = -math.floor(len(lines)/2)
    x = -math.floor(len(lines[0])/2)
    for line in lines:
        for char in line:
            if char == "#":
                activeCubes[(w,z,y,x)] = "#"
            x += 1
        x = -math.floor(len(lines[0])/2)
        y += 1
    "Starting setup: "
    printCubes(activeCubes)

    for i in range(0,6):
        activeCubes = updateCubes(activeCubes)
        print("\nAfter step ", i + 1, ": ", len(activeCubes))
        printCubes(activeCubes)

    print("Number of active cubes:\n", len(activeCubes))


t1 = time.time()
main()
t2 = time.time()
print("Elapsed time: ", t2-t1)
