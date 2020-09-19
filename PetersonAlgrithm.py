#!/usr/bin/python3
import threading
import time

def printHello(threadName, counter, delay):
    while counter:
        if exitFlag:
            threadName.exit()
        time.sleep(delay)
        print("Thread Name: %s %d"%(threadName, counter))
        counter -= 1

exitFlag = 0
flag = [False, False]
turn = 0
class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):
        print ("开始线程：" + self.name)
        flag[self.threadID]=True
        turn = (self.threadID+1)%2
        while flag[self.threadID] and turn == self.threadID:
            pass
        #critical section
        printHello(self.name, self.counter, 0)

        flag[self.threadID] = False
        print ("退出线程：" + self.name)
# 创建新线程
thread1 = myThread(0, "Thread-1", 50)
thread2 = myThread(1, "Thread-2", 50)

# 开启新线程
thread1.start()
thread2.start()
thread1.join()
thread2.join()
print ("退出主线程")
