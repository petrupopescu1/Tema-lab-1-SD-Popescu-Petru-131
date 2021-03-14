#include <iostream>
#include <fstream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <cstring>
#include <algorithm>

using namespace std;

ifstream in("intrare.in");
ofstream out("iesire.out");


unsigned long long llrand() //preluata de pe internet
{
    unsigned long long r = 0;
    for (int i = 0; i < 5; ++i)
    {
        r = (r << 15) | (rand() & 0x7FFF);
    }
    return r & 0xFFFFFFFFFFFFFFFFULL;
}

#pragma region Sortari

void interclasare(int v[], int a[], int st, int dr)
{
    int m =(st+dr)/2;
    int i = st, j = m+1, k = st;
    while(i<=m && j<=dr)
    {
        if(v[i]<=v[j])
        {
            a[k++] = v[i++];
        }
        else
        {
            a[k++] = v[j++];
        }
    }
    while(i<=m)
    {
        a[k++] = v[i++];
    }
    while(j<=dr)
    {
        a[k++] = v[j++];
    }
    for(i=st;i<=dr;i++)
    {
        v[i] = a[i];
    }
}

void mergesort(int v[], int a[], int st, int dr)
{
    /*if(dr-st <= 2)
    {
        if(v[st]>v[dr])
        {
            swap(v[st],v[dr]);
        }
        return;
    }*/
    if(dr == st)
    {
        return;
    }
    int m = (st+dr)/2;
    mergesort(v,a,st,m);
    mergesort(v,a,m+1,dr);
    interclasare(v,a,st,dr);
}


void insertsort(int v[], int n)
{
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            if(v[i]>v[j])
            {
                swap(v[i],v[j]);
            }
        }
    }
}

void countsort(int v[], int n, int maxn)
{
    int i;
    int *f= new int[maxn+2];
    for(i = 0; i<=maxn; i++)
    {
        f[i] = 0;
    }
    for(i=1;i<=n;i++)
    {
        f[v[i]]++;
    }
    int j = 1;
    for(i=0;i<=maxn;i++)
    {
        while(f[i] > 0)
        {
            v[j++] = i;
            f[i]--;
        }
    }
    delete[] f;
    //f = nullptr;
}

int partitie(int v[], int st, int dr)
{
    srand (time(NULL));
    int m = rand() % (dr-st) + st;
    swap(v[m],v[dr]);
    int i = st-1, j = st, pivot = v[dr];
    for(;j<=dr-1;j++)
    {
        if(v[j]<= pivot)
        {
            swap(v[++i], v[j]);
        }
    }
    swap(v[i+1],v[dr]);
    return i+1;
}

void quicksort(int v[], int st, int dr)
{
    if(st>=dr)
    {
        return;
    }
    int m = partitie(v,st,dr);
    quicksort(v,st,m-1);
    quicksort(v,m+1,dr);
}

int partitiestring(string v[], int st, int dr)
{
    srand (time(NULL));
    int m = rand() % (dr-st) + st;
    swap(v[m],v[dr]);
    int i = st-1, j = st;
    string pivot = v[dr];
    for(;j<=dr-1;j++)
    {
        if(v[j]<= pivot)
        {
            swap(v[++i], v[j]);
        }
    }
    swap(v[i+1],v[dr]);
    return i+1;
}

void quicksortstring(string v[], int st, int dr)
{
    if(st>=dr)
    {
        return;
    }
    int m = partitiestring(v,st,dr);
    quicksortstring(v,st,m-1);
    quicksortstring(v,m+1,dr);
}

int partitiedouble(double v[], int st, int dr)
{
    srand (time(NULL));
    int m = rand() % (dr-st) + st;
    swap(v[m],v[dr]);
    int i = st-1, j = st;
    double pivot = v[dr];
    for(;j<=dr-1;j++)
    {
        if(v[j]<= pivot)
        {
            swap(v[++i], v[j]);
        }
    }
    swap(v[i+1],v[dr]);
    return i+1;
}

void quicksortdouble(double v[], int st, int dr)
{
    if(st>=dr)
    {
        return;
    }
    int m = partitiedouble(v,st,dr);
    quicksortdouble(v,st,m-1);
    quicksortdouble(v,m+1,dr);
}


int puteremaxima2(int maxn)
{
    int p = 1, i = 0;
    while(p<=maxn)
    {
        p <<= 1;
        i++;
    }
    return i;
}

int auxradix(int v[], int st, int dr, int maxb)
{
    int masca = 1<<maxb;
    int m = st-1;
    int i;
    for (i = st; i <= dr; i++)
    {
        if ((masca & v[i]) == 0)
        {
            swap(v[i], v[++m]);
        }
    }
    return m+1;
}

void radixsortmsdbinar(int v[],int st, int dr, int maxb)
{
    if(st >= dr || maxb < 0)
    {
        return;
    }
    int m = auxradix(v,st,dr,maxb);
    radixsortmsdbinar(v,st,m-1,maxb-1);
    radixsortmsdbinar(v,m,dr,maxb-1);
}

#pragma endregion

bool verifsortare(int v[], int n)
{
    for(int i = 1; i< n; i++)
    {
        if(v[i]>v[i+1])
        {
            return false;
        }
    }
    return true;
}

bool verifsortarestring(string v[], int n)
{
    for(int i = 1; i< n; i++)
    {
        if(v[i]>v[i+1])
        {
            return false;
        }
    }
    return true;
}

bool verifsortaredouble(double v[], int n)
{
    for(int i = 1; i< n; i++)
    {
        if(v[i]>v[i+1])
        {
            return false;
        }
    }
    return true;
}

void generaretest(int v[], int n, int nmax, int tip)
{
    int i;
    int x = llrand() % nmax;
    switch(tip)
    {
        case 1:
            for(i =1; i<=n; i++)
            {
                v[i] =  llrand() % (nmax + 1);
            }
            break;
        case 2:
            for(i = 1; i<= n; i++)
            {
                v[i] = i;
            }
            break;
        case 3:
            for(i = 1; i<= n; i++)
            {
                v[i] = n-i+1;
            }
        case 4:
            for(i = 1; i<= n; i++)
            {
                v[i] = x;
            }
            break;
        default:
            for(i = 1; i<= n; i++)
            {
                in>>v[i];
            }
    }
}

void sortare(int v[], int n, int nmax, int tip, int test)
{
    string tipSortare[]={"", "quick sort", "count sort", "radix sort","merge sort", "STL sort", "insert sort"};
    double t;
    int *a = new int[n+1];
    bool ok = true;
    switch(tip)
    {
        case 1:
            t=clock();
            if(test != 4)
            {
                quicksort(v, 1, n);
            }
            else
            {
                ok = false;
                out<<"Quick sort nu este optim\n";
            }
            t = clock()-t;
            break;
        case 4:
            t=clock();
            mergesort(v,a,1,n);
            t = clock()-t;
            break;
        case 2:
            t=clock();
            if(nmax<1000000000)
            {
                countsort(v,n,nmax);
            }
            else
            {
                ok = false;
                out<<"Count sort nu este optim\n";
            }
            t = clock()-t;
            break;
        case 3:
            t=clock();
            radixsortmsdbinar(v,1,n,puteremaxima2(nmax));
            t = clock()-t;
            break;
        case 5:
            t = clock();
            sort(v+1, v+n+1);
            t = clock()-t;
            break;
        default:
            t=clock();
            if(n<=100000)
            {
                insertsort(v,n);
            }
            else
            {
                ok = false;
                out<<"Insert sort nu este optim\n";
            }
            t = clock()-t;
            break;
    }
    delete[] a;
    //a = nullptr;
    t/=CLOCKS_PER_SEC;
    if(verifsortare(v,n) && ok)
    {
        out<<"Sortarea "<<tipSortare[tip]<< " a functionat OK in "<<t<<" sec\n";
    }
    else if(ok)
    {
        out<<"Sortarea "<<tipSortare[tip]<< " nu a functionat OK in "<<t<<" sec\n";
    }
}

void copierev(int a[], int b[], int n)
{
    for(int i = 1; i<= n; i++)
    {
        a[i] = b[i];
    }
}

void rezolvare()
{
    int nrt;
    in>>nrt;
    int c = 1;
    while(nrt > 0) {
        out<<"Testul numarul "<<c<<":\n";
        int tipTest, n, nmax, tipdate;
        in>>tipdate;
        if(tipdate == 2)
        {
            in>>n;
            string *s = new string [n+1];
            int i;
            double t;
            for(i =1;i<=n;i++)
            {
                in>>s[i];
            }
            t = clock();
            quicksortstring(s,1,n);
            t = clock() - t;
            t/=CLOCKS_PER_SEC;
            if(verifsortarestring(s,n) )
            {
                out<<"Sortarea quick sort string a functionat OK in "<<t<<" sec\n";
            }
            else
            {
                out<<"Sortarea quick sort string nu a functionat OK in "<<t<<" sec\n";
            }
            delete[] s;
        }
        if(tipdate == 3)
        {
            in>>n;
            double *d = new double [n+1];
            int i;
            double t;
            for(i =1;i<=n;i++)
            {
                in>>d[i];
            }
            t = clock();
            quicksortdouble(d,1,n);
            t = clock() - t;
            t/=CLOCKS_PER_SEC;
            if(verifsortaredouble(d,n) )
            {
                out<<"Sortarea quick sort double a functionat OK in "<<t<<" sec\n";
            }
            else
            {
                out<<"Sortarea quick sort string nu a functionat OK in "<<t<<" sec\n";
            }
            delete[] d;
        }
        else if(tipdate == 1)
        {
            in >> n;
            int *v, *aux;
            v = new int[n + 1];
            aux = new int[n + 1];
            in >> nmax >> tipTest;
            generaretest(v, n, nmax, tipTest);
            for (int i = 1; i <= 6; i++) {
                copierev(aux, v, n);
                sortare(aux, n, nmax, i, tipTest);
                /*for (int j = 1; j <= n; j++)
                {
                    out << aux[j] << " ";
                }
                out << "\n";*/
            }
            delete[] v;
            //v = nullptr;
            delete[] aux;
            //aux = nullptr;
        }
        out<<"\n";
        c++;
        nrt--;
    }
}

int main() {
    rezolvare();
    return 0;
}

