#include <bits/stdc++.h>

using namespace std;
/* 多线程经典问题: 读写者问题
 * 若干读者进程与写者进程, 读不互斥，写者之间相互互斥, 且写时不可读
 * */
#define LOOPNUM 10

int main(void) {
    ios::sync_with_stdio(false);

    int readCount = 0;
    counting_semaphore<1> writeMutex(1);
    counting_semaphore<1> readCountMutex(1);

    auto writeProcess = [&writeMutex](const string& name) {
        for (int i = 0; i < LOOPNUM; i++) {
            writeMutex.acquire();

            string s = format("{}: write {} time.\n", name, i + 1);
            cout << s;

            writeMutex.release();
        }
    };
    auto readProcess = [&writeMutex, &readCountMutex,
                        &readCount](const string& name) {
        for (int i = 0; i < LOOPNUM; i++) {
            readCountMutex.acquire();
            if (readCount == 0) {
                writeMutex.acquire();
            }
            readCount++;
            readCountMutex.release();

            string s = format("{}: read {} time.\n", name, i + 1);
            cout << s;
            readCountMutex.acquire();
            readCount--;
            if (readCount == 0) {
                writeMutex.release();
            }
            readCountMutex.release();
        }
    };

    thread writer1(writeProcess, "[writer1]");
    thread writer2(writeProcess, "[writer2]");
    thread writer3(writeProcess, "[writer3]");
    thread reader1(readProcess, "[reader1]");
    thread reader2(readProcess, "[reader2]");
    thread reader3(readProcess, "[reader3]");

    writer1.join();
    writer2.join();
    writer3.join();
    reader1.join();
    reader2.join();
    reader3.join();

    return 0;
}
