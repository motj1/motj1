#!/usr/local/bin/python3
from os import system

data = [[] for i in range(4)]
for j in range(1, 5):
    # with is like your try .. finally block in this case
    with open('IsPrimeForLargeTest.cpp', 'r') as file:
        # read a list of lines into data
        code = file.readlines()

    # now change the 2nd line, note that you have to add a newline
    num = str(100*(10**j)+101)
    code[32] = f"    unsigned long number = {num};\n"

    # and write everything back
    with open('IsPrimeForLargeTest.cpp', 'w') as file:
        file.writelines( code )
        
    system("gcc -O2 -o test IsPrimeForLargeTest.cpp -lstdc++")
    for i in range(10):
        system("script -q time.txt time ./test")
        with open('time.txt') as f:
            lines = f.readlines()
            line = lines[0]
            number = ""
            for letter in line:
                if letter.isnumeric() or letter == ".":
                    number += letter
                elif letter == "r":
                    break
            data[j-1].append(number)
        

print(data)

#data = [['0.11', '0.08', '0.07', '0.08', '0.08', '0.07', '0.07', '0.08', '0.07', '0.08'], ['1.18', '1.30', '1.30', '1.31', '1.16', '0.95', '0.95', '0.96', '0.94', '0.94'], ['18.03', '18.17', '18.35', '18.34', '18.23', '18.25', '18.26', '18.59', '18.29', '18.18']]

with open('index.txt', 'r') as f:
    index = int(f.readlines()[0])

with open(f'TestData{index}.txt', 'w') as file:
    for thing in data:
        file.write( ' | '.join(thing) )
        file.write('\n')

with open('index.txt', 'w') as f:
    index = f.write(str(index+1))