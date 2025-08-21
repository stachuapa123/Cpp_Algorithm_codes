#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;
struct atom {
    int x;
    int y;
};
void otwarcie(int pp)
{
    char v = 2;
    char z = 2;
    char s = ' ';
    cout << v << v << v << s << s << s << v << s << s << s << s << s << s << z << z << s << s << s << v << v << v << v << s << s << z << s << s << z << s << s << v << v << v << s << s << s << s << z << z << s << s << s << v << s << s << s << v << endl;
    cout << v << s << s << v << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << v << s << s << z << s << s << z << s << s << v << s << s << s << v << endl;
    cout << v << s << s << v << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << s << s << s << z << s << z << s << s << s << v << s << s << v << s << s << z << s << s << z << s << s << s << v << s << v << s << endl;
    cout << v << v << v << s << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << s << s << s << z << z << s << s << s << s << v << v << v << s << s << s << z << s << s << z << s << s << s << s << v << s << s << endl;
    cout << v << s << s << v << s << s << v << s << s << s << s << s << z << z << z << z << s << s << v << s << s << s << s << s << z << s << z << s << s << s << v << s << s << v << s << s << z << s << s << z << s << s << s << v << s << v << s << endl;
    cout << v << s << s << v << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << s << s << s << z << s << s << z << s << s << v << s << s << v << s << s << z << s << s << z << s << s << v << s << s << s << v << endl;
    cout << v << v << v << s << s << s << v << v << v << v << s << s << z << s << s << z << s << s << v << v << v << v << s << s << z << s << s << z << s << s << v << v << v << s << s << s << s << z << z << s << s << s << v << s << s << s << v << endl;
    cout << endl << "Stanis" << static_cast <char> (136) << "aw Apanasiewicz ACiR 198169" << endl;
}
void wypisz(int c, char T[12][12], char TZ[2][12][12])
{
    char s = ' ';
    int g = c;
    cout << s << s << s << static_cast <char> (201);
    for (int i = 0;i <= 3 * g + 5;i++)
        cout << static_cast <char> (205);
    cout << static_cast <char> (187);
    cout << endl << s << s << s;
    cout << static_cast <char> (186);
    cout << s << s << s;
    for (int j = 1;j <= g;j++)
        cout << TZ[0][0][j] << T[0][j] << TZ[1][0][j];

    cout << s << s << s;
    cout << static_cast <char> (186) << endl << s << s << s;
    for (int i = 1;i <= g;i++)
    {
        cout << static_cast <char> (186);
        for (int j = 0;j <= g + 1;j++)
            cout << TZ[0][i][j] << T[i][j] << TZ[1][i][j];
        cout << static_cast <char> (186);
        cout << endl << s << s << s;
    }
    cout << static_cast <char> (186);
    cout << s << s << s;
    for (int j = 1;j <= g;j++)
        cout << TZ[0][g + 1][j] << T[g + 1][j] << TZ[1][g + 1][j];
    cout << s << s << s << static_cast <char> (186) << endl << s << s << s;
    cout << static_cast <char> (200);
    for (int i = 0;i <= 3 * g + 5;i++)
        cout << static_cast <char> (205);
    cout << static_cast <char> (188);
    cout << endl;
}
void generujatomy(int c, int d, atom AT[68])
{
    srand(time(NULL));
    int r;
    int tt[20];
    for (int i = 0;i < d;i++)
    {
        int w = c * c;
        r = rand();
        r = r % w;
        tt[i] = r;
        bool B = true;
        while (B == true)
        {
            B = false;
            for (int j = 0;j < i;j++)
            {
                if (tt[j] == tt[i])
                {
                    B = true;
                    r = rand();
                    r = r % w;
                    tt[i] = r;
                    break;
                }
            }
        }
    }

    cout << endl;
    for (int i = 0;i < d;i++)
    {
        AT[i].x = tt[i] % c + 1;
        AT[i].y = tt[i] / c + 1;
    }
}
void helptab(int c, char TT[12][12], char HELP[12][12], atom AT[68], int d)
{
    for (int i = 0;i <= c + 1;i++)
    {
        for (int j = 0;j <= c + 1;j++)
        {
            HELP[i][j] = TT[i][j];
        }
    }
    for (int i = 0;i < d;i++)
    {
        HELP[AT[i].y][AT[i].x] = 'A';
    }
}
void zrobhelp(int c, char T[12][12], char HELP[12][12], atom AT[68], int d, char TZ[2][12][12])
{
    char s = ' ';
    int g = c;
    cout << s << s << s << static_cast <char> (201);
    for (int i = 0;i <= 3 * g + 5;i++)
        cout << static_cast <char> (205);
    cout << static_cast <char> (187);
    cout << endl << s << s << s;
    cout << static_cast <char> (186);
    cout << s << s << s;
    for (int j = 1;j <= g;j++)
        cout << TZ[0][0][j] << HELP[0][j] << TZ[1][0][j];

    cout << s << s << s;
    cout << static_cast <char> (186) << endl << s << s << s;
    for (int i = 1;i <= g;i++)
    {
        cout << static_cast <char> (186);
        for (int j = 0;j <= g + 1;j++)
            cout << TZ[0][i][j] << HELP[i][j] << TZ[1][i][j];
        cout << static_cast <char> (186);
        cout << endl << s << s << s;
    }
    cout << static_cast <char> (186);
    cout << s << s << s;
    for (int j = 1;j <= g;j++)
        cout << TZ[0][g + 1][j] << HELP[g + 1][j] << TZ[1][g + 1][j];
    cout << s << s << s << static_cast <char> (186) << endl << s << s << s;
    cout << static_cast <char> (200);
    for (int i = 0;i <= 3 * g + 5;i++)
        cout << static_cast <char> (205);
    cout << static_cast <char> (188);
    cout << endl;
}
void save(int y, int c, char UT[1000][12][12], char T[12][12])
{
    for (int i = 0;i <= c + 1;i++)
    {
        for (int j = 0;j <= c + 1;j++)
        {
            UT[y][i][j] = T[i][j];
        }
    }
}
void undo(int y, int c, char UT[1000][12][12], char T[12][12])
{
    for (int i = 0;i <= c + 1;i++)
    {
        for (int j = 0;j <= c + 1;j++)
        {
            T[i][j] = UT[y][i][j];
        }
    }
}
int liczo(int c, char T[12][12])
{
    int suma = 0;
    for (int i = 1;i <= c;i++)
    {
        for (int j = 1;j <= c;j++)
        {
            if (T[i][j] == 'o')
                suma++;
        }

    }
    return suma;
}
void menu(int c)
{
    cout << "aby zrestartowac etap gry kliknij a" << endl;
    cout << "aby zakonczyc etap gry kliknij b" << endl;
}
void TdoTT(int c, char T[12][12], char TT[12][12])
{
    for (int i = 0;i <= c + 1;i++)
    {
        for (int j = 0;j <= c + 1;j++)
        {
            T[i][j] = TT[i][j];
        }
    }
}
void koniec(int c, int d, char T[12][12], atom AT[68])
{
    for (int i = 0;i < d;i++)
    {
        if (T[AT[i].y][AT[i].x] == 'o')
            T[AT[i].y][AT[i].x] = 'O';
        else
            T[AT[i].y][AT[i].x] = 'A';
    }
    for (int i = 0;i <= c + 1;i++)
    {
        for (int j = 0;j <= c + 1;j++)
        {
            if (T[i][j] == 'o')
            {
                T[i][j] = 'X';
            }
        }
    }
}
int main()
{
    while (1)
    {
        otwarcie(2);
        char P;
        int n, m;
        cout << "Wybierz poziom" << endl;
        cout << "Plansza 5x5, 3 atomy - kliknij a" << endl;
        cout << "Plansza 8x8, 5 atom" << static_cast <char> (162) << "w - kliknij b" << endl;
        cout << "Plansza 10x10, 8 atom" << static_cast <char> (162) << "w - kliknij c" << endl;
        cout << "Wyjd" << static_cast <char> (171) << " z gry - kliknij q" << endl;
        cin >> P;
        if (P == 'a')
        {
            n = 5;
            m = 3;
        }
        else if (P == 'b')
        {
            n = 8;
            m = 5;
        }
        else if (P == 'c')
        {
            n = 10;
            m = 8;
        }
        else if (P == 'q')
        {
            system("CLS");
            cout << "koniec gry";
            break;
        }
        char T[12][12];
        char TT[12][12];
        char TZ[2][12][12];
        atom AT[68];
        generujatomy(n, m, AT);
        char HELP[12][12];
        char UT[1000][12][12];
        char o = '*';
        char x = 'X';
        char h = '*';
        char a = '{', b = '}', e = '[', f = ']', s = ' ';
        for (int i = 0;i <= n + 1;i++)
        {
            for (int j = 0;j <= n + 1;j++)
            {
                TZ[0][i][j] = e;
                TZ[1][i][j] = f;
            }
        }
        T[0][0] = o;
        T[0][n + 1] = o;
        T[n + 1][0] = o;
        T[n + 1][n + 1] = o;
        for (int i = 1;i <= n;i++)
        {
            T[i][0] = h;
            TT[i][0] = h;
        }
        for (int i = 1;i <= n;i++)
        {
            T[0][i] = h;
            TT[0][i] = h;
        }
        for (int i = 1;i <= n;i++)
        {
            T[n + 1][i] = h;
            TT[n + 1][i] = h;

        }
        for (int i = 1;i <= n;i++)
        {
            T[i][n + 1] = h;
            TT[i][n + 1] = h;

        }
        for (int i = 1;i <= n;i++)
        {
            for (int j = 1;j <= n;j++)
            {
                T[i][j] = s;
                TT[i][j] = s;
            }
        }
        TZ[0][0][1] = a;
        TZ[1][0][1] = b;
        wypisz(n, T, TZ);
        char K;
        int kx = 1, ky = 0;
        int zx, zy;
        int px = 1, py = 0;
        int licz = 1;
        int un = 1;
        save(un, n, UT, T);
        int ix = 0, iy = 0;
        atom kord[20];
        int lo = 1;
        int unmax = un;

        for (int i = 0;i < 20;i++)
        {
            kord[i].x = 0;
            kord[i].y = 0;
        }
        while (1)
        {
            K = cin.get();
            bool b1 = true;
            bool b2 = true;
            bool b3 = true;
            bool b4 = true;
            zx = kx;
            zy = ky;
            int oo = liczo(n, T);
            if (un > unmax)
                unmax = un;
            if (K == 'a' || K == 'A')
            {
                kx -= 1;
                if (kx <= 0)
                {
                    if (kx < 0)
                        kx = n + 1;
                    else
                    {
                        if (ky == 0 || ky == n + 1)
                            kx = n;
                    }
                }
            }
            else if (K == 'w' || K == 'W')
            {
                ky -= 1;
                if (ky <= 0)
                {
                    if (ky < 0)
                    {
                        ky = n + 1;
                    }
                    else
                    {
                        if (kx == 0 || kx == n + 1)
                            ky = n;
                    }
                }
            }
            else if (K == 'd' || K == 'D')
            {
                kx += 1;
                if (kx >= n + 1)
                {
                    if (kx > n + 1)
                        kx = 0;
                    else
                    {
                        if (ky == 0 || ky == n + 1)
                            kx = 1;
                    }
                }
            }
            else if (K == 's' || K == 'S')
            {
                ky += 1;
                if (ky >= n + 1)
                {
                    if (ky > n + 1)
                        ky = 0;
                    else
                    {
                        if (kx == 0 || kx == n + 1)
                            ky = 1;
                    }
                }
            }
            else if (K == 'H')
            {
                b1 = false;
                helptab(n, TT, HELP, AT, m);
                zrobhelp(n, T, HELP, AT, m, TZ);
                this_thread::sleep_for(chrono::milliseconds(2800));
            }
            else if (K == 'o' && kx != 0 && ky != 0 && kx != n + 1 && ky != n + 1)
            {
                if (T[ky][kx] == 'o')
                {
                    T[ky][kx] = ' ';
                    un++;
                    save(un, n, UT, T);
                }
                else if (oo < m)
                {
                    T[ky][kx] = 'o';
                    un++;
                    save(un, n, UT, T);
                }
                b2 = false;
            }
            else if (K == ' ' && (kx == 0 || ky == 0 || kx == n + 1 || ky == n + 1) && T[ky][kx] == '*')
            {
                save(un, n, UT, T);
                un++;
                b2 = false;
                helptab(n, T, HELP, AT, m);
                px = kx;
                py = ky;
                bool up = false, down = false, right = false, left = false;
                if (px == 0)
                {
                    right = true;
                }
                else if (py == 0)
                {
                    down = true;
                }
                else if (py == n + 1)
                {
                    up = true;
                }
                else if (px == n + 1)
                {
                    left = true;
                }
                while (right == true || down == true || up == true || left == true)
                {
                    if (right == true)
                    {
                        if (HELP[py][px + 1] == 'A')
                        {
                            T[ky][kx] = 'H';
                            right = false;
                            break;
                        }
                        else if (HELP[py + 1][px + 1] == 'A' && HELP[py - 1][px + 1] == 'A')
                        {
                            right = false;
                            left = true;
                        }
                        else if (HELP[py + 1][px + 1] == 'A')
                        {
                            right = false;
                            up = true;
                        }
                        else if (HELP[py - 1][px + 1] == 'A')
                        {
                            right = false;
                            down = true;
                        }
                        else
                            px++;
                    }
                    else if (down == true)
                    {
                        if (HELP[py + 1][px] == 'A')
                        {
                            T[ky][kx] = 'H';
                            down = false;
                            break;
                        }
                        else if (HELP[py + 1][px + 1] == 'A' && HELP[py + 1][px - 1] == 'A')
                        {
                            down = false;
                            up = true;
                        }
                        else if (HELP[py + 1][px + 1] == 'A')
                        {
                            down = false;
                            left = true;
                        }
                        else if (HELP[py + 1][px - 1] == 'A')
                        {
                            down = false;
                            right = true;
                        }
                        else
                            py++;
                    }
                    else if (up == true)
                    {
                        if (HELP[py - 1][px] == 'A')
                        {
                            T[ky][kx] = 'H';
                            up = false;
                            break;
                        }
                        else if (HELP[py - 1][px + 1] == 'A' && HELP[py - 1][px - 1] == 'A')
                        {
                            up = false;
                            down = true;
                        }
                        else if (HELP[py - 1][px + 1] == 'A')
                        {
                            up = false;
                            left = true;
                        }
                        else if (HELP[py - 1][px - 1] == 'A')
                        {
                            up = false;
                            right = true;
                        }
                        else
                            py--;
                    }
                    else if (left == true)
                    {
                        if (HELP[py][px - 1] == 'A')
                        {
                            T[ky][kx] = 'H';
                            left = false;
                            break;
                        }
                        else if (HELP[py + 1][px - 1] == 'A' && HELP[py - 1][px - 1] == 'A')
                        {
                            left = false;
                            right = true;
                        }
                        else if (HELP[py + 1][px - 1] == 'A')
                        {
                            left = false;
                            up = true;
                        }
                        else if (HELP[py - 1][px - 1] == 'A')
                        {
                            left = false;
                            down = true;
                        }
                        else
                            px--;
                    }
                    if (px == 0 || py == 0 || px == n + 1 || py == n + 1)
                    {
                        up = false, down = false, right = false, left = false;
                        if (px == kx && py == ky)
                            T[py][px] = 'R';
                        else
                        {
                            if (licz < 10)
                            {
                                T[py][px] = char(licz + 48);
                                T[ky][kx] = char(licz + 48);
                            }
                            else
                            {
                                T[py][px] = char(licz + 87);
                                T[ky][kx] = char(licz + 87);
                            }
                            kord[licz].x = kx;
                            kord[licz].y = ky;
                            licz = licz + 1;
                        }
                    }
                }
                save(un, n, UT, T);
            }
            else if ((K == 'u' || K == 'U') && un > 1)
            {
                int ix = kord[licz - 1].x;
                int iy = kord[licz - 1].y;
                if (int(T[iy][ix]) > 48 && int(T[iy][ix]) < 58)
                {
                    licz--;
                    b3 = false;
                }
                b2 = false;
                un--;
                undo(un, n, UT, T);
            }
            else if ((K == 'r' || K == 'R') && unmax > un)
            {
                int ix = kord[licz - 1].x;
                int iy = kord[licz - 1].y;
                if (int(T[iy][ix]) > 48 && int(T[iy][ix]) < 58)
                {
                    licz++;
                    b4 = false;
                }

                b2 = false;
                un++;
                undo(un, n, UT, T);
            }
            else if (K == 'k')
            {
                int oooo = liczo(n, T);
                if (oooo < m)
                {
                    cout << "Za malo oznazen" << endl;
                }
                int punkty = 0;
                for (int i = 0;i < m;i++)
                {
                    if (T[AT[i].y][AT[i].x] == 'o')
                        punkty++;
                }
                cout << "Wynik - " << punkty << "/" << m << endl;
                if (punkty == m)
                {
                    cout << "Gratulacje wszystkie atomy znalezione" << endl;
                }
                else
                    cout << "Niestety nie uda" <<  static_cast <char> (136) <<"o sie" << endl;
                b1 = false;
                koniec(n, m, T, AT);
                wypisz(n, T, TZ);
                cout << "O - Trafiony Atom" << endl << "X - Niecelne Oznaczenie" << endl << "A - Pozycja Atomu" << endl;
                break;

            }
            else if (K == 'p')
            {
                system("CLS");
                cout << "Gra przerwana" << endl;
                helptab(n, TT, HELP, AT, m);
                zrobhelp(n, T, HELP, AT, m, TZ);
                break;
            }
            else if (K == 'q' || K == 'Q')
            {
                break;
            }
            else if (K == 'm')
            {
                char Y;
                menu(2);
                cin >> Y;
                if (Y == 'b')
                {
                    break;
                }
                if (Y == 'a')
                {
                    kx = 1, ky = 0;
                    px = 1, py = 0;
                    licz = 1;
                    un = 1;
                    TdoTT(n, T, TT);
                    ix = 0, iy = 0;
                    for (int i = 0;i < 20;i++)
                    {
                        kord[i].x = 0;
                        kord[i].y = 0;
                    }
                    save(un, n, UT, T);
                    unmax=1;
                }
            }
            if (b2 == true)
            {
                TZ[0][zy][zx] = e;
                TZ[1][zy][zx] = f;
                TZ[0][ky][kx] = a;
                TZ[1][ky][kx] = b;
            }
            if (b1 == true)
            {
                system("CLS");
                int ooo = liczo(n, T);
                if (m == 3)
                    cout << " (Do znalezienia s" << static_cast <char> (165) << " 3 atomy)" << endl;
                else if (m == 5)
                    cout << "    (Do znalezienia jest " << m << " atom" << static_cast <char> (162) << "w)" << endl;
                else if (m == 8)
                    cout << "       (Do znalezienia jest " << m << " atom" << static_cast <char> (162) << "w)" << endl;
                wypisz(n, T, TZ);
            }
            if (b3 == false)
            {
                int ooo = liczo(n, T);
                if (ooo != oo)
                    licz++;
            }
            if (b4 == false)
            {
                int ooo = liczo(n, T);
                if (ooo != oo)
                    licz--;
            }
        }
        char D;
        cout << endl << "kliknij cokolwiek, aby przejsc dalej" << endl;
        cin >> D;
        system("CLS");
    }
}
