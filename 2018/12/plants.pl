#!/usr/bin/env perl
use warnings;
use strict;

chomp(my @lines = <>);

my $state = shift @lines;
$state =~ s/initial state: //;
shift @lines;

my %rules = map { substr($_,0,5) => substr($_,-1,1) } @lines;

my $firstPot = 0;

for (my $generation=0; $generation<20; $generation++) {
    # Prepend and append four empty pots to last state.
    $state = "....".$state."....";
    $firstPot -= 2; # only the first two makes it to the next state...

    my $next_state = "";

    my $length = length($state)-4;
    for (my $i=2; $i<$length; $i++) {
        my $key = substr($state, $i, 5);
        $next_state .= $rules{$key};
    }
    $next_state =~ s/(.*)\.+$/$1/;
    my $prev_length = length($next_state);
    $next_state =~ s/^\.+(.*)/$1/;
    $firstPot += $prev_length - length($next_state);
    $state = $next_state;
}

sub calculateSum {
	my $state = shift;
	my $value = shift;
    my $sum = 0;
    for (split //, $state) {
        if ($_ eq '#') {
            $sum += $value;
        }
        $value++;
    }
    return $sum;
}

print "12.1: ".calculateSum($state, $firstPot)."\n";

