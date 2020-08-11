#include <unordered_set>
#include "list.hpp"

class Solution {
public:
    ListNode *removeDuplicateNodes(ListNode *head) {
        if (!head)
            return head;

        std::unordered_set<int> set;
        set.insert(head->val);
        ListNode *p = head;
        while (p->next) {
            auto it = set.find(p->next->val);
            if (it != set.end()) {
                ListNode *t = p->next;
                p->next = t->next;
                delete t;
            } else {
                set.insert(p->next->val);
                p = p->next;
            }
        }

        return head;
    }
};

class Solution1 {
public:
    ListNode *removeDuplicateNodes(ListNode *head) {
        if (!head)
            return head;

        int set[20001] = {0};
        set[head->val] = 1;
        ListNode *p = head;
        while (p->next) {
            if (set[p->next->val]) {
                ListNode *t = p->next;
                p->next = t->next;
                delete t;
            } else {
                set[p->next->val] = 1;
                p = p->next;
            }
        }

        return head;
    }
};

/*
 * 对每个节点，删除它后面所有与它的值相同的节点。
 * 时间复杂度O(n^2)，空间复杂度O(1)。
 */
class Solution2 {
public:
    ListNode *removeDuplicateNodes(ListNode *head) {
        ListNode *p = head;
        while (p) {
            ListNode *q = p;
            while (q->next) {
                if (q->next->val == p->val) {
                    ListNode *t = q->next;
                    q->next = t->next;
                    delete t;
                } else {
                    q = q->next;
                }
            }
            p = p->next;
        }

        return head;
    }
};

int main() {
    // 1->2->3
    ListNode *head1 = CreateList({1, 2, 3, 3, 2, 1});

    // 1->2
    ListNode *head2 = CreateList({1, 1, 1, 1, 2});

    Solution solution;
    ListNode *result1 = solution.removeDuplicateNodes(head1);
    ListNode *result2 = solution.removeDuplicateNodes(head2);

    PrintList(result1);
    PrintList(result2);

    DestroyList(result1);
    DestroyList(result2);

    return 0;
}
