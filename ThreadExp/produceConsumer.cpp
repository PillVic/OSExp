#include<bits/stdc++.h>
#include<thread>
#include<semaphore>

using namespace std;
/* 经典多线程问题: 生产者消费者问题
 * */
#define LOOPNUM  100

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int itemNum = 0;
    const int bufferNum = 10;

    counting_semaphore<1> mutex(1);
    counting_semaphore<1> empty(bufferNum);
    counting_semaphore<1> full(0);

    
    thread producer([&mutex, &empty, &full, &itemNum]{
        for(int i=0;i<LOOPNUM;i++){
            empty.acquire();
            mutex.acquire();

            string s = format("[producer]: {}+1.\n", itemNum);
            itemNum++;
            cout << s;

            mutex.release();
            full.release();
        }
    });
    
    thread consumer([&mutex, &empty, &full, &itemNum]{
        for(int i=0;i<LOOPNUM;i++){
           full.acquire();
           mutex.acquire();

           string s = format("[consumer]:{}-1.\n", itemNum);
           itemNum--;
           cout << s;

           mutex.release();
           empty.release();
        }
    });

    consumer.join();
    producer.join();
    return 0;
}
