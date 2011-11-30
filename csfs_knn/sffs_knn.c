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
	read_opt(argc, argv, &dat, &fs, SFFS, &tmode, &knum, &fold, &seed);

	/* 各分割におけるデータの個数を初期化 */
	dat.split_num = set_split(fold, dat.total);
	
	/* 配列の初期化 */
	alloc_prm(&dat, &fs);

	/* データの読み込み */
	read_data(&dat);

	/* 実験の初期化 */
	shuffle(&dat, seed);
	skip_flag = init_step(&dat, &fs, &eval_time, INITIAL, fold, knum, SFFS);

	if(!skip_flag){
		/* SFFS開始 */
		do{
			/* 
				 Forward Step: 
				 SFSで評価関数の値を最も増加させる特徴を一つ追加する。
				 削除したらBackward Stepへ。 
			*/
			sfs(&dat, &fs, &ans_value, fold, &target,	&eval_time, knum);
			ans_fi = target;
			
			/* 最も重要な特徴を一つ追加した特徴集合を作成 */
			add_one(&fs, target, ans_value);
			
			print_fs(&fs, eval_time, FORWARD);
			
			/* tmodeモードの時は、最も評価関数の値が大きい特徴集合を保存する */
			if(tmode)
				eval_best(&fs);
			
			/* sel.num <= 2の時は以下の処理を飛ばす。*/
			if(fs.sel.num <= 2)
				continue;
			
			/* 
				 Backward Step: 
				 選択された特徴集合から一つ特徴の除き評価関数の値が増加すれば削除。
				 更新されない場合にはBackward Stepへ。
			*/
			while(1){
				
				/* 選択されている特徴集合から一つ削除する */
				check(&dat, &fs, &target, &ans_value, fold, &eval_time, SFFS, knum);
				
				/* 選択した特徴を削除しても評価関数の値が増えない場合にはstep1へ */
				if(ans_value <= fs.C[fs.sel.num - 2]){
					
					/* 指定された特徴数に達した場合には終了 */
					if(fs.sel.num == fs.ext_num){
						print_fs(&fs, eval_time, FINAL);
						tflag = 1;
					}
					break;
				}
				else{
					/* 削除した特徴集合を保存する */
					remove_one(&fs, target, ans_value);
					
					print_fs(&fs, eval_time, BACKWARD);

					/* tmodeモードの時は、最も評価関数の値が大きい特徴集合を保存する */
					if(tmode)
						eval_best(&fs);
					
					/* sel.num <= 2の時はbackwardの処理を飛ばす */
					if(fs.sel.num <= 2)
						break;
				}
				
			}; /* forward step のループ */
			
		}while(!tflag); /* 全体のループ */
	}
	
	/* 選択した特徴集合を出力する */
	output(&fs, tmode, eval_time);
	
	/* 確保した配列を解放する */
	free_prm(&dat, &fs);

	exit(0);
}
