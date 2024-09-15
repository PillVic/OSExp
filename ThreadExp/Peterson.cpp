#include <bits/stdc++.h>

using namespace std;
/* 多线程经典算法:皮特森算法, 由于指令重排，在当今机器架构下已经失效
 * */
#define LOOPNUM 200

int main(void) {
    ios::sync_with_stdio(false);
    bool flag[2] = {false, false};
    int turn = 0;

    auto process = [&flag, &turn](const int& id, const string& c) {
        for (int i = 0; i < LOOPNUM; i++) {
            flag[id] = true;
            turn = (id + 1) % 2;
            while (flag[id] and id == turn);

            cout << c;
            cout.flush();

            flag[id] = false;
        }
    };

    thread t1(process, 0, "A");
    thread t2(process, 1, "B");

    t1.join();
    t2.join();
    return 0;
}
