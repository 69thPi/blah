#include<stdio.h>

void one()
{
 int a[50],b[50],c[50],n,i;
 scanf("%d",&n);//array lngth is same
 for(i=0;i<n;i++)
 scanf("%d",&a[i]);
 for(i=0;i<n;i++)
 scanf("%d",&b[i]);
 for(i=0;i<n;i++)
 {
  c[i]=a[i]+b[i];
  printf("%d ",c[i]);
 }
}

void two_one()
{
int j,pos=0,neg=0,zero=0,n,a[50];
 scanf("%d",&n);
for(j=0;j<n;j++)
 scanf("%d",&a[j]);
  for(j=0;j<n;j++)
  {
    if(a[j]>0)
	pos++;
    else if(a[j]==0)
	zero++;
    else   
	neg++;
  }
printf("positive= %d\nnegative=%d\nzero=%d",pos,neg,zero);
}

void two_two()
{
int i,j,pos=0,neg=0,zero=0,a[50][50];
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
 scanf("%d",&a[i][j]);
}
}
 for(i=0;i<3;i++)
 {
  for(j=0;j<3;j++)
  {
    if(a[i][j]>0)
	pos++;
    else if(a[i][j]==0)
	zero++;
    else   
	neg++;
  }
 }
printf("positive= %d\nnegative=%d\nzero=%d",pos,neg,zero);
}

void three()
{
int i,n;
char a[50];
gets(a);
for(i=0;a[i]!='\0';i++)
printf("%d",a[i]);
}

void fibbo()
{
int i,temp,a=0,b=1,arr[10];
a[0]=0;
a[1]=1;
for(i=2;i<10;i++)
{
 temp=b;
 b=a+b;
 arr[i]=b;
 a=temp;
}
for(i=0;i<10;i++)
printf("%d",arr[i]);
}

void xchgBigSmall()
{
 int i,n,a[50];
 scanf("%d",&n);
for(i=0;i<n;i++)
 scanf("%d",&a[i]);
 int big=a[0],min=a[0],minat=0,maxat=0,temp;
 for(i=0;i<n;i++)
 {
  if(a[i]>max)
  {
   max=a[i];
   maxat=i;
  }
  if(a[i]<min)
  {
   min=a[i];
   minat=i;
  }
}
temp=a[minat];
a[minat]=a[maxat];
a[maxat]=temp;
for(i=0;i<n;i++)
 printf("%d",&a[i]);
}

void delDuplicate()
{
 int i,j,k,n,a[50];
 scanf("%d",&n);
 for(i=0;i<n;i++)
  scanf("%d",&a[i]);
 for(i=0;i<n;i++)
{
 for(j=i;j<n;j++)
 {
  if(a[j]==a[i])
   {
     for(k=j;k<n;k++)
       a[k]=a[k+1];
      n--;
   }
 }
}
for(i=0;i<n;i++)
  printf("%d ",a[i]);
}

void bbl_sort()
{
 int i,j,n,a[50];
 scanf("%d",&n);
 for(i=0;i<n;i++)
  scanf("%d",&a[i]);
 for(i=0;i<n;i++)
 {
 for(j=i;j<n;j++)
 {
  if(a[j]>a[j+1])
  {
   temp=a[j+1];
   a[j+1]=a[j];
   a[j]=temp;
  }
 }
 }
for(i=0;i<n;i++)
  printf("%d ",a[i]);
}

void eight()
{
 int i,j,n;
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
	 for(j=0;j<n;j++)
	 {
	 	scanf("%d",&a[i][j]);  //input elments
	 }
 }
 int sum=0,flag=1;
 for(i=0;i<n;i++)//calc main sum
 {	 	
    sum+=a[0][i];
 }
int tp=0;
while(flag==1)
{
	 for(i=0;i<n;i++)
	 {
		 tp=0;
		 for(j=0;j<n;j++)  //clc sum of each row
		 {
		   tp=+a[i][j];	
		 }
		 if(tp!=sum)
		   flag=0;
	 }
	for(i=0;i<n;i++)
	 {
		 tp=0;
		 for(j=0;j<n;j++) //calc sum of each clumn
		 {
		   tp=+a[j][i];	
		 }
		 if(tp!=sum)
		   flag=0;
	 }
	for(i=0;i<n;i++)
	 {
		 tp=0;
		 for(j=0;j<n;j++) //calc sum of each clumn
		 {
		  if(i==j)
		   tp=+a[j][i];	
		 }
		 if(tp!=sum)
		   flag=0;
	 }
	for(i=0;i<n;i++)
	 {
		 tp=0;
		 for(j=0;j<n;j++) //calc sum of each clumn
		 {
		   if(i+j==n-1)
		   tp=+a[j][i];	
		 }
		 if(tp!=sum)
		   flag=0;
	 }
}
if(flag==1)
printf("magic matrix\n");
else
printf("non magic\n");
}

void nine()
{
int i,j,n;
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 for(j=0;j<n;j++)
          {
	  if(i==0 && j==0)
	   printf("*");
	  else if(i==0)
	   printf("%d",j);
	  else if(j==0)
	   printf("%d",i);
	  else
	   printf("%d",i*j);
	  }
 printf("\n");
 }
}

void last()
{
 int i,j,n,a[10][10],b[10][10];
scanf("%d",&n);
 for(i=0;i<n;i++)
 {
	 for(j=0;j<n;j++)
	 {
	 	scanf("%d",&a[i][j]);  //input elments
	 }
 }
for(i=0;i<n;i++)
 {
	 for(j=0;j<n;j++)
	 {
	 	scanf("%d",&b[i][j]);  //input elments
	 }
 }
for(i=0;i<n;i++)
 {
	 for(j=0;j<n;j++)
	 {
	   for(j=0;j<n;j++)
	    {
	 	b[i][j]+
	    }	
	 }
 }
}
