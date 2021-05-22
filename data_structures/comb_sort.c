#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int nextgap(int gap)
{
    gap = gap/1.3;
    return gap;
}

void combsort(int a[], int n)
{
    int gap = n;
    int i;
    int swapped = 1;

    while (gap > 1 || swapped)
    {
        swapped = 0;
        gap = nextgap(gap);
        for (i=0 ; i< n-gap;i++)
            {
        if(a[i]>a[i+gap])
            {
                 int buf;
                buf = a[i];
                a[i]= a[i+gap];
                a[i+gap]= buf;
                swapped = 1;
            }
        else if(a[i+gap]>(a[i]))
        {
            continue;
        }
            }

    }

}

int main()
{

    srand(time(NULL));
    int i;
    int n = 100;
    int a[n];
    combsort(a,n);
    
    printf("posortowana tablica: \n");
    for (i=0; i<n; i++){
        printf("%d\n", a[i] , rand());
    }

    return 0;


}
