#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

// Read Boolean function ANF from file, and save the string to fn_set.
// File format:
// ANF (string)
// r (int)
// ANF (string)
// r (int)
// ...
// 2^20 ANFs in total
void read_bfs_from_file(string file_name, int r, int r1, set<string> *fn_set) {
  ifstream myfile;
  myfile.open(file_name);
  string anf;
  int val;
  for (int i = 0; i < (1<<20); i ++) {
    myfile >> anf;
    myfile >> val;
    if (val == r||val==r1) {
      fn_set->insert(anf);
    //  cout<<anf<<endl;
    }
  }

  cout << "Read " << fn_set->size() << " boolean functions from file " << file_name << endl;
  myfile.close();
}

int main() {
  set<string> Ff3_12_14;
  read_bfs_from_file("Ffn3.txt", 12,14, &Ff3_12_14);

  set<string> Ff3_14;
  read_bfs_from_file("Ffn3.txt", 14,0, &Ff3_14);

  set<string> Ff10_9;
  read_bfs_from_file("Ff10.txt", 9,0, &Ff10_9);

  set<string> Ff10_7;
  read_bfs_from_file("Ff10.txt", 7,0, &Ff10_7);

  set<string> g3;

  int total_t = 0;
  int num=0;
  for (const string& anf : Ff3_12_14) {
    BooleanFun fn(6, anf);
  //  BooleanFun g(6, *Ff10_7.begin());
   //   g.add(fn);
      bool all_in = true;
    // Enumerate g
    for (const string& t_anf : Ff10_7) {
   //   BooleanFun sum = g;
      BooleanFun t(6,t_anf);
      t.add(fn);
      if (Ff3_14.find(t.get_anf()) == Ff3_14.end()) {
        all_in = false;
        break;
      }
    }
    if (all_in) {
      cout << "Bad news!" << endl;
      cout << fn.get_anf() << endl;
      g3.insert(fn.get_anf());
    }
    total_t ++;
    if (total_t % 10 == 0) {
      cout << total_t << endl;
    } 
  }
  cout<<"num is "<<num<<endl;

  total_t=0;
  num=0;
  for (const string& anf1 : g3) {
    BooleanFun fn1(6, anf1);
    bool all_in_1 = true;
    // Enumerate g
    for (const string& t_anf1 : Ff10_9) {
      BooleanFun t1(6,t_anf1);
      t1.add(fn1);
      if (Ff3_12_14.find(t1.get_anf()) == Ff3_12_14.end()) {
        all_in_1 = false;
        break;
      }
    }
    if (all_in_1) {
        cout << "Bad news!" << endl;
        cout << fn1.get_anf() << endl;
        num++;
    }
    total_t ++;
    if (total_t % 10 == 0) {
      cout << total_t << endl;
    }
  }
 cout<<"num is "<<num<<endl;
  return 0;
}
