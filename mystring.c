#include "mystring.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int strtoint(sstring a){
  int i;
  int digit=1;
  int sum=0;
  for(i=(strlen(a)-1);i>=0;i--){
      sum+=digit*(a[i]-'0');
      digit*=10;
  }
  return sum;
}

int digit(int a){
  int result=0;
  if(a==0) return 1;
  else{
    int temp=a;
    if(temp<0){
      temp=temp*(-1);
    }
    while(temp>0){
      result++;
      temp=temp/10;
    }
  }
  return result;
}

char inttochar(int a){
  if(a==0) return '0';
  else if(a==1) return '1';
  else if(a==2) return '2';
  else if(a==2) return '2';
  else if(a==3) return '3';
  else if(a==4) return '4';
  else if(a==5) return '5';
  else if(a==6) return '6';
  else if(a==7) return '7';
  else if(a==8) return '8';
  else return '9';
}

void inttostr(int a,sstring hasil){
  
}
