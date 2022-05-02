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
// 2^22 ANFs in total
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
      cout<<anf<<endl;
    }
  }

  cout << "Read " << fn_set->size() << " boolean functions from file " << file_name << endl;
  myfile.close();
}

int main() {
  set<string> Ff9_15;
  read_bfs_from_file("Ffn9.txt", 15,0, &Ff9_15);

  set<string> Ff2_8;
  read_bfs_from_file("Ffn2.txt", 8,0, &Ff2_8);

  set<string> Ff9_13_15;
  read_bfs_from_file("Ffn9.txt", 13,15, &Ff9_13_15);

  set<string> g3;

  int total_t = 0;
  int num=0;
  for (const string& anf : Ff9_15) {
    BooleanFun fn(6, anf);
    bool all_in = true;
    // Enumerate g
    for (const string& t_anf : Ff2_8) {
      BooleanFun t(6,t_anf);
      t.add(fn);
      if (Ff9_13_15.find(t.get_anf()) == Ff9_13_15.end()) {
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

  return 0;
}