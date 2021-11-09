import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag9.txt")
lines = [int(line.strip()) for line in file.readlines()]

def isValid(number, list):
    for main in list:
        for sub in list:
            if main + sub == number:
                return True
    return False

def crackCode(number, list):
    for width in range(2,len(list)):
        for ofset in range(0, len(list)-width + 1):
            sum = 0
            for i in range(0, width):
                sum += list[i + ofset]
            if sum == number:
                return(list[0+ofset:width+ofset])

def main():
    list = lines[0:25]
    print(len(list))
    breaky = 0
    for i in range(25, len(lines)):
        if isValid(lines[i], list[-25:]):
            list.append(lines[i])
        else:
            breaky = lines[i]
            print("Found fail! ", lines[i])
            print("Index: ", i)
            break
    breakers = crackCode(breaky, lines)
    print(breakers)
    print(min(breakers) + max(breakers))

main()
