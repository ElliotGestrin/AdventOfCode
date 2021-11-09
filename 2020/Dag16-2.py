import elliot_standard_library as es

file = open("Filer\Dag16.txt")
lines = [(line.strip()) for line in file.readlines()]

def fitsRules(stat, rules):
    for rule in rules.values():
        if stat in rule:
            return True
    return False

def getInvalids(ticket, rules):
    invalids = []
    for value in ticket.values():
        if not fitsRules(value, rules):
            invalids.append(value)
    return invalids

def extractRuleValues(rule_range):
    total_range = []
    for rangey in rule_range.split(" or "):
        lowerLim = int(rangey.split("-")[0])
        upperLim = int(rangey.split("-")[1])
        total_range += range(lowerLim, upperLim + 1)
    return(total_range)

def generateRules(lines):
    rules = {}
    for line in lines:
        if not line:
            break
        else:
            rule_name = line.split(": ")[0]
            rule_values = extractRuleValues(line.split(": ")[1])
            rules[rule_name] = rule_values
    return rules

def generateTicket(line):
    rule_num = 0
    ticket = {}
    for rule_val in line.split(","):
        ticket[rule_num] = int(rule_val)
        rule_num += 1
    return ticket

def getIndex(lines):
    myTicket = 0
    for index in range(0, len(lines)):
        if not lines[index]:
            myTicket = index + 2
            break
    nearbyTickets = myTicket + 3
    return(myTicket, nearbyTickets)

def getRuleOptions(rule_value, rules):
    rule_options = []
    for rule_name, rule_span in rules.items():
        if rule_value in rule_span:
            rule_options.append(rule_name)
    return rule_options

def mappingComplete(rules_mapping, rules):
    if len(rules_mapping) != len(rules):
        return False
    for rule_option in rules_mapping.values():
        if len(rule_option) != 1:
            return False
    return True

def main():
    rules = generateRules(lines)
    myTicketIndex, nearbyTicketsIndex = getIndex(lines)
    okayTickets = []
    for ticketIndex in range(nearbyTicketsIndex, len(lines)):
        ticket = generateTicket(lines[ticketIndex])
        invalids = getInvalids(ticket, rules)
        if not invalids:
            okayTickets.append(ticket)
    rules_mapping = {}
    checkedTickets = 0
    while not mappingComplete(rules_mapping, rules):
        for ticket in okayTickets:
            checkedTickets += 1
            #print(rules_mapping)
            for rule_id, rule_value in ticket.items():
                if len(rules_mapping.get(rule_id, [])) == 1:
                    continue
                rule_options = getRuleOptions(rule_value, rules)
                for alreadyFound in rules_mapping.values():
                    if alreadyFound in rule_options:
                        rule_options.remove(alreadyFound)
                #print("     ", rule_id, ", ", rule_value, "=> ", rule_options)
                if not rule_id in rules_mapping:
                    rules_mapping[rule_id] = rule_options
                else:
                    for rule in rules_mapping[rule_id]:
                        if rule not in rule_options:
                            rules_mapping[rule_id].remove(rule)
            for rule_id, rule_options in rules_mapping.items():
                if len(rule_options) == 1:
                    for subRule_id, subRule_options in rules_mapping.items():
                        if rule_id == subRule_id:
                            continue
                        if rule_options[0] in subRule_options:
                            subRule_options.remove(rule_options[0])
            if mappingComplete(rules_mapping, rules):
                break
    print("The rules mapping is: ", rules_mapping)
    myTicket = generateTicket(lines[myTicketIndex])
    print("It took ", checkedTickets, " tickets (out of ", len(okayTickets), " tickets) to crack the code.")
    departure_mult = 1
    for rule_id, rule_value in myTicket.items():
        isDeparture = rules_mapping[rule_id][0].split(" ")[0] == "departure"
        print(rules_mapping[rule_id], ": ", isDeparture)
        if isDeparture:
            departure_mult *= rule_value
    print(departure_mult)


main()
