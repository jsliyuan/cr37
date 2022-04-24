#define _CRT_SECURE_NO_WARNINGS

#include <limits.h>
#include <stdlib.h>
#include <map>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include<omp.h>
int quard1[1048576][64];//六元三阶
int quard2[1024][32];//五元二阶

int f1[64];
int f2[64];
int f3[64];
int f4[64];
int f5[64];
int f6[64];
int f7[64];
int f8[64];
int f9[64];
int f10[64];
int arry1[64],arry2[64],arry3[64],arry4[64],arry5[64],arry6[64],arry7[64],arry8[64],arry9[64],arry10[64];
void assign(){ //Truth table of fn1:0000000000000001000000000000000100000000000000010000000000000001
    int a5;
    
    for(a5=0;a5<64;a5++)
    {
        if(a5==15||a5==31||a5==47||a5==63)
        {
            f1[a5]=1;
        }
        else
        {
            f1[a5]=0;
        }    
    }
}
void assign1(){ //Truth table of fn2:0000000000000000000000000001000100000001000000010000000100010000
    int a5;

     for(a5=0;a5<64;a5++)
    {
        if(a5==27||a5==31||a5==39||a5==47||a5==55||a5==59)
        {
            f2[a5]=1;
        }
        else
        {
            f2[a5]=0;
        }    
    }
    
}
void assign2(){ //Truth table of fn3:0000000000000000000000000000001100000000000001010001000100010111
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==30||a5==31||a5==45||a5==47||a5==51||a5==55||a5==59||a5==61||a5==62||a5==63)
        {
            f3[a5]=1;
        }
        else
        {
            f3[a5]=0;
        }    
    }
}
void assign3(){ //The truth table of fn4:0000000000000000000000000000000100000000000000000000000000000001
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==31||a5==63)
        {
            f4[a5]=1;
        }
        else
        {
            f4[a5]=0;
        }    
    }
}
void assign4(){ //The truth table of fn5:0000000000000000000000000000000100000001000000010000000100000000
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==31||a5==39||a5==47||a5==55)
        {
            f5[a5]=1;
        }
        else
        {
            f5[a5]=0;
        }    
    }
}
void assign5(){//The truth table of fn6:0000000000000000000000000000000100000000000001010001000100010101
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==31||a5==45||a5==47||a5==51||a5==55||a5==59||a5==61||a5==63)
        {
            f6[a5]=1;
        }
        else
        {
            f6[a5]=0;
        }    
    }
}
void assign6(){ //The truth table of fn7:0000000000000000000000000000000000000000000000000000000000000001
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==63)
        {
            f7[a5]=1;
        }
        else
        {
            f7[a5]=0;
        }    
    }
}
void assign7(){ //The truth table of fn8:0000000000000001000000000000000100000000000000010000000000000000
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==15||a5==31||a5==47)
        {
            f8[a5]=1;
        }
        else
        {
            f8[a5]=0;
        }    
    }
}
void assign8(){ //The truth table of fn9:0000000000000000000000000001000100000001000000010000000100010001
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==27||a5==31||a5==39||a5==47||a5==55||a5==59||a5==63)
        {
            f9[a5]=1;
        }
        else
        {
            f9[a5]=0;
        }    
    }
}
void assign9(){ //The truth table of fn10:0000000000000000000000000000001100000000000001010001000100010110
    int a5;
     for(a5=0;a5<64;a5++)
    {
        if(a5==30||a5==31||a5==45||a5==47||a5==51||a5==55||a5==59||a5==61||a5==62)
        {
            f10[a5]=1;
        }
        else
        {
            f10[a5]=0;
        }    
    }
}

void cal_quard1(){//六元三阶
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

void cal_quard2(){//
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


int nlf2(int* tt) {
 int i, j, k1, _2order_nlf = INT_MAX;
 // need a transform from RSTT to TT

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
void assign1();
void assign2();
void assign3();
void assign4();
void assign5();
void assign6();
void assign7();
void assign8();
void assign9();
int main()
{ 
    cal_quard1();
    cal_quard2();
    assign();
    assign1();
    assign2();
    assign3();
    assign4();
    assign5();
    assign6();
    assign7();
    assign8();
    assign9();
   int m,n,i,j;
   int flag1_4=0,flag1_6=0,flag1_8=0,flag1_10=0,flag1_12=0,flag1_14=0,flag1_16=0;
   int flag2_6=0,flag2_8=0,flag2_10=0,flag2_12=0,flag2_14=0,flag2_16=0;
   int flag3_8=0,flag3_10=0,flag3_12=0,flag3_14=0;
   int flag4_2=0,flag4_4=0,flag4_6=0,flag4_8=0,flag4_10=0,flag4_12=0,flag4_14=0,flag4_16=0;
   int flag5_2=0,flag5_4=0,flag5_6=0,flag5_8=0,flag5_10=0,flag5_12=0,flag5_14=0,flag5_16=0,flag5_18;
   int flag6_6=0,flag6_8=0,flag6_10=0,flag6_12=0,flag6_14=0;
   int flag7_1=0,flag7_3=0,flag7_5=0,flag7_7=0,flag7_9=0,flag7_11=0,flag7_13=0,flag7_15=0,flag7_17=0;
   int flag8_3=0,flag8_5=0,flag8_7=0,flag8_9=0,flag8_11=0,flag8_13=0,flag8_15=0;
   int flag9_5=0,flag9_7=0,flag9_9=0,flag9_11=0,flag9_13=0,flag9_15=0;
   int flag10_7=0,flag10_9=0,flag10_11=0,flag10_13=0,flag10_15=0;
   int t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {  
            if(quard1[m][n]==f1[n])
                arry1[n]=0;
            else
                arry1[n]=1;
        }
        t1=nlf2(arry1);
        if(t1==4)
            flag1_4+=1;
        if(t1==6)
             flag1_6+=1;
        if(t1==8)
             flag1_8+=1;
        if(t1==10)
             flag1_10+=1;
        if(t1==12)
             flag1_12+=1;
        if(t1==14)
             flag1_14+=1;
        if(t1==16)
             flag1_16+=1;
    }
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {                  
            if(quard1[m][n]==f2[n])
                arry2[n]=0;
            else
                arry2[n]=1;
        }
         t2=nlf2(arry2);
         if(t2==6)
             flag2_6+=1;
           if(t2==8)
             flag2_8+=1;
           if(t2==10)
             flag2_10+=1;
            if(t2==12)
             flag2_12+=1;
            if(t2==14)
             flag2_14+=1;
            if(t2==16)
             flag2_16+=1;
    }
    
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {                  
            if(quard1[m][n]==f3[n])
                    arry3[n]=0;
                else
                    arry3[n]=1;
        }
         t3=nlf2(arry3);
        if(t3==8)
             flag3_8+=1;
           if(t3==10)
             flag3_10+=1;
            if(t3==12)
             flag3_12+=1;
            if(t3==14)
             flag3_14+=1;
    }
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {   
            if(quard1[m][n]==f4[n])
                arry4[n]=0;
            else
                arry4[n]=1;
        }
        t4=nlf2(arry4);
        if(t4==2)
            flag4_2+=1;
           if(t4==4)
            flag4_4+=1;
           if(t4==6)
             flag4_6+=1;
           if(t4==8)
             flag4_8+=1;
           if(t4==10)
             flag4_10+=1;
            if(t4==12)
             flag4_12+=1;
            if(t4==14)
             flag4_14+=1;
            if(t4==16)
             flag4_16+=1;
    }
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {   
            if(quard1[m][n]==f5[n])
                arry5[n]=0;
            else
                arry5[n]=1;
        }
         t5=nlf2(arry5);
         if(t5==4)
             flag5_4+=1;
        if(t5==6)
             flag5_6+=1;
           if(t5==8)
             flag5_8+=1;
           if(t5==10)
             flag5_10+=1;
            if(t5==12)
             flag5_12+=1;
            if(t5==14)
             flag5_14+=1;
            if(t2==16)
             flag5_16+=1;
    }
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {   
                if(quard1[m][n]==f6[n])
                    arry6[n]=0;
                else
                    arry6[n]=1;
        }
        t6=nlf2(arry6);
        if(t6==6)
             flag6_6+=1;
           if(t6==8)
             flag6_8+=1;
           if(t6==10)
             flag6_10+=1;
            if(t6==12)
             flag6_12+=1;
            if(t6==14)
             flag6_14+=1;
    }
     for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {   
                if(quard1[m][n]==f7[n])
                    arry7[n]=0;
                else
                    arry7[n]=1;
        }
          t7=nlf2(arry7);
           if(t7==1)
             flag7_1+=1;
           if(t7==3)
             flag7_3+=1;
           if(t7==5)
             flag7_5+=1;
            if(t7==7)
             flag7_7+=1;
            if(t7==9)
             flag7_9+=1;
            if(t7==11)
             flag7_11+=1;
            if(t7==13)
             flag7_13+=1;
            if(t7==15)
             flag7_15+=1;
             if(t7==17)
             flag7_17+=1;
    }
     for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {  
                if(quard1[m][n]==f8[n])
                    arry8[n]=0;
                else
                    arry8[n]=1;
        }
         t8=nlf2(arry8);
        if(t8==3)
             flag8_3+=1;
           if(t8==5)
             flag8_5+=1;
            if(t8==7)
             flag8_7+=1;
            if(t8==9)
             flag8_9+=1;
            if(t8==11)
             flag8_11+=1;
            if(t8==13)
             flag8_13+=1;
            if(t8==15)
             flag8_15+=1;
    }
     for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {  
                if(quard1[m][n]==f9[n])
                    arry9[n]=0;
                else
                    arry9[n]=1;
        }
         t9=nlf2(arry9);
          if(t9==5)
             flag9_5+=1;
            if(t9==7)
             flag9_7+=1;
            if(t9==9)
             flag9_9+=1;
            if(t9==11)
             flag9_11+=1;
            if(t9==13)
             flag9_13+=1;
            if(t9==15)
             flag9_15+=1;
    }
    for(m=0;m<1048576;m++)
    {
        for(n=0;n<64;n++)
        {  
                if(quard1[m][n]==f10[n])
                    arry10[n]=0;
                else
                    arry10[n]=1;
        }
           t10=nlf2(arry10);
            if(t10==7)
             flag10_7+=1;
            if(t10==9)
             flag10_9+=1;
            if(t10==11)
             flag10_11+=1;
            if(t10==13)
             flag10_13+=1;
            if(t10==15)
             flag10_15+=1;
    }    
     printf("\n |Ffn1(r)| r=4: %d; r=6: %d; r=8: %d; r=10: %d; r=12: %d; r=14: %d; r=16: %d. \n",flag1_4,flag1_6,flag1_8,flag1_10,flag1_12,flag1_14,flag1_16);
     printf("\n |Ffn2(r)| r=6: %d; r=8: %d, r=10:%d; r=12: %d; r=14: %d; r=16: %d. \n",flag2_6,flag2_8,flag2_10,flag2_12,flag2_14,flag2_16);
     printf("\n |Ffn3(r)| r=8: %d; r=10:%d; r=12:%d; r=14: %d. \n",flag3_8,flag3_10,flag3_12,flag3_14);
     printf("\n |Ffn4(r)| r=2: %d; r=4: %d; r=6: %d; r=8:  %d; r=10: %d; r=12: %d; r=14: %d; r=16: %d. \n",flag4_2,flag4_4,flag4_6,flag4_8,flag4_10,flag4_12,flag4_14,flag4_16);
     printf("\n |Ffn5(r)| r=4: %d; r=6: %d; r=8: %d; r=10: %d; r=12: %d; r=14: %d. \n",flag5_4,flag5_6,flag5_8,flag5_10,flag5_12,flag5_14);
     printf("\n |Ffn6(r)| r=6: %d; r=8: %d; r=10:%d; r=12: %d; r=14: %d. \n",flag6_6,flag6_8,flag6_10,flag6_12,flag6_14);
     printf("\n |Ffn7(r)| r=1: %d; r=3: %d; r=5: %d; r=7:  %d; r=9:  %d; r=11: %d; r=13: %d; r=15: %d; r=17: %d. \n",flag7_1,flag7_3,flag7_5,flag7_7,flag7_9,flag7_11,flag7_13,flag7_15,flag7_17);
     printf("\n |Ffn8(r)| r=3: %d; r=5: %d; r=7: %d; r=9:  %d; r=11: %d; r=13: %d; r=15: %d. \n",flag8_3,flag8_5,flag8_7,flag8_9,flag8_11,flag8_13,flag8_15);
     printf("\n |Ffn9(r)| r=5: %d; r=7: %d; r=9: %d; r=11: %d; r=13: %d; r=15: %d. \n",flag9_5,flag9_7,flag9_9,flag9_11,flag9_13,flag9_15);
     printf("\n |Ffn10(r)|r=7: %d; r=9: %d; r=11:%d; r=13: %d; r=15: %d. \n",flag10_7,flag10_9,flag10_11,flag10_13,flag10_15);
    printf("\n The program has ended. \n");
    system("pause");
    return 0;
}
