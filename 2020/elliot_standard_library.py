def deep_copy_list(original):
    copy = []
    for item in original:
        if isinstance(item, list):
            copy.append(deep_copy_list(item))
        else:
            copy.append(item)
    return(copy)

def deep_copy_dict(original):
    copy = {}
    for key,item in original.items():
        if isinstance(item, dict):
            copy[key] = (deep_copy_dict(item))
        else:
            copy[key] = (item)
    return(copy)

def printlist(list, pre_mod = "", sub_mod = ""):
    for line in list:
        print(pre_mod + str(line) + sub_mod)

def add_to_list(listy, add):
    for index in range(0,len(listy)):
        listy[index] += add

def multiply_list(listy, mult):
    for index in range(0,len(listy)):
        listy[index] *= mult

def list_remove_duplicates(listA):
    listB = []
    for item in listA:
        if item in listB:
            continue
        else:
            listB.append(item)
    listA = listB
    return listA

def stringExchange(string, char, index):
    if index < len(string) - 1:
        return string[0:index] + char + string[index + 1:]
    else:
        return string[0:index] + char

if __name__ == "__main__":
    print("testing printlist: ")
    list = [1,2,3,4]
    printlist(list, pre_mod = "  ")
    list = ["one", "two", "three", "four"]
    printlist(list, pre_mod = "  ", sub_mod = "!")
    list = ["one", 2, "three", 4]
    printlist(list, "  ", "!")
