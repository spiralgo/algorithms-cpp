#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> anagramMappings(vector<int> &A, vector<int> &B)
    {
        int size = A.size();
        int indices_of_B[100005];
        for (int i = 0; i < size; i++)
        {
            indices_of_B[B[i]] = i;
        }

        vector<int> mapping(size);

        for (int i = 0; i < size; i++)
        {
            mapping[i] = indices_of_B[A[i]];
        }

        return mapping;
    }
};

int main()
{
    vector<int> A{12, 28, 46, 32, 50};
    vector<int> B{50, 12, 32, 46, 28};
    vector<int> mapping = Solution().anagramMappings(A, B);

    for (int n : mapping)
    {
        cout << n << " ";
    }
    cout << endl;
    return 0;
}