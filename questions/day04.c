#include <stdio.h>

int main(void) {

  for (int i = 100; i > 0; i -= 20) printf("%d ", i);
  //  printf("%d\n", i);  // compiler error
  

int num	= 6;

// generates warning about use of assignment w/o parentheses
if ( num = 24 / 3 && 'c' > 'D' || ++num)
   printf("first");
else
   printf("second");
 printf("\n %d ", num);
  
  return 0;
}
