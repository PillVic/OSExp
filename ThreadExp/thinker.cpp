#include <bits/stdc++.h>

using namespace std;
/* 多线程经典问题: 哲学家思考问题
 * 5个哲学家坐在圆桌前,每个人左右均有一根筷子
 * 仅当哲学家饥饿时需要拿到左右手筷子吃饭, 不饿时进行思考
 * */
#define LOOPNUM 20

int main(void) {
    ios::sync_with_stdio(false);

    const int THINKER_NUM = 5;
    sem_t chopsticks[THINKER_NUM];
    for (int i = 0; i < THINKER_NUM; i++) {
        sem_init(chopsticks + i, 0, 1);
    }
    counting_semaphore<1> mutex(1);

    // 缓冲区输出需要用信号量进行互斥使用
    counting_semaphore<1> printMutex(1);
    auto mutexPrint = [&printMutex](const string& s) {
        printMutex.acquire();
        cout << s;
        printMutex.release();
    };

    auto thinkerProcess = [&chopsticks, &mutex, &mutexPrint,
                           &printMutex](const int& id) {
        mt19937 generater;

        int left = id;
        int right = (id + 1) % THINKER_NUM;
        for (int i = 0; i < LOOPNUM; i++) {
            int choice = generater() % 2;
            if (choice == 0) {
                mutexPrint(format("[thinker{}]: thinking.\n", id + 1));
            } else {
                mutex.acquire();
                sem_wait(chopsticks + left);
                sem_wait(chopsticks + right);

                mutexPrint(format("[thinker{}]: eating.\n", id + 1));

                sem_post(chopsticks + left);
                sem_post(chopsticks + right);
                mutex.release();
            }
        }
        mutexPrint(format("[thinker{}:die.\n", id + 1));
    };

    vector<thread> threads;
    for (int i = 0; i < THINKER_NUM; i++) {
        threads.push_back(thread(thinkerProcess, i));
    }

    for (auto& t : threads) {
        t.join();
    }

    // 使用完需要销毁信号量(信号量在系统内核中)
    for (int i = 0; i < THINKER_NUM; i++) {
        sem_destroy(chopsticks + i);
    }
    return 0;
}
