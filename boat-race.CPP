#include<conio.h>
#include<PROCESS.h>
#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<iostream.h>

int i,j,k,p,score;
union REGS in,out;
int exite(int);

int mousehide()
{
	in.x.ax=2;
	int86(51,&in,&out);
	return 1;
}
	
	
int traffic(int x, int j)
{
	//boat-body
	setfillstyle(1, RED);
	fillellipse(x, j,15,30);
	setfillstyle(1, BROWN);
	fillellipse(x, j,7.5,15);	
	//clearing graphics
	setfillstyle(1,CYAN);	
	fillellipse(x, j-60,15,30);
	return j;
}
	
void check(int xpos,int x1, int j)
{
	 traffic(xpos,j);
	 if(x1>xpos-30 && x1<xpos+30 && (j+29)<(getmaxy()-38) && (j+35)>(getmaxy()-43) )
	 {
		gotoxy(33,15);
		printf("GAME OVER");
		sound(2000);
	  	delay(100);
	  	sound(1000);
		delay(100);
		sound(200);
	  	delay(100);
	 	nosound();
	  	exite(2);
	  	delay(1000);
	  	exit(1);
	 }
}

getmouseposi(int *x, int *y, int *button)
{
	in.x.ax=3;
	int86(51,&in,&out);
	*x=out.x.cx;
	*y=out.x.dx;
	*button=out.x.bx;
	return 0;
}
	
void setposi(int &xpos,int &ypos)
{
	in.x.ax=4;
	in.x.cx=xpos;
	in.x.dx=ypos;
	int86(51,&in,&out);
}
		
int callmouse()
{
	in.x.ax=1;
	int86(51,&in,&out);
	return 1;
}
		
 void boat(int x1)
{       	
	//boat-body
	setfillstyle(1,BLACK);
	fillellipse(x1,getmaxy()-38,10,40);
	setfillstyle(1,BROWN);
	fillellipse(x1,getmaxy()-38,5,20);
	//clearing graphics
	setfillstyle(1,CYAN);	
	fillellipse(x1-20, getmaxy()-38,10,40);
	fillellipse(x1+20, getmaxy()-38,10,40);

}

void setgraphics()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"..\\bgi");
}
	
void setgraphics2()
{
	int gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
}
	
void start()
{
	setgraphics();
	setcolor(13);	//13=light-magenta
	settextstyle(10,0,5);
	outtextxy(getmaxx()/5,100,"BOAT RACE");
	delay(100);
	setcolor(13);
	settextstyle(10,0,3);
	outtextxy(getmaxx()/4,180,"CG Mini-Project");
	delay(100);
	setcolor(14);
	settextstyle(1,0,3);
	outtextxy(getmaxx()/2.5,250,"Made by:");
	delay(100);
	settextstyle(1,0,1);
	outtextxy(getmaxx()/4,280,"60004180087 : Rutu Gaglani");
	outtextxy(getmaxx()/4,300,"60004180097 : Saurav Tiwari");
	outtextxy(getmaxx()/4,320,"60004180098 : Sharayu Bokde");
	getch();
	closegraph();
	setgraphics2();
}
	
int exite(int g)
{
	cleardevice();
	setgraphics();
	if(g==1)
	{
		setcolor(15);
		settextstyle(10,0,4);
		outtextxy(40,140,"THANKS");
		delay(1000);
		exit(1);
	}
	else
	{
		setcolor(12);
		settextstyle(10,0,4);
		outtextxy(40,140,"GAME OVER");
		delay(1000);
		exit(1);
 	}
	setgraphics2();
}
	
void track()
{
	int i,gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"");
	setfillstyle(1,GREEN);
	bar3d(0,0,getmaxx()/3,getmaxy(),0,0);
	setfillstyle(1,GREEN);
	bar3d(2*getmaxx()/3,0,getmaxx(),getmaxy(),0,0);
	setfillstyle(1,CYAN);
	bar3d(getmaxx()/3,0,2*getmaxx()/3,getmaxy(),0,0);
}
	
void mainscreen()
{
	start();
	clrscr();
	char ch=7;
	int x1,y1,x2,y2,button;
	i=j=k=0;
	track();
 	p=0;
	callmouse();
	
	setposi(370,getmaxy());

	setfillstyle(1,RED);
	bar3d(550,150,560,350,0,0);
	outtextxy(565,150,"FINISH ");
	outtextxy(565,350,"START ");
	outtextxy(465,50,"Press ESC for exit ");
	while(1)
	{
		if(p<2000)
		{
			setfillstyle(1,15);
			bar3d(550,350-p/10,560,350,0,0);
		}
		sound(p);
	
		if(p>2000)
		{
			 gotoxy(30,15);
			 printf("level 1 CLEARED");
			 delay(2000);
			 exite(1);
			 exit(1);
		}
	
		gotoxy(1,1);
		printf("%d",i);
		gotoxy(1,3);
		printf("%d",p);
		gotoxy(1,5);
		printf("%d",j);
		setcolor(RED);
		outtextxy(520,5,"SCORE=");
		gotoxy(75,1);
		printf("%d",p);
	
		setcolor(CYAN);
	
		setcolor(GREEN);
		setfillstyle(1,GREEN);
		bar3d(170,getmaxy()-62,getmaxx()/3,getmaxy(),0,0);
		setfillstyle(1,GREEN);
		bar3d(2*getmaxx()/3,getmaxy()-50,500,getmaxy(),0,0);
		setcolor(CYAN);
	
		//obstacle 1
		if(p==20)
			j=0;
	
		if(p>20 && p<499)
		{
			check(370,x1,j++);
			check(330,x1,k-60);
			k=k+3;
		}
	
		//obstacle 2
		if(p==1800)
			k=0;
		if(p>1800 && p<2000)
		{
			check(370,x1,k);
			check(230,x1,k-100);
			k++;
		}
		//obstacle 3
		if(p==900)
			k=0;
	
		if(p>900 && p<1400)
		{
			check(370,x1,k);
			check(230,x1,k-200);
			k++;
		}
	
	
		//obstacle 4
		if(p==500)
			j=0;
		
		if(p>500 && p<1000)
		{
			check(370,x1,k);
			check(230,x1,j);
			k++;
			j=j+3;
		}
	
		//obstacle 5
		if(p==1200)
			j=0;
	
		if(p>1200 && p<1700)
		{
			check(270,x1,j);
			j++;
		}
	
	
		//obstacle 6
		if(p==1500)
			k=0;
	
		if(p>1500 && p<2000)
		{
			check(320,x1,k-60);
			check(360,x1,j);
			k=k+2;
			j--;
		}
	
		//obstacle 7
		if(p==200)
			k=0;
	
		if(p>200 && p<700)
		{
			check(230,x1,k);
			check(380,x1,k-130);
			k++;
		}
	
		getmouseposi(&x1,&y1,&button);
		setcolor(CYAN);
		if( (x1>210)&&(x1<400) )
		{
			boat(x1);
			mousehide();
		}
	
		if(kbhit())
		{
			p=getmaxx()/3;
			ch=getch();
			if(ch==27)
			{
			exite(1);
			delay(100);
			exit(1);
			}
		}
	
		if(i>300)
		{
			setfillstyle(1,CYAN);
			bar3d(getmaxx()/2,0,(getmaxx()/2)+10,getmaxy(),0,0);
			i=0;
		}
		i++;
		p++;
		j++;
		k++;
	}
	getch();
}
	
void main()
{
	clrscr();
	mainscreen();
	delay(100);
}


 
