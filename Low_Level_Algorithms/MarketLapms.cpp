#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
#include <iomanip>
#pragma warning(disable : 4996)
using namespace std;
void wypis(float open[], float close[], float high[], float low[], int H, int W, int il, int ir)
{
   
    char y;
    char tab[6101][50];
    float mini = 10000, maxi = 0;
    for (int i = il;i <= ir;i++)
    {
        mini = min(mini, low[i]);
        maxi = max(maxi, high[i]);
        for (int e = 0;e < 50;e++)
            tab[i][e] = '*';
    }
    
    float r = maxi - mini;
    
    float x = r / (H - 1);

    
    float p1, p, p2, pr, m, rr;
    float mantis, a1, a2, a3;
    for (int i = il;i <= ir;i++)
    {
        rr = (high[i] - low[i]) / x;
        
        if (open[i] > close[i])
        {
            y = '#';
            p1 = (open[i] - close[i]) / x;
            p = (close[i] - low[i]) / x;
            p2 = (high[i] - open[i]) / x;
        }
        else
        {
            y = 'O';
            p1 = (close[i] - open[i]) / x;
            p = (open[i] - low[i]) / x;
            p2 = (high[i] - close[i]) / x;
        }
        if (p1 == trunc(p1))
            a2 = p1;
        else
            a2 = trunc(p1) + 1;

        if (p2 == trunc(p2))
            a3 = p2;
        else
            a3 = trunc(p2) + 1;

        if (p == trunc(p))
            a1 = p;
        else
            a1 = trunc(p) + 1;

        pr = p / x;
        
        m = (low[i] - mini) / x;
        
        mantis = trunc(m);
       

        for (int j = mantis;j < (mantis + a1);j++)
        {
            tab[i][j] = '|';
        }
        for (int j = mantis + a1;j < (mantis + a1 + a2);j++)
        {
            tab[i][j] = y;
        }
        for (int j = mantis + a1 + a2;j < (mantis + a1 + a2 + a3);j++)
        {
            tab[i][j] = '|';
        }

    }

    char q;
    float f = maxi;
    ofstream plik1("chart.txt");
    if (!plik1) {
        cout << "Plik1 nie zostal otwarty";
    }
    plik1 << "Cena akcji:";
    plik1 << '\n';
    cout << "Cena akcji" << endl;
    for (int e = H - 1;e >= 0;e--)
    {
        cout << fixed << setprecision(2) << f << " ";
        plik1 << fixed << setprecision(2) << f << " ";
        f -= x;
        for (int i = il;i <= ir;i++)
        {
            if (tab[i][e] == '#' || tab[i][e] == '|' || tab[i][e] == 'O')
            {
                cout << tab[i][e];
                q = tab[i][e];
                plik1 << q;
            }
            else
            {
                cout << " ";
                plik1 << ' ';
            }
        }
        plik1 << "\n";
        cout << endl;
    }
    cout << "      ";
    plik1 << "      ";
    for (int i = 1;i <= W;i += 5)
    {
        cout << i;
        plik1 << i;
        if (i / 10 == 0)
        {
            cout << "    ";
            plik1 << "    ";
            }
            else if (i / 100 == 0)
        {
            cout << "   ";
            plik1 << "   ";
        } 
            else
        {
            cout << "  ";
            plik1 << "  ";
        }
    }
    cout << "ilosc dni" << endl;
    plik1 << "ilosc dni" <<'/n';

}
void gener(float open[], float close[], float high[], float low[])
{
    char* s = new char[80];
    int l = 80;
    char* wsk;


    ifstream plik("intc_us_data.csv");
    if (!plik) {
        cout << "Plik nie zostal otwarty";
    }
    plik >> s;
    for (int i = 1;i <= 6015;i++)
    {
        plik >> s;

        int y = 11;
        wsk = strtok(s, ",");
        wsk = strtok(NULL, ",");
        
        stringstream f1(wsk);
        float o;
        f1 >> o;
        open[i] = o;
        
        wsk = strtok(NULL, ",");
        stringstream f2(wsk);
        float h;
        f2 >> h;
        high[i] = h;
    
        wsk = strtok(NULL, ",");
        stringstream f3(wsk);
        float L;
        f3 >> L;
        low[i] = L;
       
        wsk = strtok(NULL, ",");
        stringstream f4(wsk);
        float c;
        f4 >> c;
        close[i] = c;
       
    }
}
void gener2(float open[], float close[], float high[], float low[], char wejs[])
{
    char* s = new char[80];
    int l = 80;
    char* wsk;


    ifstream plik(wejs);
    if (!plik) {
        cout << "Plik nie zostal otwarty";
    }
    plik >> s;
    for (int i = 1;i <= 6015;i++)
    {
        plik >> s;
      
        int y = 11;
        wsk = strtok(s, ",");
        wsk = strtok(NULL, ",");
     
        stringstream f1(wsk);
        float o;
        f1 >> o;
        open[i] = o;
 
        wsk = strtok(NULL, ",");
        stringstream f2(wsk);
        float h;
        f2 >> h;
        high[i] = h;
        
        wsk = strtok(NULL, ",");
        stringstream f3(wsk);
        float L;
        f3 >> L;
        low[i] = L;
       
        wsk = strtok(NULL, ",");
        stringstream f4(wsk);
        float c;
        f4 >> c;
        close[i] = c;
       
    }
}
void skalowanie(float open[], float close[], float high[], float low[], int H, int W, int il, int ir, int S, char wyjs[])
{

    char y;
    char tab[6101][50];
    char ts[2000][50];
    float open1[2000], close1[2000], high1[2000], low1[2000];
    float mini = 10000, maxi = 0, mini1, maxi1;
    for (int i = il;i <= ir;i++)
    {
        mini = min(mini, low[i]);
        maxi = max(maxi, high[i]);
        for (int e = 0;e < 50;e++)
            tab[i][e] = '*';
    }
   
    float r = maxi - mini;

    float x = r / (H - 1);
    int it = 0;
    for (int i = il;i <= ir;i += S)
    {
        open1[it] = open[i];
        maxi1 = 0;
        mini1 = 10000;
        for (int j = i;j < i + S;j++)
        {
            maxi1 = max(maxi1, high[j]);
            mini1 = min(mini1, low[j]);
        }
        close1[it] = close[i + S - 1];
        high1[it] = maxi1;
        low1[it] = mini1;
        it++;
    }
    for (int i = 0; i < it; i++)
        for (int e = 0;e < 50;e++)
            ts[i][e] = '*';
   
    float p1, p, p2, pr, m;
    float mantis, a1, a2, a3;
    for (int i = 0;i < it;i++)
    {
       
        if (open1[i] > close1[i])
        {
            y = '#';
            p1 = (open1[i] - close1[i]) / x;
            p = (close1[i] - low1[i]) / x;
            p2 = (high1[i] - open1[i]) / x;
        }
        else
        {
            y = 'O';
            p1 = (close1[i] - open1[i]) / x;
            p = (open1[i] - low1[i]) / x;
            p2 = (high1[i] - close1[i]) / x;
        }
        if (p1 == trunc(p1))
            a2 = p1;
        else
            a2 = trunc(p1) + 1;

        if (p2 == trunc(p2))
            a3 = p2;
        else
            a3 = trunc(p2) + 1;

        if (p == trunc(p))
            a1 = p;
        else
            a1 = trunc(p) + 1;

        pr = p / x;
      
        m = (low1[i] - mini) / x;

        mantis = trunc(m);
     
        for (int j = mantis;j < (mantis + a1);j++)
        {
            ts[i][j] = '|';
        }
        for (int j = mantis + a1;j < (mantis + a1 + a2);j++)
        {
            ts[i][j] = y;
        }
        for (int j = mantis + a1 + a2;j < (mantis + a1 + a2 + a3);j++)
        {
            ts[i][j] = '|';
        }

    }

    char q;
    float f = maxi;
    ofstream plik1(wyjs);
    if (!plik1) {
        cout << "Plik1 nie zostal otwarty";
    }
    plik1 << "Cena akcji:";
    plik1 << '\n';
    cout << "Cena akcji" << endl;
    for (int e = H - 1;e >= 0;e--)
    {
        cout << fixed << setprecision(2) << f << " ";
        plik1 << fixed << setprecision(2) << f << " ";
        f -= x;
        for (int i = 0;i < it;i++)
        {
            if (ts[i][e] == '#' || ts[i][e] == '|' || ts[i][e] == 'O')
            {
                cout << ts[i][e];
                q = ts[i][e];
                plik1 << q;
            }
            else
            {
                cout << " ";
                plik1 << ' ';
            }
        }
        plik1 << "\n";
        cout << endl;
    }
    int ni = 1;
    cout << "      ";
    plik1 << "      ";
    for (int i = 1;i <=  W/S;i += 5)
    {
        cout << i;
        plik1 << i;
        if (i / 10 == 0)
        {
            cout << "    ";
            plik1 << "    ";
        }
        else if (i / 100 == 0)
        {
            cout << "   ";
            plik1 << "   ";
        }
        else
        {
            cout << "  ";
            plik1 << "  ";
        }
    }
    
    if (S == 1) {
        cout << " dzien wykresu" << endl;
        plik1 << " dzien wykresu" << endl;
    }
    else if (S == 5)
    {
        cout << " tydzien wykresu" << endl;
        plik1 << " tydzien wykresu" << endl;
    }
    else if (S == 20)
    {
        cout << " miesiac wykresu" << endl;
        plik1 << " miesiac wykresu" << endl;
    }
}
int main()
{
    char Q;
    cout << "STANISLAW APANASIEWICZ 198169 ACiR" <<endl<< "aby wygemerowac standardowy wykres wcisnij g" <<endl<<"aby uzyc zaawansowanych funkcji wcisnij x"<<endl;
    ofstream plik2("info.log", ios::app);
    if (!plik2) {
        cout << "log nie zostal otwarty";
    }
    while (cin >> Q)
    {
        system("cls");
        float open[10000], close[10000], high[10000], low[10000];
        int H = 50, W = 200;
        char* s = new char[80];
        int l = 80;
        int IL;
        char wejs[80];
        char wyjs[80];
        int S = 1;
        char q1;
        if (Q == 'q')
        {
            cout << "KONIEC PROGRAMU";
            plik2 << "zakonczono program" << '\n';
            break;
        }
        else if (Q == 'g')
        {
            gener(open, close, high, low);
            wypis(open, close, high, low, H, W, 5816, 6015);
            plik2 << "wygenerowano standardowy wykres" << '\n';
        }
        else if (Q == 'x')
        {
            cout << "podaj plik wejsciowy: ";
            cin >> wejs;
            plik2 << "podano plik wejsciowy: "<< wejs << '\n';
            cout << "podaj plik wyjsciowy: ";
            cin >> wyjs;
            plik2 << "podano plik wyjsciowy: " << wyjs << '\n';
            cout << "podaj wysokosc wykresu: ";
            cin >> H;
            plik2 << "podano wysokosc wykresu: " << H << '\n';
            cout << "podaj dzien od ktorego zacznie sie wykres: ";
            cin >> IL;
            plik2 << "podano dzien rozpoczecia wykresu " << IL << '\n';
            cout << "podaj liczbe dni ";
            cin >> W;
            plik2 << "podano liczbe dni do wykresu " << W << '\n';
            cout << "1 dzien - 1 slupek - wcisnij d" << endl << "1 tydzien - 1 slupek wcisnij t" << endl << "1 miesiac - 1 slupek - wcisnij m" << endl;
            cin >> q1;
            if (q1 == 't')
                S = 5;
            else if (q1 == 'm')
                S = 20;
            else S = 1;

            gener2(open, close, high, low, wejs);
            skalowanie(open, close, high, low, H, W, IL, IL + W - 1, S, wyjs);
            plik2 << "wygenerowano zaawansowany wykres" << '\n';
        }
    }

}
