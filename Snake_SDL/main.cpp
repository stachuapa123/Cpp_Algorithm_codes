#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH    640
#define SCREEN_HEIGHT   720 // parameters of displayed picture
#define L 100   //for max snake length
#define SIZ 20  //size of snake body segment
#define D1 20   //distance from egde of displayed board to the edge of playable board
#define D2 10   //thickness of the frame of the board
#define H1 60   //heigth of the info board
#define LEN 10  //initial snake length
#define SIZ2 10         
#define SH 10           //size of snake tongue
#define SB 16           // size of the smaller body segment
#define TAIL 16         //size of snake tail
#define TP 2    // number of portal pairs
#define SPAWNX 320
#define SPAWNY 360 // coordinates of snake head at the beggining
#define SLOW 2 // defines how much the snake will be slowed down when it eats the red dot
#define CM 20 // maximum size of player name
#define TH 3  // podium size
#define WL 300 // sizes of the last printed table
#define HL 200
#define SP 20 // distance between words in leaderboards
#define CZ 8 //distance for number display
#define PB 20 //progress bar length
#define TY1 10 //heigth of the first text displayed
#define TY2 26 //heigth of the second text displayed
#define TM 128 //maximum size of the text
#define CUT 7 //segments of a snake which disappear when a boost arrive
#define FS 1.2 //how fast will the game speedup
#define WT 10 //how long is needed for a speedup
#define FL 0.2 //first time limit for a frame
#define BT 8 //duration of a red dot boost
#define RR1 10 //minimum time after a red dot appears
#define RR2 20 //maximum time after a red dot appears
#define REDP 2 //points for eating a red dot
#define BLUEP 1 //points for eating a red dot
#define DT 4000 //duration of leaderboards display
#define violet SDL_MapRGB(screen->format, 0x80, 0x00, 0x80)
#define czarny SDL_MapRGB(screen->format, 0x00, 0x00, 0x00)
#define zielony SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00)
#define czerwony SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00)
#define niebieski SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC)
#define bialy SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF)
#define zielony2 SDL_MapRGB(screen->format, 0x00, 0x80, 0x00)
#define rozowy SDL_MapRGB(screen->format, 0xFF, 0x80, 0xFF)
typedef struct
{
    bool u, d, r, l;
    int vx, vy;
}awsd;
typedef struct
{
    double x;
    double y;
}snake;
typedef struct
{
    int x;
    int y;
    double siz;
    double siz2;
    bool a;
}dot;
typedef struct  // coordinates of the board
{
    int X1;
    int X2;
    int Y1;
    int Y2;
}board;
typedef struct
{
    double timerf;
    double limit;
    int wait;
    double timerg;
    double faster;
    double boost; //for when a snake eats a red dot
    int boosttime; //time in seconds for which there will be a boost
    double tsave; //saves tlimit after a boost
    double redtimer;
    int redrand;
    int boostchoose;
    int cuts;

}gclock;
typedef struct
{
    int x1;
    int x2;
    int y1;
    int y2;
    double siz;
    bool a1;
    bool a2;

}portal;


void DrawString(SDL_Surface* screen, int x, int y, const char* text,
    SDL_Surface* charset) {
    int px, py, c;
    SDL_Rect s, d;
    s.w = CZ;
    s.h = CZ;
    d.w = CZ;
    d.h = CZ;
    while (*text) {
        c = *text & 255;
        px = (c % 16) * CZ;
        py = (c / 16) * CZ;
        s.x = px;
        s.y = py;
        d.x = x;
        d.y = y;
        SDL_BlitSurface(charset, &s, screen, &d);
        x += CZ;
        text++;
    };
};



void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
    SDL_Rect dest;
    dest.x = x - sprite->w / 2;
    dest.y = y - sprite->h / 2;
    dest.w = sprite->w;
    dest.h = sprite->h;
    SDL_BlitSurface(sprite, NULL, screen, &dest);
};



void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32*)p = color;
};


void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
    for (int i = 0; i < l; i++) {
        DrawPixel(screen, x, y, color);
        x += dx;
        y += dy;
    };
};


void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
    Uint32 outlineColor, Uint32 fillColor) {
    int i;
    DrawLine(screen, x, y, k, 0, 1, outlineColor);
    DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
    DrawLine(screen, x, y, l, 1, 0, outlineColor);
    DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
    for (i = y + 1; i < y + k - 1; i++)
        DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void speedchange(awsd* b, int si) //for a direction movement change
{

    if (b->u == true)
    {
        b->vy = -1;
        b->vx = 0;
    }
    else if (b->d == true)
    {
        b->vy = 1;
        b->vx = 0;
    }
    else if (b->r == true)
    {
        b->vy = 0;
        b->vx = 1;
    }
    else if (b->l == true)
    {
        b->vy = 0;
        b->vx = -1;
    }

}
void startparam(dot* bd, dot* rd, board* B, gclock* cs, awsd* b) //start parameters
{
    bd->siz = SIZ;
    rd->siz = SIZ;
    rd->x = 0;
    rd->y = 0;
    b->vx = 0;
    b->vy = 0;
    cs->boosttime = 8;
    rd->siz2 = SIZ2;
    bd->siz2 = SIZ2;
    B->X2 = SCREEN_WIDTH - D1 - D2 - SIZ;
    B->X1 = D1 + D2;
    B->Y1 = H1 + D1 + D2;
    B->Y2 = SCREEN_HEIGHT - D1 - D2 - SIZ;

}
void newgame(snake s[L], awsd* b, int* si, dot* bd, dot* rd, gclock* cs, int* points, double* worldTime)// for a new game
{
    *si = LEN;

    for (int i = 0; i < *si; i++)
    {
        s[i].x = SPAWNX + D2;
        s[i].y = SPAWNY + i * SIZ + D2;
    }
    b->u = true, b->d = false, b->r = false, b->l = false;
    cs->timerf = 0; //timer for frame movement
    cs->timerg = 0; //timer for game speedup
    cs->limit = FL; //time for one frame
    cs->wait = WT; //time in seconds after which the game speeds up
    cs->faster = FS; //the game will run faster by this number      
    cs->redrand = rand() % RR2 + RR1; //time after which the red dot will appear
    cs->redtimer = 0;
    bd->a = false;
    rd->a = false;
    rd->x = 0;
    rd->y = 0;
    cs->boost = 0; //for when a snake eats a red dot
    cs->tsave = 0; //saves tlimit after a boost
    cs->cuts = 0;
    cs->boostchoose = 0; // later 1 or 2 for one of boosts
    *points = 0;
    *worldTime = 0;
}
void chase(snake s[L], int si) //snake segments chasing each other
{
    for (int i = si - 1; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }
}
bool hitcheck(double x1, double y1, double s1, double x2, double y2, double s2) //checks if two objects hit each other
{
    double xdis = fabs(x1 - x2);
    double ydis = fabs(y1 - y2);
    if ((s1 + s2) / 2 > xdis && (s1 + s2) / 2 > ydis)
        return true;
    return false;
}
bool collision(snake s[L], int si, double S, portal prt[TP]) //checks if snake hits itself
{
    for (int i = 1; i < si; i++)
    {
        if (hitcheck(s[0].x, s[0].y, S, s[i].x, s[i].y, S))
        {
            for (int i = 0; i < TP; i++)
            {
                if (hitcheck(s[0].x, s[0].y, S, prt[i].x1, prt[i].y1, S) || hitcheck(s[0].x, s[0].y, S, prt[i].x2, prt[i].y2, S))
                    return false;
            }
            return true;
        }
    }
    return false;
}
void blueball(snake s[L], int si, dot* bd, board B, portal prt[TP]) //dot placement
{
    bool again = true;
    while (again)
    {
        again = false;
        int rx = (rand() % ((B.X2 - B.X1) / SIZ)) * SIZ + B.X1;
        int ry = (rand() % ((B.Y2 - B.Y1) / SIZ)) * SIZ + B.Y1;
        for (int i = 1; i < si; i++)
        {
            if (hitcheck(s[i].x, s[i].y, SIZ, rx, ry, bd->siz))
            {
                again = true;
                break;
            }

        }
        for (int i = 0; i < TP; i++)
        {
            if (hitcheck(prt[i].x1, prt[i].y1, SIZ, rx, ry, bd->siz) || hitcheck(prt[i].x2, prt[i].y2, SIZ, rx, ry, bd->siz))
            {
                again = true;
                break;
            }
        }
        bd->x = rx;
        bd->y = ry;
        bd->a = true;
    }
}

void savegame(double worldTime, int points, int si, dot bd, dot rd, gclock cs, awsd b, snake s[L]) //save game parameters
{
    FILE* file = fopen("safe.txt", "w");

    fprintf(file, "%lf\n", worldTime);
    fprintf(file, "%d\n", points);
    fprintf(file, "%d\n", si);

    fprintf(file, "%d\n", bd.a);
    fprintf(file, "%d\n", bd.x);
    fprintf(file, "%d\n", bd.y);

    fprintf(file, "%d\n", rd.a);
    fprintf(file, "%d\n", rd.x);
    fprintf(file, "%d\n", rd.y);

    fprintf(file, "%lf\n", cs.timerf);
    fprintf(file, "%lf\n", cs.timerg);
    fprintf(file, "%lf\n", cs.limit);
    fprintf(file, "%d\n", cs.wait);
    fprintf(file, "%lf\n", cs.faster);
    fprintf(file, "%d\n", cs.redrand);
    fprintf(file, "%lf\n", cs.redtimer);
    fprintf(file, "%lf\n", cs.boost);
    fprintf(file, "%lf\n", cs.tsave);
    fprintf(file, "%d\n", cs.cuts);
    fprintf(file, "%d\n", cs.boostchoose);

    fprintf(file, "%d\n", b.u);
    fprintf(file, "%d\n", b.d);
    fprintf(file, "%d\n", b.r);
    fprintf(file, "%d\n", b.l);
    fprintf(file, "%d\n", b.vx);
    fprintf(file, "%d\n", b.vy);

    for (int i = 0; i < si; i++)
    {
        fprintf(file, "%lf\n", s[i].x);
        fprintf(file, "%lf\n", s[i].y);
    }
    fclose(file);
}

void loadgame(double* worldTime, int* points, int* si, dot* bd, dot* rd, gclock* cs, awsd* b, snake s[L]) //load game parameters
{
    FILE* file = fopen("safe.txt", "r");


    fscanf(file, "%lf", worldTime);
    fscanf(file, "%d", points);
    fscanf(file, "%d", si);

    fscanf(file, "%d", &(bd->a));
    fscanf(file, "%d", &(bd->x));
    fscanf(file, "%d", &(bd->y));

    fscanf(file, "%d", &(rd->a));
    fscanf(file, "%d", &(rd->x));
    fscanf(file, "%d", &(rd->y));

    fscanf(file, "%lf", &(cs->timerf));
    fscanf(file, "%lf", &(cs->timerg));
    fscanf(file, "%lf", &(cs->limit));
    fscanf(file, "%d", &(cs->wait));
    fscanf(file, "%lf", &(cs->faster));
    fscanf(file, "%d", &(cs->redrand));
    fscanf(file, "%lf", &(cs->redtimer));
    fscanf(file, "%lf", &(cs->boost));
    fscanf(file, "%lf", &(cs->tsave));
    fscanf(file, "%d", &(cs->cuts));
    fscanf(file, "%d", &(cs->boostchoose));

    fscanf(file, "%d", &(b->u));
    fscanf(file, "%d", &(b->d));
    fscanf(file, "%d", &(b->r));
    fscanf(file, "%d", &(b->l));
    fscanf(file, "%d", &(b->vx));
    fscanf(file, "%d", &(b->vy));

    for (int i = 0; i < *si; i++)
    {
        double x, y;
        fscanf(file, "%lf", &x);
        fscanf(file, "%lf", &y);
        s[i].x = x;
        s[i].y = y;
    }
    fclose(file);
}


void drawportal(board B, portal prt[TP]) // create portal coordinates
{
    int X1 = B.X1 + SIZ;
    int X2 = B.X2 - SIZ;
    int Y1 = B.Y1 + SIZ;
    int Y2 = B.Y2 - SIZ;
    for (int i = 0; i < TP; i++)
    {
        bool ag1 = true;
        while (ag1)
        {
            ag1 = false;
            prt[i].x1 = (rand() % ((X2 - X1) / SIZ)) * SIZ + X1;
            if (prt[i].x1 == SPAWNX + D2)
                ag1 = true;
        }

        prt[i].y1 = (rand() % ((Y2 - Y1) / SIZ)) * SIZ + Y1;
        bool ag = true;
        while (ag)
        {
            ag = false;
            prt[i].x2 = (rand() % ((X2 - X1) / SIZ)) * SIZ + X1;
            prt[i].y2 = (rand() % ((Y2 - Y1) / SIZ)) * SIZ + Y1;
            if (prt[i].x1 == prt[i].x2 && prt[i].y1 == prt[i].y2 || prt[i].x2 == SPAWNX + D2)
                ag = true;
        }
        for (int j = 0; j < i; j++)
        {
            if ((prt[i].x1 == prt[j].x1 && prt[i].y1 == prt[j].y1) || (prt[i].x2 == prt[j].x2 && prt[i].y2 == prt[j].y2))
            {
                i -= 1;
                break;
            }
        }

    }

}
void best3(int p[TH], char names[TH][CM + 1]) //get usernames from a file
{
    FILE* file = fopen("podium.txt", "r");

    for (int i = 0; i < TH; i++)
        fscanf(file, "%d %20s", &p[i], names[i]);


    fclose(file);

}
void write3(int p[TH], char names[TH][CM + 1], int points, char uname[CM + 1]) //write updated usernames to a file
{
    p[TH - 1] = points;
    strcpy(names[TH - 1], uname);
    for (int i = TH - 1; i > 0; i--)
    {
        if (p[i] > p[i - 1])
        {
            char tm[CM + 1] = "";
            int tm2;
            strcpy(tm, names[i]);
            strcpy(names[i], names[i - 1]);
            strcpy(names[i - 1], tm);
            tm2 = p[i];
            p[i] = p[i - 1];
            p[i - 1] = tm2;
        }
    }
    FILE* file = fopen("podium.txt", "w");
    for (int i = 0; i < TH; i++)
    {
        fprintf(file, "%d %s\n", p[i], names[i]);
    }
    fclose(file);
}
void dirchange(snake s[L], awsd* b, board* B) //change direction of movement
{
    if (s[0].x <= B->X1)
    {
        if (s[0].y <= B->Y1)
        {
            s[0].y = B->Y1;
            b->d = false;
            b->u = false;
            b->r = true;
        }
        else
        {
            s[0].x = B->X1;
            b->l = false;
            b->u = true;
        }
    }
    else if (s[0].x >= B->X2)
    {
        if (s[0].y >= B->Y2)
        {
            s[0].y = B->Y2;
            b->d = false;
            b->u = false;
            b->l = true;
        }
        else
        {
            s[0].x = B->X2;
            b->r = false;
            b->d = true;
        }
    }
    else if (s[0].y <= B->Y1)
    {
        s[0].y = B->Y1;
        b->u = false;
        b->r = true;
    }
    else if (s[0].y >= B->Y2)
    {
        s[0].y = B->Y2;
        b->d = false;
        b->l = true;
    }
}
void startSDL(SDL_Window*& window, SDL_Renderer*& renderer, SDL_Texture*& scrtex, SDL_Surface*& screen, SDL_Surface*& charset)//initialise sdl parameters
{

    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer) != 0)
    {
        printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        SDL_Quit();
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_SetWindowTitle(window, "Snake Stanislaw Apanasiewicz 198169");

    screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_ShowCursor(SDL_DISABLE);
    charset = SDL_LoadBMP("./cs8x8.bmp");
    if (!charset)
    {
        printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
        SDL_FreeSurface(screen);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    SDL_SetColorKey(charset, true, 0x000000);

}
void draw(gclock* cs, awsd b, dot bd, dot rd, snake s[L], int si,
    int points, portal* prt, SDL_Surface* screen, SDL_Surface* charset, double worldTime, int pulse, double delta) //draw the board

{
    char text[TM];
    DrawRectangle(screen, D1, D1 + H1, SCREEN_WIDTH - 2 * D1, SCREEN_HEIGHT - 2 * D1 - H1, bialy, bialy);
    DrawRectangle(screen, D1 + D2, D1 + D2 + H1, SCREEN_WIDTH - 2 * D1 - D2 * 2, SCREEN_HEIGHT - 2 * D1 - H1 - D2 * 2, czarny, czarny);
    if (cs->cuts > 0)
    {
        for (int i = si - cs->cuts; i < si; i++)
        {
            DrawRectangle(screen, s[i].x, s[i].y, SIZ, SIZ, czarny, czarny);
        }
        for (int i = 1; i < si - cs->cuts - 1; i++)
        {
            if (i % 2 == 1)
                DrawRectangle(screen, s[i].x, s[i].y, SIZ, SIZ, zielony, zielony);
            else
                DrawRectangle(screen, s[i].x + (SIZ - SB) / 2, s[i].y + (SIZ - SB) / 2, SB, SB, zielony, zielony);

        }
        DrawRectangle(screen, s[si - cs->cuts - 1].x + (SIZ - TAIL) / 2, s[si - cs->cuts - 1].y + (SIZ - TAIL) / 2, TAIL, TAIL, rozowy, rozowy);
    }
    else
    {
        for (int i = 1; i < si - 1; i++)
        {
            if (i % 2 == 1)
                DrawRectangle(screen, s[i].x, s[i].y, SIZ, SIZ, zielony, zielony);
            else
                DrawRectangle(screen, s[i].x + (SIZ - SB) / 2, s[i].y + (SIZ - SB) / 2, SB, SB, zielony, zielony);
        }
        DrawRectangle(screen, s[si - 1].x + (SIZ - TAIL) / 2, s[si - 1].y + (SIZ - TAIL) / 2, TAIL, TAIL, rozowy, rozowy);
    }

    DrawRectangle(screen, s[0].x, s[0].y, SIZ, SIZ, zielony2, zielony2);
    if (b.u)
        DrawRectangle(screen, s[0].x + (SIZ - SH) / 2, s[0].y, SH, SH, czerwony, czerwony);
    else if (b.d)
        DrawRectangle(screen, s[0].x + (SIZ - SH) / 2, s[0].y + (SIZ - SH), SH, SH, czerwony, czerwony);
    else if (b.r)
        DrawRectangle(screen, s[0].x + (SIZ - SH), s[0].y + (SIZ - SH) / 2, SH, SH, czerwony, czerwony);
    else
        DrawRectangle(screen, s[0].x, s[0].y + (SIZ - SH) / 2, SH, SH, czerwony, czerwony);

    if (bd.a)
    {
        if (pulse)
            DrawRectangle(screen, bd.x, bd.y, bd.siz, bd.siz, niebieski, niebieski);
        else
            DrawRectangle(screen, bd.x + bd.siz2 / 2, bd.y + bd.siz2 / 2, bd.siz2, bd.siz2, niebieski, niebieski);

    }
    if (rd.a)
    {
        if (pulse)
            DrawRectangle(screen, rd.x, rd.y, rd.siz, rd.siz, czerwony, czerwony);
        else
            DrawRectangle(screen, rd.x + rd.siz2 / 2, rd.y + rd.siz2 / 2, rd.siz2, rd.siz2, czerwony, czerwony);
    }
    for (int i = 0; i < TP; i++)
    {

        DrawRectangle(screen, prt[i].x1, prt[i].y1, SIZ, SIZ, violet, violet);

        sprintf(text, "%d", i + 1);
        DrawString(screen, prt[i].x1 + SIZ / 3, prt[i].y1 + SIZ / 3, text, charset);

        DrawRectangle(screen, prt[i].x2, prt[i].y2, SIZ, SIZ, violet, violet);
        sprintf(text, "%d", i + 1);
        DrawString(screen, prt[i].x2 + SIZ / 3, prt[i].y2 + SIZ / 3, text, charset);
    }

    DrawRectangle(screen, CZ / 2, CZ / 2, SCREEN_WIDTH - CZ, H1, bialy, niebieski);
    sprintf(text, "Snake, Obligatory requirements 1-4, Optional requirements A-H");
    DrawString(screen, screen->w / 2 - strlen(text) * CZ / 2, TY1, text, charset);

    sprintf(text, "Esc - exit game   n - new game    Time passed = %.1lf s  points: %.0li", worldTime, points);
    DrawString(screen, screen->w / 2 - strlen(text) * CZ / 2, TY2, text, charset);

    if (cs->boost > 0)
    {
        DrawRectangle(screen, (SCREEN_WIDTH - cs->boosttime * PB) / 2, H1 - D1, cs->boosttime * PB, D1, bialy, bialy);
        DrawRectangle(screen, (SCREEN_WIDTH - cs->boosttime * PB) / 2, H1 - D1, cs->boost * PB, D1, czerwony, czerwony);
        cs->boost -= delta;
    }
    else
    {
        sprintf(text, "s - save game   l - load game  e - show scoreboard");
        DrawString(screen, screen->w / 2 - strlen(text) * CZ / 2, TY1 + TY2 + CZ, text, charset);
    }
}
void snakemove(snake s[L], board* B, gclock* cs, dot* bd, dot* rd, portal prt[TP], awsd* b,
    int* si, int* points, int* quit, int* pulse, bool* col) //for snake movement
{
    cs->timerf = 0;
    (*pulse)++;
    *pulse %= 2;

    chase(s, *si);
    speedchange(b, *si);
    s[0].x += b->vx * SIZ;
    s[0].y += b->vy * SIZ;
    dirchange(s, b, B);

    if (collision(s, *si - cs->cuts, SIZ, prt))
    {
        *col = true;
    }
    if (hitcheck(s[0].x, s[0].y, SIZ, bd->x, bd->y, bd->siz))
    {
        bd->a = false;
        s[*si].x = s[*si - 1].x;
        s[*si].y = s[*si - 1].y;
        (*si)++;
        (*points) += BLUEP;
    }
    if (hitcheck(s[0].x, s[0].y, SIZ, rd->x, rd->y, rd->siz))
    {
        rd->a = false;
        cs->redrand = rand() % 20 + 10;
        cs->boostchoose = rand() % 2 + 1;
        cs->boost = cs->boosttime;
        if (cs->boostchoose == 2)
            cs->cuts = CUT;
        (*points) += REDP;
    }
    for (int i = 0; i < TP; i++)
    {
        if (hitcheck(s[0].x, s[0].y, SIZ, prt[i].x1, prt[i].y1, SIZ))
        {
            s[0].x = prt[i].x2;
            s[0].y = prt[i].y2;
        }
        else if (hitcheck(s[0].x, s[0].y, SIZ, prt[i].x2, prt[i].y2, SIZ))
        {
            s[0].x = prt[i].x1;
            s[0].y = prt[i].y1;
        }
    }
    if (bd->a == false)
    {
        blueball(s, *si, bd, *B, prt);
    }


}
void timers(gclock* cs, snake s[L], dot* rd, board B, portal prt[TP], double delta, int si, double* worldTime) //timers and counters operations
{

    *worldTime += delta;
    cs->timerg += delta;

    if (cs->boost > 0 && cs->tsave == 0 && cs->cuts == 0)
    {
        cs->tsave = cs->limit;
        cs->limit *= SLOW;
    }
    else if (cs->boost <= 0 && cs->tsave != 0 && cs->cuts == 0)
    {
        cs->limit /= SLOW;
        cs->tsave = 0;
    }
    else
        cs->timerf += delta;

    if (cs->boost <= 0)
        cs->cuts = 0;


    if (cs->redtimer > cs->redrand)
    {
        blueball(s, si, rd, B, prt);
        cs->redtimer = 0;
        cs->redrand = 0;
    }
    else if (cs->redrand > 0)
    {
        cs->redtimer += delta;
    }
    if (cs->timerg >= cs->wait)
    {
        cs->limit /= cs->faster;
        cs->timerg = 0;
    }
}
void setframe(SDL_Renderer*& renderer, SDL_Texture*& scrtex, SDL_Surface*& screen) //sets the screen 
{
    SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
    SDL_RenderCopy(renderer, scrtex, NULL, NULL);
    SDL_RenderPresent(renderer);
}
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
    int t1, t2, quit = 0, frames, rc, si, points = 0;
    double delta, worldTime, distance;
    bool saved = false, esc = false, col = false;
    int pulse = 0;
    awsd b;
    snake s[L];
    gclock cs;
    dot bd, rd;
    board B;
    portal prt[TP];
    SDL_Event event;
    SDL_Surface* screen, * charset;
    SDL_Texture* scrtex;
    SDL_Window* window;
    SDL_Renderer* renderer;

    startSDL(window, renderer, scrtex, screen, charset);

    t1 = SDL_GetTicks();
    srand(time(NULL));
    startparam(&bd, &rd, &B, &cs, &b);
    drawportal(B, prt);
    newgame(s, &b, &si, &bd, &rd, &cs, &points, &worldTime);
    blueball(s, si, &bd, B, prt);
    while (!quit) {
        t2 = SDL_GetTicks();
        SDL_FillRect(screen, NULL, czarny);
        delta = (t2 - t1) * 0.001;
        t1 = t2;
        if (!col)
        {
            timers(&cs, s, &rd, B, prt, delta, si, &worldTime);

            if (cs.timerf >= cs.limit)
                snakemove(s, &B, &cs, &bd, &rd, prt, &b, &si, &points, &quit, &pulse, &col);

            draw(&cs, b, bd, rd, s, si, points, prt, screen, charset, worldTime, pulse, delta);

            setframe(renderer, scrtex, screen);
        }
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (b.d == false && s[0].y != B.Y1)
                        b.u = true, b.d = false, b.r = false, b.l = false;
                    break;
                case SDLK_DOWN:
                    if (b.u == false && s[0].y != B.Y2)
                        b.u = false, b.d = true, b.r = false, b.l = false;
                    break;
                case SDLK_RIGHT:
                    if (b.l == false && s[0].x != B.X2)
                        b.u = false, b.d = false, b.r = true, b.l = false;
                    break;
                case SDLK_LEFT:
                    if (b.r == false && s[0].x != B.X1)
                        b.u = false, b.d = false, b.r = false, b.l = true;
                    break;
                case SDLK_n:
                    newgame(s, &b, &si, &bd, &rd, &cs, &points, &worldTime);
                    drawportal(B, prt);
                    col = false;
                    break;
                case SDLK_e:
                    quit = 1;
                case SDLK_s:

                    savegame(worldTime, points, si, bd, rd, cs, b, s);
                    saved = true;
                    break;
                case SDLK_l:
                    if (saved)
                        loadgame(&worldTime, &points, &si, &bd, &rd, &cs, &b, s);

                    break;
                case SDLK_ESCAPE:
                    esc = true;
                    quit = 1;
                    break;
                }
                break;

            case SDL_KEYUP:
                break;

            case SDL_QUIT:
                quit = 1;
                break;
            };
        };

    };
    int p[TH];
    char names[TH][CM + 1];
    if (!esc)
    {
        best3(p, names);
        char uname[CM] = "";
        if (points > p[TH - 1])
        {

            SDL_FillRect(screen, NULL, bialy);
            DrawRectangle(screen, (SCREEN_WIDTH - WL) / 2, (SCREEN_HEIGHT - HL) / 2, WL, HL, niebieski, niebieski);
            char text1[TM] = "WRITE YOUR USERNAME";
            DrawString(screen, SCREEN_WIDTH / 2 - strlen(text1) * CZ / 2, SCREEN_HEIGHT / 2 - SP, text1, charset);
            setframe(renderer, scrtex, screen);
            SDL_StartTextInput();
            int run = 1;

            while (run)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_QUIT)
                    {
                        run = 0;
                        break;
                    }
                    if (event.type == SDL_TEXTINPUT)
                    {
                        if (strlen(uname) < CM)
                        {
                            strcat(uname, event.text.text);
                            DrawRectangle(screen, (SCREEN_WIDTH - WL) / 2, (SCREEN_HEIGHT) / 2, WL, HL / 2, niebieski, niebieski);
                            DrawString(screen, SCREEN_WIDTH / 2 - strlen(uname) * CZ / 2, SCREEN_HEIGHT / 2 + SP, uname, charset);
                            setframe(renderer, scrtex, screen);
                            break;
                        }
                    }
                    if (event.type == SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(uname) > 0)
                            uname[strlen(uname) - 1] = '\0';
                        else if (event.key.keysym.sym == SDLK_RETURN)
                            run = 0;
                    }
                }
            }
            DrawString(screen, SCREEN_WIDTH / 2 - strlen(uname) * CZ / 2, SCREEN_HEIGHT / 2 + SP, uname, charset);
            setframe(renderer, scrtex, screen);
            write3(p, names, points, uname);
        }
        DrawRectangle(screen, (SCREEN_WIDTH - WL) / 2, (SCREEN_HEIGHT - HL) / 2, WL, HL, niebieski, niebieski);
        for (int i = 0; i < TH; i++)
        {
            char itc[5];
            sprintf(itc, "%d", p[i]);
            DrawString(screen, (SCREEN_WIDTH - WL) / 2 + 2 * CM, SCREEN_HEIGHT / 2 + SP * (i - 1), names[i], charset);
            DrawString(screen, (SCREEN_WIDTH + WL) / 2 - 2 * CM, SCREEN_HEIGHT / 2 + SP * (i - 1), itc, charset);

        }
        setframe(renderer, scrtex, screen);
        SDL_Delay(DT);
    }
    SDL_FreeSurface(charset);
    SDL_FreeSurface(screen);
    SDL_DestroyTexture(scrtex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
};