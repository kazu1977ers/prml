#include "float_fs.h"

int
init_step(Data *dat, FInfo *fs, int *eval_time, int mode, int fold,
					int knum, int method)
{
	int i;
	
	/* 特徴集合の情報を初期化 */
	for(i = 0; i < dat->dim; i++){
		fs->C[i] = 0.0;
		fs->best.fi[i] = i;
	}

	/* 入力されたデータが正しくない場合のエラー処理 */
	if(dat->dim < 2){
		fs->best.num = 1;
		fs->best.fi[0] = 0;
		fs->best_rate = k_nn_disc(dat, fs, fold, knum);

		fs->sel.num = fs->best.num;
		fs->sel.fi[0] = fs->best.fi[0];
		fs->C[0] = fs->best_rate;

		fprintf(stderr, "\n<X> Only one feature is left\n");
		fflush(stderr);

		return 1;
	}
	
	/* パラメータの初期化	*/
	if((method == SBFS) || (method == SBS)){		/* Backward型の初期化 */
		
		fprintf(stderr, "\n* Backward type initialization\n");
		
		fs->sel.num    = dat->dim;
		fs->cur.num    = dat->dim;
		fs->rej.num    = 0;
		
		for(i = 0; i < dat->dim; i++){
			fs->sel.fi[i] = i;
			fs->cur.fi[i] = i;
			fs->rej.fi[i] = 0;
		}
		
		/* 全ての特徴を用いた時の識別率を計算する */
		fs->C[dat->dim - 1] = k_nn_disc(dat, fs, fold, knum);
		fs->best_rate = fs->C[dat->dim - 1];
		fs->best.num   = dat->dim;
		
		if(method == SBFS)
			fprintf(stderr, "\n< Start SBFS algorithm >\n\n");
		else
			fprintf(stderr, "\n< Start SBS algorithm >\n\n");
		fflush(stderr);

		print_fs(fs, *eval_time, mode);
		
	}
	else{		/* Forward型の初期化 */
		
		fprintf(stderr, "\n* Forward type initialization\n");
		
		fs->sel.num    = 0;
		fs->cur.num    = 0;
		fs->rej.num    = dat->dim;
		fs->best_rate  = 0.0;
		fs->best.num   = 0;
		
		for(i = 0; i < dat->dim; i++){
			fs->sel.fi[i] = 0;
			fs->cur.fi[i] = 0;
			fs->rej.fi[i] = i;
		}
		
		if(method == SFFS)
			fprintf(stderr, "\n< Start SFFS algorithm >\n\n");
		else
			fprintf(stderr, "\n< Start SFS algorithm >\n\n");
		fflush(stderr);

		print_fs(fs, *eval_time, mode);
		
	}

	return 0;
}
