file = open("Filer\Dag1-1.txt")
expenses = []

for line in file:
    expenses.append(int(line))

print("All in all " + str(len(expenses)) + " values")
print(expenses)

for i in range(0, len(expenses)):
    for j in range(0, len(expenses)):
        for y in range(0, len(expenses)):
            sum = expenses[i] + expenses[j] + expenses[y]
            #print("\n" + str(expenses[i]) + " + " + str(expenses[j]) + " = " + str(sum))
            if sum == 2020:
                print("\nFound em!\n")
                print(str(expenses[i]) + "\n")
                print(str(expenses[j]) + "\n")
                print(str(expenses[y]) + "\n")
                print(expenses[i] * expenses[j] * expenses[y])
                break
        else:
            continue
        break
    else:
        continue
    break
