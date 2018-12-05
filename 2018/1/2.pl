#!/usr/bin/env perl
use warnings;

chomp(my @lines = <>);

my %sums;
my $sum = 0;

while (42) {
	foreach(@lines) {
		$sum += $_;
		if (exists $sums{$sum}) {
			print "$sum\n";
			exit;
		}
		$sums{$sum} = 1;
	}
}

