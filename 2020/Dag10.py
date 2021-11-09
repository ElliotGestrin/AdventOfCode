import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag10.txt")
lines = [int(line.strip()) for line in file.readlines()]

def pick_adapter(adapter_list):
    min_ad = 1000
    for adapter in adapter_list:
        if adapter < min_ad:
            min_ad = adapter
    return(min_ad)

def generate_possible_pick()

def main():
    adapters = lines
    jolt_differences = []
    current_jolt = 0
    while adapters:
        smallest_ad = pick_adapter(adapters)
        jolt_differences.append(smallest_ad - current_jolt)
        current_jolt = smallest_ad
        adapters.remove(smallest_ad)
    jolt_differences.append(3)
    print("Finished!")
    print(jolt_differences)
    print("Value: ", jolt_differences.count(1) * jolt_differences.count(3))

main()
