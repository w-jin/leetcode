#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *CreateList(std::initializer_list<int> l) {
    if (l.size() == 0)
        return nullptr;
    auto *head = new ListNode(*l.begin());
    ListNode *p = head;
    for (auto it = l.begin() + 1; it != l.end(); ++it) {
        p->next = new ListNode(*it);
        p = p->next;
    }
    return head;
}

void PrintList(ListNode *head) {
    while (head != nullptr) {
        std::cout << head->val;
        if (head->next != nullptr)
            std::cout << "->";
        head = head->next;
    }
    std::cout << std::endl;
}

void DestroyList(ListNode *head) {
    ListNode *p = nullptr;
    while (head != nullptr) {
        p = head->next;
        delete head;
        head = p;
    }
}

class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        return head;
    }
};

int main() {
    // 1->2->2->4->3->5
    ListNode *list = CreateList({1, 4, 3, 2, 5, 2});
    int x = 3;

    Solution solution;
    ListNode *result = solution.partition(list, x);
    PrintList(result);

    DestroyList(result);
    return 0;
}
