#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using std::vector;
using std::unordered_set;
using std::unordered_map;

// 推文类，组织成一个链表
struct Tweet {
    static int global_time;  // 全局时间，每封推文的时间都不一样

    int id;          // 推文id
    int time_stamp;  // 时间戳，全局唯一
    Tweet *next;

    explicit Tweet(int id) {
        this->id = id;
        time_stamp = global_time++;
        next = nullptr;
    }

    ~Tweet() {
        delete next;
    }
};

int Tweet::global_time = 0;

struct User {
    int id;                       // 用户id
    Tweet *tweets;                // 推文列表，组织成一个链表
    unordered_set<int> follows;   // 此用户关注的用户列表

    explicit User(int id) {
        this->id = id;
        tweets = nullptr;
    }

    // 关注一个用户
    void follow(int followee_id) {
        if (id != followee_id)    // 不能关注自己
            follows.insert(followee_id);
    }

    // 取关一个用户
    void unfollow(int followee_id) {
        if (id != followee_id)    // 不能取关自己
            follows.erase(followee_id);
    }

    // 发一个推文
    void post(int tweet_id) {
        auto *new_tweet = new Tweet{tweet_id};
        new_tweet->next = tweets;
        tweets = new_tweet;
    }
};

class Twitter {
private:
    // 用户列表，不能直接使用User作为值的类型，因为它没有默认构造函数
    unordered_map<int, User *> users;

    bool exist(int user_id) {
        return users.find(user_id) != users.end();
    }

public:
    void postTweet(int user_id, int tweet_id) {
        if (!exist(user_id))
            users[user_id] = new User{user_id};
        users[user_id]->post(tweet_id);
    }

    vector<int> getNewsFeed(int user_id) {
        if (!exist(user_id))
            return {};

        // 构造大顶堆，注意比较函数应当是小于操作
        auto cmp = [](const Tweet *a, const Tweet *b) -> bool {
            return a->time_stamp < b->time_stamp;
        };
        std::priority_queue<Tweet *, vector<Tweet *>, decltype(cmp)> q(cmp);
        for (int followee_id : users[user_id]->follows) {
            if (exist(followee_id) && users[followee_id]->tweets)
                q.push(users[followee_id]->tweets);
        }
        if (users[user_id]->tweets)
            q.push(users[user_id]->tweets);

        vector<int> result;
        int n = 0;
        while (n < 10 && !q.empty()) {
            Tweet *t = q.top();
            q.pop();
            result.push_back(t->id);
            if (t->next)
                q.push(t->next);
            ++n;
        }

        return result;
    }

    void follow(int follower_id, int followee_id) {
        if (!exist(follower_id))
            users[follower_id] = new User{follower_id};
        users[follower_id]->follow(followee_id);
    }

    void unfollow(int follower_id, int followee_id) {
        if (exist(follower_id))
            users[follower_id]->unfollow(followee_id);
    }

    ~Twitter() {
        for (auto p : users)
            delete p.second;
    }
};

int main() {
    return 0;
}


