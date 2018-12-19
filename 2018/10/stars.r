#!/usr/bin/env Rscript

createImage <- function(positions, i) {
		png(filename="stars.png")
		par(mar = c(0,0,1,0))
		par(pch=19)
		plot(positions, ylim = rev(range(positions[1,])), asp=1, main=i)
		dev.off()
}

positions = read.csv("pos.txt")
velocities = read.csv("vel.txt")

previousVariation <- var(positions[,1])

i <- 0
repeat {
	positions <- positions + velocities
	currentVariation <- var(positions[,1])

	if (previousVariation < currentVariation) {
		createImage(positions - velocities, i)
		break
	}
	previousVariation <- currentVariation
	i <- i + 1
}
