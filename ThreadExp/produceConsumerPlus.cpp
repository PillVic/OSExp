#include<bits/stdc++.h>

using namespace std;
/*复杂生产者消费者问题:
 * 有一个盘子,妈妈放橘子，爸爸放苹果，儿子吃橘子，女儿吃苹果
 * 当且仅当盘子为空，父母才可放水果
 * 当且仅当盘子非空，子女才可取用自己的水果
 */

#define LOOPNUM 100

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    counting_semaphore<1> empty(1);
    counting_semaphore<1> full(0);
    counting_semaphore<1> apple(0);
    counting_semaphore<1> orange(0);

    thread mother([&empty, &orange]{
        for(int i=0;i<LOOPNUM;i++){
            empty.acquire();
            
            string s = format("[mother]:put an orange.\n");
            cout << s;

            orange.release();
        }
    });

    thread father([&full, &empty, &apple]{
        for(int i=0;i<LOOPNUM;i++){
            empty.acquire();

            string s = format("[father]:put an apple.\n");
            cout << s;

            apple.release();
        }
    });

    thread son([&empty, &orange]{
        for(int i=0;i<LOOPNUM;i++){
            orange.acquire();

            string s = "[son]:eat an orange.\n";
            cout << s;

            empty.release();
        }
    });

    thread daughter([&full, &empty, &apple]{
        for(int i=0;i<LOOPNUM;i++){
            apple.acquire();

            string s = "[daughter]:eat an apple.\n";
            cout << s;

            empty.release();
        }
    });

    father.join();
    mother.join();
    son.join();
    daughter.join();
    return 0;
}
