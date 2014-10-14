#include <stdio.h>

#define size 10

#define D(X) printf("%s:%d\n",#X,X)
#define D2(X,Y) printf("%s:%d->%d\n",#X,X,Y)
int arr[size] = {1,4,2,5,16,2,5,9,0,11};
void print()
{
  int i=0;
  for(i=0;i<size;i++)
    printf(" %d",arr[i]);
  printf("\n");
}

void quick_sort (int start, int end)
{
  if( end-start < 1 )
    return;
  else
  {
  int n = end - start;
  int pivot = start + n/2;
  int s  = start;
  int e = end;
  int p = arr[pivot];

  D2(pivot,arr[pivot]);
  while (s <= e)
  {
    D2(s,arr[s]);D2(e,arr[e]);
    if ( arr[s] <p )
      s++;
    else if ( arr[e] >p )
      e--;
    else
    {
      int t = arr[s];
      arr[s] = arr[e];
      arr[e] = t;
      s++;
      e--;
    }
  }
  D(s);D(e);
  print();
   quick_sort(start, e);
   quick_sort(s, end);
  }
}

int main()
{
  quick_sort(0,9);
  return 0;
}


