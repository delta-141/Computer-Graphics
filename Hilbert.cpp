
#include<iostream>
#include<graphics.h>
using namespace std;
void move(int, int, int &,int &);
void hilbert(int,int,int,int,int,int,int &,int &);
void move(int j,int h,int &x,int &y)
{
if(j==1)
y-=h;
else if(j==2)
x+=h;
else if(j==3)
y+=h;
else if(j==4)
x-=h;
lineto(x,y);
}
void hilbert(int r,int d,int l,int u,int i,int h,int &x,int &y)
{
if(i>0)
{
i--;
hilbert(d,r,u,l,i,h,x,y);
move(r,h,x,y);
hilbert(r,d,l,u,i,h,x,y);
move(d,h,x,y);
hilbert(r,d,l,u,i,h,x,y);
move(l,h,x,y);
hilbert(u,l,d,r,i,h,x,y);
}
}
int main()
{
int gd=DETECT,gm;
char ch;
initgraph(&gd,&gm,NULL);
do
{
int n,x1,y1;
int x0=150,y0=100,x,y,h=10,r=2,d=3,l=4,u=1;
cout<<"\n Enter the order of the curve: ";
cin>>n;
x=x0;
y=y0;
moveto(x,y);
hilbert(r,d,l,u,n,h,x,y);
cout<<"Do you want to continue(y/n)";
cin>>ch;
}while(ch=='y');
getch();
}
