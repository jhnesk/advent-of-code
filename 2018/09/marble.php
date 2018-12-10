#!/usr/bin/php -dmemory_limit=800M
<?php
gc_disable();

$players = $argv[1];
$maxMarble = $argv[2];
$scores = array_fill(0, $players, 0);

class Marble {
	public $value;
	public $previous;
	public $next;

	function __construct($value) {
		$this->value = $value;
	}

	function remove() {
		$this->next->previous = $this->previous;
		$this->previous->next = $this->next;
	}
}

$currentMarble = new Marble(0);
$currentMarble->previous = $currentMarble;
$currentMarble->next = $currentMarble;

$size=1;

for ($marble = 1; $marble <= $maxMarble; $marble++) {
	$player = $marble % $players;
	if ($marble % 23 == 0) {
		for ($i = 0; $i < 7; $i++) {
			$currentMarble = $currentMarble->previous;
		}
		$scores[$player] += $marble + $currentMarble->value;
		$currentMarble->remove();
		$toDelete = $currentMarble;
		$currentMarble = $currentMarble->next;
		$toDelete->next = NULL;
		$toDelete->previous = NULL;
		unset($toDelete);
		$size--;
	} else {
		$newMarble = new Marble($marble);
		$newMarble->next = $currentMarble->next->next;
		$newMarble->previous = $currentMarble->next;

		$currentMarble->next->next->previous = $newMarble;
		$currentMarble->next->next = $newMarble;
		$currentMarble = $newMarble;
		$size++;
	}
}

echo max($scores)."\n";
