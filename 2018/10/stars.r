#!/usr/bin/env Rscript

positions = read.csv("pos.txt")
velocities = read.csv("vel.txt")

par(mar = c(0,0,1,0))
par(pch=19)

minVar <- 1000000000000

i <- 0
repeat {
	positions <- positions + velocities

	currentVar <- var(positions[,1])

	if (minVar > currentVar) {
		minVar <- currentVar
	} else {
		plot(positions - velocities, asp=1, main=i)
		break
	}
	i <- i + 1
}

