#include "mat_utils.h"

/* ベクトルの和を求める */
double *add_vec(double *a, double *b, int size)
{
	int     i;
	double *tmp = NULL;

	tmp = new_double_vector(size);
	for(i = 0; i < size; i++)
		tmp[i] = a[i] + b[i];

	return tmp;
}

/* 二つの行列の和を求める関数 */
double **add_mat(double **a, double **b, int nrow, int ncol)
{
	int i, j;
	double **c = NULL;

	c = new_double_matrix(nrow, ncol);
	
	for(i = 0; i < nrow; i++)
		for(j = 0; j < ncol; j++)
			c[i][j] = a[i][j] + b[i][j];

	return c;
}

/* ベクトルの差を求める */
double *del_vec(double *a, double *b, int size)
{
	int     i;
	double *tmp = NULL;

	tmp = new_double_vector(size);
	for(i = 0; i < size; i++)
		tmp[i] = a[i] - b[i];

	return tmp;
}

/* 二つの行列の差を求める関数 */
double **del_mat(double **a, double **b, int nrow, int ncol)
{
	int      i, j;
	double **c = NULL;

	c = new_double_matrix(nrow, ncol);

	for(i = 0; i < nrow; i++)
		for(j = 0; j < ncol; j++)
			c[i][j] = a[i][j] - b[i][j];

	return c;
}

/* 二つの行列の積を求める関数 */
double **mult_mat(double **a, int nrow1, int ncol1, 
									double **b, int nrow2, int ncol2)
{
	int      i, j, k;
	double **c = NULL;
	
	c = new_double_matrix(nrow1, ncol2);

	/* 行列の積を出力 */
	for(i = 0; i < nrow1; i++){
		for(j = 0; j < ncol2; j++){
			c[i][j] = 0.0;
			
			for(k = 0; k < ncol1; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}

	return c;
}

/* 行列×ベクトルの計算を行う */
double *matxvec(double **mat, int nrow, int ncol, double *v, int size)
{
	int    i;
	double *vec = NULL;
	double **tmp1 = NULL, **tmp2 = NULL;
 
	/* ベクトルを1×sizeの2次元の配列にする */
	tmp1 = new_double_matrix(size, 1);
	for(i = 0; i < size; i++)
		tmp1[i][0] = v[i];

	/* 行列同士の掛け算を行う */
	tmp2 = mult_mat(mat, nrow, ncol, tmp1, size, 1);

	/* 計算結果を代入する */
	vec = new_double_vector(nrow);
	for(i = 0; i < nrow; i++)
		vec[i] = tmp2[i][0];

	free_double_matrix(tmp1);
	free_double_matrix(tmp2);

	return vec;
}

/* ベクトル×行列の計算を行う */
double *vecxmat(double *v, int size, double **mat, int nrow, int ncol)
{
	int    i;
	double *vec = NULL;
	double **tmp1 = NULL, **tmp2 = NULL;
 
	/* ベクトルを1×sizeの2次元の配列にする */
	tmp1 = new_double_matrix(1, size);
	for(i = 0; i < size; i++)
		tmp1[0][i] = v[i];

	/* 行列同士の掛け算を行う */
	tmp2 = mult_mat(tmp1, 1, size, mat, nrow, ncol);

	/* 計算結果を代入する */
	vec = new_double_vector(ncol);
	for(i = 0; i < ncol; i++)
		vec[i] = tmp2[0][i];

	free_double_matrix(tmp1);
	free_double_matrix(tmp2);

	return vec;
}

/* 行列を転置したものを出力 */
double **trans_mat(double **mat, int row, int col)
{
	int    i, j;
	double **a = NULL;

	/* 配列を確保 */
	a = new_double_matrix(row, col);

	/* 転置した行列を出力 */
	for(i = 0; i < col; i++)
		for(j = 0; j < row; j++)
			a[j][i] = mat[i][j]; 

	return a;
}

/* 対角成分だけの行列(単位行列の整数倍)を返す */
double **unit_mat(int size, double val)
{
	int i, j;
	double **mat = NULL;

	mat = new_double_matrix(size, size);

	/* 対角成分だけを1に残し、後は0にする */
	for(i = 0; i < size; i++){
		for(j = 0; j < size; j++){
			if(i == j)
				mat[i][j] = val;
			else
				mat[i][j] = 0.0;
		}
	}

	return mat;
}

/* ベクトルの内積を計算する */
double innerprod(int n, double *u, double *v)
{
	int i, n5;
	double s;

	s = 0;  
	n5 = n % 5;

	for (i = 0; i < n5; i++) 
		s += u[i]*v[i];
	for (i = n5; i < n; i += 5)
		s += u[i]*v[i] + u[i+1]*v[i+1] + u[i+2]*v[i+2]
		               + u[i+3]*v[i+3] + u[i+4]*v[i+4];
	return s;
}

/*
	GaussJordan法による逆行列の計算。
*/

double 
**matinv(int n, double **covmat, double *det)
{
	int i, j, k;
	double t, u;
	double **tmp_inv;

	tmp_inv = new_double_matrix(n, n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			tmp_inv[i][j] = covmat[i][j];

	*det = 1;
	for (k = 0; k < n; k++) {
		t = tmp_inv[k][k];  
		*det *= t;
		for (i = 0; i < n; i++)
			tmp_inv[k][i] /= t;
		tmp_inv[k][k] = 1 / t;
		for (j = 0; j < n; j++)
			if (j != k) {
				u = tmp_inv[j][k];
				for (i = 0; i < n; i++)
					if (i != k) 
						tmp_inv[j][i] -= tmp_inv[k][i] * u;
					else
						tmp_inv[j][i] = -u / t;
			}
	}
	
	return tmp_inv;
}

/* データから次元数とデータ数を自動的に判定する */
void
get_size(char *filename, int *dim, int *num)
{
	unsigned int line, word;
	char str[STR_LENGTH];
	FILE *fp = NULL;

	if(filename == NULL){
		fprintf(stderr, "\n[エラー] : ファイル名が不明です\n");
		exit(1);
	}

  if((fp = fopen(filename, "r")) == NULL){
		fprintf(stderr, "\n[エラー] : ファイル %s を開けませんでした\n",
            filename);
		exit(1);
  }
  fclose(fp);

	/* 次元数とデータ数を調べる */
	sprintf(str, "wc -l -w %s > /tmp/dim_size.log", filename);
	system(str);

	/* ファイルから調べた結果を読み込む */
	if((fp = fopen("/tmp/dim_size.log", "r")) == NULL){
		fprintf(stderr, "\n[エラー] : データの情報を取得できませんでした\n");
		exit(1);
	}
	fscanf(fp, "%d %d", &line, &word);
	fclose(fp);

	/* 行数、次元数の確認 */
	if(line == 0 && word != 0)
		line = 1;

	if((word % line) != 0){
		fprintf(stderr, "\n[エラー] : データ %s が正しくありません\n", filename);
		exit(1);
	}
	else{
		*num = line;
		*dim = word / line;
	}

	/* 一時ファイルを消す */
	strcpy(str, "rm /tmp/dim_size.log");
	system(str);
}

/* データから1行当たりのバイト数の最大値を判定する */
void
get_max_byte(char *filename, int *max_byte)
{
  char str[STR_LENGTH];
  FILE *fp = NULL;

	if(filename == NULL){
		fprintf(stderr, "\n[エラー] : ファイル名が不明です\n");
		exit(1);
	}
  
  sprintf(str, 
          "wc -L %s | gawk '{printf(\"%%d\",$1);}' > /tmp/max_byte.log",
          filename);
  system(str);
  if((fp = fopen("/tmp/max_byte.log", "r")) == NULL){
    fprintf(stderr, "\n[エラー] : ファイルの情報を取得できませんでした\n");
    exit(1);
  }
  fscanf(fp, "%d", max_byte);
  fclose(fp);
  
  /* 一時ファイルを消す */
  strcpy(str, "rm /tmp/max_byte.log");
  system(str);
}


/*
	ベクトルをLpノルムで正規化する。ベクトル x は上書きされる。
*/
void
vec_normalize(int dim, double *x, int p)
{
	int i;
	double norm;
	
	norm = get_vec_lp_norm(dim, x, p);
	for(i = 0; i < dim; i++)
		x[i] = x[i] / norm;
}


/* 
	 ベクトルのLpノルムの大きさを返す 
*/
double
get_vec_lp_norm(int dim, double *x, int p)
{
	int i;
	double norm = 0.0;

	for(i = 0; i < dim; i++)
      norm += pow(fabs(x[i]), (double)p);
    
	return pow(norm, 1.0/(double)p);
}


/*
	二つのベクトルの角度(ラジアン)を求める。[0,π]の値になる。
*/
double
vec_arg(int dim, double *x, double *y)
{
	double prod, length_x, length_y;

	/* 内積を計算する */
	prod = innerprod(dim, x, y);

	/* ベクトルのL2ノルムを計算する */
	length_x = get_vec_lp_norm(dim, x, 2);
	length_y = get_vec_lp_norm(dim, y, 2);

	return acos(prod / (length_x * length_y));
}


/*
	二つのベクトルの角度をcosで計算する。[-1,1]の値になる
*/

double
vec_cos(int dim, double *x, double *y)
{
	double prod, length_x, length_y;

	/* 内積を計算 */
	prod = innerprod(dim, x, y);

	/* ベクトルのL2ノルムを計算する */
	length_x = get_vec_lp_norm(dim, x, 2);
	length_y = get_vec_lp_norm(dim, y, 2);

	return prod / (length_x * length_y);
}

/*
	ランクを計算する
*/

int
mat_rank(int dim, double **mat)
{
	int i, j;
	int count = 0;
	double *dr = NULL, *di = NULL;
	double **tmp;
	
	dr = new_double_vector(dim);
	di = new_double_vector(dim);
	tmp = new_double_matrix(dim, dim);
	
	/* 計算途中で値が上書きされるから元の行列のコピーを使う */
	for(i = 0; i < dim; i++)
		for(j = 0; j < dim; j++)
			tmp[i][j] = mat[i][j];
	
	/* 固有値の計算 */
	hes(tmp, dim);
	hqr(tmp, dr, di, dim);

	/* 固有値を調べる */
	/* drが実数成分、diが虚数成分 */
	for(i = 0; i < dim; i++)
		if(dr[i] > 0.0 && (!(di[i] > 0.0 || di[i] < 0.0)))
			count++;
	
	/* 配列を解放 */
	free_double_vector(dr);
	free_double_vector(di);
	free_double_matrix(tmp);

	return count;
}

void
hes(double **mat, int n)  // 行列の中身は書き換えられるので注意
{
	int i, j, k;
	double aik, alpha, s, ss, uu;
	double *u, *v, *w, *vv, *ww;

	u = new_double_vector(n);
	v = new_double_vector(n);
	w = new_double_vector(n);
	vv = new_double_vector(n);
	ww = new_double_vector(n);

	for(k = 0; k < n - 2; ++k) {
		ss = 0.0;

		for(i = k + 1; i < n; ++i) {
			aik = mat[i][k];
			u[i] = aik;
			ss += aik * aik;
		}
		s = sqrt(ss);

		if(u[k + 1] > 0.0)
			s = (-s);

		u[k] = 0.0;
		u[k + 1] -= s;
		uu = sqrt(2.0 * (ss - mat[k + 1][k] * s));

		for(i = k; i < n; ++i)
			u[i] /= uu;

		for(i = k; i < n; ++i) {
			s = 0.0;
			ss = 0.0;
			for(j = k; j < n; ++j) {
				s += mat[i][j] * u[j];
				ss += mat[j][i] * u[j];
			}
			v[i] = s;
			vv[i] = ss;
		}
		s = 0.0;
		for(i = k; i < n; ++i)
			s += u[i] * v[i];
		alpha = s;
		for(i = k; i < n; ++i) {
			w[i] = (v[i] - alpha * u[i]) * 2.0;
			ww[i] = (vv[i] - alpha * u[i]) * 2.0;
		}
		for(i = k; i < n; ++i) {
			for(j = k; j < n; ++j) {
				mat[i][j] -= u[i] * ww[j] + w[i] * u[j];
			}
		}
	}
	free_double_vector(u);
	free_double_vector(v);
	free_double_vector(w);
	free_double_vector(vv);
	free_double_vector(ww);
}

void
hqr(double **mat, double *dr, double *di, int n) 
// 行列の中身は書き換えられるので注意
{
	int i, j, k, kaisuu, m;
	double d, e, p, q, r, sint, cost, beta, gamma, dd;
	double *c, *s;

	c = new_double_vector(n);
	s = new_double_vector(n);

	m = n;
	while(m >= 1) {

		if(m == 1) {
			dr[0] = mat[0][0];
			di[0] = 0.0;
			break;
		}

		for(kaisuu = 1; kaisuu < MAX_TIME; ++kaisuu) {

			/* 収束判定 */
			if(fabs(mat[m - 1][m - 2]) < STOP_THRESHOLD) {

				dr[m - 1] = mat[m - 1][m - 1];
				di[m - 1] = 0.0;
				m -= 1;
				break;

			}

			if(fabs(mat[m - 2][m - 3]) < STOP_THRESHOLD) {

				beta = (-mat[m - 2][m - 2] - mat[m - 1][m - 1]);
				gamma = mat[m - 2][m - 2] * mat[m - 1][m - 1]
					- mat[m - 2][m - 1] * mat[m - 1][m - 2];
				dd = beta * beta - 4.0 * gamma;
				d = sqrt(fabs(beta * beta - 4.0 * gamma));

				if(dd > 0.0) {
					if(beta > 0.0)
						d = (-d);
					dr[m - 2] = (-beta + d) / 2.0;
					dr[m - 1] = gamma / dr[m - 2];
					di[m - 1] = di[m - 2] = 0.0;
				}
				else {
					dr[m - 1] = dr[m - 2] = (-beta) / 2.0;
					di[m - 1] = d / 2.0;
					di[m - 2] = (-d / 2.0);
				}

				m -= 2;
				break;

			}

			/* QR分解 */
			for(k = 0; k < m-1; ++k) {
				d = mat[k][k];
				e = mat[k + 1][k];
				r = sqrt(d * d + e * e);
				c[k] = cost = d / r;
				s[k] = sint = e / r;
				for(j = k; j < m; ++j) {
					p = mat[k][j];
					q = mat[k + 1][j];
					mat[k][j] = cost * p + sint * q;
					mat[k + 1][j] = (-sint * p + cost * q);
				}
			}

			/* 逆順乗算 */
			for(k = 0; k < m-1; ++k) {
				cost = c[k];
				sint = s[k];
				for(i = 0; i <= k + 1; ++i) {
					p = mat[i][k];
					q = mat[i][k + 1];
					mat[i][k] = cost * p + sint * q;
					mat[i][k + 1] = (-sint * p + cost * q);
				}
			}

		}   // end of for(kaisuu = 1; kaisuu < MAX_ITER; ++kaisuu)
	}	  //end of while(m >= 1) {

	/* 終了処理 */
	free_double_vector(c);
	free_double_vector(s);
}
