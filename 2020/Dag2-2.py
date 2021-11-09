file = open("Filer\Dag2-1.txt")
valid_passwords = 0
total_passwords = 0

for line in file:
    total_passwords += 1
    occurrences = 0

    policy, password = line.split(": ")
    numbers, letter = policy.split(" ")
    pos1, pos2 = numbers.split("-")
    pos1 = int(pos1)
    pos2 = int(pos2)

    if password[pos1 - 1] == letter:
        occurrences += 1
    if password[pos2 - 1] == letter:
        occurrences += 1

    if(occurrences == 1):
        valid_passwords += 1
    else:
        pass

print("There were in total " + str(total_passwords) + " passwords.")
print("Out of those " + str(valid_passwords) + " were valid.")
