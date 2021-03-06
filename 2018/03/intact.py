#!/usr/bin/env python3.7
import sys

lines = [claim.rstrip('\n') for claim in open(sys.argv[1])]
canvas = [[0 for x in range(1000)] for y in range(1000)] 

for claim in lines:
    x = int(claim.split(' ')[2].split(',')[0])
    y = int(claim.split(' ')[2].split(',')[1][:-1])
    a = int(claim.split(' ')[3].split('x')[0])
    b = int(claim.split(' ')[3].split('x')[1])
    for i in range(x, x + a):
        for j in range(y, y + b):
            canvas[i][j] += 1

def checkIntact(canvas, claim):
    x = int(claim.split(' ')[2].split(',')[0])
    y = int(claim.split(' ')[2].split(',')[1][:-1])
    a = int(claim.split(' ')[3].split('x')[0])
    b = int(claim.split(' ')[3].split('x')[1])
    for i in range(x, x + a):
        for j in range(y, y + b):
            if canvas[i][j] > 1:
                return False
    # If we get here the claim is intact!
    return True

for claim in lines:
    if checkIntact(canvas, claim):
        print(claim.split(' ')[0][1:])
        break
