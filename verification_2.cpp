#include "boolean_fun.h"
#include "affine_trans.h"

#include <iostream>
#include <set>
#include <vector>
#include <fstream>

using namespace std;
// determine the nl3 of fn10||fn3+g3 whether can achieve 21
// which must satisfy F_fn10(r) \subset F_fn3(21-r)+g3,
// that is, F_fn10(r)+g3 \subset F_fn3(21-r).
// g3 is a homogeneous 6-variable Boolean function of degree 3, where g3 \in F_fn3(12) and F_fn3(14).


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
  read_bfs_from_file("Ffn10.txt", 9,0, &Ff10_9);

  set<string> Ff10_7;
  read_bfs_from_file("Ffn10.txt", 7,0, &Ff10_7);

  set<string> g3;

  int total_t = 0;
  int num=0;
  
  // Enumerate g
  for (const string& anf : Ff3_12_14) {
    BooleanFun fn(6, anf);
    bool all_in = true;
    // Enumerate f in F_fn10(7)
    for (const string& t_anf : Ff10_7) {
      BooleanFun t(6,t_anf);
      t.add(fn);
      //whether f+g belongs to F_fn3(14)
      if (Ff3_14.find(t.get_anf()) == Ff3_14.end()) {
        all_in = false;
        break;
      }
    }
    if (all_in) {
      cout << "Bad news!" << endl;
      cout << fn.get_anf() << endl;
      // store the possible homogeneous Boolean functions g of degree 3 is string set g3.
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
  
  //Enumerate g
  for (const string& anf1 : g3) {
    BooleanFun fn1(6, anf1);
    bool all_in_1 = true;
    // Enumerate f in F_fn10(9)
    for (const string& t_anf1 : Ff10_9) {
      BooleanFun t1(6,t_anf1);
      t1.add(fn1);
      //whether f+g belongs to F_fn3(12) and F_fn3(14)
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
