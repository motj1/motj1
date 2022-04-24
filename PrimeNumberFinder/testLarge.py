#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Requirements:
    python3
    gcc
It is recomended that you have this in a new folder for ease of viewing.

This code will get the times of the prime number finding code and put the results into a text file called TestData and adds a number to the end,
this can be removed by comenting out the lines 45-53 and adding back:
with open('TestData.txt', 'w') as file:
    for thing in data:
        file.write( ' | '.join(thing) )
        file.write('\n')
        
If you would like the number you must create a text file called index.txt, this will be included in this repository.
"""
from os import system

data = [[] for i in range(4)]
for j in range(1, 5):
    with open('IsPrimeForLargeTest.cpp', 'r') as file:
        code = file.readlines()

    num = str(100*(10**j)+101)
    code[32] = f"    unsigned long number = {num};  // This number must be odd for the code to find primes\n"

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
