file = open("Filer\Dag8.txt")
lines = [line.strip() for line in file.readlines()]
true_lines = lines

accumulator = [0]

def performOperation(operationLine, index, pastIndex):
    operation = operationLine.split(" ")[0]
    print(index)
    print(operation)
    if operation == "nop":
        index  += 1
        return(index, pastIndex)
    if operation == "acc":
        accumulator.append(accumulator[-1]+int(operationLine.split(" ")[1]))
        index  += 1
        return(index, pastIndex)
    if operation == "jmp":
        index += int(operationLine.split(" ")[1])
        return(index, pastIndex)

def edit_lines(previoud_index):
    lines = []
    for line in true_lines:
        lines.append(line)
    edit_index = previoud_index
    print(lines)
    for i in range(previoud_index + 1, len(true_lines)):
        print("testing i = " + str(i))
        if true_lines[i].split(" ")[0] == "nop":
            lines[i] = "jmp " + true_lines[i].split(" ")[1]
            edit_index = i
            print("Changed-> nop" + str(i))
            break
        if true_lines[i].split(" ")[0] == "jmp":
            lines[i] = "nop " + true_lines[i].split(" ")[1]
            edit_index = i
            print("Changed-> nop" + str(i))
            break
    print("Change done")
    return(lines, edit_index)


def main():
    edit_index = -1
    while(edit_index < len(true_lines)):
        lines, edit_index = edit_lines(edit_index)
        print()
        print()
        print(edit_index)
        print(lines[edit_index])
        print()
        pastIndex = []
        accumulator.append(0)
        index = 0
        while(index < len(lines)):
            if not index in pastIndex:
                pastIndex.append(index)
                index, pastIndex = performOperation(lines[index], index, pastIndex)
            else:
                break
        if index == len(lines):
            print(edit_index)
            print(accumulator[-1])
            break
    else:
        print("FUCKING BROKE")

main()
