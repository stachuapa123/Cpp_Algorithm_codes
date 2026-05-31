#include <iostream>
#define MI 20000
using namespace std;
struct lnode { // a list node
    char c;
    lnode* next;
};

struct snode{ // a stack node, contains pointers to lists
    lnode* h;
    snode* next;
};

void add2(lnode*& head, char cc) // adds an element to a list
{

    if (head == nullptr)
        {
            head = new lnode{cc, nullptr};
        }
    else
        {
            add2(head->next, cc);
        }
}

void spush2(snode*& stc) // adds a new empty stack node
{
    snode* newsnode = new snode;
    newsnode->h = nullptr;
    newsnode->next = stc;
    stc = newsnode;
}
void printList(lnode* head) // prints a list in a reverse order
 {
    if (head != nullptr)
    {
        std::cout << head->c;
        printList(head->next);
    }
}
void printList2(lnode* head) //prints a list for & operator
 {
    if (head != nullptr)
    {
        printList2(head->next);
        std::cout << head->c;
    }
}

void showstc(snode* stc, int ii, int si) // handles & task
{
    if(stc != nullptr)
    {
        showstc(stc->next, ii-1, si);
        cout<<si - ii<<": ";
        printList2(stc->h);
        cout<<endl;
    }
}
void dell(lnode* ln) //deletes whole list
{
    if (ln != nullptr)
    {
        dell(ln->next);
        delete ln;
    }
}
void stcpop(snode*& stc) // deletes a stack element (and a list it points to)
{
    if(stc != nullptr)
    {
        snode* scopy = stc;
        stc = stc->next;
        dell(scopy->h);
        delete(scopy);
    }
}
void lcopy(lnode*& ln1, lnode* ln2) //makes a copy of a list
{
    if(ln2 != nullptr)
    {
    if (ln2->next != nullptr)
        {
            ln1 = new lnode{ln2->c, nullptr};
            lcopy(ln1->next, ln2->next);
        }
    else
        ln1 = new lnode{ln2->c, nullptr};
    }

}
lnode* dupl(lnode* head) //creates a list duplicate
{
    lnode* cnode = nullptr;
    lcopy(cnode, head);
    return cnode;
}
void pushready(snode*& stc, lnode* cp) //puts an already existing list on a stack
{
    snode* newsnode = new snode;
    newsnode->h = cp;
    newsnode->next = stc;
    stc = newsnode;
}
void swapL2(snode*& stc) //swaps references on a stack to list on top and one below (does not delete lists)
{
    lnode* top = stc->h;
    stc = stc->next;
    lnode* bot = stc->h;
    stc->h = top;
    pushready(stc, bot);
}
int toint(lnode* num , int f, int sum) //converts a "number" to an actual int, these numbers have to be 1, 0 for iterating without loop
{
    if (num->next != nullptr)
        {
             sum += int(num->c - '0');
             sum *= 10;
             return toint(num->next, f+1, sum);
        }
    else
    {
        sum += int(num->c - '0');
        return sum;
    }
}

void fis(snode*& stc, snode* stc2, int fi) //finds an element on the stack which is fi below the top and pushes a copy of that list on top of the stack
{
    if (fi > 0)
        fis(stc, stc2->next, fi - 1);
    else if (stc2 != nullptr)
    {
        lnode* ndf = dupl(stc2->h);
        pushready(stc, ndf);
    }
}
char getf(lnode* fln) // a getter for the lists first element
{
    return(fln->c);
}
bool checks(lnode* cln)
{
    if(cln == nullptr)
    {
       //it is an empty list
        return true;
    }
    else if(cln->next == nullptr && cln->c == '0')
    {
        //it is '0'
        return true;
    }
    return false;
}
void push1(snode*& stc, char cc) //makes a new stack element and adds a list with only one element
{
    lnode* newln = new lnode;
    newln->c=cc;
    newln->next=nullptr;
    pushready(stc, newln);
}
char lastc(lnode* ln) //gets an element on the list which is furthest away from the stack node
{
    if(ln->next != nullptr)
        return lastc(ln->next);
    else
        return ln->c;

}
void lpop(lnode*& ln) //pops an element on the list which is furthest away from the stack node
{
    if(ln->next == nullptr)
    {
        delete ln;
        ln = nullptr;
    }
    else
    {
      lpop(ln->next);
    }
}
void addm(snode*& stc) //ads a minus
{
    lnode* ln = new lnode{'-',stc->h};
    stc->h = ln;
}
void abs(snode*& stc) //omits first element
{
    stc->h = (stc->h)->next;
}
lnode*& lastnod(lnode*& ln) // gets a reference to the list element which is the one furthers away from the stack pointer
{
    if(ln->next != nullptr)
        return lastnod(ln->next);
    else
        return ln;
}
void mergeL(snode*& stc) //handles # operator, removes an first stacknode and merges two lists by
{
    if (stc == nullptr || stc->next == nullptr) return;

    lnode* top = stc->h;
    stc = stc->next;

    lnode* bot = stc->h;

    stc->h = top;
    (lastnod(top))->next = bot;

}
int pwten(int n, int p) // p must be 0,  n is an integer which length is measure
{
    if (n/10 == 0)
        return p;
    else
        return pwten(n/10, p+1);
}
int exp10(int a, int p) // a must be equal to 1 at first input
{ // returns a power of 10, which is equivalent to a number of digits which a has
    if(p>0)
        return exp10(a*10, p-1);
    else return a;
}
void intnod(lnode*& ln, int a, int d)
{ // a is an integer which is converted into a list, d is a power of 10, which is equivalent to a number of digits which a has
    if(d>0)
    {
        int od = a / d; //oldest digit of this number
        //cout<<endl<<"a = "<<a;
        char cd = char(od + '0');
        add2(ln, cd);
        intnod(ln->next,a - od * d,d/10);
    }
}
int numd(lnode* ln, int s) //returns size of a list
{
    if(ln->next != nullptr)
    {
        if(s==0 && ln->c =='0')
        {
            return numd(ln->next, 0);
        }
        else
        {
            return numd(ln->next,s+1);
        }
    }
    else return s+1;
}
bool eq(lnode* lna, lnode* lnb) // checks if two same size numbers are equal
{
    if(lna != nullptr)
    {
        if(lna->c == lnb->c)
        {
            return eq(lna->next, lnb->next);
        }
        else return false;
    }
    return true;
}
bool gr(lnode* lna, lnode* lnb) //checks if one number is greater than other (they are the same size)
{
    if(lna != nullptr)
    {
        if(lna->c > lnb->c)
        {
            return true;
        }
        else if(lna->c < lnb->c)
        {
            return false;
        }
        else return gr(lna->next, lnb->next);
    }
    return false;
}
void skip0(lnode*& ln) // deletes all 0 elements until another sign so that a number does not start with 0
{
    if(ln->c == '0' && ln->next != nullptr)
    {
        lnode* lt = ln;
        ln = ln->next;
        delete(lt);
        skip0(ln);
    }
}
void skipf(lnode*& ln) // removes first sign
{
        lnode* lt = ln;
        ln = ln->next;
        delete(lt);
}
bool iseq(snode*& stc) //handles <, checks if 2 lists are equal
{
    int n1, n2; // lengths of lists
    bool neg1 = false, neg2=false; //true for negative numbers
    lnode* lna = stc->h;
    if(stc->h != nullptr)
    {
        if(lna->c == '-')
        {
           skipf(lna);
            neg1 = true;
        }
        skip0(lna);
        n1 = numd(lna,0);
    }
    if(lna == nullptr || lna->c == '0' ) n1=0;

    stc = stc->next;

    lnode* lnb = stc->h;
    if(stc->h != nullptr)
    {
         if(lnb->c == '-')
        {
           skipf(lnb);
            neg2 = true;
        }
        skip0(lnb);
        n2 = numd(lnb,0);
    }
    if(lnb == nullptr || lnb->c == '0' ) n2=0;
    stc = stc->next;


    if(n1==0 && n2==0) // both numbers are zeros
        return true;
    else if(neg1 != neg2) // different signs
        return false;
    else if(n1 != n2) //different lengths
    {
        return false;
    }
    else if(eq(lna,lnb))
        return true;
    else
        return false;

}

bool isgr(snode*& stc)
{
    int na, nb; // lengths
    int neg1 = 0, neg2=0; // 1 for negative numbers later on

    lnode* lna = stc->h;

  //for getting numbers and removing minuses and first zeros
    if( stc->h != nullptr)
    {
        if(lna->c == '-')
        {
           skipf(lna);
            neg1 = 1;
        }
        skip0(lna);
         na = numd(lna, 0);
    }
    if(lna->c == '0') na = 0;
    stc = stc->next;

    lnode* lnb = stc->h;
     if( stc->h != nullptr)
    {
        if(lnb->c == '-')
        {
           skipf(lnb);
            neg2 = 1;
        }
        skip0(lnb);
         nb = numd(lnb, 0);
    }
    if(lnb->c == '0') nb = 0;
    stc = stc->next;


    if(na == 0 && nb == 0)
    {
       // BOTH ARE ZEROS
        return false;

    }
    else if(neg1 < neg2) //a is positive and b is negative
    {
        return true;
    }
    else if(neg1 > neg2)
    {
       //A- B+
        return false;
    }
    else if(neg1 == 0 && neg2 == 0) // both are positive
    {
        if(na > nb)
        {
           // A is longer
            return true;
        }
        else if( na < nb)
        {
           // B is longer
            return false;
        }
        else if(gr(lna,lnb))
        {
           //A is greater
            return true;
        }

    }
    else if(neg1 == 1 && neg2 == 1) // both are negative
    {

        if(na > nb)
        {
        //   A is longer (minus)
            return false;
        }
        else if( na < nb)
        {
         // B is longer (minus)
            return true;
        }
        else if(eq(lna, lnb))
        {
            return false;
        }
        else if(!gr(lna,lnb))
        {
          //  abs of A is smaller and both number are negative
            return true;
        }

    }
    //B >= A
        return false;
}
int riddler(snode*& stc) //for ? operator, checks if W is empty or '0' and gets a number from T to an integer, returns -1 if W is different
{
    lnode* lnT = stc->h;
    stc=stc->next;
    lnode* lnW = stc->h;
    stc=stc->next;
    if( !checks(lnW) )
    {
        int r = toint(lnT, 1, 0);
        return r;
    }
    return -1;
}

void adding1(lnode*& lna, lnode*& lnb, lnode*& sum) // for addition of same sign numbers
{
    if( lna != nullptr && lnb != nullptr)
    {
        char cc = lna->c + lnb->c - '0';
         sum = new lnode{cc, sum};
        adding1(lna->next, lnb->next, sum);
    }
}
void minusing(lnode*& lna, lnode*& lnb, lnode*& sum) //for substracting, lna is always a higher ABS value number
{
    if( lna != nullptr && lnb != nullptr)
    {
        char cc = lna->c - lnb->c + '0';
         sum = new lnode{cc, sum};
        minusing(lna->next, lnb->next, sum);
    }
}

lnode* fillZ(lnode* ln, int z) //fills not equal numbers with zeros so they are the same size
{
    if (z == 0)
        return ln;
    lnode* nln = new lnode{'0', fillZ(ln, z - 1)};
    return nln;
}
void makeeq(lnode*& lna, lnode*& lnb, int na,int nb) //makes two lists equal size
{
    int d;
    if(na > nb)
    {
        d = na - nb;
        lnb = fillZ(lnb, d);
    }
    else
    {
        d = nb - na;
        lna = fillZ(lna, d);
    }

}
void decim(lnode*& sum, int p, lnode*& sum2) //handles numbers which are not decimal signs, stores them in sum2
{
    if(sum->next != nullptr)
    {
        sum->c += p;
        if(sum->c > '9')
        {
            sum->c -= 10;
            p = 1;
        }
        else p=0;
        sum2 = new lnode{sum->c, sum2};
        decim(sum->next, p, sum2);

    }
    else if(sum != nullptr && sum->next == nullptr) //for the oldest digit
    {
        sum->c += p;
        if(sum->c > '9')
        {
            sum->c -= 10;
            add2(sum, '1');
            sum2 = new lnode{sum->c, sum2};
            sum2 = new lnode{'1', sum2};
        }
        else sum2 = new lnode{sum->c, sum2};
    }
}
void decim2(lnode*& sum, int p, lnode*& sum2) //handles numbers which are not decimal signs, stores them in sum2 (for substracting)
{
    if(sum->next != nullptr)
    {
        sum->c -= p;
        if(sum->c < '0')
        {
            sum->c += 10;
            p = 1;
        }
        else p=0;
        sum2 = new lnode{sum->c, sum2};
        decim2(sum->next, p, sum2);
    }
    else if(sum != nullptr && sum->next == nullptr) //for the oldest digit
    {
        sum->c -= p;
        sum2 = new lnode{sum->c, sum2};
    }
}
void plusn(snode*& stc) //handles + operator
{
    int sgn = 0; // a sign of a number 1 for +, 0 for 0 and -1 for -
    int na=0, nb=0; //lengths of numbers we are adding
    int neg1 = 0, neg2=0; // 1 for negative two added numbers


    lnode* lna = stc->h; // takes a pointer for the list at the top of the stack
    if( stc->h != nullptr)
    {
        if(lna->c == '-') //if the sign is a minus remove it, and set neg1 to 1
        {
           skipf(lna);
            neg1 = 1;
        }
        skip0(lna); //remove all the zeros until a non zero number is found
         na = numd(lna, 0);
    }


    stc = stc->next;
    lnode* lnb = stc->h;
   if( stc->h != nullptr)
    {
        if(lnb->c == '-')
        {
           skipf(lnb);
            neg2 = 1;
        }
        skip0(lnb);
         nb = numd(lnb, 0);
    }
     stc = stc->next;

    if(na != nb)
    {
        makeeq(lna, lnb, na, nb);
    }

    lnode* sum = nullptr; //first list for a sum, stores also chars which are not 0 - 9
    lnode* sum2 = nullptr; // second list for a sum, a final one
    if(neg1 == 0 && neg2 == 0) //both numbers are positive
    {
            sgn = 1;
            adding1(lna, lnb, sum);
            decim(sum,0, sum2);

    }
    else if(neg1 == 1 && neg2 == 1)//both numbers are negative, we are adding them and than putting a minus
    {
            sgn = -1;
            adding1(lna, lnb, sum);
            decim(sum,0, sum2);
    }
    else if(neg1 == 0 && neg2 == 1) // A+ B-
    {
            if(na > nb || gr(lna, lnb)) //ABS(A) > ABS(B)
            {
                sgn = 1;
                minusing(lna, lnb, sum); // it matters because the first number in minusing function has to be bigger in abs
                decim2(sum,0,sum2);
            }
            else //ABS(A) <= ABS(B)
            {
                sgn = -1;
                minusing(lnb, lna, sum);
                decim2(sum,0,sum2);
            }
    }
    else //A- B+
    {
         if(na > nb || gr(lna, lnb)) //ABS(A) > ABS(B)
            {
                sgn = -1;
                minusing(lna, lnb, sum);
                decim2(sum,0,sum2);
            }
            else //ABS(A) <= ABS(B)
            {
                sgn = 1;
                minusing(lnb, lna, sum);
                decim2(sum,0,sum2);
            }
    }
    if(sum2 != nullptr) //removes first zeros
        skip0(sum2);

    if(sum2 == nullptr) //if the list is empty just push a list with '0'
        push1(stc, '0');
    else
    {
        pushready(stc, sum2);
        if(sgn == -1 && sum2->c != '0')
            addm(stc); //push sum2, and perhaps add a minus
    }

}
int main() {
    char t[MI]; //only array in this program
    cin >> t;
    snode* stc = nullptr; //a stack
    int si = 0; //counter of stack elements
    char q; //for . operator
    for (int i = 0; t[i] != '\0'; i++) //only loop in this program
        {

            if(t[i]=='.') //take a char from one line below
            {
                cin>>q;
                add2(stc->h, q);
                si++;
            }
            else if(t[i]=='\'') //push a new empty stack element
            {
                spush2(stc);
                si++;
            }
            else if(t[i]=='&') //print all elements
            {
                showstc(stc,si,si);
            }
            else if(t[i]==',') //pop the first stack element
            {
                stcpop(stc);
                si--;
            }
            else if(t[i]==':') //push a copy of a list on top of the stack
            {
                pushready(stc, dupl(stc->h));
                si++;
            }
            else if(t[i]==';') //swap 2 first stack elements
            {
                swapL2(stc);
            }
            else if(t[i]=='@')
            {
                int fi = toint(stc->h, 1, 0); //these numbers have to be 1, 0 for iterating without loop
                stcpop(stc);
                snode* stct = stc;
                fis(stc, stct, fi);
                si--;
            }
            else if(t[i]=='>') //prints a single char from the list and removes it
            {
                if(stc->h != nullptr)
                {
                cout<<lastc(stc->h);
                stcpop(stc);
                si--;
                }
            }
            else if(t[i]=='!') //checks if a list is empty or '0'
            {
                bool b = checks(stc->h);
                stcpop(stc);
                if(b)
                    push1(stc, '1');
                else push1(stc, '0');
            }
            else if(t[i]=='-') //adds a minus (or removes it if it already exists
            {
                if(stc->h != nullptr)
                {
                    if(getf(stc->h) == '-')
                        abs(stc);
                    else
                        addm(stc);
                }
                else(add2(stc->h,'-'));
            }
            else if(t[i]=='^') //just abs
            {
                if(stc->h != nullptr)
                 if(getf(stc->h) == '-')
                 {
                     abs(stc);
                 }
            }
            else if(t[i]==']') //puts a char which index is equivalent to the number on top of the stack
            {
                int n = toint(stc->h, 1, 0);
                stcpop(stc);
                push1(stc, char(n));
            }
            else if(t[i]=='[') // take a char, put a number which is equivalent to it's index
            {
                if(stc->h != nullptr)
                {
                    char ctl = lastc(stc->h);
                    int cn = int(ctl); //index of a char
                    stcpop(stc);
                    spush2(stc);
                    int v = pwten(cn,0);
                    int d = exp10(1,v); // d is a power of 10, for a 4digit number it is 1000 etc
                    intnod(stc->h,cn,d);
                }
            }
            else if(t[i]=='$') //remove a char from the list and put it as a next list
            {
                char cl ;
                if(stc->h != nullptr)
                    cl = lastc(stc->h);
                else
                    cl = '0';
                if(stc->h != nullptr)
                {
                    lpop(stc->h);
                    spush2(stc);
                    add2(stc->h, cl);
                    si++;
                }
            }
            else if(t[i]=='#') //merge two list
            {
                mergeL(stc);
            }
            else if(t[i]=='=') //check for equal numbers
            {
                if(stc != nullptr && stc->next != nullptr)
                {
                    si--;
                    bool b = iseq(stc);
                     if(b)
                        push1(stc, '1');
                    else push1(stc, '0');
                }
            }
            else if(t[i]=='<') // compare numbers
            {
                if(stc != nullptr && stc->next != nullptr)
                {
                    si--;
                    bool b = isgr(stc);
                     if(b)
                     {
                        push1(stc, '1');
                     }
                    else
                    {
                        push1(stc, '0');
                    }
                }
            }
            else if(t[i]=='?') //jump on the array
            {
                if(stc != nullptr && stc->next != nullptr)
                {
                    si--;
                    int bb = riddler(stc);
                    if(bb>=0)
                        i = bb-1;
                    }
            }
            else if(t[i]=='~') //put iterator (i) on the stack
            {
                si++;
                spush2(stc);
                int v = pwten(i,0);
                int d = exp10(1,v);
                intnod(stc->h,i,d);
            }
            else if(t[i]=='+') //addition
            {
                si--;
                plusn(stc);
            }
            else //add to a list
            {
                if(stc!=nullptr)
                add2(stc->h, t[i]);
            }
        }
}
