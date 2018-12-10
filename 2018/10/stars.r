#!/usr/bin/env Rscript

positions = read.csv("pos.txt")
velocities = read.csv("vel.txt")

par(mar = c(0,0,0,0))

for (i in 1:20000) {
	positions <- positions + velocities
	if (positions[1,1] < 500 && positions[1,1] > -500) {
		plot(positions, asp=1, main=i)
	}
}

