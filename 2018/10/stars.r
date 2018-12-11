#!/usr/bin/env Rscript

positions = read.csv("pos.txt")
velocities = read.csv("vel.txt")

par(mar = c(0,0,1,0))
par(pch=19)

minVar <- var(positions[,1])

i <- 0
repeat {
	positions <- positions + velocities
	currentVar <- var(positions[,1])

	if (minVar > currentVar) {
		minVar <- currentVar
	} else {
		# If the variation starts to rise, last position was correct.
		# Plot the coordinates.
		positions <- positions - velocities
		plot(positions, ylim = rev(range(positions[1,])), asp=1, main=i)
		break
	}
	i <- i + 1
}

