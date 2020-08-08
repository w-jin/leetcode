#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        auto result = new ListNode(-1);    //临时添加一个头部，以简化逻辑
        int carry = 0;  //进位
        ListNode *p = l1, *q = l2;
        ListNode *r = result;
        while (p != nullptr && q != nullptr) {
            int sum = p->val + q->val + carry;
            r->next = new ListNode(sum % 10);
            carry = sum / 10;
            p = p->next;
            q = q->next;
            r = r->next;
        }
        //l1和l2可能还有剩余的没加完
        while (p != nullptr) {
            int sum = p->val + carry;
            r->next = new ListNode(sum % 10);
            carry = sum / 10;
            p = p->next;
            r = r->next;
        }
        while (q != nullptr) {
            int sum = q->val + carry;

            r->next = new ListNode(sum % 10);
            carry = sum / 10;
            q = q->next;
            r = r->next;
        }
        //可能l1和l2都加完了，但还向更高位进了一位
        if (carry != 0) {
            r->next = new ListNode(carry);
        }

        //删掉头部
        r = result;
        result = result->next;
        delete r;

        return result;
    }
};

int main() {
    //7->0->8
    ListNode *l1 = CreateList({2, 4, 3});
    ListNode *l2 = CreateList({5, 6, 4});
    ListNode *l3 = Solution().addTwoNumbers(l1, l2);

    PrintList(l3);

    DestroyList(l1);
    DestroyList(l2);
    DestroyList(l3);

    return 0;
}
