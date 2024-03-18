#include "tcoada.h"
#include <stdio.h>

int main()
{
  TCoada* c;
  int x;
  c = InitQ();
  if(!c) return 1;
  IntrQ(c, 10);
  IntrQ(c, 100);
  IntrQ(c, 65);
  IntrQ(c, 1000);
  
  AfisareQ(c);
  ExtrQ(c, &x);
  ExtrQ(c, &x);
  ExtrQ(c, &x);

  AfisareQ(c);
  DistrQ(&c);
}
