//Enter in form n1x^n2 +/- n1x^n2 
/*./Poly '(' 1x^3 + 2x^4 - 2x^3 + 2x^18 - 12x^0 + 14x^0 ')(' 1x^3 + 2x^4 - 2x^3 + 2x^18 - 12x^0 + 14x^0 ')'*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { char result[300]; } res;
typedef struct { int nomials[200]; } SimplifyStore;
typedef struct { int number[10]; int num; char *args[10][500]; } spli;
typedef struct { res result; SimplifyStore StoreInfo; } StoreThing;

StoreThing simplify(int argc, char *argv[]) {
    res result;
    SimplifyStore nom = { { 0 } }; // The index is the power and the number is the number before
    int n1, n2;
    char *ptr;
    char delim[] = "x^";
    ptr = strtok(argv[0], delim);
    n1 = atoi(ptr);
    ptr = strtok(NULL, delim);
    n2 = atoi(ptr);
    nom.nomials[n2] += n1;
    for (int i=2; i<argc; i+=2) {
        ptr = strtok(argv[i], delim);
        n1 = atoi(ptr);
        ptr = strtok(NULL, delim);
        n2 = atoi(ptr);
        nom.nomials[n2] += (!strcmp(argv[i-1], "+"))? n1:-n1;
    }
    SimplifyStore StoreInfo = nom;
    int count = 0;
    char sign;
    result.result[0] = '\0';
    for (int i=99; i > -1; i--) {
        if (nom.nomials[i] != 0) { 
            sign = (nom.nomials[i] < 0)? '-':'+';
            if (count == 0) sign = ' ';
            sprintf(result.result, "%s%c %dx^%d ", result.result, sign, (nom.nomials[i] < 0 && count != 0)? nom.nomials[i]*-1:nom.nomials[i], i); 
            count ++; 
        }
    }
    StoreThing StoreTotal = { result, StoreInfo };
    return StoreTotal;
}

SimplifyStore simplifyAll(SimplifyStore numbers[], int num, _Bool print) {
    // TODO: Fix this
    int largest = 0;
    for (int i=num; i>-1; i--) {
        for (int j=99; j > -1; j--) {
            if (numbers[i].nomials[j] != 0) { 
                largest += j;
                break; 
            }
            // numbers[i-1].nomials[j] += numbers[i].nomials[j];
        }
    }
    /*
    For this for loop I need to find a way to save the multiplication over the iterations to multiply all of the values together
    Also fix it.
    */
    SimplifyStore multiply = { { 0 } };//[largest+1] = { 0 };
    for (int j=0; j < largest+1; j++) { // What were trying to get, the number
        for (int i=num; i>0; i--) { // num not 2
            for (int k=0; k < j+1; k++) {
                if (numbers[i].nomials[k] != 0 && numbers[i-1].nomials[j-k] != 0) {
                    multiply.nomials[j] += numbers[i].nomials[k] * numbers[i-1].nomials[j-k];
                }
            }
        }
    }
    int count = 0;
    char sign;
    res result;
    result.result[0] = '\0';
    for (int i=largest+1; i > -1; i--) {
        if (multiply.nomials[i] != 0) { 
            sign = (multiply.nomials[i] < 0)? '-':'+';
            if (count == 0) sign = ' ';
            sprintf(result.result, "%s%c %dx^%d ", result.result, sign, (multiply.nomials[i] < 0 && count != 0)? (multiply.nomials[i]*-1)/2:multiply.nomials[i]/2, i); 
            count ++; 
        }
    }
    if (print)
        printf("SimpAll: %s\n", result.result);
    return multiply;
}

spli JoinAndSplit(int argc, char *argv[]) {
    // printf("JoinAndsplit\n");
    spli splited;
    splited.num = 0;
    // printf("Inited Splited\n");
    for (int i=2; i<argc; i++) {
        // printf("Loop %d\n", i);
        // printf("argv[i]: %s\n", argv[i]);
        if (!strcmp(argv[i], ")(")) {
            splited.num ++; continue;
        } else if (argv[i][0] == ')' || argv[i][0] == '(')
            continue;
        // printf("If after\n");
        splited.args[splited.num][splited.number[splited.num]] = argv[i];
        // printf("Argv[i] assigned after\n");
        splited.number[splited.num] ++;
        // printf("Increment after\n");
    }
    // printf("Returning \n");
    return splited;
}

int main(int argc, char *argv[]) {
    spli splitted = JoinAndSplit(argc, argv);
    StoreThing simple;
    SimplifyStore numbers[10];
    SimplifyStore buf[2];
    for (int i=0; i<splitted.num+1; i++) {
        simple = simplify(splitted.number[i], splitted.args[i]);
        printf("%s\n", simple.result.result);
        numbers[i] = simple.StoreInfo;
    }
    for (int i=splitted.num; i>0; i--) {
        buf[0] = numbers[i-1];
        buf[1] = numbers[i];
        numbers[i-1] = simplifyAll(buf, 2, (i != 1)? 0:1);
    }
    return 0;
}