import elliot_standard_library as es

file = open("Filer\Dag13.txt")
lines = [(line.strip()) for line in file.readlines()]

def main():
    current_time = int(lines[0])
    timeTable = lines[1].split(",")
    busses = [(int(timeTable[index]), index) \
              for index in range(0, len(timeTable)) \
              if timeTable[index] != "x"]

    maxBus =  max([bus for bus, index in busses])
    maxIndex =  [index for bus, index in busses if bus == maxBus][0]
    current_time =  0
    while current_time % maxBus != 0:
        current_time += 1
    current_time -= maxIndex
    print("Starting count at: ", current_time)
    time_step =  maxBus
    print(maxBus, " -> ", time_step)

    perfect = False
    while(not perfect):
        perfect = True
        current_time += time_step
        if current_time % 1000000 == 0:
            print(current_time)
        for bus, index in busses:
            since_last_arrival =  current_time % bus
            if since_last_arrival == 0:
                since_last_arrival = bus
            wait = bus - since_last_arrival
            #print(bus, " arrives at +", wait, " at t = ", current_time)
            while wait < index:
                wait += bus
            if wait != index:
                perfect = False
            elif time_step % bus != 0:
                org_time_step = time_step
                while(time_step % bus != 0):
                    time_step += org_time_step
                print(bus, " -> ", time_step)

    print(current_time)

main()
