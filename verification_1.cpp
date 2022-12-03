/*
 Determine the nl3 of fn2||fn9+g whether can achieve 21,
 which must satisfy F_fn2(r) \subset F_fn9(21-r)+g,
 that is, F_fn2(r)+g \subset F_fn9(21-r).
 g is a homogeneous 6-variable Boolean function of degree 3, where g \in F_fn9(15).
*/

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
void read_bfs_from_file(string file_name, int r, set<string> *fn_set) {
  ifstream myfile;
  myfile.open(file_name);
  string anf;
  int val;
  for (int i = 0; i < (1<<20); i ++)  {
    myfile >> anf;
    myfile >> val;
    if (val == r) {
      fn_set->insert(anf);
      //cout<<anf<<endl;
    }
  }

  cout << "Read " << fn_set->size() << " boolean functions from file " << file_name << endl;
  myfile.close();
}

int main() {
  set<string> Ff9_15;
  read_bfs_from_file("Ffn9_15.txt", 15, &Ff9_15);

  set<string> Ff2_8;
  read_bfs_from_file("Ffn2_8.txt", 8 ,&Ff2_8);

  set<string> Ff9_13_15;
  read_bfs_from_file("Ffn9.txt", 13, &Ff9_13_15);
  read_bfs_from_file("Ffn9.txt", 15, &Ff9_13_15);

  set<string> g3;

  int total_t = 0;
  int num=0;
  // Enumerate g
  for (const string& anf : Ff9_15) {
    BooleanFun fn(6, anf);
    bool all_in = true;
    //Enumerate f in F_fn2(8)
    for (const string& t_anf : Ff2_8) {
      BooleanFun t(6,t_anf);
      t.add(fn);
      // Whether f+g \in F_fn9(13) and F_fn9(15)
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
  cout<<"The number of possible functions g for fn2||fn9+g to achieve 21 is "<<num<<endl;

  return 0;
}
