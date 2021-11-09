import elliot_standard_library as es

file = open("Filer\Dag25.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    DoorPublic = int(lines[1])
    KeyPublic = int(lines[0])
    KeySecretLoop = 0
    KeySubjectNumber = 7
    KeyValue = 1
    while KeyValue != KeyPublic:
        KeySecretLoop += 1
        KeyValue *= KeySubjectNumber
        KeyValue = KeyValue % 20201227
        if KeySecretLoop % 10000 == 0:
            print(f"Key {KeySecretLoop}: {KeyValue}")
    print(f"The keys secretloops is: {KeySecretLoop}")
    DoorSecretLoop = 0
    DoorSubjectNumber = 7
    DoorValue = 1
    while DoorValue != DoorPublic:
        DoorSecretLoop += 1
        DoorValue *= DoorSubjectNumber
        DoorValue = DoorValue % 20201227
    print(f"The doors secretloops is: {DoorSecretLoop}")
    DoorSubjectNumber = KeyPublic
    DoorValue = 1
    for i in range(0, DoorSecretLoop):
        DoorValue *= DoorSubjectNumber
        DoorValue = DoorValue % 20201227
    KeySubjectNumber = DoorPublic
    KeyValue = 1
    for i in range(0, KeySecretLoop):
        KeyValue *= KeySubjectNumber
        KeyValue = KeyValue % 20201227
        #print(f"Key {KeySecretLoop}: {KeyValue}")
    print(f"The encryption key is:\nKey: {KeyValue}\nDoor: {DoorValue}")

main()
