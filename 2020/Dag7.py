file = open("Filer\Dag7.txt")
lines = [line.strip() for line in file.readlines()]

def define_bags():
    bags = []
    for line in lines:
        name = line.split(" contain")[0][:-1]
        contains = line.split("contain ")[1]
        contains = contains.split(", ")
        bag = {}
        bag["name"] = name
        for contain in contains:
            if contain == "no other bags.":
                continue
            contain_name = contain[2:]
            contain_number = int(contain[0])
            if contain_name[-1] == ".":
                contain_name = contain_name[:-1]
            if contain_name[-1] == "s":
                contain_name = contain_name[:-1]
            bag[contain_name] = contain_number
        bags.append(bag)
    return(bags)

def find_gold_bags(bags):
    gold_bags = []
    for bag in bags:
        if "shiny gold bag" in bag:
            gold_bags.append(bag["name"])
    return(gold_bags)

def extend_gold_bags(all_bags, current_bags):
    old_bags = []
    while(old_bags != current_bags):
        old_bags = current_bags
        for goldie in current_bags:
            for bag in all_bags:
                if goldie in bag:
                    if bag["name"] not in current_bags:
                        current_bags.append(bag["name"])
    return(current_bags)

def find_bag(name, all_bags):
    for bag in all_bags:
        if bag["name"] == name:
            return(bag)

def bags_in_bag(bag, counted_bags, all_bags):
    count = 0
    for sub_bag in bag.keys():
        if sub_bag == "name":
            continue
        else:
            counted_bags.append(sub_bag)
            print(sub_bag)
            print(find_bag(sub_bag, all_bags))
            addition, counted_bags = bags_in_bag(find_bag(sub_bag, all_bags), counted_bags, all_bags)
            count += bag[sub_bag] * addition
    count += 1
    return(count, counted_bags)

def main():
    all_bags = define_bags()
    pure_gold = find_gold_bags(all_bags)
    extended_gold = extend_gold_bags(all_bags, pure_gold)

    print(bags_in_bag(find_bag("shiny gold bag", all_bags), [], all_bags))

main()
