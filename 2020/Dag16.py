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
    print(myTicket, nearbyTickets)
    return(myTicket, nearbyTickets)


def main():
    rules = generateRules(lines)
    invalids = []
    myTicketIndex, nearbyTicketsIndex = getIndex(lines)
    for ticketIndex in range(nearbyTicketsIndex, len(lines)):
        ticket = generateTicket(lines[ticketIndex])
        invalids += getInvalids(ticket, rules)
        print(ticketIndex, ",", ticket, ",", invalids)
    sum = 0
    for invalid in invalids:
        sum += invalid
    print(sum)


main()
