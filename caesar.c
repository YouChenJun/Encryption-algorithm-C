#include<stdio.h>
#include<string.h>
//#Copyright (c) 2021 Huang yu xiang 
//�ǵö��ԣ�����
int main()
{
	char kaisa(char password,int move);
	int i,a,n,move;
	char password[100],pass[100];
	printf("��������Ҫѡ��ļ��ܷ�ʽ��\n1.��������\n2.������ʼ���\n3.RSA�㷨����\n");
	scanf("%d",&a);
	switch (a) {
		case 1:
			
			printf("������������룺");
			gets(password);
			printf("��������Կ��(1-25)");
			scanf("%d",&move);
			for(i=0; i<strlen(password); i++)
			        {
			            if(password[i] >= 'A' && password[i] <= 'Z')
			            {
			                password[i] = ((password[i]-'A')+move)%26+'A';
			            }
			            else if(password[i] >= 'a' && password[i] <= 'z')
			            {
			                password[i] = ((password[i]-'a')+move)%26+'a';
			            }
			        }
			        printf("%s",password);
			        printf("\n");
			break;
		case 2:
			printf("����̫�ˣ����ļ�1.2���Կ��ɣ�\n");
			
			break;
		case 3:
			printf("û���������Ҳû��ʵ�֣�\n");
			
			break;
	
	}
	
}
