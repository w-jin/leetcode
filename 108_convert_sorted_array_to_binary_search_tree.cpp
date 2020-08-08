#include <vector>
#include "tree.hpp"

using std::vector;

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return sortedArrayToBST(nums, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    TreeNode *sortedArrayToBST(vector<int> &nums, int first, int last) {
        if (first > last)
            return nullptr;
        if (first == last)
            return new TreeNode(nums[first]);

        int mid = first + (last - first) / 2;
        auto root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, first, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, last);
        return root;
    }
};

int main() {
    vector<int> nums1 = {-10, -3, 0, 5, 9};

    Solution solution;
    TreeNode *tree1 = solution.sortedArrayToBST(nums1);
    PrintBinaryTree(tree1);

    DestroyTree(tree1);
    return 0;
}
