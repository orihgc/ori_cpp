//
// Created by ByteDance on 2023/4/17.
//
#include "thread"
#include "iostream"
#include <unistd.h>


using namespace std;

void func() {
    for (int ii = 1; ii <= 5; ii++) {
        cout << ii<<endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main(){

    thread t1(func);
    pthread_t thid=t1.native_handle();
    pthread_cancel(thid);
    t1.join();
}