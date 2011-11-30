#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int    pos;
	double val;

	if(argc < 3){
		fprintf(stderr, "[使用法] : round <value> <position>\n");
		exit(1);
	}

	val = atof(argv[1]);
	pos = atoi(argv[2]);

	fprintf(stdout, "%f\n", roundoff(val, pos));

	exit(0);
}
	
