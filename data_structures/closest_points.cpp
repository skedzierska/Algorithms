#include <iostream>
#include <math.h>
#include <cfloat>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Punkt
{
    public:
    int x, y;
};
// qsort
// sortowanie dla osi x
int porownajX(const void* a, const void* b)
{
    Punkt *p1 = (Punkt *)a, *p2 = (Punkt *)b;
    return (p1->x - p2->x);
}
//sortowanie dla osi y
int porownajY(const void* a, const void* b)
{
    Punkt *p1 = (Punkt *)a, *p2 = (Punkt *)b;
    return (p1->y - p2->y);
}
//odleglosc mieddzy pkt p1 a p2
float odc(Punkt p1, Punkt p2)
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
// zwracanie najmniejszej odl w tablicy P[] nxn
float bruteForce(Punkt P[], int n)
{
    float min = 9999;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (odc(P[i], P[j]) < min)
                min = odc(P[i], P[j]);
    return min;
}
//najbllizej polozone odcinki na stripie
float stripClosest(Punkt strip[], int size, float d)
{
    float min = d;
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (odc(strip[i],strip[j]) < min)
                min = odc(strip[i], strip[j]);

    return min;
}

float closestUtil(Punkt PX[],Punkt PY[], int n)
{
    if (n <= 3)
        return bruteForce(PX, n);

    int mid = n/2;
    Punkt midPunkt = PX[mid];
    //rozdzielamy pkt na odpowiednie tablice
    Punkt PYl[mid+1];
    Punkt PYr[n-mid-1];
    int li = 0, ri = 0;
    for (int i = 0; i < n; i++)
    {
      if (PY[i].x < midPunkt.x)
         PYl[li++] = PY[i];
      else
         PYr[ri++] = PY[i];
    }

    float dl = closestUtil(PX,PYl, mid);
    float dr = closestUtil(PX + mid,PYr, n - mid - 1);
    float d = min(dl, dr);
    //budownaie tablicy strip gdzie od jest mniejszy od d
    Punkt strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(PY[i].x - midPunkt.x) < d)
            strip[j] = PY[i], j++;

    return min(d, stripClosest(strip, j, d) );
}
//px wszystkie pkt posortowane dla osi x a py wszytskie pkt posortowane dla odi y
float closest(std::vector<Punkt> P, int n)
{

    Punkt PX[n];
    Punkt PY[n];
    for (int i = 0; i < n; i++)
    {
        PX[i] = P[i];
        PY[i] = P[i];
    }
    qsort(PX, n, sizeof(Punkt), porownajX);
    qsort(PY, n, sizeof(Punkt), porownajY);

    return closestUtil(PX,PY, n);
}

int main()
{
	std::vector<Punkt> P;//[] = {{2, 3}, {12, 30}, {40, 50}};
	for(int i=0 ; i<100 ; i++) {
//	    Punkt ppp({rand()/100,rand()/100});
//	    cout << ppp.x << " " << ppp.y << "\n";
        P.push_back({rand()/100,rand()/100});
	}
    int n =P.size();//= sizeof(P) / sizeof(P[0]);
    cout << "najmniejsza odleglosc wynosi " << closest(P, n-1);
    return 0;
}
