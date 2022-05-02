/*
Compute F_f(r) = {g is homogenous degree-r or 0 : nl_2(f+g) = r}

Write the results to file with format:
g1 in its ANF
nl_2(f+g1)
g2 in its ANF
nl_2(f+g2)
...
...
There are 1<<20 such g in total

The file is of size ~ 400MB
*/
#include "homogenous_bf_generator.h"

#include <iostream>
#include <fstream>
#include <map>

using namespace std;

void count(string anf, ofstream& myfile) {
  BooleanFun fn61(6);
  BooleanFun h63(6);
  std::map<int, int> dist;
  HomogenousBfGenerator gen63(6,3);
  int total = 0;
  while (1) {
    total ++;
    fn61.set_anf(anf);
    fn61.add(*gen63.get_boolean_fun());
    h63=*gen63.get_boolean_fun();
    int nl = fn61.nonlinearity(2);
    dist[nl] ++;
    myfile << h63.get_anf() << endl;
    myfile << nl << endl;
    if (total % 100 == 0) {
      cout << total << endl;
    }
    /*
    if (total % (1<<15) == 0) {
      break;
    }
    */
    if (gen63.next() == false) {
      break;
    }
  }
  // assert(total == (1<<20));
  map<int, int>::iterator it;
  for (it = dist.begin(); it != dist.end(); ++ it) {
    cout << it->first << " => " << it->second << '\n';
  }

  myfile << "Total = " << total << endl;
}

int main() {
  /*
  fn1 "x1x2x3x4"
  fn2 "x1x2x4x5+x1x2x3x6"
  fn3 "x2x3x4x5+x1x3x4x6+x1x2x5x6"
  fn4 "x1x2x3x4x5"
  fn5 "x1x2x3x4x5+x1x2x3x6"
  fn6 "x1x2x3x4x5+x1x3x4x6+x1x2x5x6"
  fn7 "x1x2x3x4x5x6"
  fn8 "x1x2x3x4x5x6+x1x2x3x4"
  fn9 "x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6"
  fn10 "x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6"
  */
  int n;
  ofstream myfile;
  //remember to change the name of .txt for different fni
  myfile.open("Ffn2.txt");
  //count("x1x2x4x5+x1x2x3x6");
  string anf;
  //string anf1,anf2,anf3;
  cout << "Please provide the ANF:";
  cin >> anf;
  cout << "ANF is [" << anf << "]" << endl;
  
 /* cout << "Please provide the ANF of fn3:";
  cin >> anf1;
  cout << "ANF of fn3 is [" << anf1 << "]" << endl;

  cout << "Please provide the ANF of fn9:";
  cin >> anf2;
  cout << "ANF of fn9 is [" << anf2 << "]" << endl;

  cout << "Please provide the ANF of fn10:";
  cin >> anf3;
  cout << "ANF of fn10 is [" << anf3 << "]" << endl;
  */

  count(anf, myfile);
  myfile.close();

  /*myfile.open("Ffn3.txt");
  count(anf1, myfile);
  myfile.close();

  myfile.open("Ffn9.txt");
  count(anf2, myfile);
  myfile.close();

  myfile.open("Ffn10.txt");
  count(anf3, myfile);
  myfile.close();
  */

  return 1;
}