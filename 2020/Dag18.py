import elliot_standard_library as es
import math

file = open("Filer\Dag18.txt")
lines = [(line.strip()) for line in file.readlines()]

def evaluateParanthesis(line, startIndex):
    operations = {"+":add, "*":multiply, ".":setStart}
    operator = "."
    value = 0
    index = startIndex
    while index < len(line):
        if line[index] == " ":
            index += 1
            continue
        if line[index] == ")":
            break
        elif line[index] == "(":
            subExpression, index = evaluateParanthesis(line, index + 1)
            value = operations[operator](subExpression, value)
        elif line[index] == "*":
            operator = "*"
        elif line[index] == "+":
            operator = "+"
        else:
            value = operations[operator](line[index], value)
        index += 1
    return value, index


def add(toAdd, value):
    return int(toAdd) + value

def multiply(mult, value):
    return int(mult)*value

def setStart(start, value):
    return int(start)


def main():
    values = []
    for line in lines:
        values.append(evaluateParanthesis(line, 0)[0])
    es.printlist(values)
    sum = 0
    for val in values:
        sum += val
    print(sum)


main()
