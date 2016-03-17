#! /usr/bin/perl
# mkcwebch.pl
# Make a CWEB change file.  
# The original file is the first argument name.
# The new file is the first argument name.
# Output the change file to standard output.

if ( $#ARGV != 1 ) { &usage; die "Need two file arguments\n"; }

open(DIFF,"diff $ARGV[0] $ARGV[1] |");

# 0 before orig;
# 1 in orig;
# 2 between orig and new
# 3 in new;
# 4 after new;
$state = 0; 

LINE: while($line=<DIFF>) {
	if ( $line=~ m/^< (.*)/ ) {
		if ( $state != 1 ) {
			if ( $state == 2 ) { print "\@y\n\@z\n"; }
			if ( $state == 3 || $state == 4 ) { print "\@z\n"; }
			print "\@x\n";
		}
		print "$1\n";
		$state=1; next LINE;
	} elsif ( $line=~ m/^> (.*)/ ) {
		if ( $state != 3 ) {
			if ( $state == 0 ) { print "\@x\n"; }
			if ( $state == 4 ) { print "\@z\n\@x\n"; }
			print "\@y\n";
		}
		print "$1\n";
		$state=3; next LINE;
	} else { 
		if ( $state==1 ) {$state=2;}
		elsif ( $state==3 ) {$state=4;}
	}
}
if ( $state==3 ) {print "\@z\n";}
