#include "float_fs.h"

void
print_fs(FInfo *fs, int time, int mode)
{
	int i;

	if(mode == FORWARD)
		fprintf(stderr, "* forward step\n");
	else if(mode == BACKWARD)
		fprintf(stderr, "* backward step\n");
	else if(mode == INITIAL)
		fprintf(stderr, "* initial step\n");
	else
		fprintf(stderr, "* final step\n");

	fprintf(stderr, "[ (Sel/Rej)=(%3d/%3d) , Eval=%6d : C(%d)=%f ]\n",
					fs->sel.num, fs->rej.num, time, fs->sel.num, fs->C[fs->sel.num - 1]);
	
	fprintf(stderr, "+ { ");
	for(i = 0; i < fs->sel.num; i++){
		fprintf(stderr, "%d", fs->sel.fi[i] + 1);
		if(i < fs->sel.num - 1)
			fprintf(stderr, " ");
	}
	fprintf(stderr, " }\n");

	fprintf(stderr, "- { ");
	for(i = 0; i < fs->rej.num; i++){
		fprintf(stderr, "%d", fs->rej.fi[i] + 1);
		if(i < fs->rej.num - 1)
			fprintf(stderr, " ");
	}
	fprintf(stderr, " }\n\n");
}

