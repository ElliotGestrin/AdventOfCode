import single_line_reader as slr
import elliot_standard_library as es
from graphics import *
import time

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
    for difference in jolt_list[1:]:
        sum += difference
    return sum

def generate_ypos(adapters):
    y_positions = {}
    current_y = 0
    for adapter in adapters:
        current_y += 20
        y_positions[adapter] = current_y
    return y_positions

def startCanvas(adapters, x_step, x_offset):
    y_positions = generate_ypos(adapters)
    x_width = len(adapters) * x_step + 2 * x_offset
    y_width = len(adapters) * 20 + 20
    canvas = GraphWin("AdapterPath", x_width, y_width)
    canvas.setCoords(0,0,x_width, y_width)
    for adapter in adapters:
        text_point = Point(x_offset / 2, y_positions[adapter])
        label = Text(text_point, adapter)
        label.setSize(8)
        label.draw(canvas)
    current_x = x_offset
    for step in range(0, len(adapters)):
        if step == 0:
            startPoint = Point(current_x, y_positions[0])
            startCir = Circle(startPoint, 4)
            startCir.setFill("Red")
            startCir.setOutline("Red")
            startCir.draw(canvas)
        elif step == len(adapters) - 1:
            endPoint = Point(current_x, y_positions[max(adapters)])
            endCir = Circle(endPoint, 4)
            endCir.setFill("Green")
            endCir.setOutline("Green")
            endCir.draw(canvas)
        else:
            for adapter in adapters:
                adaptPoint = Point(current_x, y_positions[adapter])
                adaptCir = Circle(adaptPoint, 4)
                adaptCir.setFill("Blue")
                adaptCir.setOutline("Blue")
                adaptCir.draw(canvas)
        current_x += x_step
    return canvas

def drawLine(pre_jolt_list, sub_jolt_list, current_x, x_step, y_positions, canvas):
    pre_adap = calc_current_jolt(pre_jolt_list)
    sub_adap = calc_current_jolt(sub_jolt_list)
    pre_point = Point(current_x, y_positions[pre_adap])
    sub_point = Point(current_x + x_step, y_positions[sub_adap])
    line = Line(pre_point, sub_point)
    line.setWidth(3)
    line.setFill("Blue")
    line.draw(canvas)

def showNode(jolt_list, current_x, y_positions, canvas):
    adapter = calc_current_jolt(jolt_list)
    textPoint = Point(current_x, y_positions[adapter] + 10)
    text = Text(textPoint, jolt_list[0])
    text.setSize(8)
    text.draw(canvas)

def main():
    adapters = lines
    adapters.append(max(adapters) + 3)
    adapters.append(0)
    adapters.sort()
    x_offset = 30
    x_step = 30
    canvas = startCanvas(adapters, x_offset, x_step)
    time.sleep(1)
    y_positions = generate_ypos(adapters)
    current_x = x_offset
    jolt_lists = [[1,0]]
    while(not is_done(adapters, jolt_lists)):
        new_jolts = []
        for jolt_list in jolt_lists:
            current_jolt = calc_current_jolt(jolt_list)
            new_additions = generate_next_possibilities(adapters, jolt_list, current_jolt)
            if new_additions:
                new_jolts += new_additions
                for main_jolt_list in new_additions:
                    for sub_jolt_list in new_jolts:
                        if main_jolt_list == sub_jolt_list:
                            break
                        if calc_current_jolt(main_jolt_list) == calc_current_jolt(sub_jolt_list):
                            main_jolt_list[0] += sub_jolt_list[0]
                            new_jolts.remove(sub_jolt_list)
                for new_jolt in new_jolts[-len(new_additions):]:
                    drawLine(jolt_list, new_jolt, current_x, x_step, y_positions, canvas)
                    time.sleep(0.2)
                time.sleep(0.3)
            else: #No possibilities => completed
                new_jolts.append(jolt_list)
                for sub_jolt_list in new_jolts:
                    if jolt_list == sub_jolt_list:
                        break
                    if calc_current_jolt(jolt_list) == calc_current_jolt(sub_jolt_list):
                        sub_jolt_list[0] += jolt_list[0]
                        new_jolts.remove(jolt_list)
                drawLine(jolt_list, jolt_list, current_x, x_step, y_positions, canvas)
                showNode(jolt_list, current_x, y_positions, canvas)
                time.sleep(0.3)
        jolt_lists = new_jolts.copy()
        current_x += x_step
        #for jolt_list in jolt_lists:
        #    drawLine(jolt_list, jolt_list, current_x, x_step, y_positions, canvas)
        #    time.sleep(0.2)
    total_arr = 0
    for jolt_list in jolt_lists:
        total_arr += jolt_list[0]
    #es.printlist(jolt_lists)
    print(total_arr)
    time.sleep(50)

main()
