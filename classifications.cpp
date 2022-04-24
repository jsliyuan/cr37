#define _CRT_SECURE_NO_WARNINGS
//F_fn_i(r), where i=2,3,6,9,10
#include <limits.h>
#include <stdlib.h>
#include <map>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include<omp.h>
int quard1[1048576][64];//set of homogenous 6-variable Boolean function of degree 3
int quard2[1024][32];//homogenous 6-variable Boolean function of degree 2

int fn[64];//store the truth table of fn_10
 
  //Store F_（fn_3）（r）   
int select_f3_8[2304][64];   
int select_f3_10[71680][64];;
int select_f3_12[628992][64];
int select_f3_14[345600][64];

//The truth table of fn_3 is 0000000000000000000000000000001100000000000001010001000100010111
void assign(){ 
    int position;
    
    for(position=0;position<64;position++)
    {
        if(position==30||position==31|| position==45||position==47||position==51||position==55||position==59||position==61||position==62||position==63)
        {
            fn[position]=1;
        }
        else
        {
            fn[position]=0;
        }    
    }
}
//generate homogenous 6-variable Boolean functions of degree 3
void cal_quard1(){
    int a,x;
    int bin_a[20];
    int t[]={56,52,50,49,44,42,\
        41,38,37,35,28,\
        26,25,22,21,\
        19,14,13,\
        11,7,\
    };
    for (a=0;a<1048576;++a)
    {
        for(int i=19;i> -1;--i)
            bin_a[19-i]=(a>>i) &0x1;
        for (x=0;x<64;++x)
        {
            //quard[a][x]=0;
            for(int j=0;j<20;++j)
            {
                quard1[a][x]^=(bin_a[j]&((t[j]&x)==t[j]?1:0));
            }
        }
    }
}
//generate homogenous 5-variable Boolean functions of degree 2
void cal_quard2(){
    int a,x;
    int bin_a[10];
    int t[]={24,20,18,17,\
        12,10,9,\
        6,5,\
        3,\
    };
    for (a=0;a<1024;++a)
    {
        for(int i=9;i> -1;--i)
            bin_a[9-i]=(a>>i) &0x1;
        for (x=0;x<32;++x)
        {
            //quard[a][x]=0;
            for(int j=0;j<10;++j)
            {
                quard2[a][x]^=(bin_a[j]&((t[j]&x)==t[j]?1:0));
            }
        }
    }
}
//calculate the first-order nonlinearity of 5-variable Boolean functions
int nlf1(int* tt) {
 int buf[32];
 register int i, j, k;
 for (i = 0; i < 5; ++i) {
  for (j = 0; j < 16; ++j) {
   k = j << 1;
   buf[j] = tt[k] + tt[k + 1];
   buf[j + 16] = tt[k] - tt[k + 1];
  }
  memcpy(tt, buf, 128U);
 }
 int max = 0;
 for (i = 0; i < 32; ++i)if (abs(tt[i]) > max)max = abs(tt[i]);
 return 16 - (max >> 1);
}

//calculate the second-order nonlinearity of 6-variable Boolean functions
int nlf2(int* tt) {
 int i, j, k1, _2order_nlf = INT_MAX;
 // need a transformation from RSTT to TT

 register int nlf_t;
 int _2order[4] = { INT_MAX ,INT_MAX,INT_MAX,INT_MAX };
#pragma omp parallel for num_threads(4) private(i,j,k1,nlf_t)
 for (i = 0; i < 1024; ++i) {
  k1 = 0;
  int t1[32], t2[32];
  for (j = 0; j < 32; ++j) {
   t1[j] = 1 - ((tt[k1] ^ quard2[i][j]) << 1);
   t2[j] = 1 - ((tt[k1 + 1] ^ quard2[i][j]) << 1);
   k1 += 2;
  }
  nlf_t = nlf1(t2) + nlf1(t1);
  int id = omp_get_thread_num();
  if (nlf_t < _2order[id]) {
   _2order[id] = nlf_t;
  }
  if (nlf_t < _2order_nlf)_2order_nlf = nlf_t;
 }
 for (int i = 0; i < 4; ++i)if (_2order[i] < _2order_nlf)_2order_nlf = _2order[i];
 return _2order_nlf;
}

void cal_quard2();
void cal_quard1();
void assign();
int main()
{ 
    cal_quard1();
    cal_quard2();
    assign();
   int m,n,t,arry[64],t1,i,j;
   FILE *w1;
   int flag1=0,flag2=0,flag3=0,flag4=0;

     for(m=0;m<1048576;m++)
    {
           for(n=0;n<64;n++)
            {  
                 if(quard1[m][n]==fn[n])
                {
                    arry[n]=0;
                }
                else
                {
                    arry[n]=1;
                }
            }
           t1=nlf2(arry);
           
           if(t1==8)
          {
              for(n=0;n<64;n++)
            {
                select_f3_8[flag1][n]=quard1[m][n];
            }
             flag1+=1;
          }
           if(t1==10)
          {
              for(n=0;n<64;n++)
            {
                select_f3_10[flag2][n]=quard1[m][n];
            }
             flag2+=1;
          }
           if(t1==12)
          {
              for(n=0;n<64;n++)
            {
                select_f3_12[flag3][n]=quard1[m][n];
            }
             flag3+=1;
          }
          if(t1==14)
          {
              for(n=0;n<64;n++)
            {
                select_f3_14[flag4][n]=quard1[m][n];
            }
             flag4+=1;
          }
    } 
  
    w1=fopen("fn3_12_14.txt","w+");
        
        for(i=0;i<flag3;i++)
        {
            for(j=0;j<64;j++)
            {
                fprintf(w1,"%d",select_f3_12[i][j]);
                if(j!=63)
                    fprintf(w1," ");
            }
            fprintf(w1,"\n");
        }
    fclose(w1);
    w1=fopen("fn3_12_14.txt","a");
        
        for(i=0;i<flag4;i++)
        {
            for(j=0;j<64;j++)
            {
                fprintf(w1,"%d",select_f3_14[i][j]);
                if(j!=63)
                    fprintf(w1," ");
            }
            fprintf(w1,"\n");
        }
    fclose(w1);
 
    printf("the number of r=8 is %d\n",flag1);
    printf("the number of r=10 is %d\n",flag2);
    printf("the number of r=12 is %d\n",flag3);
    printf("the number of r=14 is %d\n",flag4);
    printf("The program has ended.\n");
    system("pause");
    return 0;
}
