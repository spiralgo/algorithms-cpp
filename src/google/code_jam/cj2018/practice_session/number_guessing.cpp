#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <unordered_set>

using namespace std;

void guess(int lo, int hi)
{
  int mid = (lo + hi) / 2;
  cout << mid << endl;
  string res;
  cin >> res;

  if (res == "CORRECT")
  {
    return;
  }
  if (res == "TOO_SMALL")
  {
    guess(mid + 1, hi);
  }
  else
  {
    guess(lo, mid - 1);
  }
}

int main()
{
  int tests;
  cin >> tests;
  while (tests-- > 0)
  {
    int lo, hi;
    cin >> lo >> hi;
    int num_tries;
    cin >> num_tries;
    
    guess(lo+1, hi);
  }
  return 0;
}