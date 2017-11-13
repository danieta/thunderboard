#!/usr/bin/python3

from sys import stdin


def sort_list(A):
    # NOTICE: The sorted list must be returned.
    # SKRIV DIN KODE HER
    newArray = []
    while len(A) != 0: #kjører så lenge lista ikke er tom. Vi popper ut et element fra A for hver loop i whilen, så lista blir tom til slutt
        minimum = A[0]  #minimum settes til et hvilket som helst tall i lista    
        for x in A: #her er x et tall inni arrayet A. x er altså ikke en indeks, men et element i lista
            if x < minimum:
                minimum = x
        newArray.append(minimum)
        A.remove(minimum)    
    return newArray


def find(A, lower, upper):
    # NOTICE: The result must be returned.
    # SKRIV DIN KODE HER

    nyLower = A[0]
    nyUpper = A[len(A)-1]
    for i in range(0,len(A)):
        if (lower >= A[i]):
            nyLower = A[i]
        if (A[i] >= upper):
            nyUpper = A[i]
            break

    return(nyLower, nyUpper)

def main():
    input_list = []
    for x in stdin.readline().split():
        input_list.append(int(x))

    sorted_list = sort_list(input_list)
    #print(sorted_list)

    for line in stdin:
        word = line.split()
        minimum = int(word[0])
        maximum = int(word[1])
        result = find(sorted_list, minimum, maximum)
        print(str(result[0]) + " " + str(result[1]))


if __name__ == "__main__":
    main()