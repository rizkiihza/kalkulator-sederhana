#include <stdio.h>
#include <math.h>
#include <string.h>
#include "stackt.h"
#include "boolean.h"
#include <stdbool.h>
#include <stdlib.h>

#define forr(i,a,b) for((i)=(a);(i)<=(b);i++)


typedef unsigned long ul;
typedef long long ull;
typedef char sstring[50];

sstring in;
sstring outp;


boolean is_number(char c){
  if((int)c-(int)'0'>=0 && (int)c-(int)'0'<=9)
    return true;
  else return false;
}



boolean is_operator(char c){
  if(c=='*' || c=='/' || c=='+' || c=='-' )
    return true;
  else
    return false;
}



int is_priority(char op1,char op2){
  if((op1=='*' || op1=='/') && (op2=='+' || op2=='-'))
    return 1;
  else if((op2=='*' || op2=='/') && (op1=='+' || op1=='-'))
    return -1;
  else if((op2=='+' || op2=='-') && (op1=='+' || op1=='-'))
    return 0;
  else if ((op2=='/' || op2=='*') && (op1=='/' || op1=='*')) {
    return 0;
  }
  else
    return -9999;
}



void to_post(sstring inp){
  Stack op; CreateEmpty(&op);
  outp[0]='\0';
  //Stack result;CreateEmpty(&result);
  int i=0;

  while(i<strlen(inp)){

    if(is_number(inp[i])){
      while(is_number(inp[i]) || inp[i]=='.'){
        char c[]={inp[i],'\0'};
        strcat(outp,c);
        i++;
      }
      strcat(outp,"|");
    }
      //Push(&result,inp[i]);

    if(is_operator(inp[i])){

      if(IsEmpty(op)==true || InfoTop(op)=='(')
        Push(&op,inp[i]);

      else{
        int prio=is_priority(inp[i],InfoTop(op));

        if(prio==1){
            Push(&op,inp[i]);
        }

        else if(prio==0){
          char c[]={InfoTop(op),'|','\0'};
          strcat(outp,c);
          char x;
          Pop(&op,&x);
          Push(&op,inp[i]);
        }

        else if(prio==-1){
          while(IsEmpty(op)==false && InfoTop(op)!='(' && is_priority(inp[i],InfoTop(op))==-1){
              // if(is_priority(inp[i],InfoTop(op))==-1){
                char c[]={InfoTop(op),'|','\0'};
                strcat(outp,c);
                char x;
                Pop(&op,&x);
          }
          if(IsEmpty(op)==false && InfoTop(op)!='(' &&  is_priority(inp[i],InfoTop(op)==0)){
              char c[]={InfoTop(op),'|','\0'};
              strcat(outp,c);
              char x;
              Pop(&op,&x);
          }


          Push(&op,inp[i]);
        }
      }
      i++;
    }
    else{
      if(inp[i]=='('){
        if(inp[i+1]=='-'){
          char c[]={'-','\0'};
          strcat(outp,c);
          Push(&op,'(');
          i++;
          i++;
        }
        else{
          Push(&op,'(');
          i++;
        }
      }
      if(inp[i]==')'){
        while(InfoTop(op)!='('){
          char c[]={InfoTop(op),'|','\0'};
          strcat(outp,c);

          // Push(&result,InfoTop(op));
          char x;
          Pop(&op,&x);
        }
        char x;
        Pop(&op,&x);
        i++;
      }
    }
    //
    //
    // int i;
    // forr(i,0,Top(op))
    //   printf("%c ",op.T[i]);
    // printf("\n%s\n",outp);
  }

  while(IsEmpty(op)==false){
    char c[]={InfoTop(op),'|','\0'};
    strcat(outp,c);
    //Push(&result,InfoTop(op));
    char x;
    Pop(&op,&x);
  }

  //return result;
}




float post_to_value(sstring inp){
  double tumpuk[1000];int topp=0;


  int idx=0;
  while(idx<strlen(inp)){

    if(inp[idx]=='-' && is_number(inp[idx+1])){
      idx++;
      float sum=0;
      while(inp[idx]!='|' && inp[idx]!='.'){
        sum=sum*10+((int)inp[idx]-(int)'0');
        idx++;
      }

      if(inp[idx]=='.'){
        idx++;
        float ten=0.1;
        while(inp[idx]!='|'){
          sum+=ten*((int)inp[idx]-(int)'0');
          ten*=0.1;
          idx++;
        }
      }

      topp++;
      tumpuk[topp]=(-1)*sum;
      idx++;
    }

    else if(is_number(inp[idx])){
      float sum=0;
      while(inp[idx]!='|' && inp[idx]!='.'){
        sum=sum*10+((int)inp[idx]-(int)'0');
        idx++;
      }

      if(inp[idx]=='.'){
        idx++;
        float ten=0.1;
        while(inp[idx]!='|'){
          sum+=ten*((int)inp[idx]-(int)'0');
          ten*=0.1;
          idx++;
        }
      }

      topp++;
      tumpuk[topp]=sum;
      idx++;
    }

    else if(is_operator(inp[idx])){
      float n1,n2;
      float result;

      n1=tumpuk[topp];topp--;
      n2=tumpuk[topp];topp--;
      // printf("\n %f %f\n",n1,n2);
      if(inp[idx]=='+')
        result=n1+n2;
      if(inp[idx]=='-')
        result=n2-n1;
      if(inp[idx]=='*')
        result=n1*n2;
      if(inp[idx]=='/')
        result=n2/n1;
      topp++;
      tumpuk[topp]=result;
      idx++;idx++;
    }
  }
  return tumpuk[topp];
}



int i; //iterator

//input symbol
char o[4] = {'+','-','*','/'}; //operator
char l = '('; //kurung buka
char r = ')'; //kurung tutup
char n[9] = {'1','2','3','4','5','6','7','8','9'}; //angka selain 0
char d = '.'; //koma
char m = '-'; //tanda minus
char z = '0'; //angka 0

bool validation(char state,int left,int right)
{
    bool result=false;
    bool is_float=false;
    bool contains_operator=false;
    int dot_index=-1;
    int operator_index=right+1;
    int parentheses_index=right+1;
    int inside=0; //0 = outside parentheses, >0 = inside parentheses
    int max_depth=0; //maximum parentheses depth

    //transition rules

    switch(state)
    {
        case 'A' :
            if(!result) result = result || validation('Z',left,right);
            if(!result) result = result || validation('N',left,right);
            if(!result) result = result || (validation('N',left,left) && validation('A',left+1,right));
            if(!result) result = result || (validation('N',left,left) && validation('Z',left+1,left+1) && validation('A',left+2,right));
            break;

        case 'B' :
            if(!result) result = result || validation('Z',left,right);
            if(!result) result = result || validation('N',left,right);
            if(!result) result = result || (validation('Z',left,left) && validation('B',left+1,right));
            if(!result) result = result || (validation('N',left,left) && validation('B',left+1,right));
            break;

        case 'C' :
            for(i=left;i<=right;i++) //check if the number is float or integer
            {
                if(in[i]==d)
                {
                    is_float=true;
                    dot_index=i;
                    break;
                }
            }

            if(is_float)
            {
                if(!result) result = result || (validation('A',left,dot_index-1) && validation('B',dot_index+1,right));
                if(!result) result = result || (validation('M',left,left) && validation('A',left+1,dot_index-1) && validation('B',dot_index+1,right));
            }
            else
            {
                if(!result) result = result || validation('A',left,right);
                if(!result) result = result || (validation('M',left,left) && validation('A',left+1,right));
            }

            break;

        case 'E' :
            if(left==right+1) result = true; //epsilon
            else
            {
                for(i=left+1;i<=right;i++) //skip first operator, look for second operator
                {
                    if(in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/')
                    {
                         operator_index=i;
                         break;
                    }
                }

                if(!result) result = result || (validation('O',left,left) && validation('C',left+1,operator_index-1) && validation('E',operator_index,right));
            }

            break;

        case 'G' :
            for(i=left+1;i<=right;i++) //look for first operator
            {
                if(in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/')
                {
                     operator_index=i;
                     break;
                }
            }

            result = result || (validation('C',left,operator_index-1) && validation('E',operator_index,right));

            break;

        case 'H' :
            for(i=left+1;i<=right;i++) //ignore first character
            {
                if(in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/') //look for first operator
                {
                     operator_index=i;
                     break;
                }
            }

            for(i=left+1;i<=right;i++) //ignore first character
            {
                if(in[i]=='(') //look for second '('
                {
                     parentheses_index=i;
                     break;
                }
            }

            if(!result) result = result || (validation('L',left,left) && validation('G',left+1,right-1) && validation('R',right,right));

            break;

        case 'I' :
            if(left==right+1) result = true; //epsilon
            else
            {
                for(i=left+1;i<=right;i++) //ignore first character
                {
                    if(in[i]==')') //look for first ')'
                    {
                        parentheses_index=i;
                        break;
                    }
                }

                if(!result) result = result || (validation('O',left,left) && validation('H',left+1,parentheses_index) && validation('I',parentheses_index+1,right));
            }

            break;

        case 'J' :
            for(i=left+1;i<=right;i++) //ignore first character
            {
                if(in[i]==')') //look for first ')'
                {
                    parentheses_index=i;
                    break;
                }
            }

            result = result || (validation('H',left,parentheses_index) && validation('I',parentheses_index+1,right));

            break;

        case 'L' :
            if(left==right && in[left]=='(') result = true;
            break;

        case 'M' :
            if(left==right && in[left]=='-') result = true;
            break;

        case 'N' :
            if(left==right)
            {
                for(i=0;i<9;i++)
                {
                    if(!result) result = result || (in[left]==n[i]);
                    else break;
                }
            }

            break;

        case 'O' :
            if(left==right)
            {
                for(i=0;i<4;i++)
                {
                    if(!result) result = result || (in[left]==o[i]);
                    else break;
                }
            }

            break;

        case 'R' :
            if(left==right && in[left]==')') result = true;
            break;

        case 'S' :
            for(i=left;i<=right;i++)
            {
                if(in[i]=='(') max_depth++;
            }

            while(max_depth--)
            {
                for(i=left;i<=right;i++)
                {
                    if(in[i]=='(') inside++;
                    else if(in[i]==')') inside--;
                    else
                    {
                        //look for first operator outside parentheses depth = 1, if not found, outside parentheses depth = 2, ...
                        if((in[i]=='+' || in[i]=='-' || in[i]=='*' || in[i]=='/') && (inside==0))
                        {
                            if((in[i-1]>='0' && in[i-1]<='9') || (in[i-1]==')'))
                            {
                                contains_operator=true;
                                operator_index=i;
                                break;
                            }
                        }
                    }
                }

                if(contains_operator) break;
                else
                {
                    left++;
                    right--;
                }
            }

            if(contains_operator)
            {
                result = result || (validation('S',left,operator_index-1) && validation('O',operator_index,operator_index) && validation('S',operator_index+1,right));
            }
            else
            {
                if(!result) result = result || validation('G',left,right);
                if(!result) result = result || validation('J',left,right);
            }

            break;

        case 'Z' :
            if(left==right && in[left]=='0') result = true;
            break;
    }

    return result;
}



int main(){
  system("clear");
  printf("Masukkan ekspresi matematika : ");
  scanf("%s",in);



  if(validation('S',0,strlen(in)-1)){
    printf("Ekspresi matematika yang Anda masukkan bernilai: ");
    to_post(in);
    // printf("%s\n",outp);
    printf("%f\n",post_to_value(outp));
  }
  else printf("syntax error\n");
}
