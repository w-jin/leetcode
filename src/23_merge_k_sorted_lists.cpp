#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "list.hpp"

/* Solution和Solution1都是直接比较所有链表第一个元素的做法，Solution1错误地使用了临时头节点。
 * 时间复杂度O(m * N)，m为总的元素个数，n为链表个数。 */
class Solution {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        //添加临时节点
        std::vector<ListNode *> heads(lists.size(), nullptr);
        for (int i = 0; i < heads.size(); ++i) {
            heads[i] = new ListNode(-1);
            heads[i]->next = lists[i];
        }

        //合并
        ListNode *result = new ListNode(-1);
        ListNode *r = result;
        while (true) {
            int min = 0x7fffffff;
            int min_i = -1;
            for (int i = 0; i < heads.size(); ++i) {
                if (heads[i]->next != nullptr && min >= heads[i]->next->val) {
                    min = heads[i]->next->val;
                    min_i = i;
                }
            }
            if (min == 0x7fffffff)
                break;

            r->next = heads[min_i]->next;
            heads[min_i]->next = heads[min_i]->next->next;
            r = r->next;
        }

        //删除临时头节点
        for (auto &head : heads)
            delete head;
        ListNode *temp = result;
        result = result->next;
        delete temp;

        return result;
    }
};

class Solution1 {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        //并不需要添加临时头节点
        ListNode *result = new ListNode(-1);
        ListNode *r = result;
        while (true) {
            int min = 0x7fffffff;
            int min_i = -1;
            for (int i = 0; i < lists.size(); ++i)
                if (lists[i] != nullptr && min > lists[i]->val) {
                    min_i = i;
                    min = lists[i]->val;
                }
            if (min_i < 0)
                break;

            r->next = lists[min_i];
            lists[min_i] = lists[min_i]->next;
            r = r->next;
        }

        ListNode *temp = result;
        result = result->next;
        delete temp;

        return result;
    }
};

/* Solution和Solution1中，每次选取所有链表第一个节点的最小值时，除第一次外都只有一个新值，其它元素都是比较过的。
 * 所以大量的比较都浪费了，为改进性能，对链表第一个元素维护一个小顶堆，每次将堆顶元素取出，剩下的元素重新建堆，
 * 时间复杂度为O(log(N))，总的时间复杂度为O(N + m * log(N)) */
class Solution2 {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        if (lists.empty())
            return nullptr;

        ListNode *result = new ListNode(-1);
        ListNode *r = result;

        //创建小顶堆
        std::make_heap(lists.begin(), lists.end(), compare);
        //每次取最小的元素
        while (lists[0] != nullptr) {
            //移动最小元素到末尾
            std::pop_heap(lists.begin(), lists.end(), compare);
            r->next = lists[lists.size() - 1];
            lists[lists.size() - 1] = lists[lists.size() - 1]->next;
            r = r->next;
            //执行pop_heap后前n-1个元素已成堆，加入一个元素重新建堆
            std::push_heap(lists.begin(), lists.end(), compare);
        }

        ListNode *temp = result;
        result = result->next;
        delete temp;
        return result;
    }

private:
    //用于建立小顶堆，较小的元素放前面，较大的放后面，空指针放后面
    static bool compare(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr)
            return true;
        if (l2 == nullptr)
            return false;
        return l1->val > l2->val;
    }
};

/* 和Solution2一样的思路，但是使用优先队列来寻找队首元素的最小值。
 * 注意：优先队列一般用堆来实现，但是比堆更加易于使用，这个版本和Solution2几乎没有区别。 */
class Solution3 {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        ListNode *result = new ListNode(-1);
        ListNode *r = result;

        //以链表首节点建立优先队列，较小的数排前面
        auto compare = [](const ListNode *l1, const ListNode *l2) { return l1->val > l2->val; };
        std::priority_queue<ListNode *, std::vector<ListNode *>, decltype(compare)> front(compare);
        for (ListNode *l : lists)
            if (l != nullptr)
                front.push(l);

        while (!front.empty()) {
            ListNode *min = front.top();
            front.pop();
            r->next = min;
            r = r->next;
            if (min->next != nullptr)
                front.push(min->next);
        }

        ListNode *temp = result;
        result = result->next;
        delete temp;
        return result;
    }
};

/* 使用分治法，将要合并的链表分为两部分，对左半部分和右半部分分别进行合并，再将结果合并。
 * 时间复杂度：T(N) = 2T(N/2) + O(m) = O(N + m * log(N))。 */
class Solution4 {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        if (lists.empty())
            return nullptr;
        return mergeKListsRecursive(lists, 0, static_cast<int>(lists.size() - 1));
    }

private:
    //递归的合并链接，先合并左半部分，再合并右半部分，再将这两个结果合并
    ListNode *mergeKListsRecursive(std::vector<ListNode *> &lists, int first, int last) {
        if (first == last)
            return lists[first];
        if (first + 1 == last)
            return mergeTwoLists(lists[first], lists[last]);

        int mid = (first + last) / 2;
        ListNode *r1 = mergeKListsRecursive(lists, first, mid);
        ListNode *r2 = mergeKListsRecursive(lists, mid + 1, last);
        return mergeTwoLists(r1, r2);
    }

    //合并两个链表
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *result;
        if (l1->val <= l2->val) {
            result = l1;
            l1 = l1->next;
        } else {
            result = l2;
            l2 = l2->next;
        }

        ListNode *r = result;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                r->next = l1;
                l1 = l1->next;
                r = r->next;
            } else {
                r->next = l2;
                l2 = l2->next;
                r = r->next;
            }
        }

        if (l1 != nullptr)
            r->next = l1;
        else // l2 != nullptr
            r->next = l2;

        return result;
    }
};

/*
 * Solution4的循环版本，leetcode的测试中没什么区别
 */
class Solution5 {
public:
    ListNode *mergeKLists(std::vector<ListNode *> &lists) {
        if (lists.empty())
            return nullptr;
        while (lists.size() > 1) {
            int i = 0;
            for (i = 0; i < lists.size() / 2; ++i)
                lists[i] = mergeTwoLists(lists[2 * i], lists[2 * i + 1]);
            if (lists.size() % 2 == 1)
                lists[i++] = lists.back();
            lists.erase(lists.begin() + i, lists.end());
        }
        return lists[0];
    }

private:
    //合并两个链表
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr)
            return l2;
        if (l2 == nullptr)
            return l1;

        ListNode *result = nullptr;
        if (l1->val <= l2->val) {
            result = l1;
            l1 = l1->next;
        } else {
            result = l2;
            l2 = l2->next;
        }

        ListNode *r = result;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val <= l2->val) {
                r->next = l1;
                l1 = l1->next;
                r = r->next;
            } else {
                r->next = l2;
                l2 = l2->next;
                r = r->next;
            }
        }

        if (l1 != nullptr)
            r->next = l1;
        else // l2 != nullptr
            r->next = l2;

        return result;
    }
};

int main() {
    /* 
    输入:
        [
         1->4->5,
         1->3->4,
         2->6
        ]
    输出: 1->1->2->3->4->4->5->6
    */
    std::vector<ListNode *> lists(4, nullptr);
    lists[0] = CreateList({1, 4, 5});
    lists[1] = CreateList({1, 3, 4});
    lists[2] = CreateList({2, 6});

    Solution5 solution;
    ListNode *result = solution.mergeKLists(lists);

    PrintList(result);
    DestroyList(result);

    return 0;
}
