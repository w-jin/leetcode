#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        //添加临时头节点。l1和l2并不需要头节点
        auto *h1 = new ListNode(-1);
        h1->next = l1;
        auto *h2 = new ListNode(-1);
        h2->next = l2;
        auto *result = new ListNode(-1);

        //合并
        ListNode *r = result;
        while (h1->next != nullptr && h2->next != nullptr) {
            if (h1->next->val <= h2->next->val) {
                //将h1->next摘下来放在r后
                r->next = h1->next;
                h1->next = h1->next->next;
                r = r->next;
            } else {
                //将h2->next摘下来放在r后
                r->next = h2->next;
                h2->next = h2->next->next;
                r = r->next;
            }
        }
        if (h1->next != nullptr)
            r->next = h1->next;
        if (h2->next != nullptr)
            r->next = h2->next;

        //删除临时头节点
        ListNode *temp = result;
        result = result->next;
        delete h1;
        delete h2;
        delete temp;

        return result;
    }
};

class Solution1 {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode head_result(-1);   // 结果链表的临时头节点

        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *tail = &head_result;
        while (p1 && p2) {
            if (p1->val < p2->val) {
                tail->next = p1;
                p1 = p1->next;
                tail = tail->next;
            } else {
                tail->next = p2;
                p2 = p2->next;
                tail = tail->next;
            }
        }
        if (p1)
            tail->next = p1;
        if (p2)
            tail->next = p2;

        return head_result.next;
    }
};

int main() {
    //1->1->2->3->4->4
    ListNode *l1 = CreateList({1, 2, 4});
    ListNode *l2 = CreateList({1, 3, 4});
    Solution1 solution;
    ListNode *result = solution.mergeTwoLists(l1, l2);

    PrintList(result);

    DestroyList(result);
    return 0;
}