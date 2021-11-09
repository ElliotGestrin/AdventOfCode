import elliot_standard_library as es

file = open("Filer\Dag14.txt")
lines = [(line.strip()) for line in file.readlines()]

def get_mask(line):
    info = line.split(" = ")[1]
    mask = {}
    pos = 35
    for char in info:
        if char == "X":
            mask[pos] = char
        else:
            mask[pos] = int(char)
        pos = pos - 1
    return mask

def decimal_to_binary(decimal):
    pos = 35
    binary = {}
    while(pos >= 0):
        pos_value = pow(2, pos)
        if decimal >= pos_value:
            binary[pos] = 1
            decimal -= pos_value
        else:
            binary[pos] = 0
        pos = pos - 1
    return binary

def binary_to_decimal(binary_list):
    decimal_list = []
    for binary in binary_list:
        decimal = 0
        for pos in binary.keys():
            pos_value = pow(2, pos)
            decimal += binary[pos] * pos_value
        decimal_list.append(decimal)
    return decimal_list

def apply_mask(orig_binary, mask):
    binary_list = [{}]
    for pos in mask.keys():
        if mask[pos] == "X":
            new_binary_list = []
            for binary in binary_list:
                for val in [0,1]:
                    clone = binary.copy()
                    clone[pos] = val
                    new_binary_list.append(clone)
            binary_list = new_binary_list
        else:
            if mask[pos] == 0:
                for binary in binary_list:
                    binary[pos] = orig_binary[pos]
            else:
                for binary in binary_list:
                    binary[pos] = 1
    return binary_list

def main():
    mask = {}
    memory = {}
    for line in lines:
        print(line)
        if line.split(" = ")[0] == "mask":
            mask = get_mask(line)
        else:
            mem_loc = int(line.split("]")[0].split("[")[1])
            mem_loc = decimal_to_binary(mem_loc)
            mem_locs = apply_mask(mem_loc, mask)
            mem_locs = binary_to_decimal(mem_locs)
            decimal = int(line.split(" = ")[1])
            for mem_loc in mem_locs:
                memory[mem_loc] = decimal
    sum = 0
    for val in memory.values():
        sum += val
    print(sum)

main()
