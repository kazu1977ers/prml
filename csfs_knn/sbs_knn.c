#include "float_fs.h"

int main(int argc, char **argv)
{
	int          tmode, ans_fi, target, fold, knum;
	unsigned int seed;
	int          tflag = 0, eval_time = 0, skip_flag = 0;
	double       ans_value;
	Data         dat;
	FInfo        fs;

	/* 引数の読み込み */
	read_opt(argc, argv, &dat, &fs, SBS, &tmode, &knum, &fold, &seed);

	/* 各分割におけるデータの個数を初期化 */
	dat.split_num = set_split(fold, dat.total);

	/* 配列の初期化 */
	alloc_prm(&dat, &fs);

	/* データの読み込み */
	read_data(&dat);

	/* 実験の初期化 */
	shuffle(&dat, seed);
	skip_flag = init_step(&dat, &fs, &eval_time, INITIAL, fold, knum, SBS);
	
	if(!skip_flag){
		/* SBS開始 */
		while(1){
			/* 
				 Backward Step: 
				 SBSで評価関数の値を最も少なく減少させる特徴を一つ削除する。
				 削除したらFoward Stepへ。 
			*/
			sbs(&dat, &fs, &ans_value, fold, &target, &eval_time, knum);
			ans_fi = target;
			
			/* 最も不要な特徴を除いた特徴集合を作成 */
			remove_one(&fs, target, ans_value);
			
			print_fs(&fs, eval_time, BACKWARD);
			
			/* tmodeモードの時は、最も評価関数の値が大きい特徴集合を保存する */
			if(tmode)
				eval_best(&fs);
			
			if(fs.sel.num == fs.ext_num){
				print_fs(&fs, eval_time, FINAL);
				tflag = 1;
				break;
			}
			
		};  /* 全体のループ */
	}
	
	/* 選択した特徴集合を出力する */
	output(&fs, tmode, eval_time);
	
	/* 確保した配列を解放する */
	free_prm(&dat, &fs);

	exit(0);
}
