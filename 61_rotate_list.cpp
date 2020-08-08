#include <iostream>
#include "list.hpp"

class Solution {
public:
	ListNode *rotateRight(ListNode *head, int k) {
        //统计链表的长度
        int len = 0;
        for (ListNode *p = head; p != nullptr; p = p->next)
            ++len;

        if (len == 0)
            return nullptr;

        //计算实际要移动的量，以len为周期，每len次回到原位
        k = k % len;

        //把末尾k个放到开头
        ListNode *p = head, *q = head;
        for (int i = 0; i < k; ++i)
            q = q->next;
        while (q->next != nullptr) {
            p = p->next;
            q = q->next;
        }
        //现在p已经指向倒数第k个节点的前驱，q指向最后一个节点，把末尾k个放到开头即可
        q->next = head;
        q = p->next;
        p->next = nullptr;

        return q;
	}
};

class Solution1 {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == nullptr)
            return nullptr;

        //统计链表的长度
        int len = 1;
        ListNode *p = head;
        while (p->next != nullptr) {
            p = p->next;
            ++len;
        }

        //计算实际要移动的量，以len为周期，每len次回到原位
        k = k % len;

        //现在p已经指向最后一个节点，把末尾k个放到开头即可
        p->next = head;
        for (int i = 0; i < len - k; ++i)
            p = p->next;
        head = p->next;
        p->next = nullptr;

        return head;
    }
};


int main() {
    Solution1 solution;

    //4->5->1->2->3
	ListNode *head1 = CreateList({1, 2, 3, 4, 5});
	int k1 = 2;
	//2->0->1
	ListNode *head2 = CreateList({0, 1, 2});
	int k2 = 4;

	ListNode *l1 = solution.rotateRight(head1, k1);
	ListNode *l2 = solution.rotateRight(head2, k2);

	PrintList(l1);
	PrintList(l2);

	DestroyList(l1);
	DestroyList(l2);
	return 0;
}

