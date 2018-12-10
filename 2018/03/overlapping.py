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

count = 0

for i in range(1000):
    for j in range(1000):
        if canvas[i][j] > 1:
            count += 1


print(count)
