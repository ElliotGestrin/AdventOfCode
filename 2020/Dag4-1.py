def validate(key, value):
    try:
        if key == "byr":
            return len(value) == 4 and 1920 <= int(value) <= 2002
        if key == "iyr":
            return len(value) == 4 and 2010 <= int(value) <= 2020
        if key == "eyr":
            return len(value) == 4 and 2020 <= int(value) <= 2030
        if key == "hgt":
            if value[-2:] == "cm":
                return 150 <= int(value[:-2]) <= 193
            if value[-2:] == "in":
                return 59 <= int(value[:-2]) <= 76
        if key == "hcl":
            if value[0] != "#":
                return False
            for char in value[1:]:
                if not char in ["0","1","2","3","4","5","6","7","8","9", "a","b","c","d","e","f"]:
                    return False
            return True
        if key == "ecl":
            return value in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]
        if key == "pid":
            if len(value) != 9:
                return False
            for char in value:
                if not char in ["0","1","2","3","4","5","6","7","8","9"]:
                    return False
            return True
        if key == "cid":
            return True
    except ValueError:
        return False

def main():
    file = open("Filer\Dag4.txt")

    passports = []
    password = {}

    for line in file:
        line = line.strip()
        if not line:
            password["cid"] = "123"
            passports.append(password)
            password = {}
        else:
            info = line.split(" ")
            for item in info:
                trait, value = item.split(":")
                password[trait] = value
    if password:
        password["cid"] = "123"
        passports.append(password)
    correct = 0

    for password in passports:
            if len(password) == 8:
                for key in password.keys():
                    if not validate(key, password[key]):
                        #print(password)
                        #print("Failed for key: " + key)
                        break
                else:
                    correct += 1
    print(correct)

main()
