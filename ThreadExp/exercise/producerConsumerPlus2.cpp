#include <bits/stdc++.h>

using namespace std;
/* 2014 信号量编程大题
 * 缓冲区可以存放1000件产品, 生产者在缓冲区未满时可以放入一件, 否则等待,
 * 缓冲区非空时，消费者进程可以从缓冲区取走一件产品, 否则等待,
 * 要求一个消费者进程从缓冲区连续取出10件产品后，其他消费者才可以取出产品
 * */

const int BUFFER_MAX = 1000;

const int PRODUCE_NUM = 10000;
const int CONSUME_NUM = 100;
const int CONSUMER_NUM = PRODUCE_NUM / (CONSUME_NUM * 10);

int main(void) {
    counting_semaphore<1> mutex(1);
    counting_semaphore<BUFFER_MAX> empty(BUFFER_MAX);
    counting_semaphore<BUFFER_MAX> full(0);
    counting_semaphore<1> consumerMutex(1);
    queue<int> buffer;

    thread producer([&mutex, &empty, &full, &buffer]() {
        mt19937 generator;

        for (int i = 0; i < PRODUCE_NUM; i++) {
            empty.acquire();
            mutex.acquire();

            buffer.push(generator() % 10000);
            cout << format("[producer] {} in, size:{}, rest:{}.\n",
                           buffer.front(), buffer.size(), PRODUCE_NUM - i - 1);
            full.release();
            mutex.release();
        }

        cout << format("[producer]: die.\n");
    });

    auto consumerProcess = [&mutex, &consumerMutex, &empty, &full,
                            &buffer](const int& id) {
        cout << format("[{}]: create.\n", id);
        for (int i = 0; i < CONSUME_NUM; i++) {
            consumerMutex.acquire();
            cout << format("[{}]: get consumer lock.\n", id);
            for (int j = 0; j < 10; j++) {
                full.acquire();
                mutex.acquire();

                cout << format(
                    "[{}]: {} out, buffer size:{}, consume num:{}-{}.\n", id,
                    buffer.front(), buffer.size(), i + 1, j + 1);
                buffer.pop();
                empty.release();
                mutex.release();
            }
            cout << format("[{}]: release consumer lock.\n", id);
            consumerMutex.release();
        }
        cout << format("[{}]: die.\n", id);
    };

    vector<thread> consumers;
    for (int i = 0; i < CONSUMER_NUM; i++) {
        consumers.push_back(thread(consumerProcess, i));
    }

    for (auto& consumer : consumers) {
        consumer.join();
    }
    producer.join();
    return 0;
}
