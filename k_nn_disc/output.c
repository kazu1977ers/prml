#include "k_nn_disc.h"

void 
output(Spec *spc, KNN *knn)
{
	int i, j;
	int total = 0;

	/* 識別結果を処理フォーマットで出力 */
	fprintf(stdout, "\t\t(( Discrimination Result ))\n\n");
	fprintf(stdout, "in\\out | ");

	for(i = 0; i < spc->class; i++){
		fprintf(stdout, "[ %2d]", i + 1);

		if(i != spc->class - 1)
			fprintf(stdout, "   ");
	}
	fprintf(stdout, "\n");

	fprintf(stdout, "--------");
	for(i = 0; i < spc->class; i++)
		fprintf(stdout, "--------");
	fprintf(stdout, "\n");

	for(i = 0; i < spc->class; i++){
		fprintf(stdout, "[ %2d]  |", i + 1);

		for(j = 0; j < spc->class; j++){
			if(i == j)
				total += knn->count[i][j];

			fprintf(stdout, " %4d", knn->count[i][j]);

			if(j != spc->class - 1)
				fprintf(stdout, "   ");
		}
		fprintf(stdout, "\n");
	}

	fprintf(stdout, "\n=> Recognition rate is %f\n", 
					100.0 * (double)total / (double)spc->te_total);
	fprintf(stdout, "MULOUT %4d of %4d\n", total, spc->te_total);
}

