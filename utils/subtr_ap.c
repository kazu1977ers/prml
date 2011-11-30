#include <stdio.h>
#include <stdlib.h>
#include "pattern.h"

#define  NAME_LEN  31

int main(int argc, char **argv)
{
  int     i;
  int     dim, line;
  int    *index;
  double *item, ratio;
  char    ofname[NAME_LEN];
  FILE   *fp;

  if(argc != 2){
    fprintf(stderr, "\n[使用法] : subtr_ap <file>\n");
    exit(1);
  }
  
  /* データの大きさを調べる */
  get_size(argv[1], &dim, &line);
  
  /* 準備 */
  index = new_int_vector(line);
  item  = new_double_vector(line);

  /* データを読み込む */
  if((fp = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
    exit(1);
  }
  for(i = 0; i < line; i++)
    fscanf(fp, "%d %lf", &index[i], &item[i]);

  fclose(fp);

  /* 見せかけの値の分だけ減算する */
	ratio = item[line-1] - item[line-2];
  for(i = 0; i < line; i++)
    item[i] = item[i] - ((i + 1) * ratio);

  /* 結果を出力 */
  sprintf(ofname, "%s.sbt", argv[1]);
  if((fp = fopen(ofname, "w")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", ofname);
    exit(1);
  }
  for(i = 0; i < line; i++)
    fprintf(fp, "%3d\t%10.6g\n", index[i], item[i]);

  fclose(fp);

  /* 終了処理 */
  free_int_vector(index);
  free_double_vector(item);

  exit(0);
}
