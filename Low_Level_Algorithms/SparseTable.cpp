#include <iostream>
using namespace std;
struct node { //node of a trie
        int key;
        node** child = nullptr; //child pointer is allocated to nullptr by default to save more memory
};
void childAlloc(node& nod, int k) //allocates child pointers
{
        if (nod.child == nullptr) //but only if the child pointer is not allocated yet
        {
                nod.child = new node * [k];
                for (int i = 0; i < k; i++)
                        nod.child[i] = nullptr;
        }
}
void addnode(node& nod, int x) //adds a value to the node
{
        nod.key = x;
        nod.child = nullptr;

}
void insert2(node& nod, int x, int xdv, int k) // inserts a value into the trie, it is another function to avoid sending so many parameters by recursion
{
        int pos = xdv % k; //position to allocate
        if (x == nod.key)
        {
                printf("%d exist\n", x);
                return; //if the value already exists
        }
        childAlloc(nod, k); //checks if child pointer allocation is needed

        if (nod.child[pos] != nullptr)
                insert2(*nod.child[pos], x, xdv / k, k); //going deeper if needed
        else
        {
                nod.child[pos] = new node; //here we are in a good position to allocate a new node
                addnode(*nod.child[pos], x);
        }
}
void insert(node& nod, int x, int n, int k) // inserts a value into the trie
{
        int pos = x % n;
        if (x == nod.key)
        {
                printf("%d exist\n", x);
                return;
        }
        childAlloc(nod, k);

        if (nod.child[pos] != nullptr)
                insert2(*nod.child[pos], x, x/n, k);
        else
        {
                nod.child[pos] = new node;
                addnode(*nod.child[pos], x);
        }
}
void show2(node& nod, int k)
{
        printf("%d ", nod.key); //prints the key of the node
        if (nod.child == nullptr) //if there are no children, we stop
                return;
        for (int i = 0; i < k; i++)
        {
                if (nod.child[i] != nullptr) //if it has children in that position, we go deeper
                {
                        show2(*nod.child[i], k);
                }
        }
}
void show(node& nod, int n, int k)
{
        printf("%d ", nod.key);
        if (nod.child == nullptr) //if there are no children, we stop
                return;
        for (int i = 0; i < n; i++)
        {
                if (nod.child[i] != nullptr)
                {
                        show2(*nod.child[i],k);
                }
        }
}
bool look2(node& nod, int x, int xdv, int k)
{
        if (nod.key == x) //this is the key we are looking for
        {
                return true;
        }
        else
        {
                int pos = xdv % k;
                if (nod.child != nullptr && nod.child[pos] != nullptr) //checks whether it has children and if there is a child in the right place
                {
                        return look2(*nod.child[pos], x, xdv / k, k); //and goes deeper if it is the case
                }
                else
                        return false; //and stops when it is not the case
        }
}
bool look(node& nod, int x, int n, int k)
{
        if (nod.key == x)
        {
                return true;
        }
        else
        {
                int pos = x % n;
                if (nod.child != nullptr && nod.child[pos] != nullptr)
                {
                        return look2(*nod.child[pos], x, x / n, k);
                }
                else
                        return false;
        }
}

int leftLeaf(node*& nod, int k) // finds the leftmost leaf in the trie and deletes it
{
        for (int i = 0; i < k; i++)
        {
                if (nod->child != nullptr && nod->child[i] != nullptr)
                {
                        return leftLeaf(nod->child[i], k); //goes deeper if there is the first (leftmost) child
                }
        }
        int rep = nod->key; //deletes the node with the leftmost leaf and returns its key
        delete nod;
        nod = nullptr;
        return rep;
}
void dell2(node*& nod, int x, int xdv, int k)
{
        if (nod->key == x) //here we found the node we are looking for
        {
                bool b = true; //it is a flag to check if the node is a leaf or not
                if (nod->child != nullptr)
                {
                        for (int i = 0; i < k; i++)
                        {
                                if (nod->child[i] != nullptr) //here we found that the node has children, we are going to set the current's nodde value for leftmost child
                                {
                                        int ll = leftLeaf(nod->child[i], k);
                                        nod->key = ll;
                                        b = false;
                                        break;
                                }
                        }
                }
                if(b)
                {
                        delete nod;  // here it indicates that deleted value is a leaf, we just delete the node
                        nod = nullptr;
                }

        }
        else
        {
                int pos = xdv % k;
                if (nod->child != nullptr && nod->child[pos] != nullptr)//checks if it there is any child and than if there is a child in the right place
                {
                        dell2(nod->child[pos], x, xdv / k, k); //here it goes deeper because the node has a child in the right place
                }
                else
                {
                        printf("%d not exist\n", x); // here we know the node we want to delete does not exist
                }

        }
}
void dell(node& nod, int x, int n, int k)
{
        if (nod.key == x)
        {
                if (nod.child != nullptr)
                {
                        for (int i = 0; i < n; i++)
                        {
                                if (nod.child[i] != nullptr)
                                {
                                        int ll = leftLeaf(nod.child[i], k);
                                        nod.key = ll;
                                        break;
                                }
                        }
                }
        }
        else
        {
                int pos = x % n;
                if (nod.child != nullptr && nod.child[pos] != nullptr)
                {
                    dell2(nod.child[pos], x, x / n, k);
                }
                else
                {
                        printf("%d not exist\n", x);
                }

        }
}
int main()
{
        int N; //number of inputs
        int mx, mi; //maximum and minimum values (not used for the code)
        int n, k; //n - size of the child array in root, k - size of the child array in other nodes
        scanf("%d %d %d %d %d", &N, &mx, &mi, &n, &k);
        char q;
        int x;
        node root; //data structure variable for this task, it is not a reference so I cannot delete the root, I can only delete its children
        int siz = 0; //so I implemented a variable for counting the number of elements
        for(int i=0;i<N;i++)
        {
                scanf(" %c", &q);
                if (q == 'I')
                {
                        scanf("%d", &x);
                        if (siz == 0) //size is 0, we add the first element and allocate child nodes pointers, siz will be equal to 0 only once
                        {
                                addnode(root, x);
                                childAlloc(root, n);
                        }
                        else if (siz == -1) // siz is -1, when all elements were previously deleted
                        {
                                root.key = x; //we set the root key fot element from input, but now we can print it, siz will be equal to 1 after that
                                siz++;
                        }
                        else
                        {
                                insert(root, x, n, k); //inserting the element
                        }
                        siz++;
                }
                else if (q == 'P')//showing all elements in inorder
                {
                        if(siz > 0)
                                show(root,n,k);
                }
                else if (q == 'L')//looks if there is an inputed number
                {
                        scanf("%d", &x);
                        if (look(root, x, n, k) && siz > 0) //and checks additionally if size of the trie is greater than 0
                                printf("%d exist\n", x);
                        else
                                printf("%d not exist\n", x);
                }
                else if (q == 'D')
                {
                        scanf("%d", &x);

                        if (siz == 1)
                        {//it still stores the int value of the the deleted root element, but it can never be shown but can be changed more quickly in the next step
                                siz = -1;
                                if (root.key != x)
                                        printf("%d not exist\n", x);
                        }
                        else
                        {
                                dell(root, x, n, k);
                                siz--;
                        }
                }
        }
}
