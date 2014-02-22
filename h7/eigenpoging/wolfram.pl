use strict;
use warnings;
use XML::Parser;
use LWP::Simple;
use Data::Dumper;

my $waarde = 9;
my $url    = "http://api.wolframalpha.com/v1/query?input=GF(".$waarde.")&format=html&appid=285YJQ-4XVWGLTG29";
#print $url , "\n\n";
my $xml    = get($url) or die "could not retrieve data";

my $parser = XML::Parser->new( Handlers => {
                                      Start=>\&handle_start,
                                      End=>\&handle_end,
                                      Char=>\&handle_char
});
my @data = ();#afbeelding in pc data
$parser->parse($xml);
foreach (@data){
	$_ =~ s/\R//g; #alles op een lijn easy regex
	if ($_ =~ /.*Addition table.*alt="([^"]*)/){
		#print "*$_*\n";
		#print $1;
		my @lines = ($1 =~ /([^\\n]*)/g );
		foreach (@lines){
			print "$_\n" if (length($_) > 0);
		}
		print "\n\n";
	}elsif ($_ =~ /.*Multiplication table.*alt="&times;\ ([^"]*)/){
		#print "*$_*\n";
		#print $1;
		my @lines = ($1 =~ /([^\\n]*)/g );
		print "x ";#fix voor &times;
		foreach (@lines){
			print "$_\n" if (length($_) > 0);
		}
	}
}

my $msg;
sub handle_start{
	my( $expat, $element, %attrs ) = @_;
	if($element eq "markup"){
		$msg = "";
	}
	#if ($element eq "pod"){ print $element , " started at " , $expat->current_line , "\n";	}
}
sub handle_end{
	my ( $expat, $element) = @_;
	if ($element eq "markup"){
		push @data , $msg if $msg;;
		undef $msg;
	}
	#if ($element eq "pod"){ print $element , " stopped at " , $expat->current_line , "\n";	}
}
sub handle_char{
	my ($p, $str) = @_;
    $msg .= $str;
}