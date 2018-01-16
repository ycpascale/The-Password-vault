#include <stdio.h>
#include <string.h>
#include <stdio.h>

#define SIZE1 100
#define SIZE2 1000

int myHashFunction(size_t tableSize, char* key)
{
   char tempStr[8];
   int i = 0;
   int sum = 0;

   strncpy(tempStr, key, 4);

   for (i= 0; i < 4; i++)
   {
       sum = sum + tempStr[i];
   }

   return (sum % (int)tableSize);
}

int main()
{
   int num1[10];
   int num2[10];
   int i = 0;

   num1[0] = myHashFunction(SIZE1, "Heya");
   num1[1] = myHashFunction(SIZE1, "ThisIS");
   num1[2] = myHashFunction(SIZE1, "Helloooo");
   num1[3] = myHashFunction(SIZE1, "Lovesleeep");
   num1[4] = myHashFunction(SIZE1, "AssignmentThree");
   num1[5] = myHashFunction(SIZE1, "nopebshd");
   num1[6] = myHashFunction(SIZE1, "dscscbshcbhjs");
   num1[7] = myHashFunction(SIZE1, "thisis");
   num1[8] = myHashFunction(SIZE1, "AAAA");

   num2[0] = myHashFunction(SIZE2, "Heya");
   num2[1] = myHashFunction(SIZE2, "ThisIS");
   num2[2] = myHashFunction(SIZE2, "Helloooo");
   num2[3] = myHashFunction(SIZE2, "Lovesleeep");
   num2[4] = myHashFunction(SIZE2, "AssignmentThree");
   num2[5] = myHashFunction(SIZE2, "nopebshd");
   num2[6] = myHashFunction(SIZE2, "dscscbshcbhjs");
   num2[7] = myHashFunction(SIZE2, "thisis");
   num2[8] = myHashFunction(SIZE1, "AAAA");

   printf("Data set from table of size 100\n");
   for (i= 0; i < 9; i++)
   {
      printf("%d ", num1[i]);
   }

   printf("\n\nData set from table of size 1000\n");
   for (i=0; i < 8; i++)
   {
      printf("%d ", num2[i]);
   }

   return 0;

}
