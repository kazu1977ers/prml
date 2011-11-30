#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	double a, b;

	if(argc != 3){
		fprintf(stderr, "\n[エラー] : 引数が足りません\n");
		fprintf(stderr, "[使用法] : npow <num> <num>\n");
		exit(1);
	}
	
	a = atof(argv[1]);
	b = atof(argv[2]);
	
	printf("%f\n", pow(a, b));
	
	exit(0);
}
