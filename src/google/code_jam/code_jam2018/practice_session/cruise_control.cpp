#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>
#include <unordered_set>
#include <utility>
#include <queue>

using namespace std;

void solve(int case_id)
{
  double D;
  int N;
  cin >> D >> N;
  double max_time = 0;
  
  for (int h = 0; h < N; h++)
  {
    double p, s;
    cin >> p >> s;
    double time = (D - p) / s;
    if (time > max_time)
    {
      max_time = time;
    }
  }
  printf("Case #%d: %.9lf\n", case_id, (D / max_time));
}

int main()
{
  int tests;
  cin >> tests;

  for (int i = 1; i <= tests; i++)
  {
    solve(i);
  }
}