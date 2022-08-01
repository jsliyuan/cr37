#include <iostream>
#include <time.h>
#include <assert.h>
#include <utility>

#include "boolean_fun.h"
#include "affine_trans.h"


using namespace std;

int main() {
  BooleanFun f1(6,"x1x2x3x4");
  BooleanFun f2(6,"x1x2x4x5+x1x2x3x6");
  BooleanFun f3(6,"x2x3x4x5+x1x3x4x6+x1x2x5x6");
  BooleanFun f4(6,"x1x2x3x4x5");
  BooleanFun f5(6,"x1x2x3x4x5+x1x2x3x6");
  BooleanFun f6(6,"x1x2x3x4x5+x1x3x4x6+x1x2x5x6");
  BooleanFun f7(6,"x1x2x3x4x5x6");
  BooleanFun f8(6,"x1x2x3x4x5x6+x1x2x3x4");
  BooleanFun f9(6,"x1x2x3x4x5x6+x1x2x4x5+x1x2x3x6");
  BooleanFun f10(6,"x1x2x3x4x5x6+x2x3x4x5+x1x3x4x6+x1x2x5x6");

  assert(f1.nonlinearity()==4);
  assert(f2.nonlinearity()==6);
  assert(f3.nonlinearity()==10);
  assert(f4.nonlinearity()==2);
  assert(f5.nonlinearity()==4);
  assert(f6.nonlinearity()==8);
  assert(f7.nonlinearity()==1);
  assert(f8.nonlinearity()==3);
  assert(f9.nonlinearity()==7);
  assert(f10.nonlinearity()==9);
  
  assert(f1.nonlinearity(2)==4);
  assert(f2.nonlinearity(2)==6);
  assert(f3.nonlinearity(2)==10);
  assert(f4.nonlinearity(2)==2);
  assert(f5.nonlinearity(2)==4);
  assert(f6.nonlinearity(2)==8);
  assert(f7.nonlinearity(2)==1);
  assert(f8.nonlinearity(2)==3);
  assert(f9.nonlinearity(2)==7);
  assert(f10.nonlinearity(2)==9);

  assert(f1.nonlinearity(3)==4);
  assert(f2.nonlinearity(3)==6);
  assert(f3.nonlinearity(3)==8);
  assert(f4.nonlinearity(3)==2);
  assert(f5.nonlinearity(3)==4);
  assert(f6.nonlinearity(3)==6);
  assert(f7.nonlinearity(3)==1);
  assert(f8.nonlinearity(3)==3);
  assert(f9.nonlinearity(3)==5);
  assert(f10.nonlinearity(3)==7);

  cout << "Everything looks good. End of all tests." << endl;
  return 0;
}
