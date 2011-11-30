/*
	nCkの組合せリストを生成する。但し、unsigned intの上限(UINT_MAX) =
	4294967295 通りの組合せまで求めることができる。
	Time-stamp: <12:24:45 2003/11/5>
*/
#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

int main(int argc, char **argv)
{
	int          i, j;
	int          n, k;
	unsigned int size;
	int          **combi;

	if(argc < 3){
		fprintf(stderr, "\n[使用法] : gencomb (num1) (num2)\n");
		exit(1);
	}

	n = atoi(argv[1]);
	k = atoi(argv[2]);
	
	combi = gen_comb(n, k, &size);
	
	for(i = 0; i < size; i++){
		printf("( ");
		for(j = 0; j < k; j++){
			printf("%3d", combi[i][j] + 1);
			if(j != k-1)
				printf(" , ");
		}
		printf(" )\n");
	}
	printf("合計 %5d 通り\n", size);

	free_int_matrix(combi);

	exit(0);
}
