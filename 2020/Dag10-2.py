import single_line_reader as slr
import elliot_standard_library as es

file = open("Filer\Dag10.txt")
lines = [int(line.strip()) for line in file.readlines()]

def find_adapters(adapter_list, current_jolt):
    ok_ad = []
    for adapter in adapter_list:
        if current_jolt < adapter <= current_jolt + 3:
            ok_ad.append(adapter)
    return(ok_ad)

def generate_next_possibilities(adapter_list, jolt_differences, current_jolt):
    choices = find_adapters(adapter_list, current_jolt)
    new_jolts = []
    for changed in choices:
        changed_jolt = jolt_differences.copy()
        changed_jolt.append(changed - current_jolt)
        new_jolts.append(changed_jolt)
    return new_jolts

def is_done(adapter_list, jolt_lists):
    for jolt_list in jolt_lists:
            if not calc_current_jolt(jolt_list) == max(adapter_list):
                return False
    return True

def calc_current_jolt(jolt_list):
    sum = 0
    for difference in jolt_list:
        sum += difference
    return sum

def main():
    adapters = lines
    adapters.append(max(adapters) + 3)
    jolt_lists = [[0]]
    while(not is_done(adapters, jolt_lists)):
        new_jolts = []
        for jolt_list in jolt_lists:
            current_jolt = calc_current_jolt(jolt_list)
            new_jolts += generate_next_possibilities(adapters, jolt_list, current_jolt)
        for jolt_list in jolt_lists:
            if is_done(adapters, [jolt_list]):
                new_jolts.append(jolt_list)
        jolt_lists = new_jolts.copy()
    #for jolt_list in jolt_lists:
    #    print(jolt_list)
    print(len(jolt_lists))

main()
