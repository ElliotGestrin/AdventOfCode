import elliot_standard_library as es

file = open("Filer\Dag19.txt")
lines = [(line.strip()) for line in file.readlines()]

def simplifyRule(rule_id, rules):
    #print(f"\n\nTrying to simplify {rule_id} ({rules[rule_id][0]})")
    options = rules[rule_id][0].split(" | ")
    simplifiedRule = []
    for option in options:
        if '"' in option:
            simplifiedRule.append(option[1])
        else:
            subRules = [int(rule_num) for rule_num in option.split(" ")]
            subOption = []
            for subRule in subRules:
                if rules[subRule][1] == 1:
                    subOption.append(rules[subRule][0])
                else:
                    simplifyRule(subRule, rules)
                    subOption.append(rules[subRule][0])
            subOption = joinLists(subOption)
            simplifiedRule.append(subOption)
    #print(f"\nSimplified rule {rule_id}. {rules[rule_id][0]} => {simplifiedRule}")
    rules[rule_id] = (simplifiedRule, 1)

def joinLists(listA):
    options = [""]
    for item in listA:
        #print(f"Evaluating {item}")
        if isinstance(item, str):
            #print(f"{item} was a string. Adding to {options}")
            for option_num in range(0, len(options)):
                options[option_num] += item
            #print(f"The result of addition: {options}")
        else:
            #print(f"{item} was a list. Adding to {options}")
            new_options = []
            for option in options:
                for subOption in item:
                    if isinstance(subOption, list):
                        for megaSub in subOption:
                            new_options.append(option + megaSub)
                    else:
                        new_options.append(option + subOption)
            options = new_options
            #print(f"The result of addition: {options}")
        #es.list_remove_duplicates(options)
    return options

def inRule0(word,rules):
    rule42 = []
    for stuff in rules[42][0]:
        rule42 += stuff
    rule31 = []
    for stuff in rules[31][0]:
        rule31 += stuff
    print(f"Rule42: {rule42}")
    print(f"Rule31: {rule31}")
    chunkSize = len(rule42[0])
    if len(word) % chunkSize != 0:
        print(f"Word has incorrect length")
        return False
    numChunks = int(len(word)/chunkSize)
    print(f"The chunk size is: {chunkSize}\nThe wordsize is: {len(word)} ({numChunks})")
    chunks = [word[chunkSize*(i-1):chunkSize*i] for i in range(1, numChunks + 1)]
    print(f"The chunks are: {chunks}")
    Active31 = False
    for chunkId in range(0, numChunks):
        chunk = chunks[chunkId]
        if chunkId == numChunks - 1:
            Active31 = True
        if Active31 == False:
            if not chunk in rule42:
                print(f"{chunk} did not fit in 42. Switching to 31")
                if chunkId <= numChunks/2:
                    print(f"We haven't progressed enough for 31!")
                    return False
                Active31 = True
        if Active31 == True:
            if not chunk in rule31:
                print(f"{chunk} did no fit in 31. It's dead")
                break
    else:
        return True
    return False

def main():
    rules = {}
    textStartIndex = 0
    for rule in lines:
        if not rule:
            textStartIndex = lines.index(rule) + 1
            break
        rule_id, basic_rule = rule.split(": ")
        rule_id = int(rule_id)
        rules[rule_id] = (basic_rule, 0)
    simplifyRule(42, rules)
    simplifyRule(31, rules)
    correct_texts = 0
    for textIndex in range(textStartIndex, len(lines)):
        print(f"Checking if {lines[textIndex]} fits")
        if inRule0(lines[textIndex], rules):
            print("True")
            correct_texts += 1
        else:
            print("False")
    print(f"Number of matching texts: {correct_texts}")

main()
