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

//determine the nl3 of fn2||fn9+g3 whether can achieve 21
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
set<string> fn2_6;
set<string>  fn9_15;
set<string>  fn2_8;
set<string>  fn9_13_15;

int num=0;
fin.open( "f2_6.txt", ios::in);  
 if(fin.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin.eof())
{   
  string anf2_6;
  BooleanFun *f1 = new BooleanFun(6);
  getline(fin,line);
  stringstream stringin(line);
   //transform truth table to coefficient_anf
  read_boolean_fun(line,f1);
  anf2_6=f1-> get_coe_list();
  //store coefficient ANF of F_fn10(7)
  fn2_6.insert(anf2_6); 
  num++; 
  cout<<f1->get_anf()<<endl;
}
fin.close();
cout<<num<<endl;

num=0;
fin1.open( "f9_15.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  string anf_f9_15;
  BooleanFun *f2 = new BooleanFun(6);
  getline(fin1,line1);
  stringstream stringin(line1);
  //transform truth table to coefficient_anf
  read_boolean_fun(line1,f2);
  anf_f9_15=f2->get_coe_list();
  //store coefficient ANF of F_fn3(14)
   fn9_15.insert(anf_f9_15);   
    cout<<f2->get_anf()<<endl;
   num++; 
} 
fin1.close();
cout<<num<<endl;

int num1=0;
fin2.open( "f2_8.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin2.eof())
{ 
  string anf_fn2_8;
  BooleanFun *f3 = new BooleanFun(6);
  getline(fin2,line3);
  stringstream stringin(line3);
  //transform truth table to coefficient_anf
  read_boolean_fun(line3,f3);
  anf_fn2_8=f3->get_coe_list();
  //store coefficient ANF of F_fn3(12)\cap F_fn3(14) 
   fn2_8.insert(anf_fn2_8); 
   num1++;   
   cout<<f3->get_anf()<<endl;
} 
fin2.close();
cout<<"num1 is "<<num1<<endl;

 num1=0;
fin2.open( "fn9_13_15.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin2.eof())
{ 
  string anf_fn9_13_15;
  BooleanFun *f4 = new BooleanFun(6);
  getline(fin2,line2);
  stringstream stringin(line2);
  //transform truth table to coefficient_anf
  read_boolean_fun(line2,f4);
  anf_fn9_13_15=f4->get_coe_list();
  //store coefficient ANF of F_fn10(9) 
   fn9_13_15.insert(anf_fn9_13_15); 
   num1++;   
   cout<<f4->get_anf()<<endl;
} 
fin2.close();
cout<<"num1 is "<<num1<<endl;
//int count=0;

int flag=0;
int flag1=0;
set<string> G3;

for (set<string>::iterator g=fn9_15.begin();g!=fn9_15.end();g++) 
{
     int all_in=true;
     for(set<string>::iterator t=fn2_8.begin();t!=fn2_8.end();t++)
     {
        string result;
       //let h=g+t
        result=string_xor(*t,*g);  
        //h\in fn3_14?
        if(fn9_13_15.find(result)==fn9_13_15.end())
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
cout<<"flag is "<<flag<<endl;

/*for (set<string>::iterator g1=G3.begin();g1!=G3.end();g1++) 
{
   int allin=true;
     for(set<string>::iterator l=fn10_9.begin();l!=fn10_9.end();l++)
     {
        string result1;
       //let h=g1+ l
        result1=string_xor(*g1,*l);  
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
cout<<"flag1 is "<<flag1<<endl;*/
  return 0;
}