#!/usr/bin/env php
<?php

$players = $argv[1];
$maxMarble = $argv[2];
$scores = array_fill(0, $players, 0);

$marbles = array (0);
$currentMarbleIndex=0;

for ($marble = 1; $marble < $maxMarble; $marble++) {
	$player = $marble % $players;
	if ($marble % 23 == 0) {
		$newIndex = $currentMarbleIndex - 7;
		if ($newIndex < 0) {
			$newIndex = count($marbles)+$newIndex;
		}
		$scores[$player] += $marble;
		$scores[$player] += $marbles[$newIndex];
		array_splice($marbles, $newIndex, 1); // remove marble at index
		if ($newIndex >= count($marbles)) {
			$newIndex = 0;
		}
	} else {
		$newIndex = $currentMarbleIndex+2;
		if ($newIndex >= count($marbles)) {
			$newIndex = $newIndex - count($marbles);
		}
		array_splice($marbles, $newIndex, 0, array($marble));
	}

	$currentMarbleIndex = $newIndex;
}

echo max($scores)."\n";
