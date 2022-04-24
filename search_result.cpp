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

//Our goal is to find A,b and g such that fn10(Ax+b)+g||fn6 with nl3=21. deg(g)=3
//that is, fn10||fn6(A^-1x+ A^-1b)+g(A^-1x+b) with nl3=21.
//We have verified that the number of (Ai,bi) such that (Ai,bi)f= fn10(Ax+b) mod RM(3,6) is 65112;
//The length of orbits of fn10(Ax+b) mod RM(3,6) is 888832.

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
string line;
string line1;

set<string> fn10_15;
set<string>  fn6_6;

vector<AffineTrans> all_trans;

 int num=0;
fin.open( "f10_15.txt", ios::in);  
 if(fin.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin.eof())
{   
  string anf10_15;
  BooleanFun *f1 = new BooleanFun(6);
  getline(fin,line);
  stringstream stringin(line);
   //transform truth table to coefficient_anf
  read_boolean_fun(line,f1);
  anf10_15=f1-> get_coe_list();
  //store coefficient ANF of F_fn10(15) in string set "fn10_15"
  fn10_15.insert(anf10_15);  
}
fin.close();

fin1.open( "f6_6.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  string anf_32;
  BooleanFun *f1 = new BooleanFun(6);
  getline(fin1,line1);
  stringstream stringin(line1);
  //transform truth table to coefficient_anf
  read_boolean_fun(line1,f1);
  anf_32=f1->get_coe_list();
  //store coefficient ANF of F_fn6(6) in string set "fn6_6"
   fn6_6.insert(anf_32);    
} 
fin1.close();

/*int start_idx;
int end_idx;
cin>>start_idx;
cin>>end_idx;*/

string line_anf;
//int count=0;

set<string> G3;
int flag=0;
int sign=0;
int flag1=0;

//read A,b from fn10_af.txt
//A and b are in string format, e.g.,
// [100000 010000 001000 000100 000010 000001]100000
fin1.open( "fn10_af.txt", ios::in);   //
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  getline(fin1,line_anf);
 // count++;
  bool all_in_A = false;
  //if(count>=start_idx&&count<=end_idx)
  //{
      stringstream stringin(line_anf);
      AffineTrans *T = new AffineTrans(6, line_anf);
      set<string> magic32_trans;
      // get A^-1
      T->inverse();
      for (set<string>::iterator magic32=fn6_6.begin();magic32!=fn6_6.end();magic32++) 
    {
        string anf2;
        anf2= *magic32;
        BooleanFun fm(6) ;
        fm.set_coe_list(anf2);
        // fm=F_fn6(6)(A^-1x)
        fm.apply_affine_trans(*T);
        // fm=F_fn6(6)(A^-1x) mod RM(3,6)
        fm.trim_degree_below(3);
        string anf=fm.get_coe_list();
        //store coefficient_anf of fm=F_fn6(A^-1x)(6) mod RM(3,6)
        magic32_trans.insert(anf);
    }
      set<string> g_s_t;
     for(set<string>::iterator t=fn10_15.begin();t!=fn10_15.end();t++)
     {
        string result;
        string s0;
        s0=*magic32_trans.begin();
       //let g=s0+ ti, where s0 is the first element of H3_{F_{fn6(A^-1x)}(6)}, ti\in F_fn10(15)
        result=string_xor(*t,s0);  
        //store coefficient_anf of g=s0+ti
        g_s_t.insert(result);
    } 

    //traverse the set of g, of which the size is 34560
    for (set<string>::iterator it=g_s_t.begin();it!=g_s_t.end();it++) 
    {
         bool all_in = true;
         string anff=*it;
         string result1;
         BooleanFun valid_g(6) ;
       
        for (set<string>::iterator m=magic32_trans.begin();m!=magic32_trans.end();m++) 
        {
            string anfm;
            //  h=g+si. where si \in H3_{F_{fn6(Ax)}(6)}
            result1=string_xor(*it,*m);
            //if h \notin F_fn10(15), then g is invalid.
            if(fn10_15.find(result1)==fn10_15.end())
            {
              all_in = false;
              break;
            }       
        }
        //if we find a possible g. store the ANF in the string set "G3"
        if(all_in)
        { 
          valid_g.set_coe_list(result1);
          G3.insert( valid_g.get_anf());
          flag=flag+1;
          all_in_A = true;
        }
    }
     //flag represents the number of possible g corresponding to each A,b
      cout<< "i: "<<flag1++<<";"<<" the number of possible g: "<< flag<<endl;
   //   cout<< line_anf<<" "<<*magic32_trans.begin()<<endl;
      //print valid A,b
      if(all_in_A)
      {
        cout<<"possible (A,b): "<<line_anf<<endl;
        cout<<"possible g: "<<endl;
      }
      // print all the possbile g
     for (set<string>::iterator n=G3.begin();n!=G3.end();n++) 
    {
      string anf_g1;
      anf_g1= *n;
      cout<<anf_g1<<endl;  
      sign++;
    }
    flag=0;
  //}
}
//print the number of possbile g ;
// if there doesn't exist possbile g, then sign==0.
   if(sign==0)
cout<<"There doesn't exist possbile (A,b) and g such that nl_3(fn10||fn6(A^-1+A^-1b)+g(A^-1x))=21. "<<endl;
  return 0;
}
