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
for (x = 0; x < 300; x++) {
	for (y = 0; y < 300; y++) {
		fuelCells[x][y] = powerLevel(x+1, y+1);
	}
}

def gridSum = { int x, int y, int s ->
	sum = 0
	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			sum += fuelCells[x+a][y+b];
		}
	}
	return sum
}

def borderSum = { int x, int y, int s ->
	sum = 0
	for (a = 0; a < s; a++) {
		sum += fuelCells[x+s-1][y+a];
	}
	for (a = 0; a < s-1; a++) {
		sum += fuelCells[x+a][y+s-1];
	}
	return sum
}

def maxX = 0
def maxY = 0
def maxValue = 0;

for (x = 0; x < 300-3; x++) {
	for (y = 0; y < 300-3; y++) {
		sum = gridSum(x, y, 3)
		if (sum > maxValue) {
			maxX = x+1
			maxY = y+1
			maxValue = sum
		}
	}
}

print "11.1: "
print maxX
print "," 
println maxY

maxX = 0
maxY = 0
maxValue = 0
def maxSize = 0

for (x = 0; x < 300; x++) {
	for (y = 0; y < 300; y++) {
		maxSquare = Math.min(300-y, 300-x)
		sum = 0
		for (s = 1; s <= maxSquare; s++) {
			sum += borderSum(x, y, s)
			if (sum > maxValue) {
				maxX = x+1
				maxY = y+1
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
