#include <iostream> 
//#include <stdio.h>

using namespace std;

void function( int& nTmp1, int nTmp2 )
{
  nTmp1 = 10;
  nTmp2 = 11;

  cout << nTmp1 << " " << nTmp2 << " ";
}

int main(int argc, char* argv[])
{
  int nTmp1 = 5;
  int nTmp2 = 6;

  function( nTmp1, nTmp2 );

  cout << nTmp1 <<" " << nTmp2 << endl;
  cout << "siezof null " << sizeof('0');

  return 0;
}
