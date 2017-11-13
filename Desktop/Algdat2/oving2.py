#!/usr/bin/python3

from sys import stdin
from itertools import repeat


def merge(decks):
    # SKRIV DIN KODE HER
    mittOrd = ""

    while(len(decks) != 0 ):
        minsteVerdi = decks[0][0][0]
        minsteVerdiIndex = 0 #i vårt tilfelle kan minsteVerdiIndex være 0,1,2,3 eller 4. 
        for i in range(0,len(decks)):
            
            if (decks[i][0][0] < minsteVerdi):
                minsteVerdi = decks[i][0][0]
                minsteVerdiIndex = i

        mittOrd += decks[minsteVerdiIndex][0][1] #legger til bokstaven som minsteverdiindex hører sammen med
        decks[minsteVerdiIndex].pop(0) #popper første element i lista som har den minste verdien. Altså popper minste verdien som er i decks

        if(len(decks[minsteVerdiIndex]) == 0): #sjekker at lengden på lista som den minste verdien er i, er 0
            decks.pop(minsteVerdiIndex)

        #print(minsteVerdi)
        
        

    #print(mittOrd)
    #print(len(decks))
    #print(decks)

    #print(decks)
    return mittOrd

def main():
    # Read input.
    decks = []
    for line in stdin:
        (index, csv) = line.strip().split(':')
        deck = list(zip(map(int, csv.split(',')), repeat(index)))
        decks.append(deck)
    # Merge the decks and print result.
    print(merge(decks))


if __name__ == "__main__":
    main()