import single_line_reader as slr

file = open("Filer\Dag8.txt")
true_lines = [line.strip() for line in file.readlines()]

def copy_list(list):
    copy = []
    for item in list:
        copy.append(item)
    return(copy)

def edit_lines(previoud_index):
    lines = copy_list(true_lines)
    for i in range(previoud_index + 1, len(lines)):
        line = lines[i]
        instruction, value = line.split(" ")
        if instruction == "nop":
            lines[i] = "jmp " + value
            return(lines, i)
        if instruction == "jmp":
            lines[i] = "nop " + value
            return(lines, i)

def main():
    edit_index = -1
    while edit_index < len(true_lines) - 1:
        lines, edit_index = edit_lines(edit_index)
        #print("Editing for index " + str(edit_index))
        #for line in lines:
        #    print("  " + line)
        reader = slr.line_reader(lines)
        ind, acc = reader.run()
        if ind == len(true_lines):
            print("Found faulty line! " + str(edit_index))
            print("Correct accumulator value: " + str(acc))
            break
    else:
        print("Couldn't fix it...")
        print("Edit_index: " + str(edit_index))

main()
