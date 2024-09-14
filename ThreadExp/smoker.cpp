#include<bits/stdc++.h>
#include <semaphore>
/* 经典吸烟者问题
 * 一个系统有三个吸烟者与一个供应者
 * 制作烟需要三种材料:烟草，纸，胶水
 * 每个吸烟者分别自带一种材料
 * 每次供应者将两种材料放到桌面上,拥有剩下一种材料的抽烟者卷烟并抽掉, 桌上可以放若干烟
 * */
using namespace std;

#define LOOPNUM 20

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    counting_semaphore<1> mutex(1);
    counting_semaphore<1> smoker1(0);
    counting_semaphore<1> smoker2(0);
    counting_semaphore<1> smoker3(0);

    vector<int> turns;
    for(int i=0;i<LOOPNUM*3;i++){
        turns.push_back(i%3);
    }
    random_device rd;
    shuffle(turns.begin(),turns.end(),rd);

    thread producer([&mutex, &smoker1, &smoker2, &smoker3, &turns]{
        for(int i=0;i<LOOPNUM*3;i++){
            mutex.acquire();

            int turn = turns[i];
            string s = format("[producer]:prepared for smoker{}.\n", turn+1);
            cout << s;
            switch(turn){
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
            mutex.release();
        }
    });
    
    thread smoke1([&mutex, &smoker1]{
        for(int i=0; i<LOOPNUM;i++){
            smoker1.acquire();
            mutex.acquire();
            
            string s = format("[smoke1] smoke for {} time.\n", i+1);
            cout << s;
            
            mutex.release();
        }
    });
    thread smoke2([&mutex, &smoker2]{
        for(int i=0; i<LOOPNUM;i++){
            smoker2.acquire();
            mutex.acquire();
            
            string s = format("[smoke2] smoke for {} time.\n", i+1);
            cout << s;
            
            mutex.release();
        }
    });
    thread smoke3([&mutex, &smoker3]{
        for(int i=0; i<LOOPNUM;i++){
            smoker3.acquire();
            mutex.acquire();
            
            string s = format("[smoke3] smoke for {} time.\n", i+1);
            cout << s;
            
            mutex.release();
        }
    });

    producer.join();
    smoke1.join(); smoke2.join(); smoke3.join();
    return 0;
}
