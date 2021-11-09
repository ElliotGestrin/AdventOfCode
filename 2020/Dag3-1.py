file = open("Filer\Dag3-1.txt")
map = []

for line in file:
    row = []
    for letter in line:
        if(letter == "."):
            row.append(0)
        if(letter == "#"):
            row.append(1)
    map.append(row)

y = 0
x = 0
sum1 = 0
while(y < len(map)):
    sum1 += map[y][x]
    y += 1
    x += 1
    if (x >= len(map[0])):
        x -= len(map[0])

y = 0
x = 0
sum2 = 0
while(y < len(map)):
    sum2 += map[y][x]
    y += 1
    x += 3
    if (x >= len(map[0])):
        x -= len(map[0])

y = 0
x = 0
sum3 = 0
while(y < len(map)):
    sum3 += map[y][x]
    y += 1
    x += 5
    if (x >= len(map[0])):
        x -= len(map[0])

y = 0
x = 0
sum4 = 0
while(y < len(map)):
    sum4 += map[y][x]
    y += 1
    x += 7
    if (x >= len(map[0])):
        x -= len(map[0])

y = 0
x = 0
sum5 = 0
while(y < len(map)):
    sum5 += map[y][x]
    y += 2
    x += 1
    if (x >= len(map[0])):
        x -= len(map[0])

print(sum1 * sum2 * sum3 * sum4 * sum5)
