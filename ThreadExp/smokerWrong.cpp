#include <bits/stdc++.h>
/* 经典吸烟者问题
 * 一个系统有三个吸烟者与一个供应者
 * 制作烟需要三种材料:烟草，纸，胶水
 * 每个吸烟者分别自带一种材料
 * 每次供应者将两种材料放到桌面上,拥有剩下一种材料的抽烟者卷烟并抽掉
 *
 * 此处为课本的方案(执行会发现有先吸烟后提供烟的错误)
 * */
using namespace std;

#define LOOPNUM 20

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    counting_semaphore<1> smoker1(0);
    counting_semaphore<1> smoker2(0);
    counting_semaphore<1> smoker3(0);
    counting_semaphore<0> empty(0);

    vector<int> turns;
    for (int i = 0; i < LOOPNUM * 3; i++) {
        turns.push_back(i % 3);
    }
    random_device rd;
    shuffle(turns.begin(), turns.end(), rd);

    thread producer([&empty, &smoker1, &smoker2, &smoker3, &turns] {
        for (int i = 0; i < LOOPNUM * 3; i++) {
            int turn = turns[i];
            switch (turn) {
                case 0:
                    smoker1.release();
                    break;
                case 1:
                    smoker2.release();
                    break;
                case 2:
                    smoker3.release();
                    break;
            }
            string s = format("[producer]:prepared for smoker{}.", turn + 1);
            cout << s;

            empty.acquire();
        }
    });

    auto smokeProcess = [&empty, &smoker1, &smoker2, &smoker3](const int& id) {
        for (int i = 0; i < LOOPNUM; i++) {
            switch (id) {
                case 1:
                    smoker1.acquire();
                    break;
                case 2:
                    smoker2.acquire();
                    break;
                case 3:
                    smoker3.acquire();
                    break;
            }

            string s = format("[smoke{}] smoke for {} time.\n", id, i + 1);
            cout << s;

            empty.release();
        }
    };
    thread smoke1(smokeProcess, 1);
    thread smoke2(smokeProcess, 2);
    thread smoke3(smokeProcess, 3);

    producer.join();
    smoke1.join();
    smoke2.join();
    smoke3.join();
    return 0;
}
