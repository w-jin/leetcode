/*
 * 此头文件实现一个简单的链表及相关操作。
 */
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <initializer_list>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

inline ListNode *CreateList(std::initializer_list<int> l) {
    if (l.size() == 0)
        return nullptr;
    auto *head = new ListNode(*l.begin());
    ListNode *p = head;
    for (const auto *it = l.begin() + 1; it != l.end(); ++it) {
        p->next = new ListNode(*it);
        p = p->next;
    }
    return head;
}

inline ListNode *CreateListWithHead(std::initializer_list<int> l) {
    auto *head = new ListNode{0};
    ListNode *p = head;
    for (int n : l) {
        p->next = new ListNode(n);
        p = p->next;
    }
    return head;
}

inline void PrintList(ListNode *head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr)
            std::cout << "->";
        head = head->next;
    }
    std::cout << std::endl;
}

inline void PrintListWithHead(ListNode *head) {
    PrintList(head->next);
}

inline void DestroyList(ListNode *head) {
    while (head != nullptr) {
        ListNode *t = head->next;
        delete head;
        head = t;
    }
}

#endif // LIST_H
