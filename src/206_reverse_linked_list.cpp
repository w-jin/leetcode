#include "list.hpp"

/*
    循环翻转链表
*/
class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        while (curr) {
            ListNode *t = curr->next;
            curr->next = prev;
            prev = curr;
            curr = t;
        }
        return prev;
    }
};

/*
    递归翻转链表
*/
class Solution1 {
public:
    ListNode *reverseList(ListNode *head) {
        if (!head || !head->next)
            return head;
        ListNode *t = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return t;
    }
};

int main() {
    // 5->4->3->2->1
    ListNode *head1 = CreateList({1, 2, 3, 4, 5});

    Solution1 solution;
    ListNode *result1 = solution.reverseList(head1);

    PrintList(result1);

    DestroyList(result1);
    return 0;
}
