#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pattern.h"

#define  NAME_LEN   30

int main(int argc, char **argv)
{
  int  i, j, k;
  int  line, dim, max_byte;
  int  split, *num = NULL;
  char **buffer;
  char ofname[NAME_LEN] = {'\0'}, str[NAME_LEN] = {'\0'};
  FILE *fp = NULL;

  /* 引数の確認 */
  if(argc < 4){
    fprintf(stderr, "\n[使用法] : file_split <file> [-q (num) / -s (M) (n1)...(nM)] (-o (str))\n");
    exit(1);
  }

  strcpy(ofname, argv[1]);
  if(is_opt(argc, argv, "-o"))
    strcpy(ofname, get_char_arg(argc, argv, "-o"));

  /* 1行当たりのバイト数の最大値とデータの行の総数を調べる */
  get_max_byte(argv[1], &max_byte);
  get_size(argv[1], &dim, &line);

  /* データの分割数を設定する */
  if(is_opt(argc, argv, "-q")){
    split = get_int_arg(argc, argv, "-q");
    
    num = new_int_vector(split);
    
    for(i = 0; i < split; i++)
      num[i] = line / split;

    for(i = 0; i < (line % split); i++)
      num[i]++;
  }
  else if(is_opt(argc, argv, "-s")){
    num = get_int_arg_list(argc, argv, "-s", &split);

    j = 0;
    for(i = 0; i < split; i++)
      j += num[i];

    if(j != line){
      fprintf(stderr, "\n[エラー] : 指定された分割方法は正しくありません\n");
      exit(1);
    }
  }
  else{
    fprintf(stderr, "\n[エラー] : 分割方法を必ず指定して下さい\n");
    exit(1);
  }
  
  /* データを確保するための配列を準備する */
  buffer = new_char_matrix(line, sizeof(char)*(max_byte + 2));
  for(i = 0; i < line; i++) 
    for(j = 0; j <= sizeof(char)*max_byte + 1; j++)
      buffer[i][j] = '\0';

  /* ファイルからデータを読み込む */
  if((fp = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", argv[1]);
    exit(1);
  }
  
  for(i = 0; i < line; i++){
    for(j = 0; j <= max_byte*sizeof(char); j++){
      fscanf(fp, "%c", &buffer[i][j]);
      if(buffer[i][j] == '\n')
        break;
    }
  }

  fclose(fp);

  /* 指定された方法によりデータを分割する */
  line = 0;
  for(i = 0; i < split; i++){

    sprintf(str, "%s_%d", ofname, i+1);
    if((fp = fopen(str, "w")) == NULL){
      fprintf(stderr, "\n[エラー] : ファイル %s が開けません\n", str);
      exit(1);
    }

    for(j = 0; j < num[i]; j++){
      for(k = 0; k <= max_byte*sizeof(char); k++){
        fprintf(fp, "%c", buffer[line + j][k]);
        if(buffer[line + j][k] == '\n')
          break;
      }
    }

    fclose(fp);
    line += num[i];
  }

  /* 作業用の配列を解放 */
  free_char_matrix(buffer);
  free_int_vector(num);

  exit(0);
}
