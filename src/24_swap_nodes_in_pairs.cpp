#include <iostream>
#include "list.hpp"

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        //先交换第一二个节点
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *second = head->next;
        head->next = head->next->next;
        second->next = head;
        head = second;

        //再交换后续节点
        ListNode *p = head->next;
        while (p->next != nullptr && p->next->next != nullptr) {
            second = p->next->next;
            p->next->next = second->next;
            second->next = p->next;
            p->next = second;
            p = p->next->next;
        }

        return head;
    }
};

class Solution1 {
public:
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *second = head->next;
        head->next = swapPairs(second->next); //将后续节点交换好后接到第一个节点后
        second->next = head; //把第一个节点接到第二个节点后
        return second;
    }
};


int main()
{
    //2->1->4->3
    Solution1 solution;
    ListNode *head = CreateList({1, 2, 3, 4});
    ListNode *result = solution.swapPairs(head);
    PrintList(result);
    DestroyList(result);

    return 0;
}
