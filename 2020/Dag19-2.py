import elliot_standard_library as es

file = open("Filer\Dag19.txt")
lines = [(line.strip()) for line in file.readlines()]

def simplifyRule(rule_id, rules):
    #print(f"\n\nTrying to simplify {rule_id} ({rules[rule_id][0]})")
    options = rules[rule_id][0].split(" | ")
    simplifiedRule = []
    if rule_id in [8,11]:
        rule42 = simplifyRule(42, rules)
        rule31 = simplifyRule(31, rules)
        print(f"Handling special looping node {rule_id}")
        current_rep = []
        for i in range(0,3):
            if rule_id == 8:
                current_rep.append(rule42)
            if rule_id == 11:
                temp = []
                temp.append(rule42)
                current_rep = temp + current_rep
                current_rep.append(rule31)
            simplifiedRule.append(joinLists(current_rep))
        #print(f"Resulted in: {simplifiedRule}")
    if False:
        pass
    else:
        for option in options:
            if '"' in option:
                simplifiedRule.append(option[1])
            else:
                subRules = [int(rule_num) for rule_num in option.split(" ")]
                subOption = []
                for subRule in subRules:
                    subVal = simplifyRule(subRule, rules)
                    subOption.append(subVal)
                subOption = joinLists(subOption)
                simplifiedRule.append(subOption)
    #print(f"\nSimplified rule {rule_id}. {rules[rule_id][0]} => {simplifiedRule if len(simplifiedRule) < 200  else len(simplifiedRule)}")
    return simplifiedRule

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
    active_rule = simplifyRule(0, rules)[0]
    print(f"Rule 0 is: {active_rule}")
    correct_texts = 0
    for textIndex in range(textStartIndex, len(lines)):
        print(f"Checking if {lines[textIndex]} fits: {lines[textIndex] in active_rule}")
        if lines[textIndex] in active_rule:
            correct_texts += 1
    print(f"Number of matching texts: {correct_texts}")

main()
