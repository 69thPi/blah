#include<stdio.h>
char ig[2];

void one()
{
 char inp[50];
 printf("enter string:");
 gets(ig);
 gets(inp);
 int i=0;
for(i=0;inp[i]!='\0';i++);
printf("length = %d\n",i);
}

void two()
{
 char  one[50];
 char  two[50];
printf("enter string:");
gets(ig);
 gets(one);
printf("enter string:");
 gets(two);
int i,j,k;
	for(i=0;one[i]!='\0';i++);
	for(j=i,k=0;two[k]!='\0';k++,j++)
		{
		 	one[j]=two[k];
		}
	one[j]='\0';
puts(one);
printf("\n");
puts(two);
}

void three()
{
 char inp[50];
 int i,t,j;
 printf("enter string:");
 gets(ig);
 gets(inp);
 	for(i=0;inp[i]!='\0';i++);
        i--;
	 for(j=0;j<(i+1)/2;j++)
		 {
			  t=inp[j];
			  inp[j]=inp[i-j];
			  inp[i-j]=t;
		 }
 puts(inp);
}

void four()
{
 char inp[50];
 int map[26],i;
 for(i=0;i<26;i++)
  map[i]=0;
 printf("enter string:");
gets(ig);
 gets(inp);
 for(i=0;inp[i]!='\0';i++)
 {
  map[(int)inp[i]-97]++;//65= ASCII of 'A'//97='a'
 }
for(i=0;i<26;i++)
{
 if(map[i]!=0)
 {
  printf("%c = %d\n",(char)(i+65),map[i]); 
 }
}
}

void five()
{
 char inp[50];
 printf("enter string:");
gets(ig);
 gets(inp);
 int i=0;
  for(i=0;inp[i]!='\0';i++)
  {
   if((int)inp[i]>=97)
     inp[i]=inp[i]-32;
   else
     inp[i]=inp[i]+32;
  }
puts(inp);
}

void main()
{
int ch1;
char ch2;
	while(1)
	{
	 printf(" press       option\n");
	printf(" 1            one\n");
	printf(" 2            two\n");
	printf(" 3            three\n");
	printf(" 4            four\n");
	printf(" 5            five\n");
	printf("choice :");
	scanf("%d",&ch1);
		switch(ch1)
		{
		 case 1:one();
			 break;
		 case 2:two();
			 break;
		 case 3:three();
			 break;
		 case 4:four();
			 break;
		 case 5:five();
			 break;
		 default:printf("error\n");
			 break;
		}
	printf("continue?(Y/N):");
	scanf("%c",&ch2);
	if(ch2=='N' ||ch2=='n')
		break;
	}
}

