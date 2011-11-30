/* オプションで指定された引数を読み込む関数群 */
#ifndef OPT_UTILS_H
#define OPT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ary_utils.h"

#define DEFAULT_LENGTH  100

/* 文字列型の引数を取り出す */
char *get_char_arg(int argc, char **argv, char *opt_str);
/* 文字列型の引数リストを取り出す */
char **get_char_list(int argc, char **argv, char *opt_str, 
												 int arg_num);

/* 整数型の引数を取り出す */
int  get_int_arg(int argc, char **argv, char *opt_str);
/* 整数型の固定長の引数リストを取り出す */
int *get_int_list(int argc, char **argv, char *opt_str, 
											 int arg_num);
/* 整数型の可変長の引数リストを取り出す */
int *get_int_arg_list(int argc, char **argv, char *opt_str, int *arg_num);

/* 浮動小数点型の引数を取り出す */
double       get_double_arg(int argc, char **argv, char *opt_str);
/* 浮動小数点型の引数リストを取り出す */
double *get_double_list(int argc, char **argv, char *opt_str, 
														 int arg_num);

/* オプションが含まれるかどうか判定する */
int is_opt(int argc, char **argv, char *opt_str);
/* オプションで指定された引数の個数を調べる */
int num_opt(int argc, char **argv, char *opt_str);

#endif
