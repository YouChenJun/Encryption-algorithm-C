#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//#Copyright (c) 2021 Huang yu xiang 
//�ǵö��ԣ�����
/*��ʮ������ת���ɶ����ƣ����ڼ�������� p �� q*/
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
/*��չŷ������㷨��˷���Ԫ�������ָ�� d*/
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
/*���������*/
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
/*���ټ���ģָ��*/
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
	int p, q, e, d, n, yn, m[1000], c[10000], mw[1000]; //c[10000] ��ż��ܺ���������ģ� m[1000] ��Ž��ܺ���������ģ���Ӣ�������� zimu_biao[69] �е��±�,mw[1000]���ڴ���û���������ġ�
	int yinzi[1000], e1[1000]; //yinzi[1000]���ڴ�Ŧ�(n)����������,e1[1000]���ڴ��һ�����ֵ������
	int i, j = 0, j1; //������
	char min_wen[1000], mi_wen[1000], re_min_wen[1000]; // �ֱ�Ϊ�û���������ģ����ģ����ܺ�����ġ�
//��Կ����
	char zimu_biao[52] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char shuzi_biao[10] = "0123456789";
	printf(" ��������Ҫ���͵����ģ�СдӢ�ı�ʾ�� :\n");
	gets(min_wen);
//����Զ�����p��q��ֵ
	while (1)
	{
		srand((unsigned)time(NULL));
		p = rand() % 500 + 2;
		if (Witness(2, p) == 1)
		{
			printf(" �Զ����ɵĵĵ�һ�������� p��ֵΪ��%d  \n", p);
			break;
		}
	}
	while (1)
	{
		srand((unsigned)time(NULL));
		q = rand() % 600 + 2;
		if (Witness(2, q))
		{
			printf(" �Զ����ɵĵĵڶ���������q��ֵΪ��%d  \n", q);
			break;
		}
	}
	n = p * q;
	yn = (p - 1) * (q - 1);
//�Զ��������e
	for (i = 2; i <= yn; i++)  //�����(n)����������
	{
		if (yn % i == 0)
		{
			yinzi[j] = i;
			j++;
		}
		j1 = j;
	}
	srand(time(NULL));
	for (i = 0; i < j1 + 1; i++) //���ɴ������Ӹ����ĺ�ѡֵ�����ѡȡ����e��1<e<��(n)����Ϊ��Կ��
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

	for (i = 0; i < j1 + 1; i++) //Ҫ������e�릵(n)�����Լ��Ϊ1�������߻���
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

	d = extend(yn, e); //��Կ
	printf("\n�Զ����ɵļ���ָ�� e=%d", e);
//����ת������
	for (i = 0; i < strlen(min_wen); i++)
		for (j = 0; j < 51; j++) //for(j=0;j<26;j++)
			if (min_wen[i] == zimu_biao[j])
				m[i] = j; // ���ַ������Ļ������֣����浽�������� m ���棬�����ĵ���һ�ֱ�ʾ����
//���ܹ���
	for (i = 0; i < strlen(min_wen); i++)
		c[i] = mod(m[i], e, n);
	printf(" ������ģ� \n");
	for (i = 0; i < strlen(min_wen); i++)
		printf("%d", c[i]);
//���ܹ���
	printf("\n����Ҫ���ܵ�����8��\n");
	gets(mi_wen);

	for (i = 0; i < strlen(mi_wen); i++)
		for (j = 0; j < 9; j++)
			if (mi_wen[i] == shuzi_biao[j])
				mw[i] = j;

	printf("���ܽ����");
	for (i = 0; i < strlen(min_wen); i++)
		m[i] = mod(mw[i], d, n);
	for (i = 0; i < strlen(min_wen); i++)
		re_min_wen[i] = zimu_biao[m[i]];

	for (i = 0; i < strlen(min_wen); i++)
		printf("%c", re_min_wen[i]);
	printf("\n\n");

}
