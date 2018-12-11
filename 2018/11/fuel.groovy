#!/usr/bin/env groovy

serialNumber = args[0].toInteger()

def hundreds = { int p ->
	Integer.toString(p).reverse().substring(2).take(1).toInteger()
}

def powerLevel = { int x, int y ->
	rackId = x + 10
	value = rackId * y
	value += serialNumber
	value *= rackId
	value = hundreds(value)
	return value - 5
}

def fuelCells = new int[300][300]
for (i = 0; i < 300; i++) {
	for (j = 0; j < 300; j++) {
		fuelCells[i][j] = powerLevel(i+1, j+1);
	}
}

def gridSum = { int x, int y, int s ->
	sum = 0
	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			sum += fuelCells[x+a-1][y+b-1];
		}
	}
	return sum
}

def maxX = 0
def maxY = 0
def maxValue = 0;

for (x = 1; x <= 298; x++) {
	for (y = 1; y <= 298; y++) {
		sum = gridSum(x, y, 3)
		if (sum > maxValue) {
			maxX = x
			maxY = y
			maxValue = sum
		}
	}
}

print "11.1: "
print maxX
print "," 
println maxY

/*
maxX = 0
maxY = 0
maxValue = 0
def maxSize = 0

for (s = 1; s <= 300; s++) {
	for (x = 1; x <= 301-s; x++) {
		for (y = 1; y <= 301-s; y++) {
			sum = gridSum(x, y, s)
			if (sum > maxValue) {
				maxX = x
				maxY = y
				maxSize = s
				maxValue = sum
			}
		}
	}
}

print "11.2: "
print maxX
print "," 
print maxY
print "," 
println maxSize
*/

