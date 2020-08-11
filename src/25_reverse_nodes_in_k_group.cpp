#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        //翻转前k个
        int n = 0;
        ListNode *p = head;
        //统计节点个数，不够k个的不翻转
        while (n < k && p != nullptr) {
            ++n;
            p = p->next;
        }
        if (n < k)
            return head;

        //逐个翻转
        ListNode *new_head = new ListNode(-1);
        new_head->next = p;
        p = head;
        for (n = 0; n < k; ++n) {
            ListNode *temp = p->next;
            p->next = new_head->next;
            new_head->next = p;
            p = temp;
        }
        head->next = reverseKGroup(head->next, k);

        p = new_head;
        new_head = new_head->next;
        delete p;
        return new_head;
    }
};

class Solution1 {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if (k < 2)
            return head;

        int n = 0;
        ListNode *p = head;
        //统计节点个数，不够k个的不翻转
        while (n < k && p != nullptr) {
            ++n;
            p = p->next;
        }
        if (n < k)
            return head;

        //翻转k个
        p = head;
        ListNode *q = p->next;
        ListNode *r = nullptr;
        while (--n > 0) {
            r = q->next;
            q->next = p;
            p = q;
            q = r;
        }
        head->next = reverseKGroup(q, k);

        return p;
    }
};


int main() {
    //3->2->1->4->5
    Solution1 solution;
    ListNode *head = CreateList({1, 2, 3, 4, 5});
    ListNode *result = solution.reverseKGroup(head, 3);
    PrintList(result);
    DestroyList(result);

    return 0;
}
