class line_reader:
    def __init__(self, lines):
        self.lines = lines
        self.pastIndex = []
        self.accumulator = 0
        self.index = 0

    def run(self):
        while(self.index < len(self.lines)):
            if not self.index in self.pastIndex:
                self.pastIndex.append(self.index)
                self.operation()
            else:
                break
        return(self.index, self.accumulator)

    def operation(self):
        instruction, value = self.instruction()
        if instruction == "nop":
            self.index += 1
        if instruction == "acc":
            self.index += 1
            self.accumulator += value
        if instruction == "jmp":
            self.index += value

    def instruction(self):
        line = self.lines[self.index]
        instruction, value = line.split(" ")
        value = int(value)
        return(instruction, value)
