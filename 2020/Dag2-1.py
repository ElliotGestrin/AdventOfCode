file = open("Filer\Dag2-1.txt")
valid_passwords = 0
total_passwords = 0

for line in file:
    total_passwords += 1

    policy, password = line.split(": ")
    numbers, letter = policy.split(" ")
    min, max = numbers.split("-")
    min = int(min)
    max = int(max)

    count = password.count(letter)

    if(count >= min and count <= max):
        valid_passwords += 1
    else:
        pass

print("There were in total " + str(total_passwords) + " passwords.")
print("Out of those " + str(valid_passwords) + " were valid.")
