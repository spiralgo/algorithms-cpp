#include <iostream>
#include <unordered_map>
#include <math.h>

using namespace std;

class Solution
{

public:
    bool confusingNumber(int N)
    {
        int old_trace = N;
        int new_num = 0;
        while (old_trace > 0)
        {
            int remainder_digit = old_trace % 10;
            if (!mirrored_nums.count(remainder_digit))
            {
                return false;
            }
            new_num = new_num *10 + mirrored_nums.at(remainder_digit);
                
            old_trace /= 10;
        }

        return new_num != N;
    }

private:
    const unordered_map<int, int> mirrored_nums = {
        {0, 0},
        {1, 1},
        {6, 9},
        {8, 8},
        {9, 6}};
};

int main()
{
    Solution solution = Solution();
    cout << solution.confusingNumber(86) << endl; // 1
    cout << solution.confusingNumber(88) << endl; // 0
    cout << solution.confusingNumber(6) << endl; // 1 
    cout << solution.confusingNumber(11) << endl; // 0
    cout << solution.confusingNumber(25) << endl; // 0
    cout << solution.confusingNumber(181) << endl; // 0
    cout << solution.confusingNumber(189) << endl; // 1
    return 0;
}