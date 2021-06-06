#include <iostream>
#include <string>
#include <math.h>

using namespace std;

class Solution
{
public:
    bool isArmstrong(int N)
    {
        int length = to_string(N).length();
        return N == get_sum_of_kth_power_digits(N, length);
    }

private:
    int get_sum_of_kth_power_digits(int N, int k)
    {
        int result = 0;

        while (N != 0)
        {
            result += pow(N % 10, k);
            N = N / 10;
        }
        return result;
    }
};

int main()
{
    Solution solution = Solution();
    cout << solution.isArmstrong(153) << endl; // prints 1
    cout << solution.isArmstrong(371) << endl; // prints 1
    cout << solution.isArmstrong(87) << endl;  // prints 0
}
