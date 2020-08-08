#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        ListNode *p = head;
        while (p && p->next) {
            while (p->next && p->val == p->next->val) {
                auto t = p->next;
                p->next = t->next;
                delete t;
            }
            p = p->next;
        }
        return head;
    }
};

int main() {
    // 1->2
    ListNode *list1 = CreateList({1, 1, 2});

    // 1->2->3
    ListNode *list2 = CreateList({1, 1, 2, 3, 3});

    Solution solution;
    ListNode *result1 = solution.deleteDuplicates(list1);
    ListNode *result2 = solution.deleteDuplicates(list2);

    PrintList(result1);
    PrintList(result2);

    DestroyList(result1);
    DestroyList(result2);

    return 0;
}
