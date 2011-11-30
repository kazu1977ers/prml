#include "float_fs.h"

void output(FInfo *fs, int tflag, int time)
{
	int i;

	fprintf(stderr,
					"\n-*-*-*-*-*-*-*- RESULT -*-*-*-*-*-*-*-\n\n");
	if(tflag){
		fprintf(stderr, "Feature subsets := { ");
		for(i = 0; i < fs->best.num; i++){
			fprintf(stderr, "%d", fs->best.fi[i] + 1);
			if(i < fs->best.num - 1)
				fprintf(stderr, " ");
		}
		fprintf(stderr, " }\n\n");
		fprintf(stderr, "Selected # of features := %d\n\n", fs->best.num);
		fprintf(stderr, "Best criterion value := %.1f\n\n", fs->best_rate);
		fprintf(stderr, "Evaluation time := %6d\n\n", time);
	}
	else{
		fprintf(stderr, "Feature subsets := { ");
		for(i = 0; i < fs->sel.num; i++){
			fprintf(stderr, "%d", fs->sel.fi[i] + 1);
			if(i < fs->sel.num - 1)
				fprintf(stderr, " ");
		}
		fprintf(stderr, " }\n\n");
		fprintf(stderr, "Selected # of features := %d\n\n", fs->sel.num);
		fprintf(stderr, "Criterion(%5d) value := %.1f\n\n", 
						fs->sel.num, fs->C[fs->sel.num - 1]);
		fprintf(stderr, "Evaluation time := %6d\n\n", time);
	}

	fflush(stderr);
}
