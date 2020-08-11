#include <stack>
#include "list.hpp"

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // 对齐数位
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        while (p1 && p2) {
            p1 = p1->next;
            p2 = p2->next;
        }
        if (p2) {            // 把长的放到l1
            std::swap(l1, l2);
            p1 = p2;
        }
        int difference = 0;  // 计算长度差值
        while (p1) {
            p1 = p1->next;
            ++difference;
        }
        p2 = l2;             // l2前面补0使得l2和l1长度相同
        for (int i = 0; i < difference; ++i) {
            auto *t = new ListNode(0);
            t->next = p2;
            p2 = t;
        }

        // 把对齐的低位相加
        int carry = 0;
        ListNode *result = addTwoAligningNumbers(l1, p2, carry);

        // 处理低段可能存在的进位
        if (0 != carry) {
            auto *t = new ListNode(carry);
            t->next = result;
            result = t;
        }

        // 将l2前面补的0释放掉
        while (p2 != l2) {
            ListNode *t = p2->next;
            delete p2;
            p2 = t;
        }

        return result;
    }

private:
    ListNode *addTwoAligningNumbers(ListNode *l1, ListNode *l2, int &carry) {
        if (!l1 || !l2) {
            carry = 0;
            return nullptr;
        }

        int c = 0;
        ListNode *temp = addTwoAligningNumbers(l1->next, l2->next, c);
        int curr = l1->val + l2->val + c;
        carry = curr / 10;
        auto *result = new ListNode(curr % 10);
        result->next = temp;
        return result;
    }
};

class Solution1 {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        std::stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }

        ListNode *result = nullptr;
        int carry = 0;
        while (!s1.empty() && !s2.empty()) {
            int temp = s1.top() + s2.top() + carry;
            carry = temp / 10;
            auto *t = new ListNode(temp % 10);
            t->next = result;
            result = t;
            s1.pop();
            s2.pop();
        }
        while (!s1.empty()) {
            int temp = s1.top() + carry;
            carry = temp / 10;
            auto *t = new ListNode(temp % 10);
            t->next = result;
            result = t;
            s1.pop();
        }
        while (!s2.empty()) {
            int temp = s2.top() + carry;
            carry = temp / 10;
            auto *t = new ListNode(temp % 10);
            t->next = result;
            result = t;
            s2.pop();
        }
        if (carry) {
            auto *t = new ListNode(carry);
            t->next = result;
            result = t;
        }

        return result;
    }
};

int main() {
    // 7->8->0->7
    ListNode *l1 = CreateList({7, 2, 4, 3});
    ListNode *l2 = CreateList({5, 6, 4});

    Solution1 solution;
    ListNode *r1 = solution.addTwoNumbers(l1, l2);
    PrintList(r1);

    DestroyList(l1);
    DestroyList(l2);
    DestroyList(r1);
    return 0;
}
