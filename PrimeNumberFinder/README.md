This folder contains the IsPrimeFullyOptamised.cpp, the main code and the python code to test said .cpp code. This IsPrime c++ code is as optamised as I could make it, feel free to make the number very large and run it overnight. To change the number it must be odd and you enter it on line 33 of the program, it is assigned as a unsigned long so it has a maximum number count of 18,446,744,073,709,551,615. On my mac I ran it using:
gcc -O2 path/to/file.cpp -lstdc++
This was because g++ does not to my knowledge have a optomisation feature.
