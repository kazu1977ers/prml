#include "calc_utils.h"

/* 桁溢れ防止機能付きexp関数 */
double safe_exp(double x)
{
	if(exp(x) > DBL_MAX)
		return DBL_MAX;
	else if(exp(x) < DBL_MIN)
		return DBL_MIN;
	else
		return exp(x);
}

/* 桁溢れ防止機能付き足し算 */
double
add(double x, double y)
{
	if((x + y) > DBL_MAX)
		return DBL_MAX;
	else if((x + y) < -DBL_MAX)
		return -DBL_MAX;
	else
		return (x + y);
}

/* 桁溢れ防止機能付き引き算 */
double 
del(double x, double y)
{
	if((x - y) > DBL_MAX)
		return DBL_MAX;
	else if((x - y) < -DBL_MAX)
		return -DBL_MAX;
	else
		return DBL_MAX;
}

/* 桁溢れ防止機能付き掛け算 */
double 
mult(double x, double y)
{
	if((x == 0.0) || (y == 0.0))
		return 0.0;
	else{
		if(x > 0.0){
			if(y > 0.0){
				if((x * y) > DBL_MAX)
					return DBL_MAX;
				else if((x * y) < DBL_MIN)
					return DBL_MIN;
				else
					return (x * y);
			}
			else{
				if((x * y) < -DBL_MAX)
					return -DBL_MAX;
				else if((x * y) > -DBL_MIN)
					return -DBL_MIN;
				else
					return (x * y);
			}
		}
		else{
			if(y > 0.0){
				if((x * y) < -DBL_MAX)
					return -DBL_MAX;
				else if((x * y) > -DBL_MIN)
					return -DBL_MIN;
				else
					return (x * y);
			}
			else{
				if((x * y) > DBL_MAX)
					return DBL_MAX;
				else if((x * y) < DBL_MIN)
					return DBL_MIN;
				else
					return (x * y);
			}
		}
	}
}

/* 桁溢れ防止機能付き割算 */
double 
dvid(double x, double y)
{
	if(x == 0.0)
		return 0.0;
	else{
		if(x > 0.0){
			if(y == 0.0)
				return DBL_MAX;
			else if(y > 0.0){
				if((x / y) > DBL_MAX)
					return DBL_MAX;
				else if((x / y) < DBL_MIN)
					return DBL_MIN;
				else
					return (x / y);
			}
			else{
				if((x / y) < -DBL_MAX)
					return -DBL_MAX;
				else if((x / y) > -DBL_MIN)
					return -DBL_MIN;
				else
					return (x / y);
			}
		}
		else{
			if(y == 0.0)
				return -DBL_MAX;
			else if(y > 0.0){
				if((x / y) < -DBL_MAX)
					return -DBL_MAX;
				else if((x / y) > -DBL_MIN)
					return -DBL_MIN;
				else
					return (x / y);
			}
			else{
				if((x / y) > DBL_MAX)
					return DBL_MAX;
				else if((x / y) < DBL_MIN)
					return DBL_MIN;
				else
					return (x / y);
			}
		}
	}
}

/* 桁溢れ防止機能付き2乗の計算 */
double
pow2(double x)
{
	return mult(x, x);
}

/* 平均を計算する */
double *calc_mean(double **mat, int nrow, int ncol)
{
	int i, j;
	double *tmp = NULL;
	
	/* 平均ベクトルの準備 */
	tmp = new_double_vector(ncol);
	
	/* 初期化 */
	for(i = 0; i < ncol; i++)
		tmp[i] = 0.0;
	
	/* 次元毎に計算を行う */
	for(i = 0; i < ncol; i++){
		for(j = 0; j < nrow; j++)
			tmp[i] += mat[j][i];
		
		tmp[i] = tmp[i] / (double)nrow;
	}
	
	return tmp;
}

/* 共分散行列を計算する */
double **calc_cov_mat(double **mat, double *mean, int nrow, int ncol)
{
	int i, j, k;
	double **cov_mat = NULL;
	
	/* 共分散行列の準備(次元数×次元数) */
	cov_mat = new_double_matrix(ncol, ncol);

	/* 初期化 */
	for(i = 0; i < ncol; i++)
		for(j = 0; j < ncol; j++)
			cov_mat[i][j] = 0.0;

	/* 共分散行列の左上の成分から計算する */
	for(i = 0; i < ncol; i++){
		for(j = 0; j < ncol; j++){
			for(k = 0; k < nrow; k++)
				cov_mat[i][j] += 
					(mat[k][i] - mean[i]) * (mat[k][j] - mean[j]);
			
      /* 不偏推定量 */
			cov_mat[i][j] = cov_mat[i][j] / (double)(nrow - 1);
		}
	}

	return cov_mat;
}

/* 相関係数行列を計算する */
double **calc_corr_mat(double **mat, int dim)
{
	int i, j;
	double **cor_mat = NULL;
	
	cor_mat = new_double_matrix(dim, dim);
	
	for(i = 0; i < dim; i++)
		for(j = 0; j < dim; j++)
			cor_mat[i][j] = mat[i][j] / sqrt(mat[i][i] * mat[j][j]);
	
	return cor_mat;
}

/* nCkの組合せを求める関数 */
int **gen_comb(int n, int k, unsigned int *size)
{
	int          i, j;
	int          count = 0;
	unsigned int limit = num_comb(n, k);
	int          *index = NULL;    /* 作業用の配列 */
	int          **combi = NULL;   /* k個の組合せを保存する配列 */

	index = new_int_vector(k);
	combi = new_int_matrix(limit, k);

	/* 初期状態 */
	for(i = 0; i < k; i++)
		index[i] = i;

	/* 組合せを求める */
	i = 0;
	while(count < limit){
		while(index[i] <= n-k+i){
			if(i < k-1){ 
				i++;
				index[i] = index[i-1] + 1;
			}
			else{
				for(j = 0; j < k; j++)
					combi[count][j] = index[j];

				count++;
				index[i]++;
			}
		}
		i--;
		index[i]++;
	}

	/* 作業用の配列を解放 */
	free_int_vector(index);

	/* 組合せの個数を保存する */
	*size = limit;

	/* 組合せを返す */
	return combi;
}

/* nCkの組合せの個数を求める関数 */
unsigned int num_comb(int n, int k)
{
	int i;
	double bunsi = 1.0, bunbo = 1.0;
	
	for(i = k; i > 0; i--){
		bunsi *= (double)(i-k+n);
		bunbo *= (double)i;
	}
	
	if((bunsi/bunbo) > (double)UINT_MAX){
		fprintf(stderr, "\n[エラー] : 組合せの数が %u を越えました\n", UINT_MAX);
		return -1;
	}
	else
		return (unsigned int)(bunsi / bunbo);
}

/* 
	 単変量正規分布 N(μ,σ)の X における値を計算する。
	 多変量の正規分布には対応していないので注意。
*/
double
get_val_norm(double mean, double sigma, double X)
{
	return mult(dvid(1.0, mult(sqrt(2.0 * M_PI), sigma)), 
							safe_exp(mult((-1.0 / 2.0), pow2(dvid((X - mean), sigma)))));
}

/*
  多変量正規分布 N(Μ,Σ)の X に対する値を計算する。
  単変量の正規分布は上の関数を使うこと。
*/
double
get_multi_norm(double *mean, double **covmat, double *X, int dim)
{
  double *tmp1 = NULL, *tmp2 = NULL;
  double det, **invmat = NULL;
	double val;

  tmp1 = del_vec(X, mean, dim);
  tmp2 = tmp1;
  invmat  = matinv(dim, covmat, &det);
  tmp1 = vecxmat(tmp1, dim, invmat, dim, dim);
  val = dvid(safe_exp(-0.5 * innerprod(dim, tmp1, tmp2)),
						 (pow(2.0 * M_PI, dim / 2.0) * sqrt(det)));

	free_double_matrix(invmat);
	free_double_vector(tmp1);
	free_double_vector(tmp2);

	return val;
}

/* ベータ分布 
	 f(x) = Γ(a+b)/(Γ(a)Γ(b)) * x^(a-1) * (1-x)^(b-1),
	 0 <= x <= 1, a > 0, b > 0
	 に従う乱数を発生させる
*/
double 
beta_rnd(double a, double b)
{
	double temp;

	temp = gamma_rnd(a);
	return temp / (temp + gamma_rnd(b));
}

/* コーシー分布に従う乱数を発生させる */
double
cauchy_rnd(void)
{
	return tan(M_PI * uni_rnd());
}

/* 自由度 n のカイ2乗分布に従う乱数を発生させる */
double
chisq_rnd(double n)
{
	return 2.0 * gamma_rnd(0.5 * n);
}

/* exp(-x), x>=0 の指数分布に従う乱数を発生させる */
double
exp_rnd(void)
{
	return -log(1.0 - uni_rnd());
}

/* 自由度(n1,n2)のF分布に従う乱数を発生させる */
double
f_rnd(double n1, double n2)
{
	return (chisq_rnd(n1) * n2) / (chisq_rnd(n2) * n1);
}

/* ガンマ分布 
	 f(x)=(x^(a-1) * exp(-x))/Γ(a), x>0 
	 に従う乱数を発生させる
*/
double
gamma_rnd(double a)
{
	double t, u, x, y;

	if (a > 1) {
		t = sqrt(2 * a - 1);
		do {
			do {
				/* 次の4行は y = tan(PI * uni_rnd()) と同値 */
				do {
					x = 1 - uni_rnd();  
					y = 2 * uni_rnd() - 1;
				} while (x * x + y * y > 1);

				y /= x;
				x = t * y + a - 1;
			} while (x <= 0);

			u = (a - 1) * log(x / (a - 1)) - t * y;
		} while (u < -50 || uni_rnd() > (1 + y * y) * exp(u));
	}
	else {
		t = M_E / (a + M_E);
		do {
			if (uni_rnd() < t) {
				x = pow(uni_rnd(), 1 / a);  y = exp(-x);
			}
			else {
				x = 1 - log(uni_rnd());  y = pow(x, a - 1);
			}
		} while (uni_rnd() >= y);
	}

	return x;
}

/* N(mean,sigma)の正規分布に従う乱数を生成する */
double
norm_rnd(double mean, double sigma)
{
	double r1, r2;

	if(sigma <= 0.0){
		fprintf(stderr, "\n[エラー] : 分散の値が正しくありません\n");
		exit(1);
	}

	r1 = uni_rnd();
	r2 = uni_rnd();

	return (sigma * sqrt(-2 * log(r1)) * cos(2 * M_PI * r2) + mean);
}

/* (n+1)*x^nの累乗分布に従う乱数を発生させる */
double
pow_rnd(double n)
{
	return pow(uni_rnd(), (1.0 / (n + 1)));
}

/* 自由度 n のt分布に従う乱数を発生させる */
double 
t_rnd(double n)
{
	double a, b, c;

	if (n <= 2) 
		return norm_rnd(0.0, 1.0) / sqrt(chisq_rnd(n) / n);

	do {
		a = norm_rnd(0.0, 1.0);
		b = a * a / (n - 2);
		c = log(1 - uni_rnd()) / (1 - 0.5 * n);
	} while (exp(-b-c) > 1 - b);

	return a / sqrt((1 - 2.0 / n) * (1 - b));
}

/* [-1,1]の三角分布に従う乱数を発生させる */
double
tri_rnd(void)
{
	return (uni_rnd() - uni_rnd());
}

/* [0,1)の一様乱数を発生させる */
double 
uni_rnd(void)
{
	return (1.0 / (RAND_MAX + 1.0)) * (rand() + 0.5);
}

/* 幾何分布に従う乱数を発生させる */
int
geome_rnd(double p)
{
	int n = 1;
	
	while(uni_rnd() > p) 
		n++;

	return n;
}

/* 2項分布に従う乱数を発生させる */
int
bin_rnd(int n, double p)
{
	int i, r = 0;

	for(i = 0; i < n; i++)
		if(uni_rnd() < p) 
			r++;

	return r;
}

/* ポアソン分布に従う乱数を発生させる */
int poi_rnd(double lambda)
{
	int k = 0;

	lambda = exp(lambda) * uni_rnd();

	while (lambda > 1.0) {
		lambda *= uni_rnd();  
		k++;
	}

	return k;
}

/*
  n次元の単位球上のランダムな点を発生させる
*/
double *rnd_vect(int dim)
{
  int i;
  double r, *v = NULL;

  v = new_double_vector(dim);

  r = 0.0;
  for(i = 0; i < dim; i++){
    v[i] = norm_rnd(0.0, 1.0);
    r += (v[i] * v[i]);
  }

  r = sqrt(r);
  for(i = 0; i < dim; i++)
    v[i] = v[i] / r;
  
  return v;
}

/* 
   val を pos で指定された位で四捨五入しその値を返す。
	 pos は 10^x のxを指定する。例えば、100の位なら 2、0.0001なら -4
	 と指定する。
*/
double roundoff(double val, int pos)
{
	return (int)(val * pow(10.0, (double)(-pos-1)) + 0.5) 
		* pow(10.0, (double)pos+1);
}

/*
  2個の整数 x,y の最大公約数(greatest common divisor)を求める
*/
int gcd(int x, int y)
{
  int t;

  while(y != 0){
    t = x % y;
    x = y;
    y = t;
  }

  return x;
}

/*
  2個の整数 x,y の最小公倍数(least common multiple)を求める
*/
int lcm(int x, int y)
{
  return abs(x * y) / gcd(x, y);
}

/*
	Γ関数の値を求める
*/
double gamma(double x)
{
	if (x < 0)
		return M_PI / (sin(M_PI * x) * exp(loggamma(1 - x)));
	else
		return exp(loggamma(x));
}

/* Γ関数のlogをとった値を返す */
double loggamma(double x)
{
	double v = 1, w;
	
	while(x < N_gamma){
		v *= x;
		x++;
	}
	w = 1 / (x * x);
	
	return ((((((((B16 / (16.0 * 15.0)) * w + (B14 / (14.0 * 13.0))) * w
							 + (B12 / (12.0 * 11.0))) * w + (B10 / (10.0 * 9.0))) * w
						 + (B8 / (8.0 * 7.0))) * w + (B6 / (6.0 * 5.0))) * w
					 + (B4 / (4.0 * 3.0))) * w + (B2 / (2.0 * 1.0))) / x
		+ 0.5 * log(2.0 * M_PI) - log(v) - x + (x - 0.5) * log(x);
}

/*
	半径 r の超球の体積を求める
*/

double
get_volume_sphere(double r, int dim)
{
	return pow(M_PI, (double)dim / 2.0) / gamma(((double)dim / 2.0) + 1.0)
		* pow(r, (double)dim);
}
