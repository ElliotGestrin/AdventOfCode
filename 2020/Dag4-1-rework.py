file = open("Filer\Dag4.txt")

def build_passports():
    lines = [line.strip() for line in file.readlines()]
    passports = []
    passport = {}
    for line in lines:
        if not line:
            passports.append(passport)
            passport = {}
        else:
            for pair in line.split(" "):
                key, value = pair.split(":")
                passport[key] = value
    return(passports)

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

def isValid(passport):
    passport["cid"] = ":P"
    if len(passport) != 8:
        return False
    for key, value in passport.items():
        if not validate(key, value):
            return False
    return True

def main():
    correct = [passport for passport in build_passports() if isValid(passport)]
    print(len(correct))

main()
