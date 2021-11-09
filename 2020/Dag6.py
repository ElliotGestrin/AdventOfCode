file = open("Filer\Dag6.txt")

def validateGroup(groupAnswers):
    mega = {}
    existing = []
    for groupAnswer in groupAnswers:
        for key in groupAnswer.keys():
            mega[key] = 1
    for key in mega:
        for groupAnswer in groupAnswers:
            if not key in groupAnswer:
                break
        else:
            existing.append(key)
    return existing

def main():
    lines = [k.strip() for k in file.readlines()]
    answers = []
    groupAnswer = []
    answer = {}

    for line in lines:
        if not line:
            answers.append(validateGroup(groupAnswer))
            groupAnswer = []
        else:
            for char in line:
                answer[char] = 1
            groupAnswer.append(answer)
            answer = {}

    sum = 0
    for group in answers:
        sum += len(group)

    print(answers[-1])
    print(sum)

main()
