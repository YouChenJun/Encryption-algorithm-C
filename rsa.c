#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//#Copyright (c) 2021 Huang yu xiang 
//记得动脑！！！
/*将十进制数转换成二进制，用于检验大素数 p 和 q*/
int zh(int b, int a[], int k)
{
	int t, temp = -1;
	while (b > 0)
	{
		t = b % 2;
		temp++;
		a[temp] = t;
		b = b / 2;
	}
	return temp;
}
/*扩展欧几里得算法求乘法逆元，求解密指数 d*/
int extend(int n, int b)
{
	int q, r, r1 = n, r2 = b, t, t1 = 0, t2 = 1, i = 1;
	while (r2 > 0)
	{
		q = r1 / r2;
		r = r1 % r2;
		r1 = r2;
		r2 = r;
		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}
	if (t1 >= 0) return t1 % n;
	else
	{
		while ((t1 + i * n) < 0)
			i++;
		return t1 + i * n;
	}
}
/*检验大素数*/
int Witness(int a, int n)
{
	int d = 1, k, r = n - 1, i, x, b[1000];
	k = zh(r, b, 1000);
	for (i = k; i >= 0; i--)
	{
		x = d;
		d = (d * d) % n;
		if ((d == 1) && (x != 1) && (x != n - 1)) return 0;
		if (b[i] == 1) d = (d * a) % n;
	}
	if (d != 1) return 0;
	else return 1;
}
/*快速计算模指数*/
int mod(int a, int b, int n)
{
	int x = 0, y = 1, k, i, s[1000];
	k = zh(b, s, 1000);
	for (i = k; i >= 0; i--)
	{
		x = 2 * x;
		y = (y * y) % n;
		if (s[i] == 1)
		{
			x++;
			y = (y * a) % n;
		}
	}
	return y;
}

void main()
{
	int p, q, e, d, n, yn, m[1000], c[10000], mw[1000]; //c[10000] 存放加密后的数字密文， m[1000] 存放解密后的数字明文，即英文明文在 zimu_biao[69] 中的下标,mw[1000]用于存放用户输入的密文。
	int yinzi[1000], e1[1000]; //yinzi[1000]用于存放Φ(n)的所有因子,e1[1000]用于存放一组随机值，用于
	int i, j = 0, j1; //计数器
	char min_wen[1000], mi_wen[1000], re_min_wen[1000]; // 分别为用户输入的明文，密文，解密后的明文。
//密钥生成
	char zimu_biao[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char shuzi_biao[10] = "0123456789";
	printf(" 请输入您要发送的明文（小写英文表示） :\n");
	gets(min_wen);
//随机自动生成p和q的值
	while (1)
	{
		srand((unsigned)time(NULL));
		p = rand() % 500 + 2;
		if (Witness(2, p) == 1)
		{
			printf(" 自动生成的的第一个大素数 p的值为：%d  \n", p);
			break;
		}
	}
	while (1)
	{
		srand((unsigned)time(NULL));
		q = rand() % 600 + 2;
		if (Witness(2, q))
		{
			printf(" 自动生成的的第二个大素数q的值为：%d  \n", q);
			break;
		}
	}
	n = p * q;
	yn = (p - 1) * (q - 1);
//自动随机生成e
	for (i = 2; i <= yn; i++)  //求出Φ(n)的所有因子
	{
		if (yn % i == 0)
		{
			yinzi[j] = i;
			j++;
		}
		j1 = j;
	}
	srand(time(NULL));
	for (i = 0; i < j1 + 1; i++) //生成大于因子个数的候选值（随机选取整数e（1<e<Φ(n)）作为公钥）
	{
		e1[i] = rand() % (yn - 2) + 2;
		for (j = 0; j < i; j++)
		{
			if (e1[j] == e1[i])
			{
				i--;
				break;
			}
		}
	}
	for (i = 0; i < j1 + 1; i++)
	{
		for (j = j1; j > i; j--)
		{
			int x;
			if (e1[i] > e1[j])
			{
				x = e1[i];
				e1[i] = e1[j];
				e1[j] = x;
			}
		}
	}

	for (i = 0; i < j1 + 1; i++) //要求满足e与Φ(n)的最大公约数为1，即两者互素
	{
		for (j = 0; j < j1; j++)
		{
			if (e1[i] == yinzi[j])
			{
				e1[i] = 0;
				break;

			}
		}
		if (e1[i] != 0)
		{
			e = e1[i];
			break;

		}
	}

	d = extend(yn, e); //密钥
	printf("\n自动生成的加密指数 e=%d", e);
//明文转换过程
	for (i = 0; i < strlen(min_wen); i++)
		for (j = 0; j < 51; j++) //for(j=0;j<26;j++)
			if (min_wen[i] == zimu_biao[j])
				m[i] = j; // 将字符串明文换成数字，并存到整型数组 m 里面，即明文的另一种表示方法
//加密过程
	for (i = 0; i < strlen(min_wen); i++)
		c[i] = mod(m[i], e, n);
	printf(" 输出密文： \n");
	for (i = 0; i < strlen(min_wen); i++)
		printf("%d", c[i]);
//解密过程
	printf("\n输入要解密的密文8：\n");
	gets(mi_wen);

	for (i = 0; i < strlen(mi_wen); i++)
		for (j = 0; j < 9; j++)
			if (mi_wen[i] == shuzi_biao[j])
				mw[i] = j;

	printf("解密结果：");
	for (i = 0; i < strlen(min_wen); i++)
		m[i] = mod(mw[i], d, n);
	for (i = 0; i < strlen(min_wen); i++)
		re_min_wen[i] = zimu_biao[m[i]];

	for (i = 0; i < strlen(min_wen); i++)
		printf("%c", re_min_wen[i]);
	printf("\n\n");

}
