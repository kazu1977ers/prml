#include <stdio.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	if(argc < 2){
		fprintf(stderr, "\n[使用法] : gamma_val <value>\n");
		exit(1);
	}

	printf("%f\n", gamma(atof(argv[1])));

	exit(0);
}
