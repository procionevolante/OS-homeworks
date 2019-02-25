#!/bin/awk -f
# Alternative solution
BEGIN{
	maxlen= 0;
}
{
	if (length($0) > maxlen)
		maxlen= length($0);
}
END{
	print "longest line length: " maxlen ;
	print "line number: " NR ;
}
