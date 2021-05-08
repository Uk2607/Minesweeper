#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string>
#include<windows.h>
#include<conio.h>
using namespace std;
#define X 10
#define Y 10
#define mines 10
char grid[Y][X];
bool click[Y][X],minexy[Y][X],flag[Y][X];
void Draw()
{
    system("cls");
    cout<<"No. if mines: "<<mines<<endl;
    cout<<"No. of flags used: ";
    int count=0;
    for(int y=0;y<Y;y++)
    for(int x=0;x<X;x++)
    if(flag[y][x])
    count++;
    cout<<count<<endl;
    cout<<"   ";
    for(int x=0;x<X;x++)
    cout<<x<<" ";
    cout<<endl;
    cout<<"   ";
    for(int x=0;x<X;x++)
    cout<<"--";
    cout<<endl;
    for(int y=0;y<Y;y++)
    {
        cout<<y<<"| ";
        for(int x=0;x<X;x++)
        {
            if(click[y][x]) {cout<<grid[y][x]<<" ";}
            else if(flag[y][x]) {cout<<"F ";}
            else {cout<<"# ";}
        }
        cout<<"|"<<y<<endl;
    }
    cout<<"   ";
    for(int x=0;x<X;x++)
    cout<<"--";
    cout<<endl;
    cout<<"   ";
    for(int x=0;x<X;x++)
    cout<<x<<" ";
    cout<<endl;
}
void updateValue(int x,int y)
{
    if(grid[y][x]!='M')
    {
        if(grid[y][x]==' ')grid[y][x]='1';
        else if(grid[y][x]=='1')grid[y][x]='2';
        else if(grid[y][x]=='2')grid[y][x]='3';
        else if(grid[y][x]=='3')grid[y][x]='4';
        else if(grid[y][x]=='4')grid[y][x]='5';
        else if(grid[y][x]=='5')grid[y][x]='6';
        else if(grid[y][x]=='6')grid[y][x]='7';
        else if(grid[y][x]=='7')grid[y][x]='8';
        else if(grid[y][x]=='8')grid[y][x]='9';
    }
}
void AssignBombValue(int x,int y)
{
    int l,r,u,d,lux,luy,ldx,ldy,rux,ruy,rdx,rdy;
    if(x>0 && x<X-1)
    {
        l=x-1;
        updateValue(l,y);
        r=x+1;
        updateValue(r,y);
        if(y>0 && y<Y-1)
        {
            u=y-1;
            updateValue(x,u);
            d=y+1;
            updateValue(x,d);
            lux=x-1;
            luy=y-1;
            updateValue(lux,luy);
            ldx=x-1;
            ldy=y+1;
            updateValue(ldx,ldy);
            rux=x+1;
            ruy=y-1;
            updateValue(rux,ruy);
            rdx=x+1;
            rdy=y+1;
            updateValue(rdx,rdy);
        }
        else if(y==0)
        {
            d=y+1;
            updateValue(x,d);
            ldx=x-1;
            ldy=y+1;
            updateValue(ldx,ldy);
            rdx=x+1;
            rdy=y+1;
            updateValue(rdx,rdy);
        }
        else if(y==Y-1)
        {
            u=y-1;
            updateValue(x,u);
            lux=x-1;
            luy=y-1;
            updateValue(lux,luy);
            rux=x+1;
            ruy=y-1;
            updateValue(rux,ruy);
        }
    }
    else if(x==0)
    {
        r=x+1;
        updateValue(r,y);
        if(y>0 && y<Y-1)
        {
            u=y-1;
            updateValue(x,u);
            d=y+1;
            updateValue(x,d);
            rux=x+1;
            ruy=y-1;
            updateValue(rux,ruy);
            rdx=x+1;
            rdy=y+1;
            updateValue(rdx,rdy);
        }
        else if(y==0)
        {
            d=y+1;
            updateValue(x,d);
            rdx=x+1;
            rdy=y+1;
            updateValue(rdx,rdy);
        }
        else if(y==Y-1)
        {
            u=y-1;
            updateValue(x,u);
            rux=x+1;
            ruy=y-1;
            updateValue(rux,ruy);
        }
    }
    else if(x==X-1)
    {
        l=x-1;
        updateValue(l,y);
        if(y>0 && y<Y-1)
        {
            u=y-1;
            updateValue(x,u);
            d=y+1;
            updateValue(x,d);
            lux=x-1;
            luy=y-1;
            updateValue(lux,luy);
            ldx=x-1;
            ldy=y+1;
            updateValue(ldx,ldy);
        }
        else if(y==0)
        {
            d=y+1;
            updateValue(x,d);
            ldx=x-1;
            ldy=y+1;
            updateValue(ldx,ldy);
        }
        else if(y==Y-1)
        {
            u=y-1;
            updateValue(x,u);
            lux=x-1;
            luy=y-1;
            updateValue(lux,luy);
        }
    }
}
void revealSpace(int x,int y)
{
	if(!click[y][x] && grid[y][x]!='M' && x>=0 && x<X && y>=0 && y<Y)
    {
    	if(grid[y][x]==' ')
    	{
//    	    if(!minexy[y][x])
//	        {
        	    click[y][x]=true;
    	        revealSpace(x,y-1);
	            revealSpace(x,y+1);
            	revealSpace(x-1,y);
        	    revealSpace(x+1,y);
    	        revealSpace(x-1,y-1);
	            revealSpace(x-1,y+1);
            	revealSpace(x+1,y-1);
        	    revealSpace(x+1,y+1);
//    	    }
	    }
    	else
	    	click[y][x]=true;
	}
}
int main()
{
	int countClicks,safe=(X*Y)-mines;
    for(int y=0;y<Y;y++)
    for(int x=0;x<X;x++)
    {
        grid[y][x]=' ';
        click[y][x]=false;
        minexy[y][x]=false;
        flag[y][x]=false;
    }
    srand(time(0));
    for(int i=0;i<mines;i++)
    {
        int x,y;
        do{
            x=rand()%X;
            y=rand()%Y;
            if(!minexy[y][x])
            {
                minexy[y][x]=true;
                break;
            }
        }while(1);
        grid[y][x]='M';
    }
    for(int y=0;y<Y;y++)
    for(int x=0;x<X;x++)
    {
        if(minexy[y][x])
        AssignBombValue(x,y);
    }
    do{
        Draw();
        cout<<"Enter coordinates(Row Col): ";
        char char1,char2,char3;
        cin>>char1>>char2;
        if(char1=='F' || char1=='f')
        {
        	cin>>char3;
        	int y=atoi(&char2);
        	int x=atoi(&char3);
    	    x=x/10;
        	if(!flag[y][x])
        	flag[y][x]=true;
        	else
        	flag[y][x]=false;
		}
        else
        {
        	int y=atoi(&char1);
        	int x=atoi(&char2);
    	    x=x/10;
    	    if(minexy[y][x])
	        {
            	click[y][x]=true;
        	    break;
    	    }
	        revealSpace(x,y);
		}
		countClicks=0;
		for(int y=0;y<Y;y++)
   		for(int x=0;x<X;x++)
   		if(click[y][x])
   		countClicks++;
    }while(countClicks<safe);
    Draw();
    if(countClicks==safe)
    cout<<"\tYOU WIN";
    else
    {
    	for(int y=0;y<Y;y++)
    	for(int x=0;x<X;x++)
    	if(minexy[y][x])
    	click[y][x]=true;
    	Draw();
    	cout<<"\tYou LOSE";
	}
    cout<<"\n Thank you for playing!!\nEnter any button to exit....";
    getch();
}