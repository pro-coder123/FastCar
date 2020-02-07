#define cls cleardevice();
#define sq(a,b) \
setfillstyle(1,8);\
bar(a,b,a+50,b+50);
#define GRAPHPATH "C:\\TurboC3\\BGI"
#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
int settings();
void speedometer(int);
int highscore(int);
void car(int);
void road(int);
void bomb(int,int);
void coin(int,int);
void gas(int,int);
void load(int);
void endgame();
void credits();
int left=19200,right=19712,knt=0,fuel=0,c=250,col=4,e=4,high,p;
float speed;
char string[5],l[]={char(27),'\0'},r[]={char(26),'\0'},u[]={char(24),'\0'},d[]={char(25),'\0'};
class game{
	  public:
		int point;
		char name[100];
}player,t[300],temp;
int homescreen()
{
	int a,b,p=0,ran=random(2)+1,q=190,i=0,poly1[]={0,0,0,getmaxy(),getmaxx(),getmaxy(),0,0},poly2[]={0,getmaxy(),getmaxx(),getmaxy(),getmaxx(),0};
	cls
	top:
	randomize();
	setfillstyle(11,BLUE);
	setcolor(BLACK);
	fillpoly(3,poly1);
	fillpoly(3,poly2);
	//bar(0,0,getmaxx(),getmaxy());
	b=7181;
	if(p>4) p=0;
	else if(p<0) p=4;
	setbkcolor(BLACK);
	for(i=0;i<5;i++)
	{
		setcolor(WHITE);
		setfillstyle(1,LIGHTGRAY);
		bar3d(140,q,400,q+30,10,1);
		q+=50;
	}
	q=190;
	if(p==1) q+=50;
	if(p==2) q+=100;
	if(p==3) q+=150;
	if(p==4) q+=200;
	setfillstyle(1,GREEN);
	setcolor(WHITE);
	bar3d(120,q-7,420,q+40,10,1);
	q=192;
	settextstyle(7,0,2);
	setcolor(BLUE);
	outtextxy(200,q,"START");
	outtextxy(200,q+50,"INSTRUCTIONS");
	outtextxy(200,q+100,"HIGHSCORES");
	outtextxy(200,q+150,"SETTINGS");
	outtextxy(200,q+200,"EXIT");
	a=0;
	while(!kbhit())
	{
		settextstyle(7,0,10);
		i=random(15);
		setcolor(i);
		outtextxy(80,0,"Fast");
		outtextxy(350,0,"Car");
		delay(200);
	}
	while(a!=7181)
	{
	  if(kbhit()) a=bioskey(0);
	  if(a==20480)
	  {
		  cls p++;a=0;goto top;
	  }
	  else if(a==18432)
	  {
		  cls p--;a=0;goto top;
	  }
	}
	if(p==0)
	{
	  cls
	  setcolor(15);
	  load(ran);
	  c=250;
	  setbkcolor(BLACK);
	  player.point=0;
	  return 0;
	}
	else if(p==1)
	{
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  settextstyle(7,0,5);
	  if(knt%2==0)
	  {
			outtextxy(50,180,"Press arrow keys");
			outtextxy(50,210,"to move the car");
			settextstyle(0,0,3);
			sq(100,350);sq(170,350);
			sq(240,350);sq(170,290);
			outtextxy(110,362,l);outtextxy(260,362,r);outtextxy(185,362,d);
			outtextxy(185,312,u);
			settextstyle(7,0,5);

	  }
	  else
	  {
			outtextxy(50,200,"Press Z and X keys");
			outtextxy(50,230,"to move the car");
	  }
	  delay(2000);
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  outtextxy(50,200,"Press esc to pause");
	  delay(2000);
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  outtextxy(50,200,"Watch out for the bombs");
	  bomb(200,300);
	  delay(2000);cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  outtextxy(50,200,"Collect as many");
	  outtextxy(50,230,"coins as possible to");
	  outtextxy(50,260,"earn points");
	  coin(200,330);
	  delay(2000);
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  outtextxy(50,200,"Check your fuel tank");setfillstyle(4,RED);
	  bar(320,250,325,350);bar(325,345,370,350);bar(370,350,375,250);
	  setfillstyle(9,RED);bar(325,300,370,345);
	  delay(2000);
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  outtextxy(50,200,"Collect gas to refill");
	  outtextxy(50,230,"your fuel tank");
	  gas(200,330);
	  delay(2000);
	  cls
	  if(kbhit()) b=bioskey(0);
	  if(b!=7181) goto top;
	  setbkcolor(BLACK);
	  setcolor(WHITE);
	  settextstyle(7,0,5);
	  outtextxy(50,200,"This is your speedometer");
	  speedometer(80);
	  delay(2000);
	  cls
	  goto top;
	}
	else if(p==2)
	{
	  highscore(1);goto top;
	}
	else if(p==3)
	{
	  settings();goto top;
	}
	else if(p==4)
	{
		credits();goto top;
	}
	return 0;
}
int pause()
{
	cls
	int p=255,a;
	top:
	if(p>355) p=255;
	else if(p<255) p=355;
	setbkcolor(BLACK);
	settextstyle(0,0,2);
	setfillstyle(2,1);
	bar3d(50,100,200,450,100,1);
	setcolor(WHITE);
	outtextxy(100,190,"POINTS :");
	outtextxy(300,190,string);
	outtextxy(100,250,"RESUME");
	outtextxy(100,300,"GOTO MENU");
	outtextxy(100,350,"EXIT");
	a=0;
	bomb(80,p);
	while(a!=7181)
	{
	  if(kbhit())
		  a=bioskey(0);
	  if(a==20480)
	  {
		  cls p+=50;a=0;goto top;
	  }
	  else if(a==18432)
	  {
		  cls p-=50;a=0;goto top;
	  }
	}
	if(p==255)
	{
		setbkcolor(BLACK);
		cls settextstyle(0,0,5);
		car(p);road(10);
		outtextxy(270,230,"3");
		delay(900);
		cls car(p);road(10);
		outtextxy(270,230,"2");
		delay(900);
		cls car(p);road(10);
		outtextxy(270,230,"1");
		delay(900); cls
		return 0;
	}
	else if(p==305){cls homescreen();}
	else if(p==355) credits();
	return 1;
}
int settings()
{
	int a=0,p=205,i,q=192;
	up:
	if(p>355) p=205;
	else if(p>255 && p<355 && a==20480) p=355;
	else if(p>255 && p<355 && a==18432) p=255;
	else if(p<205) p=355;
	cls   a=0;
	bomb(80,p);
	setcolor(CYAN);
	settextstyle(7,0,2);
	outtextxy(100,q,"ENABLE SOUND");
	outtextxy(100,q+50,"CONTROL CONFIG");
	outtextxy(100,q+150,"BACK");
	while(a!=7181)
	{
	  if(kbhit())
		  a=bioskey(0);
	  if(a==20480)
	  {
		  cls p+=50;goto up;
	  }
	  else if(a==18432)
	  {
		  cls p-=50;goto up;
	  }
	}
	if(p==255)
	{
	  cls a=0;
	  bomb(80,205);
	  if(knt%2==0) outtextxy(100,200,"Controls : Arrow Keys");
	  else outtextxy(100,200,"Controls : Z & X");
	  while(bioskey(0)!=7181) bomb(80,205);
	  if(knt%2==0)
	  {
		    cls
		    outtextxy(100,200,"Controls : Z & X");
		    left=11386;
		    right=11640;
		    getch();
	  }
		  else
		  {  cls
		    outtextxy(100,200,"Controls : Arrow Keys");
		    left=19200;
		    right=19712;
		    getch();
		  }
		  getch();
		  knt++;
		  goto up;
	}
	else if(p==205)
	{
		cls
		for(i=0;i<getmaxx();i++)
		{
			setcolor(BLUE);
			bar(0,450,i,460);
			outtextxy(10,250,"Searching for sound hardware");
			delay(10);
		}
		outtextxy(10,350,"Sound hardware not found");delay(1500);cls
	}
	else if(p==355)
	{
	  cls
	  return 0;
	}
	return 0;
}
void gas(int x,int y)
{
    int a[]={218+x,50+y-100,246+x,y-100,283+x,50+y-100};
    setcolor(RED);
    setfillstyle(1,RED);
    pieslice(250+x,100+y-100,230,310,50);
    setcolor(WHITE);
    bar(218+x,137+y-100,283+x,50+y-100);
    pieslice(250+x,10+y-100,230,310,50);
    setcolor(BLACK);
    setfillstyle(1,BLACK);
    fillpoly(3,a);
    setcolor(WHITE);
    arc(250+x,86+y-100,50,130,50);
    setcolor(BLACK);
    settextstyle(0,1,2);
    outtextxy(256+x,80+y-100,"GAS");
    setcolor(15);
}
void speedometer(int speed)
{
	float x1=550,y1=485,x;
	if(speed>=15 && speed<30);
		x=random(10)+165;
	if(speed>=20 && speed<35)
		x=random(30)+130;
	if(speed>=25 && speed<40)
		x=random(20)+90;
	if(speed>=30 && speed<50)
		x=random(20)+50;
	if(speed>=35 && speed<55)
		x=random(15)+25;
	settextstyle(0,0,1);


	setfillstyle(1,BLACK);
	pieslice(x1,y1,0,180,50);
	setcolor(GREEN);
	pieslice(x1,y1,-195,x,45);
	setcolor(BLACK);
	circle(x1,y1,45);
	setfillstyle(1,RED);
	pieslice(x1,y1,0,180,30);
	setcolor(WHITE);
	outtextxy(540,470,"mph");
	outtextxy(510,470,"0");
	outtextxy(544,437,"50");
	outtextxy(576,470,"100");
}
void load(int n)
{
	settextstyle(0,0,3);
	for(int i=0;i<n;i++)
	{
		outtextxy(5,170,"Loading");
		delay(300);
		cls
		outtextxy(5,170,"Loading.");
		delay(300);
		cls
		outtextxy(5,170,"Loading..");
		delay(300);
		cls
		outtextxy(5,170,"Loading...");
		delay(300);
		cls
	}
}
void bomb(int x,int y)
{
	setcolor(WHITE);
	line(x,y-15,x+10,y-25);
	setfillstyle(9,8);
	bar(x-5,y-15,x+5,y-5);
	setfillstyle(8,8);
	fillellipse(x,y,10,10);

}
void coin(int x,int y)
{
	int a[]={x,y-15,x+10,y,x,y+15,x-10,y,x,y-10};
	setfillstyle(11,14);
	fillpoly(4,a);
}
void car(int x)
{
	int a[]={x+100,300,x+150,300,x+170,420,x+80,420,x+100,300};
	setfillstyle(2,8);
	bar(x+160,320,x+170,350);
	bar(x+170,375,x+180,405);     //Wheels
	bar(x+80,320,x+90,350);
	bar(x+70,375,x+80,405);

	setfillstyle(6,4);    //car body
	fillpoly(4,a);

	setfillstyle(1,7);
	bar(x+155,435,x+160,420);    //bottom
	bar(x+90,435,x+95,420);

	int b[]={x+100,345,x+150,345,x+140,400,x+110,400,x+100,445};
	int c[]={x+105,415,x+145,415,x+150,430,x+100,430,x+150,415};
	setfillstyle(1,0);
	pieslice(x+125,340,0,180,25);
	fillpoly(4,b);
	setfillstyle(2,1);
	fillpoly(4,c);
	line(x+110,415,x+115,405);
	line(x+140,415,x+135,405);
}
void road(int a)
{
	int y=getmaxy(),i;
	setcolor(15);
	line(0,0,0,y);
	for(i=0;i<=y;i+=50)
	  line(120,i+a,120,i+a+15);         //lanes
	for(i=0;i<=y;i+=50)
	  line(240,i+a,240,i+a+15);
	for(i=0;i<=y;i+=50)
	  line(360,i+a,360,i+a+15);
	line(480,0,480,y);
	setcolor(3);
	settextstyle(0,0,1);
	outtextxy(500,100,"Press Y to exit");
	outtextxy(500,130,"Press Esc to pause");
	itoa(player.point,string,10);
	settextstyle(0,0,2);
	setcolor(2);
	outtextxy(500,30,"Points");
	outtextxy(500,50,string);
	if(player.point>high)                  //new highscore
	{
		setcolor(GREEN);
		settextstyle(5,0,7);
		outtextxy(130,200,"New Highscore");
		delay(500);high=32000;
	}
	setfillstyle(RED,4);
	outtextxy(500,200,"Fuel :");
	bar3d(520,250,525,350,15,1);
	bar3d(525,345,570,350,15,1);
	bar3d(570,350,575,250,15,1);
	setfillstyle(9,col);
	bar3d(525,c,570,345,15,1);
	if(fuel%e==0) c++;
	if(c>345) endgame();
	else if(c>330)
	{
		outtextxy(140,200,"FUEL CRITICALLY LOW!");
		col=fuel;
	}
	setcolor(WHITE);
	fuel++;
	speedometer(speed);
}
void move(int &p)
{
	  int a;
	  up:a=0;
	  if(kbhit()) a=bioskey(0);
	  if(a==right) p+=120;
	  if(a==left) p-=120;
	  if(a==283) pause();
	  a=0;
	  if(p>340) p-=120;
	  if(p<-100) p+=120;
}
void again(int pt)
{
	cls
	player.point+=pt;
}
void endgame()
{
	sound(200);
	delay(100);
	nosound();
	cls
	int i=0,w,x;
	char c[50][50];
	top:
	x=120;
	setbkcolor(WHITE+BLUE);
	randomize();
	int a[]={100,100,600,100,600,300,100,300,100,100},ran=random(4);
	char b[4];
	setfillstyle(11,BLUE);
	setcolor(WHITE);
	fillpoly(4,a);
	fstream f("score.dat",ios::out |  ios::app | ios::binary);
	settextstyle(0,1,3);
	setcolor(BLUE);
	outtextxy(70,70,"GAME   OVER");
	settextstyle(0,0,3);
	itoa(player.point,b,10);
	setcolor(RED);
	outtextxy(100,140,"POINTS:");
	setcolor(WHITE);
	outtextxy(300,140,b);
	setcolor(RED);
	outtextxy(100,186,"Enter Your Name :");
	settextstyle(8,0,3);
	setcolor(BLACK);
	setfillstyle(5,6);
	bar(120,260,500,270);
	setcolor(i+1);
	for(w=0;w<i;w++)
	{
		if(w!=BLACK) setcolor(w);
		else setcolor(CYAN);
		outtextxy(x,226,c[w]);x+=20;
	}
	c[i][0]=getch();
	c[i][1]='\0';
	while(c[i][0]!='\r')
	{
		if(c[i][0]=='\b')
		{
			x-=20;  i--;if(i<0)i=0; c[i][0]='\0';cls goto top;
		}
		if(i!=BLACK) setcolor(i);
		else setcolor(CYAN);
		outtextxy(x,226,c[i]);
		i++;
		c[i][0]=getch();
		c[i][1]='\0';
		x+=20;
	}
	for(w=0;w<i;w++)
		player.name[w]=c[w][0];
	player.name[w]='\0';
	f.write((char*)&player,sizeof(player));
	f.close();
	load(ran);
	highscore(1);
	credits();
}
int highscore(int ch)
{
	cls
	int i=0,n,j,y=77;
	char point[300][5];

	fstream f("score.dat",ios::in | ios::binary);
	f.seekg(0);
	f.read((char*)&t[0],sizeof(game));
	while(f)
	{
	  i++;
	  f.read((char*)&t[i],sizeof(game));
	}
	for(n=0;n<i;n++)
	   for(j=n+1;j<i;j++)
		if(t[n].point<t[j].point)
		{
			temp=t[n];
			t[n]=t[j];
			t[j]=temp;
		}
	if(ch==0) {f.close();  return t[0].point; }
	setbkcolor(GREEN);
	settextstyle(6,0,2);
	setcolor(8);
	outtextxy(190,30,"High Scores");
	for(n=0;n<i;n++) itoa(t[n].point,point[n],10);
	n=0;
	while(n<i)
	{
	  settextstyle(7,0,2); setcolor(RED);
	  outtextxy(50,y,t[n].name);
	  setcolor(BLUE);
	  outtextxy(500,y,point[n]);
	  y+=47;   n++;
	  if(n==8)break;
	}
	getch();
	cls
	f.close();
	return 0;
}
void credits()
{
  /*	int g,x=10,y=250;
	cls
	randomize();
	for(g=4;g>=1;g--)
	{
		settextstyle(8,HORIZ_DIR,g);
		setbkcolor(BLACK);
		setcolor(g+random(2)+1);
		outtextxy(x,200,"A GAME BY VARUN MUKUNDHAN");
		outtextxy(x+50,y,"12-F1");
		x+=30;
		y-=7;
		delay(1000);
		cls
	}
	setbkcolor(YELLOW);
	setcolor(RED);
	settextstyle(5,HORIZ_DIR,5);
	outtextxy(100,200,"Thank You For Playing");
	outtextxy(100,250,"I really appreciate it");
	getch();*/
	exit(0);
}
void main()
{
	int gd=DETECT,gm,i;
	initgraph(&gd,&gm,GRAPHPATH);
	/*settextstyle(5,0,2);
	high=highscore(0);
	outtextxy(150,200,"Developed By :");
	settextstyle(4,0,5);
	setcolor(GREEN);
	delay(2000);
	outtextxy(100,250,"Atomic ARTS inc ");
	for(i=0;i<=360;i++)
	{
		setcolor(BLUE);
		ellipse(320,240,0,i,300,200);
		delay(12);
		if(kbhit())
		{ ellipse(320,240,0,360,300,200);break; }
	}
	if(kbhit())
		bioskey(0);
	delay(500);*/
	homescreen();
	p=56;
	int k=100,lane=100,ktr,pt=0;
	float n;
	player.point=0;
	setbkcolor(BLACK);
	randomize();
	setviewport(10,0,486,getmaxy(),0);
	  start:
	  nosound();
	  if(player.point>=0 && player.point<50)                         //point & speed scheme
	  {
		  speed=random(15)+15;
		  pt=10;
	  }
	  if(player.point>=50 && player.point<100)                         //point & speed scheme
	  {
		  speed=random(15)+20;
		  pt=15;
	  }
	  else if(player.point>=100 && player.point<250)
	  {
		  speed=random(15)+25;
		  pt=20;  e=3;
	  }
	  else if(player.point>=250 && player.point<350)
	  {
		  speed=random(20)+30;
		  pt=25;  e=2;
	  }
	  else if(player.point>=350)
	  {
		  speed=random(20)+35;
		  pt=30; e=1;
	  }
	  k=random(5);
	  if(k==0 || k==1)                             //3 bombs
	  {
		  lane=random(4);
		  if(lane==0)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 bomb(180,ktr);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if((p>=-64 && p<176)||(p>=296 && p<416))
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==1)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 bomb(180,ktr);
			 bomb(300,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=-64 && p<296)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==2)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(180,ktr);
			 bomb(300,ktr);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=56 && p<416)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==3)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 bomb(300,ktr);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if((p>=-64 && p<56)||(p>=176 && p<416))
			 {
				 car(p);
				 endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				 again(pt);
				 goto start;
			 }
		    }
		  }
	  }
	  else if(k==2)
	  {                                            //1 bomb
		  lane=random(4);
		  if(lane==0)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 gas(55,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 {
				if(p>=-64 && p<56)
				{
					 car(p);
					 endgame();
				}
				if(p>=176 && p<296)
				{
					if(c>=300) c-=50;else c=250 ;col=4;
					goto start;
				}
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==1)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(180,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=56 && p<176)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				 again(pt);
				 goto start;
			 }
		    }
		  }
		  else if(lane==2)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(300,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=176 && p<296)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				 again(pt);
				 goto start;
			 }
		    }
		  }
		  else if(lane==3)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=296 && p<416)
			 {
				 car(p);
				 endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				 again(pt);
				 goto start;
			 }
		    }
		  }
	  }
	  else if(k==3)                               //2 bombs
	  {
		  lane=random(4);
		  if(lane==0)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 bomb(180,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=-64 && p<176)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==1)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(180,ktr);
			 bomb(300,ktr);
			 gas(-195,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)

			 {
				if(p>=56 && p<296)
				{
					 car(p);
					 endgame();
				}
				if(p>=-64 && p<56)
				{
					if(c>=300) c-=50;else c=250 ;col=4;
					goto start;
				}
			 }
			 if(ktr>=getmaxy())
			 {
				 again(pt);
				 goto start;
			 }
		    }
		  }
		  else if(lane==2)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(300,ktr);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=176 && p<416)
			 {
				car(p);
				endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==3)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 bomb(60,ktr);
			 bomb(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if((p>=-64 && p<56)||(p>=296 && p<416))
			 {
				 car(p);
				 endgame();
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
	  }
	  else if(k==4)
	  {
		  lane=random(4);
		  if(lane==0)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 coin(60,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=-64 && p<56)
			 {
				 cls
				 sound(2000);delay(50);
				 player.point+=50;
				 goto start;
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==1)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 coin(180,ktr);
			 gas(176,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 {

				if(p>=56 && p<176)
				{
					 cls
					 sound(2000);delay(50);
					 player.point+=50;
					 goto start;
				 }
				 if(p>=296 && p<416)
				 {
					 if(c>=300) c-=50;else c=250 ;col=4;
					 goto start;
				 }
				}
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
		  }
		  else if(lane==2)
		  {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 coin(300,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=176 && p<296)
			 {
				 cls
				 sound(2000);delay(50);
				 player.point+=50;
				 goto start;
			 }
			 if(ktr>=getmaxy())
			 {
				again(pt);
				goto start;
			 }
		    }
	       }
	       else if(lane==3)
	       {
		    ktr=0;
		    for(n=0;;n+=3.3)
		    {
			 car(p);
			 road(n);
			 coin(420,ktr);
			 ktr+=speed;
			 move(p);
			 delay(50);
			 cls
			 if(ktr>=300 && ktr<=420)
			 if(p>=296 && p<416)
			 {
			       cls
			       sound(2000);delay(50);
			       player.point+=50;
			       goto start;
			 }
			 if(ktr>=getmaxy())
			 {
			       again(pt);
			       goto start;
			 }

		    }
		  }
	  }

}