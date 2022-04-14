#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>
#include<vector>
#include <iostream>  // I/O 
#include <fstream>   // file I/O
#include <sstream>
#include <iomanip>   // format manipulation
#include <string>
using namespace std;

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


int count_all_mod_rm36(string fni,vector<AffineTrans>& all_trans) {
  BooleanFun fn1(6);
   AffineTrans *t6_rand=new AffineTrans(6);
  set<string> all_bfs;
  int total = 0;

  while (1) {
     
    t6_rand->set_random();
    fn1.set_anf(fni);
  	fn1.apply_affine_trans(*t6_rand);
  	fn1.trim_degree_below(4);

  	string anf = fn1.get_anf();
  	if (all_bfs.find(anf) == all_bfs.end()) {
      //cout<<t6_rand.get_a_str()<<endl;
     // printf("\n");
      t6_rand->inverse();
   // cout<<t6_rand.get_a_str()<<endl;
    all_trans.push_back(*t6_rand);
      all_bfs.insert(anf);
      total ++;
    // cout << total << endl;
      t6_rand=new AffineTrans(6);
    }
    if(total==13888)
    break;
  }

  return total;
}

int main() {
  /*
 
  cout << count_all_mod_rm36("x1x2x4x5+x1x2x3x6") << endl;

  cout << count_all_mod_rm36("x1x2x3x4x5") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x2x3x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x3x4") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6") << endl;
  cout << count_all_mod_rm36("x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6") << endl;
  */
//  cout << count_all_mod_rm36("x1x2x4x5+x1x2x3x6") << endl;

//cout << count_all_mod_rm36("x1x2x3x4") << endl;
ifstream fin;
ifstream ffin;
ifstream fin1;
string line;
string line1;
string line2;
string line3;
string line4;
BooleanFun g(6);
BooleanFun h(6);
BooleanFun g3(6);
set<string> fn10_15;
set<string> H3_6_8;
set<string> fn10_13_15;
set<string> magic8;
set<string> bad_g;
set<string>  fn6_6;

set<string>  fn6_8;
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
    read_boolean_fun(line,f1);
    anf10_15=f1->get_anf();
   fn10_15.insert(anf10_15);
}
fin.close();

/*for(set<string>::iterator it=fn10_15.begin();it!=fn10_15.end();it++)
{
    cout<<*it<<endl;
    num=num+1;
}
printf("%d\n",num);*/

ffin.open( "H3_6_8.txt", ios::in);  
if(ffin.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!ffin.eof())
{
  string anf_h368;
   BooleanFun *f1 = new BooleanFun(6);
    getline(ffin,line1);
      stringstream stringin(line1);
    read_boolean_fun(line1,f1);
    anf_h368=f1->get_anf();
   H3_6_8.insert(anf_h368);
}
 ffin.close();

/*for(set<string>::iterator it=H3_6_8.begin();it!=H3_6_8.end();it++)
{
    cout<<*it<<endl;
    num=num+1;
}
printf("%d",num);*/

 int num2=0;
 int start_idx,end_idx;
 cin>>start_idx;
 cin>>end_idx;
fin1.open( "fn10_13_15.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  getline(fin1,line2);
  num2=num2+1;
  if(num2>end_idx)
    break;
  if(num2>=start_idx&&num2<=end_idx)
  {
  string anf_f10;
 BooleanFun *f1 = new BooleanFun(6);
      stringstream stringin(line2);
    read_boolean_fun(line2,f1);
  f1->set_truth_table_done();
  anf_f10=f1->get_anf();
   fn10_13_15.insert(anf_f10);
  } 
}

/*for(set<string>::iterator it=fn10_13_15.begin();it!=fn10_13_15.end();it++)
{
    cout<<*it<<endl;
    num2=num2+1;
}
 printf("%d \n",num2);*/
 fin1.close();

  num2=0;
fin1.open( "6_s8_1.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  string anf_magic8;
  BooleanFun *f1 = new BooleanFun(6);
    getline(fin1,line3);
      stringstream stringin(line3);
    read_boolean_fun(line3,f1);
    anf_magic8=f1->get_anf();
   magic8.insert(anf_magic8);
}
/*for(set<string>::iterator it=magic8.begin();it!=magic8.end();it++)
{
    cout<<*it<<endl;
    num2=num2+1;
}
 printf("%d \n",num2);*/
 fin1.close();

num2=0;
string line8;
fin1.open( "f6_8.txt", ios::in);  
if(fin1.fail())
  {
    cout<<"no file!"<<endl;
    getchar();
    exit(0);
  }
while(!fin1.eof())
{ 
  string anf_magic2112;
  BooleanFun *f1 = new BooleanFun(6);
    getline(fin1,line8);
      stringstream stringin(line8);
    read_boolean_fun(line8,f1);
    anf_magic2112=f1->get_anf();
  fn6_8.insert(anf_magic2112);
}
/*for(set<string>::iterator it=fn6_8.begin();it!=fn6_8.end();it++)
{
    cout<<*it<<endl;
    num2=num2+1;
}
 printf("%d \n",num2);*/
 fin1.close();

num2=0;
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
    getline(fin1,line4);
      stringstream stringin(line4);
    read_boolean_fun(line4,f1);
    anf_32=f1->get_anf();
   fn6_6.insert(anf_32);
}
for(set<string>::iterator it=fn6_6.begin();it!=fn6_6.end();it++)
{
    cout<<*it<<endl;
    num2=num2+1;
}
 printf("%d \n",num2);
 fin1.close();

num2=0;
count_all_mod_rm36("x2x3x4x5+x1x3x4x6+x1x2x5x6", all_trans);
for(vector<AffineTrans>::iterator it=all_trans.begin();it!=all_trans.end();it++)
{
    cout<<it->get_a_str()<<endl;
    printf("\n");
    num2=num2+1;
}
cout<<num2<<endl;

int flag = 0;
int flag1 = start_idx;

for(set<string>::iterator g=fn10_13_15.begin();g!=fn10_13_15.end();g++)
{
  set<string> inter; 
  set<string> add_f_g; 
  string anf_g;
  anf_g=*g; 
  cout<<anf_g<<endl;
  BooleanFun g3(6,anf_g); //BooleanFun g3

//g+h\in Ffn10_15 
   for(set<string>::iterator h=H3_6_8.begin();h!=H3_6_8.end();h++){
    string anf_h;
    anf_h=*h; 
    BooleanFun hg(6,anf_h); //BooleanFun H3_6_8
    hg.add(g3);// h+g
    string anf;
    anf=hg.get_anf();

      if (fn10_15.find(anf) != fn10_15.end()) {
       // O(1)
      inter.insert(anf_h);  // hg + g = h
    }
  }
  //Enumerate A
    for (vector<AffineTrans>::iterator trans=all_trans.begin();trans!=all_trans.end();trans++ ) {
    bool all_in = true;
    bool all_in_32 = true;
      for (set<string>::iterator magic=magic8.begin();magic!=magic8.end();magic++) {
        string anf2;
        anf2= *magic;
        BooleanFun fm(6,anf2) ;
        fm.apply_affine_trans(*trans);
        fm.trim_degree_below(3);
        string anf=fm.get_anf();
        //cout<<anf<<endl;
        if (inter.find(anf) == inter.end())
        {
          all_in = false;
          break;
        }
      }
    if (all_in) {

      for (set<string>::iterator magic32=fn6_6.begin();magic32!=fn6_6.end();magic32++) {
          string anf_magic32;
          anf_magic32=*magic32;
          BooleanFun fmm(6,anf_magic32) ;//Ffn6(6)
        fmm.apply_affine_trans(*trans);
        fmm.trim_degree_below(3);
        fmm.add(g3);
        string anf7=fmm.get_anf();
      
          if(fn10_15.find(anf7)==fn10_15.end())
          {
         //   cout<<anf7<<endl;
            all_in_32 = false;
            break;
          }
      }
      
      if(all_in_32)
      {
        bad_g.insert(*g);
      cout << "\n Bad news! Need more work!" << endl;
      cout << trans->get_a_str() << endl;
      cout << *g << endl;
      flag=flag+1;
      break;
      } 
    }
  }
  cout<< flag1++<<" ";
}
cout<<"find "<<flag<<endl;

//
for (set<string>::iterator n=bad_g.begin();n!=bad_g.end();n++) {
      string anf_g1;
      anf_g1= *n;
      cout<<anf_g1<<endl;  
    }
  return 0;
}
