#include "float_fs.h"
#include <unistd.h>

void
read_opt(int argc, char **argv, Data *dat, FInfo *fs, int method, 
				 int *tmode, int *knum, int *fold, unsigned int *seed)
{
	int i;
	int num, dim;

	if(argc < 5){
		fprintf(stderr, "\n[エラー] : 引数が不足しています\n");
		fprintf(stderr, "\n[使用法] : %s <file> [-c (num)] [-tr (n1)...(nC)] [-sel (num) / -trace] (-k (num)) (-fold (num)) (-i (seed))\n", argv[0]);
		exit(1);
	}

	/* ファイル名、識別子、クラス数、サンプル数を読みとる */
	dat->filename = argv[1];

	if(is_opt(argc, argv, "-c"))
		dat->class = get_int_arg(argc, argv, "-c");
	else{
		fprintf(stderr, "\n[エラー] : クラス数が指定されていません\n");
		exit(1);
	}

	if(is_opt(argc, argv, "-tr"))
		dat->trnum = get_int_list(argc, argv, "-tr", dat->class);
	else{
		fprintf(stderr, "\n[エラー] : サンプル数が指定されていません\n");
		exit(1);
	}
		
	/* 訓練サンプルの合計を計算し、与えられたデータと一致するか確認。特徴
		 数を調べる */
	dat->total = 0;
	for(i = 0; i < dat->class; i++)
		dat->total += dat->trnum[i];

	get_size(dat->filename, &dim, &num);

	if(num != dat->total){
		fprintf(stderr, 
						"\n[エラー] : データの個数が指定された個数と一致しません\n");
		exit(1);
	}
	dat->dim = dim;

	fprintf(stderr, "\n");
	fprintf(stderr, "File    : %s\n", dat->filename);
	fprintf(stderr, "Class   : %d\n", dat->class);
	fprintf(stderr, "Sample  : ");
	for(i = 0; i < dat->class; i++)
		fprintf(stderr, "%d ", dat->trnum[i]);
	fprintf(stderr, "(%d samples total)\n", dat->total);
	fprintf(stderr, "Feature : %d\n\n", dat->dim);

	/* k近隣の個数が指定されていれば読み込む */
	fprintf(stderr, "* ");
	if(is_opt(argc, argv, "-k")){
		*knum = get_int_arg(argc, argv, "-k");
		if((*knum < 0) || (*knum > dat->total)){
			fprintf(stderr, "\n[エラー] : kの指定が正しくありません\n");
			exit(1);
		}
	}
	else{
		*knum = 1;
		fprintf(stderr, "<default> ");
	}
	fprintf(stderr, 
					"Use %d-nearest neighbor rule for criterion.\n\n", *knum);

	/* 分割数が指定されていれば読み込む */
	fprintf(stderr, "* ");
	if(is_opt(argc, argv, "-fold")){
		*fold = get_int_arg(argc, argv, "-fold");
		if((*fold < 0) || (*fold == 1) || (*fold > dat->total)){
			fprintf(stderr, "\n[エラー] : 分割数の指定が正しくありません\n");
			exit(1);
		}
		else if(*fold == 0)
			*fold = dat->total;
	}
	else{
		*fold = dat->total;		
		fprintf(stderr, "<default> ");
	}
	if(*fold == dat->total)
		fprintf(stderr, "leave-one-out technique is used.\n\n");
	else
		fprintf(stderr, "%d-fold cross validation is used.\n\n", *fold);

	/* 乱数の種が指定されていれば読み込む */
	fprintf(stderr, "* ");
	if(is_opt(argc, argv, "-i")){
		*seed = (unsigned int)get_int_arg(argc, argv, "-i");
	}
	else{
		*seed = getpid();
		fprintf(stderr, "<default> ");
	}
	fprintf(stderr, "%u is used for random seed.\n\n", *seed);
	
	/* 選択する特徴の個数が指定されていれば読み込む */
	if(is_opt(argc, argv, "-sel")){
		fs->ext_num = get_int_arg(argc, argv, "-sel");
		if(fs->ext_num == dat->dim){
			fprintf(stderr, 
							"\n[エラー] : 選択する特徴数の指定が有効ではありません\n");
			exit(1);
		}

		*tmode = 0;
		fprintf(stderr, "* Select %d features.\n\n", fs->ext_num);
	}
	else if(is_opt(argc, argv, "-trace")){
		if((method == SBFS) || (method == SBS))
			fs->ext_num = 1;
		else
			fs->ext_num = dat->dim;
		
		*tmode = 1;
		fprintf(stderr, "* Select feature subset that maximizes criterion.\n");
	}
	else{
		fprintf(stderr, "\n[エラー] : 特徴を選択する方法が指定されていません\n");
		exit(1);
	}
}
