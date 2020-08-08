#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        //添加一个临时头节点，以简化逻辑
        auto *h = new ListNode(-1);
        h->next = head;

        ListNode *p = h;
        ListNode *q = h;

        //不检验n的合法性
        for (int i = 0; i < n; ++i)
            p = p->next;
        while (p->next != nullptr) {
            p = p->next;
            q = q->next;
        }

        ListNode *t = q->next;
        q->next = t->next;
        delete t;

        head = h->next;
        delete h;
        return head;
    }
};

int main()
{
    //1->2->3->5
    ListNode *head = CreateList({1, 2, 3, 4, 5});
    int n = 2;
    Solution().removeNthFromEnd(head, n);

    PrintList(head);
    DestroyList(head);

    return 0;
}
