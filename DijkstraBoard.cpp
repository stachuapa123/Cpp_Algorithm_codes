#include <iostream>
using namespace std;

#define INF 10000000

struct lift { // lift structure

    int sx, sy;
    int ex, ey;
    int time;
    int wait;

};
struct dijk { //dijstra's structure visited and distance

    int dist;
    bool vis;
};
struct dijQ { // heap structure, position and distance (or time)
    int x;
    int y;
    int d;
};

int distance(int a, int b) // distance beetween hills (format from the task)
{
    if (a >= b)
        return 1;
    return b - a + 1;

}
void swaph(dijQ& a, dijQ& b) // swapper
{
    dijQ tmp = a;
    a = b;
    b = tmp;
}
void hMinTop(dijQ heap[], int siz) // heapify the top of the heap
{
    int pos = siz;
        while (pos > 0) //put a node higher if it is smaller than its parent
    {
        int par = (pos - 1) / 2;
        if (heap[pos].d < heap[par].d)
        {
            swaph(heap[pos], heap[par]);
            pos = par;
        }
        else
            break; //and break if it isn't
    }
}
void hpush(dijQ heap[], int d, int x, int y, int& siz) //adding a new element to the heap
{
    heap[siz].d = d;
    heap[siz].x = x;
    heap[siz].y = y;
    hMinTop(heap, siz);
    siz++;
}
void hfall(dijQ heap[], int siz, int h) // choosing the smallest distance element after putting the last heapnode on the top
{
    while (1) {

        int hmin = h;
        int l = h * 2 + 1;
        int r = h * 2 + 2;

                if (l < siz && heap[l].d < heap[h].d) //checking whether the left child is smaller than the parent
            hmin = l;

        if (r < siz && heap[r].d < heap[hmin].d)
            hmin = r;

                if (h != hmin) //and swapping if it is
        {
            swaph(heap[h], heap[hmin]);
            h = hmin;
        }
        else
            break; //and breaking if neither is
    }
}
dijQ htake(dijQ heap[], int& siz) //popping the top of the heap
{
    dijQ top = heap[0];
    heap[0] = heap[siz - 1];
    siz--;
    hfall(heap, siz, 0);
    return top;
}
int waitTime(int d, int w) // calculating the waiting time for the lift
{
    if (d % w == 0) //right on time for the lift
        return 0;
    return w - d % w; //wait time
}
void notLifts(int x, int y, int W, int H, int** tab, dijk** dij, dijQ* heap, int& siz, int* ox, int* oy)
{
    for (int ii = 0; ii < 4; ii++)
    {
        int tx = x + ox[ii];
        int ty = y + oy[ii];
        if (tx >= 0 && ty >= 0 && tx < W && ty < H)
        {
            if (dij[ty][tx].vis == false)
            {
                int nd = dij[y][x].dist + distance(tab[y][x], tab[ty][tx]);
                if (nd < dij[ty][tx].dist)
                {
                    dij[ty][tx].dist = nd;
                    hpush(heap, nd, tx, ty, siz);
                }
            }
        }
    }
}
void withLifts(int x, int y, lift* Li, int li, dijk** dij, dijQ* heap, int& siz, bool& nextdif)
{
    for (int i = 0; i < li; i++)
    {
        if (x == Li[i].sx && y == Li[i].sy && dij[Li[i].ey][Li[i].ex].vis == false)
        {
            nextdif = true;
            int tx = Li[i].ex;
            int ty = Li[i].ey;
            int nd = dij[y][x].dist + Li[i].time + waitTime(dij[y][x].dist, Li[i].wait);
            if (nd < dij[ty][tx].dist)
            {
                dij[ty][tx].dist = nd;
                hpush(heap, nd, tx, ty, siz);
            }
        }
    }

}
void dijkstra(int H, int W, int sx, int sy, int ex, int ey, lift* Li, int li, dijk** dij, int** tab, int difsp)
{
    dijQ* heap = new dijQ[H * W]; // heap tab
        int siz = 0; //size of the heap
    int x = sx, y = sy;
        int ox[4] = { 0, 0, 1, -1 }; //fixed arrays for smooth neighbour checking
    int oy[4] = { 1, -1, 0, 0 };

    dij[y][x].dist = 0;
        hpush(heap, 0, sx, sy, siz); //pushing the startpoint to the heap

    int sp = 0; //startpoints

        while (1)// loop until we find the destination
    {
        dijQ closest = htake(heap, siz); //taking element from min heap
        x = closest.x;
        y = closest.y;

        if (x < 0 || x >= W || y < 0 || y >= H) //out of bounds
        {
            continue;
        }

                if (dij[y][x].vis == true) //we have already visited this node and have the smallest possible distance
            continue;

        dij[y][x].vis = true;

        if (x == ex && y == ey) //destination reached
        {
            cout << closest.d << endl;
            break;
        }

        bool nextdif = false; // if we used the lifts from current point

        if (sp < difsp)
        {
                        withLifts(x, y, Li, li, dij, heap, siz, nextdif); //checking the lifts from the current position
        }

        if (nextdif)
                        sp++;  //if lifts from all points are used we can stop checking them

                notLifts(x, y, W, H, tab, dij, heap, siz, ox, oy); //checking the neighbours of the current position
    }
    delete[] heap;
}
int main()
{
        int W, H; // width and height of the map
    int sx, sy; // start position
    int ex, ey; // end position
        int li; // number of lifts
    scanf("%d %d %d %d %d %d %d", &W, &H, &sx, &sy, &ex, &ey, &li);

        int** tab = new int* [H]; //declaring input array
    for (int i = 0; i < H; i++)
        tab[i] = new int[W];

    dijk** dij = new dijk * [H];
    for (int i = 0; i < H; i++)
        dij[i] = new dijk[W];

    lift* Li = new lift[li];
    int difsp = 1; // different startpoints

    for (int i = 0; i < li; i++)
    {
        scanf("%d %d %d %d %d %d", &Li[i].sx, &Li[i].sy, &Li[i].ex, &Li[i].ey, &Li[i].time, &Li[i].wait);

        if (i > 0 && (Li[i].sx != Li[i - 1].sx || Li[i - 1].sy != Li[i].sy)) //if lift startpoints are different, we note it
            difsp++;
    }

        for (int i = 0; i < H; i++) //default values for dijkstra's algorithm arrays
        for (int j = 0; j < W; j++)
        {
            scanf("%d", &tab[i][j]);
            dij[i][j].dist = INF;
            dij[i][j].vis = false;
        }

        dijkstra(H, W, sx, sy, ex, ey, Li, li, dij, tab, difsp); //dijkstra's algorithm

    delete[] Li; //destructors
    for (int i = 0; i < H; i++)
        delete[] dij[i];
    delete[] dij;

    for (int i = 0; i < H; i++)
        delete[] tab[i];
    delete[] tab;
    return 0;
}
