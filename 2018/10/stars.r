#!/usr/bin/env Rscript

positions = read.csv("pos.txt")
velocities = read.csv("vel.txt")


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
		png(filename="stars.png")
		par(mar = c(0,0,1,0))
		par(pch=19)
		plot(positions, ylim = rev(range(positions[1,])), asp=1, main=i)
		dev.off()
		break
	}
	i <- i + 1
}

