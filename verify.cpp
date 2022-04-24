#include "boolean_fun.h"
#include "affine_trans.h"
#include <set>
#include<vector>
#include <iostream>  // I/O 
#include <fstream>   // file I/O
#include <sstream>
#include <iomanip>   // format manipulation
#include <string>
#include <iterator>
using namespace std;

//determine the nl3 of fn10||fn3+g3 whether can achieve 21
// g3 is in H_3,6

//read truth table and construct BooleanFun f
void read_boolean_fun( string line, BooleanFun *f)
{
    stringstream stringin(line);
    for (int i = 0; i < (1<<6); i ++) {
      int y = 0, x = i;
    for (int j = 0; j < 6; j ++) {
      y = y*2 + x % 2;
      x = x / 2;
    }

    int v;
    stringin >> v;
    f->set_truth_table(y, v);
    }
  f->set_truth_table_done();
}
//s1,s2 are as a 01 string of length 2^n
string string_xor(string s1, string s2) {
  string result = "";
  for (int i = 0; i < (1<<6); i ++) {
    if ((s1[i] == '0' && s2[i] == '1') ||(s1[i] == '1' && s2[i] == '0'))
      result += "1";
    else
      result += "0";
  }
return result;
}

int main() {

ifstream fin;
ifstream fin1;
ifstream fin2;
string line;
string line1;
string line2;
string line3;
set<string> fn3_14;
set<string>  fn3_12_14;
set<string>  fn10_7;
set<string>  fn10_9;

int num=0;
fin.open( "f10_7.txt", ios::in);  
 if(fin.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin.eof())
{   
  string anf10_7;
  BooleanFun *f1 = new BooleanFun(6);
  getline(fin,line);
  stringstream stringin(line);
   //transform truth table to coefficient_anf
  read_boolean_fun(line,f1);
  anf10_7=f1-> get_coe_list();
  //store coefficient ANF of F_fn10(7)
  fn10_7.insert(anf10_7); 
 // num++; 
 // cout<<f1->get_anf()<<endl;
}
fin.close();
//cout<<num<<endl;

num=0;
fin1.open( "fn3_14.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  string anf_fn3_14;
  BooleanFun *f2 = new BooleanFun(6);
  getline(fin1,line1);
  stringstream stringin(line1);
  //transform truth table to coefficient_anf
  read_boolean_fun(line1,f2);
  anf_fn3_14=f2->get_coe_list();
  //store coefficient ANF of F_fn3(14)
   fn3_14.insert(anf_fn3_14);   
 //   cout<<f2->get_anf()<<endl;
 //  num++; 
} 
fin1.close();
//cout<<num<<endl;

int num1=0;
fin2.open( "f3_12_14.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin2.eof())
{ 
  string anf_fn3_12_14;
  BooleanFun *f3 = new BooleanFun(6);
  getline(fin2,line3);
  stringstream stringin(line3);
  //transform truth table to coefficient_anf
  read_boolean_fun(line3,f3);
  anf_fn3_12_14=f3->get_coe_list();
  //store coefficient ANF of F_fn3(12)\cap F_fn3(14) 
   fn3_12_14.insert(anf_fn3_12_14); 
 //  num1++;   
//   cout<<f3->get_anf()<<endl;
} 
fin2.close();
//cout<<"num1 is "<<num1<<endl;

 num1=0;
fin2.open( "f10_9.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin2.eof())
{ 
  string anf_fn10_9;
  BooleanFun *f4 = new BooleanFun(6);
  getline(fin2,line2);
  stringstream stringin(line2);
  //transform truth table to coefficient_anf
  read_boolean_fun(line2,f4);
  anf_fn10_9=f4->get_coe_list();
  //store coefficient ANF of F_fn10(9) 
   fn10_9.insert(anf_fn10_9); 
 //  num1++;   
//   cout<<f4->get_anf()<<endl;
} 
fin2.close();
//cout<<"num1 is "<<num1<<endl;
//int count=0;

int flag=0;
int flag1=0;
set<string> G3;

for (set<string>::iterator g=fn3_12_14.begin();g!=fn3_12_14.end();g++) 
{
     int all_in=true;
     BooleanFun g3(6);
     g3.set_coe_list(*g);
     for(set<string>::iterator t=fn10_7.begin();t!=fn10_7.end();t++)
     {
        string result;
       //let h=g+t
        BooleanFun ti(6);
        ti.set_coe_list(*t);
        ti.add(g3);
        result=string_xor(*t,*g); 
        //ti.get_coe_list(); 
        
        //h\in fn3_14?
        if(fn3_14.find(result)==fn3_14.end())
            {
              all_in = false;
              break;
            }       
    } 
    if(all_in)
    {
      flag++;
      G3.insert(*g);
    }    
}
cout<<"In the first step, the number of g is "<<flag<<endl;
    //In the first step, print all possible 6912 homogeneous g in the form of truth table .
/* for(set<string>::iterator term=G3.begin();term!=G3.end();term++)
{
        cout<<*term<<endl;
} */

for (set<string>::iterator g1=G3.begin();g1!=G3.end();g1++) 
{
   int allin=true;
   BooleanFun g_1(6);
  g_1.set_coe_list(*g1);
     for(set<string>::iterator l=fn10_9.begin();l!=fn10_9.end();l++)
     {
        string result1;
       //let h=g1+ l
         BooleanFun li(6);
         li.set_coe_list(*l);
         li.add(g_1);
        result1=string_xor(*g1,*l); 
        //li.get_coe_list();
        //store coefficient_anf of g=s0+ti
        if(fn3_12_14.find(result1)==fn3_12_14.end())
            {
              allin = false;
              break;
            }       
    } 
    if(allin)
    {
      flag1++;
    }    
}
//if flag1==0, then there exists no valid g3.
    if(flag1==0)
    {cout<<"Cannot achieve 21 "<<flag1<<endl;}
  return 0;
}
