#include<stdio.h>
#include<string.h>
//#Copyright (c) 2021 Huang yu xiang 
//记得动脑！！！
int main()
{
	char kaisa(char password,int move);
	int i,a,n,move;
	char password[100],pass[100];
	printf("请输入你要选择的加密方式：\n1.凯撒加密\n2.异或性质加密\n3.RSA算法加密\n");
	scanf("%d",&a);
	switch (a) {
		case 1:
			
			printf("请输入你的密码：");
			gets(password);
			printf("请输入密钥：(1-25)");
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
			printf("作者太菜，打开文件1.2试试看吧！\n");
			
			break;
		case 3:
			printf("没错，这个功能也没有实现！\n");
			
			break;
	
	}
	
}
