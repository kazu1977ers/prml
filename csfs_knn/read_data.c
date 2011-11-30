#include "float_fs.h"

void
read_data(Data *dat)
{
	int i, j, k;
	int index = 0;
	FILE *fp;

	/* ファイルを開きデータを読み込む */
	if((fp = fopen(dat->filename, "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", dat->filename);
		exit(1);
	}

	for(i = 0; i < dat->class; i++){

		/* クラスi番目のデータを読み込む */
		for(j = 0; j < dat->trnum[i]; j++){
			for(k = 0; k < dat->dim; k++)
				fscanf(fp, "%lf", &dat->sample[index][k]);

			dat->label[index] = i;  /* クラスラベルを確定する */
			index++;
		}

	}

	fclose(fp);
}
