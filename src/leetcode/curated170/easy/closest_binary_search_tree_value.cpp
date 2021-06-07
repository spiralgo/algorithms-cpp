#include <data_structures/tree_node.cpp>
#include <math.h>

class Solution
{
public:
    int closestValue(TreeNode *root, double target)
    {
        if (root == nullptr)
        {
            return current_best;
        }

        int current_val = root->val;

        if (current_best == -1)
        {
            current_best = current_val;
        }
        current_best = abs(current_val - target) < abs(current_best - target) ? current_val : current_best;

        if (target < current_val)
        {
            closestValue(root->left, target);
        }
        else if (target > current_val)
        {
            closestValue(root->right, target);
        }
        return current_best;
    }

private:
    int current_best = -1;
};

int main()
{
    return 0;
}