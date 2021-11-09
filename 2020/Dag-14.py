import elliot_standard_library as es

file = open("Filer\Dag14.txt")
lines = [(line.strip()) for line in file.readlines()]

def get_mask(line):
    info = line.split(" = ")[1]
    mask = {}
    pos = 35
    for char in info:
        if char != "X":
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

def binary_to_decimal(binary):
    decimal = 0
    for pos in binary.keys():
        pos_value = pow(2, pos)
        decimal += binary[pos] * pos_value
    return decimal

def apply_mask(binary, mask):
    for pos in mask.keys():
        binary[pos] = mask[pos]

def main():
    mask = {}
    memory = {}
    for line in lines:
        print(line)
        if line.split(" = ")[0] == "mask":
            mask = get_mask(line)
        else:
            mem_loc = int(line.split("]")[0].split("[")[1])
            decimal = int(line.split(" = ")[1])
            #print("Decimal ", decimal)
            binary = decimal_to_binary(decimal)
            #print("binary ", binary)
            apply_mask(binary, mask)
            #print("Binary masked ", binary)
            decimal2 = binary_to_decimal(binary)
            #print("Decimal2 ", decimal2)
            memory[mem_loc] = decimal2
    sum = 0
    for val in memory.values():
        sum += val
    print(sum)

main()
