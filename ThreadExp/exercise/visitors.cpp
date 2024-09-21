#include <bits/stdc++.h>
#include <unistd.h>

/*
 * 2013 信号量编程大题
 * 一个可容纳500人的博物馆，只有一个出入口且每次只能进出一个人
 * */

const int MUSEUM_CONTAIN = 11;
const int PEOPLE_NUM = 101;

const int MAX_VISIT_TIME = 5;

int main(void) {
    using namespace std;

    counting_semaphore<1> mutex(1);
    counting_semaphore<MUSEUM_CONTAIN> museum(MUSEUM_CONTAIN);

    counting_semaphore<1> printMutex(1);
    auto mutexPrint = [&printMutex](const string &s) {
        printMutex.acquire();
        cout << s;
        printMutex.release();
    };

    mt19937 generator;
    auto visitorProcess = [&mutex, &museum, &mutexPrint,
                           &generator](const int &id) {
        museum.acquire();
        mutex.acquire();

        cout << format("[{}]: in.\n", id);
        int visitTime = (generator() % MAX_VISIT_TIME) + 1;
        mutex.release();

        mutexPrint(format("[{}]: visiting for {} second.\n", id, visitTime));
        sleep(visitTime);

        mutex.acquire();
        cout << format("[{}]: out.\n", id);
        mutex.release();
        museum.release();
    };

    vector<thread> visitors;
    for (int i = 0; i < PEOPLE_NUM; i++) {
        visitors.push_back(thread(visitorProcess, i));
    }

    for (auto &t : visitors) {
        t.join();
    }
    cout <<"done.\n";
    return 0;
}
