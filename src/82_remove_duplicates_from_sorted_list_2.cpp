#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        // 添加一个临时头节点以方便操作
        auto *result = new ListNode(-1);
        result->next = head;

        ListNode *p = result;
        ListNode *q = p->next;
        while (q && q->next) {
            if (q->val == q->next->val) {
                int curr = q->val;
                while (q && q->val == curr) {
                    p->next = q->next;
                    delete q;
                    q = p->next;
                }
            } else {
                p = q;
                q = q->next;
            }
        }

        p = result;
        result = result->next;
        delete p;
        return result;
    }
};

int main() {
    // 1->2->5
    ListNode *list1 = CreateList({1, 2, 3, 3, 4, 4, 5});

    // 2->3
    ListNode *list2 = CreateList({1, 1, 1, 2, 3});

    Solution solution;
    ListNode *result1 = solution.deleteDuplicates(list1);
    ListNode *result2 = solution.deleteDuplicates(list2);

    PrintList(result1);
    PrintList(result2);

    DestroyList(result1);
    DestroyList(result2);

    return 0;
}
