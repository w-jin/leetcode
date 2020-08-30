#include <vector>
#include "list.hpp"
#include "tree.hpp"

/*
 * 将链表转换成数组，然后按照108的思路，将中间元素作为根节点，将左半部分元素作为左子树，
 * 右半部分元素作为右子树，递归建立二叉树。
 * 时间复杂度O(n)，空间复杂度O(n)。
 */
class Solution {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        std::vector<int> nums;
        ListNode *p = head;
        while (p) {
            nums.push_back(p->val);
            p = p->next;
        }

        return sortedArrayToBST(nums, 0, static_cast<int>(nums.size()) - 1);
    }

private:
    TreeNode *sortedArrayToBST(const std::vector<int> &nums, int first, int last) {
        if (first > last)
            return nullptr;
        else if (first == last) {
            return new TreeNode{nums[first]};
        } else {
            int mid = first + (last - first) / 2;
            TreeNode *root = new TreeNode{nums[mid]};
            root->left = sortedArrayToBST(nums, first, mid - 1);
            root->right = sortedArrayToBST(nums, mid + 1, last);
            return root;
        }
    }
};


/*
 * 有序的序列转换成平衡二叉树实际上是从中序遍历的结果建立平衡二叉树，可以先建立左子树，再建立根节点，
 * 然后建立右子树，这样就不需要随机访问链表的元素。问题在于如何知道各个子树有多少个节点，这个可以通过
 * 总的节点个数推算出来。
 */
class Solution1 {
public:
    TreeNode *sortedListToBST(ListNode *head) {
        int n = 0;
        ListNode *p = head;
        while (p) {
            ++n;
            p = p->next;
        }

        return sortedListToBST(head, n);
    }

private:
    TreeNode *sortedListToBST(ListNode *&head, int n) {
        if (n <= 0)
            return nullptr;

        // 4个元素时左边2个，右边1个；5个元素时左边2个，右边2个(上个解答左轻右重)
        int left_n = n / 2;
        int right_n = (n - 1) / 2;

        // 先建立左子树
        TreeNode *left = sortedListToBST(head, left_n);

        // 建立根节点
        TreeNode *root = new TreeNode{head->val};
        head = head->next;

        // 建立右子树
        TreeNode *right = sortedListToBST(head, right_n);

        root->left = left;
        root->right = right;
        return root;
    }
};

int main() {
    // 0
    // ├─── -10
    // │    ├─── missing
    // │    └─── -3
    // └─── 5
    //      ├─── missing
    //      └─── 9
    ListNode *head1 = CreateList({-10, -3, 0, 5, 9});

    Solution1 solution;
    TreeNode *root1 = solution.sortedListToBST(head1);

    PrintBinaryTree(root1);

    DestroyList(head1);
    DestroyTree(root1);

    return 0;
}
