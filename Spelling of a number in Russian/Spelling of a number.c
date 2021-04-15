#include <stdio.h>
#include <locale.h>

int main(){
   setlocale(LC_ALL, "Russian");
   char *first_dig[] = {"ноль","один", "два", "три","четыре","пять","шесть","семь","восемь","девять"};
   char *second_dig[] = {"десять", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят",
    "восемьдесят", "девяносто"};
   char *third_dig[] = {"сто","двести","триста","четыреста","пятьсот","шестьсот","семьсот","восемьсот","девятьсот"};
   int n;
   scanf("%d", &n);
   if (n < 10){
       printf("%s \n", first_dig[n]);
   }
   else if (n < 100){
       printf("%s %s\n",second_dig[(n / 10) - 1],first_dig[n % 10]);
   }
   else{
       printf("%s %s %s\n",third_dig[(n / 100) - 1], second_dig[((n / 10) % 10) - 1],first_dig[n % 10]);
   }
   return 0;
}