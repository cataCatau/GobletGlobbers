#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>
using namespace std;
enum stadiu {meniu,play,playmenu,settings,color,leaderboard};
stadiu stadiuc=meniu;
int culoare,culoare1=4,culoare2=5,ok=0,jucator,cnt[4][4],cntculoare=0,scor1=0,scor2=0,botdif=0,urmmutare=0,ulpoz=1;
char NUME1[15]="PLAYER 1",NUME2[15]="PLAYER 2";

ifstream fin("clasament.txt");
struct inaltime
{
    int player,dim;
};
struct matrice
{
    int val=0,player=-1,contorpiesa=0;
    inaltime height[4];

} tabla[4][4];
struct clasament
{
    char poz[15],nume[15],scor[15];
    int scorint=0;

} clasament[101];
void dmeniu()
{
    stadiuc=meniu;
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
        {
            tabla[i][j].player=-1;
            tabla[i][j].val=0;
            cnt[i][j]=2;
            tabla[i][j].height[0].dim=0;
            tabla[i][j].height[0].player=-1;
        }
    setbkcolor(5);
    cleardevice();
    readimagefile("fundal.jpg",200,100,getmaxwidth()-200,getmaxheight()-400);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR, 3);
    rectangle(getmaxwidth()/2-textwidth("PLAY"),500,getmaxwidth()/2+textwidth("PLAY"),550);
    outtextxy(getmaxwidth()/2-textwidth("PLAY")+25,510,"PLAY");
    rectangle(getmaxwidth()/2-textwidth("SETTINGS"),600,getmaxwidth()/2+textwidth("SETTINGS"),650);
    outtextxy(getmaxwidth()/2-textwidth("SETTINGS")+50,610,"SETTINGS");
    rectangle(getmaxwidth()/2-textwidth("LEADERBOARD"),700,getmaxwidth()/2+textwidth("LEADERBOARD"),750);
    outtextxy(getmaxwidth()/2-textwidth("LEADERBOARD")+75,710,"LEADERBOARD");
    outtextxy(1,1,"EXIT");
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);


}
void dclasament()
{
    stadiuc=leaderboard;
    setbkcolor(0);
    cleardevice();
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    outtextxy(1,1,"BACK");
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(getmaxwidth()/2-175,20,"LEADERBOARD");
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    rectangle(getmaxwidth()/2-300,getmaxheight()/12,getmaxwidth()/2+300,getmaxheight());
    line(getmaxwidth()/2-200,getmaxheight()/12,getmaxwidth()/2-200,getmaxheight());
    line(getmaxwidth()/2+200,getmaxheight()/12,getmaxwidth()/2+200,getmaxheight());
    for(int i=1; i<=12; i++)
    {
        line(getmaxwidth()/2-300,getmaxheight()/12 *i,getmaxwidth()/2+300,getmaxheight()/12*i);
    }
    for(int i=2;i<=ulpoz;i++)
        for(int j=0; j<strlen(clasament[i].scor); j++)
            clasament[i].scorint=clasament[i].scorint*10+(clasament[i].scor[j]-48);
    int oksortare;
    do
    {
        oksortare=1;
        for(int i=2; i<ulpoz; i++)
            if(clasament[i].scorint<clasament[i+1].scorint)
            {
                swap(clasament[i].scor,clasament[i+1].scor);
                swap(clasament[i].nume,clasament[i+1].nume);
                swap(clasament[i].scorint,clasament[i+1].scorint);
                oksortare=0;
            }
    }
    while(oksortare==0);
    for(int i=1; i<=ulpoz; i++)
    {
        outtextxy(getmaxwidth()/2-290,getmaxheight()/12*i+10,clasament[i].poz);
        outtextxy(getmaxwidth()/2-190,getmaxheight()/12*i+10,clasament[i].nume);
        outtextxy(getmaxwidth()/2+210,getmaxheight()/12*i+10,clasament[i].scor);

    }
}
void verificareWIN()
{
    for(int i=1; i<=3; i++)
    {
        if(tabla[i][1].player==1 && tabla[i][2].player==1 && tabla[i][3].player==1)
        {
            delay(500);
            cleardevice();
            for(int i=1; i<=ulpoz; i++)
                if(strcmp(NUME1,clasament[i].nume)==0)
                {
                    int scor=std::atoi(clasament[i].scor);
                    scor++;
                    sprintf(clasament[i].scor, "%d", scor);
                    break;
                }
            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
            outtextxy(getmaxwidth()/2-textwidth(NUME1),getmaxheight()/2,NUME1);
            outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
            delay(1000);
            dmeniu();

        }
        if(tabla[i][1].player==0 && tabla[i][2].player==0  && tabla[i][3].player==0)
        {
            delay(500);
            cleardevice();
            for(int i=1; i<=ulpoz; i++)
                if(strcmp(NUME2,clasament[i].nume)==0)
                {
                    int scor=std::atoi(clasament[i].scor);
                    scor++;
                    sprintf(clasament[i].scor, "%d", scor);
                    break;
                }
            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
            outtextxy(getmaxwidth()/2-textwidth(NUME2),getmaxheight()/2,NUME2);
            outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
            delay(1000);
            dmeniu();
        }
        if(tabla[1][i].player==1 && tabla[2][i].player==1 && tabla[3][i].player==1)
        {
            delay(500);
            cleardevice();
            for(int i=1; i<=ulpoz; i++)
                if(strcmp(NUME1,clasament[i].nume)==0)
                {
                    int scor=std::atoi(clasament[i].scor);
                    scor++;
                    sprintf(clasament[i].scor, "%d", scor);
                    cout<<clasament[i].scor;
                    break;
                }
            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
            outtextxy(getmaxwidth()/2-textwidth(NUME1),getmaxheight()/2,NUME1);
            outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
            delay(1000);
            dmeniu();
        }
        if(tabla[1][i].player==0 && tabla[2][i].player==0  && tabla[3][i].player==0)
        {
            delay(500);
            cleardevice();
            for(int i=1; i<=ulpoz; i++)
                if(strcmp(NUME2,clasament[i].nume)==0)
                {
                    int scor=std::atoi(clasament[i].scor);
                    scor++;
                    sprintf(clasament[i].scor, "%d", scor);
                    break;
                }
            settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
            outtextxy(getmaxwidth()/2-textwidth(NUME2),getmaxheight()/2,NUME2);
            outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
            delay(1000);
            dmeniu();
        }
    }
    if(tabla[1][1].player==1 && tabla[2][2].player==1 && tabla[3][3].player==1)
    {
        delay(500);
        cleardevice();
        for(int i=1; i<=ulpoz; i++)
            if(strcmp(NUME1,clasament[i].nume)==0)
            {
                int scor=std::atoi(clasament[i].scor);
                scor++;
                sprintf(clasament[i].scor, "%d", scor);
                break;
            }
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
        outtextxy(getmaxwidth()/2-textwidth(NUME1),getmaxheight()/2,NUME1);
        outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
        delay(1000);
            dmeniu();
    }
    if(tabla[1][1].player==0 && tabla[2][2].player==0  && tabla[3][3].player==0)
    {
        delay(500);
        cleardevice();
        for(int i=1; i<=ulpoz; i++)
            if(strcmp(NUME2,clasament[i].nume)==0)
            {
                int scor=std::atoi(clasament[i].scor);
                scor++;
                sprintf(clasament[i].scor, "%d", scor);
                break;
            }
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
        outtextxy(getmaxwidth()/2-textwidth(NUME2),getmaxheight()/2,NUME2);
        outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
        delay(1000);
            dmeniu();
    }
    if(tabla[1][3].player==1 && tabla[2][2].player==1 && tabla[3][1].player==1)
    {
        delay(500);
        cleardevice();
        for(int i=1; i<=ulpoz; i++)
            if(strcmp(NUME1,clasament[i].nume)==0)
            {
                int scor=std::atoi(clasament[i].scor);
                scor++;
                sprintf(clasament[i].scor, "%d", scor);
                break;
            }
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
        outtextxy(getmaxwidth()/2-textwidth(NUME1),getmaxheight()/2,NUME1);
        outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
        delay(1000);
            dmeniu();
    }
    if(tabla[1][3].player==0 && tabla[2][2].player==0  && tabla[3][1].player==0)
    {
        delay(500);
        cleardevice();
        for(int i=1; i<=ulpoz; i++)
            if(strcmp(NUME2,clasament[i].nume)==0)
            {
                int scor=std::atoi(clasament[i].scor);
                scor++;
                sprintf(clasament[i].scor, "%d", scor);
                break;
            }
        settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
        outtextxy(getmaxwidth()/2-textwidth(NUME2),getmaxheight()/2,NUME2);
        outtextxy(getmaxwidth()/2+5,getmaxheight()/2,"WON");
        delay(1000);
        dmeniu();
    }
}
void desenpiesa(int x,int y,int dim)
{
    circle(x,y,30*dim);
    setfillstyle(SOLID_FILL,culoare);
    floodfill(x,y,WHITE);
    circle(x-15,y,dim*2);
    circle(x+15,y,dim*2);
}
void dplaymenu()
{
    stadiuc=playmenu;
    setbkcolor(5);
    cleardevice();
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
    outtextxy(1,1,"BACK");
    readimagefile("fundal.jpg",200,100,getmaxwidth()-200,getmaxheight()-400);
    rectangle(671,500,848,550);
    outtextxy(getmaxwidth()/2-textwidth("PLAY VS HUMAN")+75,510,"PLAY VS HUMAN");
    rectangle(590,600,917,650);
    outtextxy(getmaxwidth()/2-textwidth("PLAY VS BOT (RANDOM MOVES)")+150,610,"PLAY VS BOT (RANDOM MOVES)");
    rectangle(623,700,887,750);
    outtextxy(getmaxwidth()/2-textwidth("PLAY VS BOT (STRATEGY)")+120,710,"PLAY VS BOT (STRATEGY)");
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);

}
void dplay()
{
    stadiuc=play;
    ok=0;
    jucator=1 ;
    for(int i=1; i<=3; i++)
        for(int j=1; j<=3; j++)
        {
            tabla[i][j].player=-1;
            tabla[i][j].val=0;
            cnt[i][j]=2;
            tabla[i][j].contorpiesa=0;
        }
    setbkcolor(CYAN);
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,3);
    outtextxy(1,1,"BACK");
    outtextxy(1,350,NUME1);
    outtextxy(getmaxwidth()-textwidth(NUME2),350,NUME2);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);
    rectangle(0,30,getmaxwidth(),230);
    int dim=1;
    culoare=culoare1;

    for(int i=1; i<=7; i++)
    {
        line(getmaxwidth()/7*i,30,getmaxwidth()/7*i,230);
        desenpiesa(getmaxwidth()/7*i-105,130,dim);
        if(i==3)
        {
            dim=0;
            culoare=culoare2;
        }

        else
            dim++;
        setfillstyle(SOLID_FILL,CYAN);
        floodfill(762,132,WHITE);
        setcolor(BLACK);
        line(getmaxwidth()/7*2,250,getmaxwidth()/7*2,850);
        line(getmaxwidth()/7*3,250,getmaxwidth()/7*3,850);
        line(getmaxwidth()/7*4,250,getmaxwidth()/7*4,850);
        line(getmaxwidth()/7*5,250,getmaxwidth()/7*5,850);
        line(getmaxwidth()/7*2,250,getmaxwidth()/7*5,250);
        line(getmaxwidth()/7*2,450,getmaxwidth()/7*5,450);
        line(getmaxwidth()/7*2,650,getmaxwidth()/7*5,650);
        line(getmaxwidth()/7*2,850,getmaxwidth()/7*5,850);
        setcolor(WHITE);



    }



}

void dsettings()
{
    stadiuc=settings;
    setbkcolor(BLACK);
    cleardevice();
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,3);
    outtextxy(1,1,"BACK");
    line(getmaxwidth()/2,0,getmaxwidth()/2,getmaxheight());
    culoare=culoare1;
    desenpiesa(getmaxwidth()/4,getmaxheight()/2,3);
    culoare=culoare2;
    outtextxy(getmaxwidth()/4-50,100,NUME1);
    desenpiesa(getmaxwidth()/2+getmaxwidth()/4,getmaxheight()/2,3);
    rectangle(getmaxwidth()/4-textwidth("CHANGE NAME"),getmaxheight()/2+150,getmaxwidth()/4+textwidth("CHANGE NAME"),getmaxheight()/2+200);
    outtextxy(getmaxwidth()/4-75,getmaxheight()/2+160,"CHANGE NAME");
    rectangle(getmaxwidth()/4-textwidth("CHANGE COLOR"),getmaxheight()/2+250,getmaxwidth()/4+textwidth("CHANGE COLOR"),getmaxheight()/2+300);
    outtextxy(getmaxwidth()/4-75,getmaxheight()/2+260,"CHANGE COLOR");
    rectangle(getmaxwidth()/2+getmaxwidth()/4-textwidth("CHANGE NAME"),getmaxheight()/2+150,getmaxwidth()/2+getmaxwidth()/4+textwidth("CHANGE NAME"),getmaxheight()/2+200);
    outtextxy(getmaxwidth()/2+getmaxwidth()/4-75,getmaxheight()/2+160,"CHANGE NAME");
    rectangle(getmaxwidth()/2+getmaxwidth()/4-textwidth("CHANGE COLOR"),getmaxheight()/2+250,getmaxwidth()/2+getmaxwidth()/4+textwidth("CHANGE COLOR"),getmaxheight()/2+300);
    outtextxy(getmaxwidth()/2+getmaxwidth()/4-75,getmaxheight()/2+260,"CHANGE COLOR");
    outtextxy(getmaxwidth()/2+getmaxwidth()/4-50,100,NUME2);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR,1);

}
void ccolor()
{
    stadiuc=color;
    setcolor(WHITE);
    line(getmaxwidth()/7*2,250,getmaxwidth()/7*2,850);
    line(getmaxwidth()/7*3,250,getmaxwidth()/7*3,850);
    line(getmaxwidth()/7*4,250,getmaxwidth()/7*4,850);
    line(getmaxwidth()/7*5,250,getmaxwidth()/7*5,850);
    line(getmaxwidth()/7*2,250,getmaxwidth()/7*5,250);
    line(getmaxwidth()/7*2,450,getmaxwidth()/7*5,450);
    line(getmaxwidth()/7*2,650,getmaxwidth()/7*5,650);
    line(getmaxwidth()/7*2,850,getmaxwidth()/7*5,850);
    setfillstyle(SOLID_FILL,1);
    floodfill((652+435)/2,(250+450)/2,WHITE);
    setfillstyle(SOLID_FILL,2);
    floodfill((658+870)/2,(250+450)/2,WHITE);
    setfillstyle(SOLID_FILL,4);
    floodfill((870+1087)/2,(250+450)/2,WHITE);
    setfillstyle(SOLID_FILL,5);
    floodfill((652+435)/2,(450+650)/2,WHITE);
    setfillstyle(SOLID_FILL,6);
    floodfill((658+870)/2,(450+650)/2,WHITE);
    setfillstyle(SOLID_FILL,7);
    floodfill((870+1087)/2,(450+650)/2,WHITE);
    setfillstyle(SOLID_FILL,8);
    floodfill((652+435)/2,(650+850)/2,WHITE);
    setfillstyle(SOLID_FILL,9);
    floodfill((658+870)/2,(650+650)/2,WHITE);
    setfillstyle(SOLID_FILL,10);
    floodfill((870+1087)/2,(650+850)/2,WHITE);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,5);
    outtextxy(getmaxwidth()/2-textwidth("SELECT YOUR COLOR")+250,100,"SELECT YOUR COLOR");
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,1);
}
int verificareCastig(int player)
{
    for (int i=1; i<=3; i++)
        if (tabla[i][1].player==player && tabla[i][2].player==player && tabla[i][3].player==player)
            return 1;
    for (int i=1; i<=3; i++)
        if (tabla[1][i].player==player && tabla[2][i].player==player && tabla[3][i].player==player)
            return 1;
    if (tabla[1][1].player==player && tabla[2][2].player==player && tabla[3][3].player==player)
        return 1;
    if (tabla[1][3].player==player && tabla[2][2].player==player && tabla[3][1].player==player)
        return 1;
    return 0;
}

int main()
{
    fopen("clasament.txt","r+");
    int ok=0;
    while(fin>>clasament[ulpoz].poz)
    {
        fin>>clasament[ulpoz].nume;
        fin>>clasament[ulpoz].scor;
        ulpoz++;
    }
    initwindow(getmaxwidth(),getmaxheight());
    setlinestyle(SOLID_LINE,0,5);
    srand(time(0));
    dmeniu();
    while(true)
    {
        verificareWIN();/// verificam daca exista in matrice o combinatie ce rezulta in incheierea jocului

        if(cnt[1][1]==0)            /// verificam daca mai avem destule piese
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(115,127,CYAN);
            cnt[1][1]=-1;
        }
        if(cnt[1][2]==0)
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(331,127,CYAN);
            cnt[1][2]=-1;
        }
        if(cnt[1][3]==0)
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(549,204,CYAN);
            cnt[1][3]=-1;
        }
        if(cnt[2][1]==0)
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(987,127,CYAN);
            cnt[2][1]=-1;
        }
        if(cnt[2][2]==0)
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(1193,127,CYAN);
            cnt[2][2]=-1;
        }
        if(cnt[2][3]==0)
        {
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(1425,204,CYAN);
            cnt[2][3]=-1;
        }
        if (ismouseclick(WM_LBUTTONDOWN)) // daca  inregistram o apasare de mouse
        {

            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(stadiuc==meniu)
            {
                /// cele trei butoane din meniu
                if(x>=getmaxwidth()/2-textwidth("PLAY") && x<=getmaxwidth()/2+textwidth("PLAY") && y>=500 && y<=550)
                    dplaymenu();
                else if(x>=getmaxwidth()/2-textwidth("SETTINGS") && x<=getmaxwidth()/2+textwidth("SETTINGS") && y>=600 && y<=650)
                    dsettings();
                else if(x>=getmaxwidth()/2-textwidth("LEADERBOARD") && x<=getmaxwidth()/2+textwidth("LEADERBOARD") && y>=700 && y<=750)
                    dclasament();
                else if(x>=0 && x<=57 && y>=0 && y<=19)
                {
                    cout<<"program closed";
                    break;
                }
            }
            else if(stadiuc==playmenu)
            {
                if(x>=671 && x<=848 && y>=500 && y<=550) /// player vs player
                {
                    dplay();
                    botdif=0;
                }
                else if(x>= 590 && x<=917 && y>=600 && y<=650) /// player vs bot(miscari random)
                {
                    dplay();
                    botdif=1;
                }
                else if(x>=623 && x<=887 && y>=700 && y<=750) /// player vs bot(strategie)
                {
                    dplay();
                    botdif=2;
                }
                else
                    if(x>=0 && x<=57 && y>=0 && y<=19)
                        dmeniu();
            }
            else if(x>=0 && x<=57 && y>=0 && y<=19)
                dmeniu(); /// butonul de back dp celelalte 'pagini'

            else if(stadiuc==play)
            {

                if(y>57 && y<=230 && ok==0) /// selectarea piesei dorite din cele de sus
                {
                    if(x>=0 && x<=getmaxwidth()/7 && jucator%2==1 && cnt[1][1]>0)
                    {
                        ok=1;
                        cnt[1][1]--;
                    }
                    else if(x>=getmaxwidth()/7 && x<=getmaxwidth()/7*2 && jucator%2==1 && cnt[1][2]>0)
                    {
                        ok=2;
                        cnt[1][2]--;
                    }
                    else if(x>=getmaxwidth()/7*2 && x<=getmaxwidth()/7*3 && jucator%2==1 && cnt[1][3]>0)
                    {
                        ok=3;
                        cnt[1][3]--;
                    }
                    else if(x>=getmaxwidth()/7*4 && x<=getmaxwidth()/7*5 && jucator%2==0 && cnt[2][1]>0)
                    {
                        ok=1;
                        cnt[2][1]--;
                    }
                    else if(x>=getmaxwidth()/7*5 && x<=getmaxwidth()/7*6 && jucator%2==0 && cnt[2][2]>0)
                    {
                        ok=2;
                        cnt[2][2]--;
                    }
                    else if(x>=getmaxwidth()/7*6 && x<=getmaxwidth()/7*7 && jucator%2==0 && cnt[2][3]>0)
                    {
                        ok=3;
                        cnt[2][3]--;
                    }
                }
                if(ok!=0) /// plasarea piesei
                {
                    if(jucator%2==0)
                    {
                        culoare=culoare2;
                        setfillstyle(SOLID_FILL,culoare1);
                    }
                    else
                    {
                        culoare=culoare1;
                        setfillstyle(SOLID_FILL,culoare2);
                    }
                    floodfill(742,108,WHITE);
                    if(x>=435 && x<= 652 && y>=250 && y<=450 && ok>tabla[1][1].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((652+435)/2,(250+450)/2,ok);
                        tabla[1][1].val=ok;
                        tabla[1][1].player=jucator%2;
                        tabla[1][1].contorpiesa++;
                        tabla[1][1].height[tabla[1][1].contorpiesa].player=jucator%2;
                        tabla[1][1].height[tabla[1][1].contorpiesa].dim=ok;
                        jucator++;
                        ok=0;

                    }
                    if(x>=658 && x<= 870 && y>=250 && y<=450 && ok>tabla[1][2].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((658+870)/2,(250+450)/2,ok);
                        tabla[1][2].val=ok;
                        tabla[1][2].player=jucator%2;
                        tabla[1][2].contorpiesa++;
                        tabla[1][2].height[tabla[1][2].contorpiesa].player=jucator%2;
                        tabla[1][2].height[tabla[1][2].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=870 && x<= 1087 && y>=250 && y<=450 && ok>tabla[1][3].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((870+1087)/2,(250+450)/2,ok);
                        tabla[1][3].val=ok;
                        tabla[1][3].player=jucator%2;
                        tabla[1][3].contorpiesa++;
                        tabla[1][3].height[tabla[1][3].contorpiesa].player=jucator%2;
                        tabla[1][3].height[tabla[1][3].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=435 && x<= 652 && y>=450 && y<=650 && ok>tabla[2][1].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((652+435)/2,(650+450)/2,ok);
                        tabla[2][1].val=ok;
                        tabla[2][1].player=jucator%2;
                        tabla[2][1].contorpiesa++;
                        tabla[2][1].height[tabla[2][1].contorpiesa].player=jucator%2;
                        tabla[2][1].height[tabla[2][1].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=658 && x<= 870 && y>=450 && y<=650 && ok>tabla[2][2].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((658+870)/2,(650+450)/2,ok);
                        tabla[2][2].val=ok;
                        tabla[2][2].player=jucator%2;
                        tabla[2][2].contorpiesa++;
                        tabla[2][2].height[tabla[2][2].contorpiesa].player=jucator%2;
                        tabla[2][2].height[tabla[2][2].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=870 && x<= 1087 && y>=450 && y<=650 && ok>tabla[2][3].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((870+1087)/2,(650+450)/2,ok);
                        tabla[2][3].val=ok;
                        tabla[2][3].player=jucator%2;
                        tabla[2][3].contorpiesa++;
                        tabla[2][3].height[tabla[2][3].contorpiesa].player=jucator%2;
                        tabla[2][3].height[tabla[2][3].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=435 && x<= 652 && y>=650 && y<=850 && ok>tabla[3][1].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((652+435)/2,(650+850)/2,ok);
                        tabla[3][1].val=ok;
                        tabla[3][1].player=jucator%2;
                        tabla[3][1].contorpiesa++;
                        tabla[3][1].height[tabla[3][1].contorpiesa].player=jucator%2;
                        tabla[3][1].height[tabla[3][1].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=658 && x<= 870 && y>=650 && y<=850 && ok>tabla[3][2].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((658+870)/2,(650+850)/2,ok);
                        tabla[3][2].val=ok;
                        tabla[3][2].player=jucator%2;
                        tabla[3][2].contorpiesa++;
                        tabla[3][2].height[tabla[3][2].contorpiesa].player=jucator%2;
                        tabla[3][2].height[tabla[3][2].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }
                    if(x>=870 && x<= 1087 && y>=650 && y<=850 && ok>tabla[3][3].val)
                    {
                        setfillstyle(SOLID_FILL,CYAN);
                        floodfill(x,y,BLACK);
                        desenpiesa((870+1087)/2,(650+850)/2,ok);
                        tabla[3][3].val=ok;
                        tabla[3][3].player=jucator%2;
                        tabla[3][3].contorpiesa++;
                        tabla[3][3].height[tabla[3][3].contorpiesa].player=jucator%2;
                        tabla[3][3].height[tabla[3][3].contorpiesa].dim=ok;
                        ok=0;
                        jucator++;
                    }


                }
                else /// in cazul in care dorim mutarea unei piese deja pusa in matrice
                {
                    if(x>=435 && x<= 652 && y>=250 && y<=450 && tabla[1][1].val!=0  && tabla[1][1].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[1][1].val;
                        tabla[1][1].contorpiesa--;
                        tabla[1][1].val=tabla[1][1].height[tabla[1][1].contorpiesa].dim;
                        tabla[1][1].player=tabla[1][1].height[tabla[1][1].contorpiesa].player%2;
                        if(tabla[1][1].height[tabla[1][1].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[1][1].val!=0)
                            desenpiesa((652+435)/2,(250+450)/2,tabla[1][1].height[tabla[1][1].contorpiesa].dim);
                    }
                    if(x>=658 && x<= 870 && y>=250 && y<=450 && tabla[1][2].val!=0  && tabla[1][2].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[1][2].val;
                        tabla[1][2].contorpiesa--;
                        tabla[1][2].val=tabla[1][2].height[tabla[1][2].contorpiesa].dim;
                        tabla[1][2].player=(tabla[1][2].height[tabla[1][2].contorpiesa].player)%2;
                        if(tabla[1][2].height[tabla[1][2].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[1][2].val!=0)
                            desenpiesa((658+870)/2,(250+450)/2,tabla[1][2].height[tabla[1][2].contorpiesa].dim);
                    }
                    if(x>=870 && x<= 1087 && y>=250 && y<=450 && tabla[1][3].val!=0  && tabla[1][3].player==jucator%2 )
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[1][3].val;
                        tabla[1][3].contorpiesa--;
                        tabla[1][3].val=tabla[1][3].height[tabla[1][3].contorpiesa].dim;
                        tabla[1][3].player=tabla[1][3].height[tabla[1][3].contorpiesa].player%2;
                        if(tabla[1][3].height[tabla[1][3].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[1][3].val!=0)
                            desenpiesa((870+1087)/2,(250+450)/2,tabla[1][3].height[tabla[1][3].contorpiesa].dim);
                    }
                    if(x>=435 && x<= 652 && y>=450 && y<=650 && tabla[2][1].val!=0  && tabla[2][1].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[2][1].val;
                        tabla[2][1].contorpiesa--;
                        tabla[2][1].val=tabla[2][1].height[tabla[2][1].contorpiesa].dim;
                        tabla[2][1].player=tabla[2][1].height[tabla[2][1].contorpiesa].player%2;
                        if(tabla[2][1].height[tabla[2][1].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[2][1].val!=0)
                            desenpiesa((652+435)/2,(450+650)/2,tabla[2][1].height[tabla[2][1].contorpiesa].dim);
                    }
                    if(x>=658 && x<= 870 && y>=450 && y<=650 && tabla[2][2].val!=0  && tabla[2][2].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[2][2].val;
                        tabla[2][2].contorpiesa--;
                        tabla[2][2].val=tabla[2][2].height[tabla[2][2].contorpiesa].dim;
                        tabla[2][2].player=tabla[2][2].height[tabla[2][2].contorpiesa].player%2;
                        if(tabla[2][2].height[tabla[2][2].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[2][2].val!=0)
                            desenpiesa((658+870)/2,(450+650)/2,tabla[2][2].height[tabla[2][2].contorpiesa].dim);
                    }
                    if(x>=870 && x<= 1087 && y>=450 && y<=650 && tabla[2][3].val!=0  && tabla[2][3].player==jucator%2 )
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[2][3].val;
                        tabla[2][3].contorpiesa--;
                        tabla[2][3].val=tabla[2][3].height[tabla[2][3].contorpiesa].dim;
                        tabla[2][3].player=tabla[2][3].height[tabla[2][3].contorpiesa].player%2;
                        if(tabla[2][3].height[tabla[2][3].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[2][3].val!=0)
                            desenpiesa((870+1087)/2,(450+650)/2,tabla[2][3].height[tabla[2][3].contorpiesa].dim);

                    }
                    if(x>=435 && x<= 652 && y>=650 && y<=850 && tabla[3][1].val!=0  && tabla[3][1].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[3][1].val;
                        tabla[3][1].contorpiesa--;
                        tabla[3][1].val=tabla[3][1].height[tabla[3][1].contorpiesa].dim;
                        tabla[3][1].player=tabla[3][1].height[tabla[3][1].contorpiesa].player%2;
                        if(tabla[3][1].height[tabla[3][1].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[3][1].val!=0)
                            desenpiesa((652+435)/2,(650+850)/2,tabla[3][1].height[tabla[3][1].contorpiesa].dim);

                    }
                    if(x>=658 && x<= 870 && y>=650 && y<=850 && tabla[3][2].val!=0  && tabla[3][2].player==jucator%2)
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[3][2].val;
                        tabla[3][2].contorpiesa--;
                        tabla[3][2].val=tabla[3][2].height[tabla[3][2].contorpiesa].dim;
                        tabla[3][2].player=tabla[3][2].height[tabla[3][2].contorpiesa].player%2;
                        if(tabla[3][2].height[tabla[3][2].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[3][2].val!=0)
                            desenpiesa((658+870)/2,(650+850)/2,tabla[3][2].height[tabla[3][2].contorpiesa].dim);

                    }
                    if(x>=870 && x<= 1087 && y>=650 && y<=850 && tabla[3][3].val!=0  && tabla[3][3].player==jucator%2 )
                    {
                        setfillstyle(SOLID_FILL, CYAN);
                        floodfill(x,y,BLACK);
                        ok=tabla[3][3].val;
                        tabla[3][3].contorpiesa--;
                        tabla[3][3].val=tabla[3][3].height[tabla[3][3].contorpiesa].dim;
                        tabla[3][3].player=tabla[3][3].height[tabla[3][3].contorpiesa].player%2;
                        if(tabla[3][3].height[tabla[3][3].contorpiesa].player==0)
                            culoare=culoare2;
                        else
                            culoare=culoare1;
                        if(tabla[3][3].val!=0)
                            desenpiesa((870+1087)/2,(650+850)/2,tabla[3][3].height[tabla[3][3].contorpiesa].dim);
                    }
                }
            }
            else if(stadiuc==settings) /// meniul de setari
            {
                if(x>=getmaxwidth()/4-textwidth("CHANGE NAME") && x<=getmaxwidth()/4+textwidth("CHANGE NAME") && y>=getmaxheight()/2+150 && y<=getmaxheight()/2+200)
                {
                    cout<<"INPUT PLAYER1 NAME: ";
                    cin>>NUME1;
                    int oknumenou=1;
                    for(int i=1; i<ulpoz; i++)
                        if(strcmp(clasament[i].nume,NUME1)==0)
                        {
                            oknumenou=0;
                            break;
                        }

                    if(oknumenou==1)
                    {
                        sprintf(clasament[ulpoz].poz, "%d", ulpoz-1);
                        strcpy(clasament[ulpoz].nume,NUME1);
                        strcpy(clasament[ulpoz].scor,"0");
                        ulpoz++;
                    }

                    dsettings();
                }
                else if(x>=getmaxwidth()/4+getmaxwidth()/2-textwidth("CHANGE NAME") && x<=getmaxwidth()/4+getmaxwidth()/2+textwidth("CHANGE NAME") && y>=getmaxheight()/2+150 && y<=getmaxheight()/2+200)
                {
                    cout<<"INPUT PLAYER2 NAME: ";
                    cin>>NUME2;
                    int oknumenou=1;
                    for(int i=1; i<ulpoz; i++)
                        if(strcmp(clasament[i].nume,NUME2)==0)
                        {
                            oknumenou=0;
                            break;
                        }
                    if(oknumenou==1)
                    {
                        sprintf(clasament[ulpoz].poz, "%d", ulpoz-1);
                        strcpy(clasament[ulpoz].nume,NUME2);
                        strcpy(clasament[ulpoz].scor,"0");
                        ulpoz++;
                    }

                    dsettings();
                }
                else if(x>=getmaxwidth()/4-textwidth("CHANGE COLOR") && x<=getmaxwidth()/4+textwidth("CHANGE COLOR") && y>=getmaxheight()/2+250 && y<=getmaxheight()/2+300)
                {
                    cleardevice();
                    ccolor();
                    cntculoare=1;
                }
                else if(x>=getmaxwidth()/4+getmaxwidth()/2-textwidth("CHANGE COLOR") && x<=getmaxwidth()/4+getmaxwidth()/2+textwidth("CHANGE COLOR") && y>=getmaxheight()/2+250 && y<=getmaxheight()/2+300)
                {
                    cleardevice();
                    ccolor();
                    cntculoare=2;
                }

            }
            else if(stadiuc==color) /// schimbarea culorii
            {
                if(x>=435 && x<= 652 && y>=250 && y<=450)
                {
                    if(cntculoare==1)
                        culoare1=1;
                    else
                        culoare2=1;
                }
                if(x>=658 && x<= 870 && y>=250 && y<=450)
                {
                    if(cntculoare==1)
                        culoare1=2;
                    else
                        culoare2=2;
                }
                if(x>=870 && x<= 1087 && y>=250 && y<=450)
                {
                    if(cntculoare==1)
                        culoare1=4;
                    else
                        culoare2=4;
                }
                if(x>=435 && x<= 652 && y>=450 && y<=650)
                {
                    if(cntculoare==1)
                        culoare1=5;
                    else
                        culoare2=5;
                }
                if(x>=658 && x<= 870 && y>=450 && y<=650)
                {
                    if(cntculoare==1)
                        culoare1=6;
                    else
                        culoare2=6;
                }
                if(x>=870 && x<= 1087 && y>=450 && y<=650)
                {
                    if(cntculoare==1)
                        culoare1=7;
                    else
                        culoare2=7;
                }
                if(x>=435 && x<= 652 && y>=650 && y<=850)
                {
                    if(cntculoare==1)
                        culoare1=8;
                    else
                        culoare2=8;
                }
                if(x>=658 && x<= 870 && y>=650 && y<=850)
                {
                    if(cntculoare==1)
                        culoare1=9;
                    else
                        culoare2=9;
                }
                if(x>=870 && x<= 1087 && y>=650 && y<=850)
                {
                    if(cntculoare==1)
                        culoare1=10;
                    else
                        culoare2=10;
                }
                dsettings();
            }
        }
        else if(botdif==1 && jucator%2==0 && stadiuc==play) /// bot cu miscari random
        {
            int lb,cb,dimbot;
            delay(500);
            if(urmmutare==0)
                do
                {
                    lb=rand()%3+1;
                    cb=rand()%3+1;
                    dimbot=rand()%4;
                    if(dimbot==0 && tabla[lb][cb].player==0)
                    {
                        break;
                    }


                }
                while(tabla[lb][cb].val>=dimbot || cnt[2][dimbot]<=0);
            int xPos=getmaxwidth()/7*(cb+2)-(getmaxwidth()/7/2);
            int yPos=250+(lb-1)*200+100;
            if(dimbot!=0)
            {
                cnt[2][dimbot]--;
                culoare=culoare2;
                setfillstyle(SOLID_FILL,CYAN);
                floodfill(xPos,yPos,BLACK);
                desenpiesa(xPos,yPos,dimbot);
                tabla[lb][cb].val=dimbot;
                tabla[lb][cb].player=0;
                tabla[lb][cb].contorpiesa++;
                tabla[lb][cb].height[tabla[lb][cb].contorpiesa].player=0;
                tabla[lb][cb].height[tabla[lb][cb].contorpiesa].dim=dimbot;
                jucator++;
                culoare=culoare2;
                setfillstyle(SOLID_FILL,culoare1);
                floodfill(742,108,WHITE);
                urmmutare=0;
            }
            else
            {
                setfillstyle(SOLID_FILL, CYAN);
                floodfill(xPos,yPos,BLACK);
                dimbot=tabla[lb][cb].val;
                tabla[lb][cb].contorpiesa--;
                tabla[lb][cb].val=tabla[lb][cb].height[tabla[lb][cb].contorpiesa].dim;
                tabla[lb][cb].player=tabla[lb][cb].height[tabla[lb][cb].contorpiesa].player%2;
                if(tabla[lb][cb].height[tabla[lb][cb].contorpiesa].player==0)
                    culoare=culoare2;
                else
                    culoare=culoare1;
                if(tabla[lb][cb].val!=0)
                    desenpiesa(xPos,yPos,tabla[lb][cb].height[tabla[lb][cb].contorpiesa].dim);
                urmmutare=1;
                do
                {
                    lb=rand()%3+1;
                    cb=rand()%3+1;
                }
                while(tabla[lb][cb].val>=dimbot);
            }
        }
        else if(botdif==2 && jucator%2==0 && stadiuc==play) /// bot cu strategie
        {
            int lb,cb,dimbot;
            delay(500);

            bool moveMade=false;
            for(int i=1; i<=3 &&!moveMade; i++)
            {
                for(int j=1; j<=3&&!moveMade; j++)
                {
                    for(int dim=3; dim>=1&&!moveMade; dim--)
                    {
                        if(cnt[2][dim]>0 && tabla[i][j].val<dim && tabla[i][j].player!=0)
                        {
                            int copieval=tabla[i][j].val;
                            int copiepl=tabla[i][j].player;
                            tabla[i][j].val=dim;
                            tabla[i][j].player=0;
                            if(verificareCastig(0))
                            {
                                lb=i;
                                cb=j;
                                dimbot=dim;
                                moveMade=true;
                            }
                            tabla[i][j].val=copieval;
                            tabla[i][j].player=copiepl;
                        }
                    }
                }
            }

            if(!moveMade)
            {
                for(int i=1; i<=3&&!moveMade; i++)
                {
                    for(int j=1; j<=3&&!moveMade; j++)
                    {
                        for(int dim=3; dim>=1&&!moveMade; dim--)
                        {

                            if(cnt[2][dim]>0 && tabla[i][j].val<dim && tabla[i][j].player!=1)
                            {
                                int copieval=tabla[i][j].val;
                                int copiepl=tabla[i][j].player;
                                tabla[i][j].val=dim;
                                tabla[i][j].player=1;
                                if(verificareCastig(1))
                                {
                                    lb=i;
                                    cb=j;
                                    dimbot=dim;
                                    moveMade=true;
                                }
                                tabla[i][j].val=copieval;
                                tabla[i][j].player=copiepl;
                            }
                        }
                    }
                }
            }

            if(!moveMade)
            {
                if(tabla[2][2].val==0)
                {
                    lb=2;
                    cb=2;
                    dimbot=3;
                    moveMade=true;
                }
                else
                {
                    for(int i=1; i<=3&&!moveMade; i+=2)
                    {
                        for(int j=1; j<=3&&!moveMade; j+=2)
                        {
                            if(tabla[i][j].val==0)
                            {
                                lb=i;
                                cb=j;
                                dimbot=tabla[i][j].val+1;
                                moveMade=true;
                            }
                        }
                    }
                }
            }

            if(!moveMade)
            {
                do
                {
                    lb=rand()%3+1;
                    cb=rand()%3+1;
                    dimbot=rand()%4;
                }
                while(tabla[lb][cb].val>=dimbot || cnt[2][dimbot]<=0);
            }

            int xPos=getmaxwidth()/7*(cb+2)-(getmaxwidth()/7/2);
            int yPos=250+(lb-1)*200+100;
            cnt[2][dimbot]--;
            culoare=culoare2;
            setfillstyle(SOLID_FILL,CYAN);
            floodfill(xPos,yPos,BLACK);
            desenpiesa(xPos,yPos,dimbot);
            tabla[lb][cb].val=dimbot;
            tabla[lb][cb].player=0;
            tabla[lb][cb].contorpiesa++;
            tabla[lb][cb].height[tabla[lb][cb].contorpiesa].player=0;
            tabla[lb][cb].height[tabla[lb][cb].contorpiesa].dim=dimbot;
            jucator++;
            setfillstyle(SOLID_FILL,culoare1);
            floodfill(742,108,WHITE);
        }

    }
    ofstream fout("clasament.txt");
    for(int i=1; i<ulpoz; i++)
        fout<<clasament[i].poz<<" "<<clasament[i].nume<<" "<<clasament[i].scor<<endl;
    fout.close();
    exit(0);
    getch();
    closegraph();
    return 0;
}
