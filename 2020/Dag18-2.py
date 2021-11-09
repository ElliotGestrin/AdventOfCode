import elliot_standard_library as es
import math

file = open("Filer\Dag18.txt")
lines = [(line.strip()) for line in file.readlines()]

def createOrderList(line):
    list = []
    for char in line:
        if char == " ":
            continue
        else:
            list.append(char)
    return list

def fixParanthesis(orderList):
    index = 0
    paranStarts = -1
    parans = []
    owedClosing = 0
    while index < len(orderList):
        order = orderList[index]
        if order == "(" and paranStarts == -1:
            paranStarts = index
        elif order == "(" and paranStarts != -1:
            owedClosing += 1
        if order == ")" and owedClosing == 0:
            parans.append(orderList[paranStarts + 1: index])
            paranStarts = -1
        elif order == ")":
            owedClosing -= 1
        index += 1
    inParan = False
    paranNum = 0
    semiDone = []
    owedClosing = 0
    index = 0
    while index < len(orderList):
        order = orderList[index]
        if order == "(" and not inParan:
            semiDone.append(parans[paranNum])
            paranNum += 1
            inParan = True
        elif order == "(":
            owedClosing += 1
        elif order == ")" and owedClosing == 0:
            inParan = False
        elif order == ")":
            owedClosing -= 1
        elif not inParan:
            semiDone.append(order)
        index += 1
    return semiDone

def evaluateOrderList(orderList):
    index = 0
    value = 0
    if "(" in orderList:
        orderList = fixParanthesis(orderList)
    if "+" in orderList:
        while index < len(orderList):
            order = orderList[index]
            if order == "+":
                orderList[index-1:index+2] = add(orderList[index-1], orderList[index+1])
            else:
                index += 1
    try:
        mult = int(orderList[0])
    except TypeError:
        mult = int(evaluateOrderList(orderList[0]))
    for order in orderList[1:]:
        if order == "*":
            continue
        if isinstance(order, list):
            order = evaluateOrderList(order)
        mult *= int(order)
    return mult

def add(add1, add2):
    if isinstance(add1, list):
        add1 = evaluateOrderList(add1)
    if isinstance(add2, list):
        add2 = evaluateOrderList(add2)
    return [int(add1) + int(add2)]

def main():
    values = []
    orderLists = []
    for line in lines:
        orderLists.append(createOrderList(line))
    es.printlist(orderLists)
    evaluations = []
    for orderList in orderLists:
        print(f"Evaluating {orderList}")
        evaluations.append(evaluateOrderList(orderList))
        print(f"The result is {evaluations[-1]}")
    es.printlist(evaluations)
    sum = 0
    for eval in evaluations:
        sum += eval
    print(f"\nSum: {sum}")


main()
