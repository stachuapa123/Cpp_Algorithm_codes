#pragma warning(disable : 4996)
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <string.h>
#include <ctime>
#include <stdlib.h>
#define H 49
#define W 100
#define F 4
#define H1 2
#define W1 5
#define S1 2
#define S2 6
#define AN 10
#define RED "\033[31m"
#define BGRED "\033[41m"
#define GREEN "\033[32m"
#define CL "\033[0m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BROWN "\033[33m"
#define BGGREEN "\033[42m"
#define BGREEN "\033[92m"
#define cl system("CLS")
#define ms milliseconds
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

typedef struct
{
    int x;
    int y;
    int sx;
    int sy;
    int a;
    bool help;

} Auto1;

typedef struct
{
    int x;
    int y;
    int s;

} Animal;
typedef struct
{
    int lvl;
    int lives;
    int j;
    int time[3];
} game;

int sgn(int a)
{
   if(a>0)
        return 1;
   else if(a == 0)
        return 0;
   else return -1;
}
void p0(Animal* f, Animal* Stork, game *g, int *cd)
{
    f->y = H - F;
    f->x = W/2;
    Stork->x = W/2;
    Stork->y = H/2;
     g->lives -=1;
     *cd = 20;
     sleep_for(ms(2000));

}
int blockup(char tab[H][W+1], Animal f, int Flen)
{
    for(int i=0;i<f.s;i++)
    {
        for(int j=0;j<Flen;j++)
        {
           if(tab[ f.y-i-1][f.x+j] == 'H' || tab[f.y-i-1][f.x+j] == '#' || tab[f.y-i-1][f.x+j] == 'T')
            return i;
        }
    }
    return f.s;
}
int blockdown(char tab[H][W+1], Animal f, int Flen)
{
    for(int i=0;i<f.s;i++)
    {
        for(int j=0;j<Flen;j++)
        {
           if(tab[f.y+i+Flen][f.x+j] == 'H' || tab[f.y+i+Flen][f.x+j] == '#' || tab[f.y+i+Flen][f.x+j] == 'T')
            return i;
        }
    }
    return f.s;
}
int blockright(char tab[H][W+1], Animal f, int Flen)
{
    for(int i=0;i<Flen;i++)
    {
        for(int j=0;j<f.s;j++)
        {
           if(tab[f.y+i][f.x+Flen+j] == 'T' || tab[f.y+i][f.x+Flen+j] == '#' || tab[f.y+i][f.x+Flen+j] == 'H')
            return j;
        }
    }
    return f.s;
}
int blockleft(char tab[H][W+1], Animal f, int Flen)
{
    for(int i=0;i<Flen;i++)
    {
        for(int j=0;j<f.s;j++)
        {
           if(tab[f.y+i][f.x-j-1] == 'T' || tab[f.y+i][f.x-j-1] == '#' ||  tab[f.y+i][f.x-j-1] == 'H')
            return j;
        }
    }
    return f.s;
}
bool timer(int* cd, int* ic)
{
        if((*ic)>0)
        {
            (*ic)-=1;
        }
        else
        {
            (*cd)-=1;
            (*ic)=5;
        }
        cout<<"Time remaining: "<< *cd<<endl;
        if(*cd == 0)
            return false;
        return true;
}
bool collide(Animal* f, char carboard[H][W+1], char tab[H][W+1])
{
    for(int i=f->y;i<f->y+F-1;i++)
    {
        for(int j=f->x;j<f->x+F-1;j++)
        {
            if(carboard[i][j]!=' ' && f->y > 5)
                return true;
            if(tab[i][j] == 't')
                return true;
        }
    }
    return false;
}
void sedanmove(char tab[H][W + 1], char carboard[H][W + 1], char car1[H1][W1], Auto1 sedan[AN], int ns, int c)
{
    for (int q = 0; q < ns; q++)
        {
        for (int i = 0; i < H1; i++)
         {
            for (int j = 0; j < W1 - 1; j++)
            {
                if(j+sedan[q].x < W)
                    carboard[i + sedan[q].y][j + sedan[q].x] = car1[i][j];
                else
                    carboard[i + sedan[q].y][j + sedan[q].x] = ' ';
            }
        }
        if(sedan[q].x > W)
        {
            if(sedan[q].a==1)
                {
                    sedan[q].x = 1;
                    sedan[q].a = 0;
                    for(int ii=0;ii<H1;ii++)
                    {
                        for(int jj=0;jj<W1-1;jj++)
                        {
                            carboard[ii + sedan[q].y][jj + sedan[q].x] = car1[ii][jj];
                        }
                    }
                }
            else if(sedan[q].a==0)
            {
                if(c==1)
                    sedan[q].a=8;
                else if(c==2)
                    sedan[q].a= 4 + rand() % 5;
                else if(c == 3)
                    sedan[q].a = 3 + rand() % 3;
            }
            else sedan[q].a-=1;
        }
    }
}
void restore(int r, char carboard[H][W+1], Auto1 CC[AN])
{
    for (int q = 0; q < r; q++)
        {
        for (int i = 0; i < H1; i++)
         {
            for (int j = 0; j < W1 - 1; j++)
                carboard[i + CC[q].y][j + CC[q].x] = ' ';
        }
    }
}
void carbreak(Auto1 CC[AN], Animal* f, int ns)
{
    for(int q=0;q<ns;q++)
    {
        if( abs(f->y-CC[q].y) < 5 && f->x - CC[q].x < 9 && f->x - CC[q].x > 0)
        {

                CC[q].sx = 0;
        }
        else CC[q].sx = 3;
    }
}
void sfmove(char tab[H][W+1], char rep[F - 1][F],char a[F-1][F], int siz, Animal S)
{
     for (int i = 0; i < siz; i++) {
        for (int j = 0; j < siz; j++) {
            rep[i][j] = tab[i + S.y][j + S.x];
            tab[i + S.y][j + S.x] = a[i][j];
        }
    }
}
void sfrestore(char tab[H][W+1],char rep[F-1][F], int siz, Animal S)
{
     for (int i = 0; i < siz; i++) {
        for (int j = 0; j < siz; j++) {
            tab[i + S.y][j + S.x] = rep[i][j];
        }
    }
}
bool storkcatch(Animal f, Animal Stork, int siz)
{
    if( abs(f.y - Stork.y) < siz && abs(f.x - Stork.x) < siz)
        return true;
    else return false;
}
void revers(char carboard[H][W+1], int n)
{
        for(int i=0;i<H1;i++)
        {
            for(int j=0;j<W/2;j++)
            {
                swap(carboard[i+n][j], carboard[i+n][W-j-1]);
            }
        }
}
void dirc(int dir[H], int street[S2], int mobstreet[S1], char carboard[H][W+1])
{
    for(int i=0;i<S1;i++)
    {
        if(dir[mobstreet[i]]==1)
            revers(carboard, mobstreet[i]);
    }
    for(int i=0;i<S2;i++)
    {
        if(dir[street[i]]==1)
            revers(carboard, street[i]);
    }
}
void display(char tab[H][W+1], char carboard[H][W+1], Animal f, Animal Stork, game g)
{
     for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {

            if (i >= Stork.y && i < Stork.y + F - 1 && j >= Stork.x && j < Stork.x + F - 1)
                cout<<CYAN<<tab[i][j]<<CL;
            else if (carboard[i][j] != ' ')
                cout << BLUE << carboard[i][j] << CL;
            else if (i >= f.y && i < f.y + F - 1 && j >= f.x && j < f.x + F - 1)
                cout << GREEN << tab[i][j] << CL;
            else if(tab[i][j] == 'H')
                cout << BROWN <<tab[i][j]<<CL;
            else if(tab[i][j] == 'T')
                cout << BGGREEN<<' '<<CL;
            else if(tab[i][j] == 't')
                cout << BGRED<<' '<<CL;
            else if(tab[i][j] == '.')
                cout <<' ';
            else cout<<tab[i][j];
        }
        if(i==2)
            cout<<"  Level: "<<g.lvl;
        else if(i==3)
        {
            cout<<"  Lives ";
            for(int v=0;v<g.lives;v++)
                cout<<"<3"<<" ";
        }
        else if(i==4)
            cout<<"  Total jumps "<<g.j;
        else if(i==5)
            cout<<" Stanislaw Apanasiewicz 198169";
        cout << endl;
    }
}
void speed(int ns, int nt, int na, Auto1 sedan[AN], Auto1 truck[AN], Auto1 ally[AN])
{
    for (int i = 0; i < ns; i++)
    sedan[i].x += sedan[i].sx;

    for(int i=0;i<nt;i++)
    truck[i].x += truck[i].sx;

    for(int i=0;i<na;i++)
    ally[i].x += ally[i].sx;

}
void breakp(int na, Animal* f, int* h, Auto1 ally[AN], bool *uber)
{
    if(*uber == true)
    {
        for(int i=0;i<na;i++)
        {
            if(f->x - ally[i].x < 10 && abs(f->y - ally[i].y) < 3)
            {
                *h = i;
                ally[i].help = true;
                break;
            }
        }
    }
    if(*h>=0)
    {
        f->y=ally[*h].y - 1;
         f->x = ally[*h].x + 4;
    }
    else *uber = false;
}
void acc(int nt, Auto1 truck[AN], game* g)
{
     for(int i=0;i<nt;i++)
    {
        if(truck[i].a>0)
            truck[i].sx=1+g->lvl;
        else if(truck[i].x>W/2)
            truck[i].sx=3+g->lvl;
    }
}
void play(char tab[H][W + 1], char frog[F][F], Animal* f,
              char carboard[H][W + 1], char car1[H1][W1], Auto1 sedan[AN],
              int ns, Auto1 truck[AN], char car2[H1][W1], int nt, Auto1 ally[AN]
              , char car3[H1][W1], int na, bool *uber, Animal* Stork, char st[F][F], game *g, int dir[H], int street[S2], int mobstreet[S1], int *cd)
{

    cl;
    acc(nt, truck, g);
    int h = -1;
    breakp(na, f, &h, ally, uber);


    sedanmove(tab, carboard, car1, sedan, ns, 1);
    sedanmove(tab, carboard, car2, truck, nt, 2);
    sedanmove(tab, carboard, car3, ally, na, 3);
    dirc(dir, street, mobstreet, carboard);
    char frep[F - 1][F], srep[F - 1][F];


    sfmove(tab, frep, frog, F - 1, *f );
    sfmove(tab, srep, st, F -1, *Stork);


    display(tab, carboard, *f, *Stork, *g);

    sfrestore(tab, srep, F-1, *Stork);
    sfrestore(tab, frep, F-1, *f);

    if (collide(f, carboard, tab))
        p0(f, Stork, g, cd);


    dirc(dir, street, mobstreet, carboard);
    restore(ns, carboard, sedan);
    restore(nt, carboard, truck);
    restore(na, carboard, ally);



    carbreak(ally, f, ns);

    if(*uber == true && f->x-ally[h].x == 4)
        ally[h].sx=3;
    speed(ns, nt, na, sedan, truck, ally);




}
void level1(int street[S2], int mobstreet[S1], Auto1 sedan[AN], Auto1 truck[AN], Auto1 ally[AN], Animal *Stork, int n1, int n2, int n3, int dir[H], int ss[2])
{
    Stork->s = 0;
    int r;
    int N =  S2, in = 0;
    int* t =(int*)malloc(n2*sizeof(int));
    int* num =(int*)malloc((N+1)*sizeof(int));
    for(int i=0;i<N;i++)
        num[i]=i;

    dir[mobstreet[0]] = rand()%2;
    dir[mobstreet[1]] = rand()%2;
    for(int i=0;i<n2;i++)
    {
        r=rand()%(N-in);
        in++;

        t[i] = num[r];
        swap(num[r], num[N-in] );
    }
    for(int i=0;i<n1/2;i++)
    {
         sedan[i].x = i*15 + 3;
         sedan[i].y = mobstreet[0];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=n1/2;i<n1;i++)
    {
         sedan[i].x = (i-n1/2)*15 + 3;
         sedan[i].y = mobstreet[1];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=0;i<n2;i++)
    {
        truck[i].y= street[t[i]];
        truck[i].x = rand() % 80 + 1;
        truck[i].sx = ss[1];
        truck[i].a=0;
        dir[street[t[i]]] = rand()%2;
    }
     for(int i=0;i<n3;i++)
    {
         ally[i].x = rand() % 80 + 1;
         ally[i].y = street[num[i]];
         ally[i].sx = ss[1];
         ally[i].a = 0;
         ally[i].help = false;
         dir[street[num[i]]] = 0;
    }
    Stork->x = 3;
    Stork->y = H - 4;
    free(t);
    free(num);
}
void level2(int street[S2], int mobstreet[S1], Auto1 sedan[AN], Auto1 truck[AN], Auto1 ally[AN], Animal *Stork, int n1, int n2, int n3, int dir[H], int ss[2])
{
    Stork->s = 1;
    int r;
    int N =  S2, in = 0;
    //int t[n2];
    int* t =(int*)malloc(n2*sizeof(int));
    int* num =(int*)malloc((N+1)*sizeof(int));
    for(int i=0;i<N;i++)
        num[i]=i;
    for(int i=0;i<n2;i++)
    {
        r=rand()%(N-in);
        in++;
        t[i] = num[r];
        swap(num[r], num[N-in] );
    }
        dir[mobstreet[0]] = rand()%2;
        dir[mobstreet[1]] = rand()%2;
    for(int i=0;i<n1/2;i++)
    {
         sedan[i].x = i*15 + 3;
         sedan[i].y = mobstreet[0];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=n1/2;i<n1;i++)
    {
         sedan[i].x = (i-n1/2)*15 + 3;
         sedan[i].y = mobstreet[1];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=0;i<n2;i++)
    {
        truck[i].y= street[t[i]];
        truck[i].x = rand() % 80 + 1;
        truck[i].sx = ss[1] + 1;
        truck[i].a=0;
        dir[street[t[i]]] = rand()%2;
    }
     for(int i=0;i<n3;i++)
    {
         ally[i].x = rand() % 80 + 1;
         ally[i].y = street[num[i]];
         ally[i].sx = ss[1];
         ally[i].a = 0;
         ally[i].help = false;
         dir[street[num[i]]] = 0;
    }
    Stork->x = 3;
    Stork->y = H - 4;
     free(t);
    free(num);
}

void level3(int street[S2], int mobstreet[S1], Auto1 sedan[AN], Auto1 truck[AN], Auto1 ally[AN], Animal *Stork, int n1, int n2, int n3, int dir[H], int ss[2])
{
    Stork->s = 1;
    int r;
    int N =  S2;

    int* num =(int*)malloc((N+1)*sizeof(int));
    for(int i=0;i<N;i++)
        num[i]=i;
    r=rand()%(N);
    swap(num[r], num[N-1] );
      dir[mobstreet[0]] = rand()%2;
        dir[mobstreet[1]] = rand()%2;
    for(int i=0;i<n1/2;i++)
    {
         sedan[i].x = i*15 + 3;
         sedan[i].y = mobstreet[0];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=n1/2;i<n1;i++)
    {
         sedan[i].x = (i-n1/2)*15 + 3;
         sedan[i].y = mobstreet[1];
         sedan[i].sx = ss[0];
         sedan[i].a = 0;
    }
    for(int i=0;i<n2;i++)
    {
        truck[i].y= street[num[i/2]];
        truck[i].x = rand() % 40 + 50*(i%2);
        truck[i].sx = ss[1]+2;
        truck[i].a=0;
    }
    for(int i=0;i<n2/2;i++)
        dir[street[num[i]]]=rand()%2;
     for(int i=0;i<n3;i++)
    {
         ally[i].x = rand() % 80 + 1;
         ally[i].y = street[r];
         ally[i].sx = ss[1];
         ally[i].a = 0;
         ally[i].help = false;
         dir[street[r]]=0;
    }
    Stork->x = 3;
    Stork->y = H - 4;
    free(num);
}
void endscreen(game g)
{
    cl;
    int p=0;
    cout<<"Total lives left "<<g.lives<<endl<<" (1 life = 10 points)"<< endl<<endl;
    p+=g.lives*10;
   sleep_for(ms(500));
    for(int i=0;i<3;i++)
    {
        cout<<"Time left in level "<<g.time[i] <<endl;
        sleep_for(ms(500));
        p+=(i+1)*g.time[i];
        if(g.time[i]>0)
            p+=(i+1)*10;
    }
    cout<<"(1 time unit = one point * level)"<<endl<<endl;
   sleep_for(ms(500));
    cout<<"(beating each level = 10 points * level )"<<endl<<endl;
    if(g.lvl>3)
    {
        cout<<"game beaten + 50 points";
    }
    else cout<<"No, stuck at level "<<g.lvl;
    sleep_for(ms(500));
    cout<<endl<<"Total jumps "<<g.j<<endl<< "(10 jumps = minus one point)"<<endl<<endl;
    sleep_for(ms(500));
    p-=g.j/10;
    cout<<"Total points "<<p<<endl<<endl;
    cout<<"Game ranking"<<endl;
    cout<<" > 150 - Frog master"<<endl;
    cout<<" > 120 - Frog veteran"<<endl;
    cout<<" > 90 - Frog newbie"<<endl;
    cout<<" 90 or less - Flat frog"<<endl;
}
void clearboard(Animal *f, char carboard[H][W+1])
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
            carboard[i][j]=' ';
    }
    f->y = H - F;
    f->x = W/2;
}
void load1(char f[F][F], FILE *file, int* S)
{
    char fl[AN];
    int s;
    fscanf(file,  "%d\n", &s);
    //fgets(fl, sizeof(fl), file);
    for (int i = 0; i < s; i++)
    {
        fgets(fl, sizeof(fl), file);
          for (int j = 0; j < s; j++)
            {
               if (fl[j] != '\n' && fl[j] != '\0')
               {
                    if(fl[j]=='?')
                        f[i][j]=' ';
                    else f[i][j] = fl[j];
               }
                else
                    f[i][j] = ' ';
            }
    }
    *S = s;
}
void load2(char c[H1][W1], FILE *file)
{
    char fl[AN];
    int h,w;
    fscanf(file, "%d %d\n", &h, &w);
    //fgets(fl, sizeof(fl), file);
    for (int i = 0; i < h; i++)
    {
        fgets(fl, sizeof(fl), file);

          for (int j = 0; j < w+1; j++)
            {
               if (fl[j] != '\n' && fl[j] != '\0')
                    c[i][j] = fl[j];
                else
                    c[i][j] = ' ';
            }
    }
}
void load(char frog[F][F], char tab[H][W+1], char carboard[H][W+1], char car1[H1][W1], char car2[H1][W1], char car3[H1][W1], char sto[F][F], int* ns, int* nt, int *na, int street[S2], int mobstreet[S1], int v[2][3], int ss[2] , int *S, int* h, int* w)
{
    FILE *file;
    file = fopen("att4.txt", "r");

    fscanf(file, "%d %d\n", h, w);
    char li[W + 2];
    for (int i = 0; i < *h; i++)
    {
        fgets(li, sizeof(li), file);

            for (int j = 0; j < *w; j++)
            {
                if(li[j]!='\n')
                    tab[i][j]=li[j];
                carboard[i][j] = ' ';
            }
    }

    load1(frog, file, S);
    load1(sto, file, S);
    load2(car1, file);
    load2(car2, file);
    load2(car3, file);

    fscanf(file, "%d %d %d\n", ns, nt, na);
    fscanf(file, "%d %d %d\n", &v[0][0], &v[0][1], &v[0][2]);
    fscanf(file, "%d %d %d\n", &v[0][1], &v[0][1], &v[1][2]);
    for (int i = 0; i < S2; i++)
        fscanf(file, "%d", &street[i]);

    for (int i = 0; i < S1; i++)
        fscanf(file, "%d", &mobstreet[i]);
    fscanf(file, "%d", &ss[0]);
    fscanf(file, "%d", &ss[1]);

}
void gp(Animal* f, game *g)
{
    f->y = H - F;
    f->x = W / 2;
    f->s = 3;
    g->lvl=1;
    g->lives = 3;
    g->j=0;
    for(int i=0;i<3;i++)
        g->time[i]=0;
}
void getq(char q, game* g, Animal *f, char tab[H][W+1], bool *uber )
{
                if (q == 'w')
                {
                        g->j++;
                        f->y -= blockup(tab, *f, F - 1);
                }
                else if (q == 'a')
                {
                    g->j++;
                        f->x -= blockleft(tab, *f, F - 1);
                }
                else if (q == 'd')
                {
                    g->j++;
                     f->x += blockright(tab, *f, F- 1);
                }
                else if (q == 's')
                {
                    g->j++;
                    f->y += blockdown(tab, *f, F - 1);
                    *uber = false;
                }
                else if(q == 'q')
                {
                   if( *uber == false)
                *uber = true;
                   else
                   {
                       *uber = false;
                       f->x += f->s+1;
                   }
                }
                else if( q=='t')
                {
                    f->x = W/2;
                    f->y= 1;

                }
}
void levc(game g, int street[S2], int mobstreet[S1], Auto1 sedan[AN], Auto1 truck[AN], Auto1 ally[AN], Animal *Stork, int *ns, int *nt, int *na, int dir[H], int v[2][3], int ss[2])
{
        if(g.lvl==1)
        {
            level1(street, mobstreet, sedan, truck, ally, Stork, *ns, *nt, *na, dir, ss);
        }
        else if(g.lvl == 2)
        {
             //*ns = 14, *nt = 4, *na = 2,
             *ns = v[0][0];
             *nt = v[0][1];
             *na = v[0][2];
            level2(street, mobstreet, sedan, truck, ally, Stork, *ns, *nt, *na, dir, ss);
        }
        else if (g.lvl == 3)
        {
             //*na = 1, *ns = 16, *nt = 10;
             *ns = v[1][0];
             *nt = v[1][1];
             *na = v[1][2];
            level3(street, mobstreet, sedan, truck, ally, Stork, *ns, *nt, *na, dir, ss);
        }
}
int main()
{
    srand(time(NULL));
    Animal f, Stork;
    game g;

    char tab[H][W+1],  frog[F][F], sto[F][F],  carboard[H][W+1], car1[H1][W1], car2[H1][W1], car3[H1][W1];
    Auto1 sedan[AN], truck[AN], ally[AN];
    int street[S2], mobstreet[S1], dir[H], na, ns ,nt, v[2][3], ss[2], S, h, w;
    load(frog, tab, carboard, car1, car2, car3, sto, &ns, &nt, &na, street, mobstreet, v, ss , &S, &h, &w);
     gp(&f, &g);

    while(1)
    {
        bool uber = false;
        int cd=20,ic=5;
        levc(g, street, mobstreet, sedan, truck, ally, &Stork, &ns, &nt, &na, dir, v, ss);
        while (1)
        {
            char q;

            if (_kbhit()) {
                q = _getch();
                getq(q, &g, &f, tab, &uber);
            }
            play(tab, frog, &f, carboard, car1, sedan, ns, truck, car2, nt, ally, car3, na, &uber, &Stork, sto, &g, dir, street, mobstreet, &cd);
            Stork.x += sgn(f.x - Stork.x) * Stork.s;
            Stork.y += sgn(f.y - Stork.y) * Stork.s;

            if(storkcatch(f, Stork, F - 1) || !timer(&cd, &ic))
                p0(&f, &Stork, &g, &cd);

            if(f.y<4)
            {
                g.time[g.lvl-1]+=cd;
                g.lvl++;
                clearboard(&f, carboard);
                break;
            }
            if(g.lives < 1)
                break;

            sleep_for(ms(200));
        }
        if(g.lvl>3 || g.lives<1)
            break;
    }
    endscreen(g);
}
/*
49
100
####################################################################################################
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#=============HHHHHHHHHHHHHHHHHH===========HHHHHHHHHHHHHHHHHHH==============HHHHHHHHHHHHHHH========#
#..................................................................................................#
#..................................................................................................#
#--------------------------------------------------------------------------------------------------#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#--------------------------------------------------------------------------------------------------#
#..................................................................................................#
#..................................................................................................#
#HHHHHHHHHHHHHHH==========================================HHHHHHHHHHHHHHHH=========================#
#...............ttt.............................TTT...............................TTT..............#
#...............ttt.............................TTT...............................TTT..............#
#................t...............................T.................................T...............#
#==================================HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH==============================#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#--------------------------------------------------------------------------------------------------#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#==================================================================================================#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#==========================HHHHHHHHHHHHHHHHHHHH====================================================#
#...............ttt.............................TTT...............................TTT..............#
#...............ttt.............................TTT...............................TTT..............#
#................t...............................T.................................T...............#
#==================================================HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH=================#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#--------------------------------------------------------------------------------------------------#
#..................................................................................................#
#..................................................................................................#
#..................................................................................................#
#====================================HHHHHHHHHHHHHHHHHHHHHHH=======================================#
#....................TTT...................................................TTT.....................#
#....................TTT...................................................TTT.....................#
#.....................T.....................................................T......................#
####################################################################################################
3
@.@
?O?
>O<
3
?C>
{O}
||?
2
4
_WW_
WWWW
2
4
XXxx
XXXX
2
4
uUUu
UUUU
8 2 4
14 4 2
16 5 1
5 13 20 25 38 42
9 29
2 3




*/
