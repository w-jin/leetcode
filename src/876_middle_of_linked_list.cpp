#include <iostream>
#include <vector>
#include "list.hpp"

using std::cout;
using std::endl;
using std::vector;

/*
    注意：此题题目说链表带有头结节，实际上没有！
*/

/*
    使用一个数组保存所有节点指针，返回数组中点。
    时间复杂度O(N)，只需遍历一次，空间复杂度O(N)。
 */
class Solution {
public:
    ListNode *middleNode(ListNode *head) {
        vector<ListNode *> temp;

        ListNode *p = head;
        while (p) {
            temp.push_back(p);
            p = p->next;
        }

        return temp[temp.size() / 2];
    }
};

/*
    先遍历一次计算出节点数量，然后计算出需要返回第几个节点，然后再遍历一次返回。
    时间复杂度O(N)，需要遍历两次，空间复杂度O(1)。
 */
class Solution1 {
public:
    ListNode *middleNode(ListNode *head) {
        int length = 0;

        ListNode *p = head;
        while (p) {
            ++length;
            p = p->next;
        }

        int middle = length / 2;
        p = head;
        while (middle > 0) {
            --middle;
            p = p->next;
        }

        return p;
    }
};

/*
    使用两个指针进行遍历，一快一慢，快的一次跳过两个节点，慢的一次跳过一个，当快的到达末尾时，慢的
    刚好指向中点。
    时间复杂度O(N)，只需要遍历一次，空间复杂度O(1)。
 */
class Solution2 {
public:
    ListNode *middleNode(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        return slow;
    }
};

int main() {
    // 3
    ListNode *head1 = CreateList({1, 2, 3, 4, 5});

    // 4
    ListNode *head2 = CreateList({1, 2, 3, 4, 5, 6});

    Solution1 solution;
    cout << solution.middleNode(head1)->val << endl;
    cout << solution.middleNode(head2)->val << endl;

    DestroyList(head1);
    DestroyList(head2);

    return 0;
}
