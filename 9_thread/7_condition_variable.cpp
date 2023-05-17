//
// Created by ByteDance on 2023/4/24.
//

#include "iostream"
#include "deque"
#include <mutex>
#include "thread"
#include "queue"
#include "condition_variable"


using namespace std;

class PC {
private:
    mutex m_mutex;
    condition_variable m_cond;
    queue<string, deque<string> > m_q;
public:
    void InCache(int num) {
        lock_guard<mutex> lock(m_mutex);
        for (int i = 0; i < num; i++) {
            static int bn = 1;
            string message = to_string(bn++) + "号超女";//拼接处一个数据
            m_q.push(message);//将生产的数据入队
        }
//        m_cond.notify_one();//唤醒一个当前被条件变量阻塞的线程
        m_cond.notify_all();
    }

    void OutCache() {
        while (true) {
            string message;
            {
                cout << "线程" << this_thread::get_id() << ",申请加锁..."<<endl;
                ///普通的互斥锁一定要转为unique_lock后才能应用于条件变量
                unique_lock<mutex> lock(m_mutex);
                cout << "线程" << this_thread::get_id() << ",加锁成功。"<<endl;

//                while (m_q.empty()) {
//                    m_cond.wait(lock);///1、把互斥锁解锁 2、阻塞，等待被唤醒 3、唤醒后给互斥锁加锁
//                }
                m_cond.wait(lock,[this]{return !m_q.empty();});//和上面的效果相同
                message = m_q.front();
                m_q.pop();
                cout << "线程" << this_thread::get_id() << "," << message << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1));
        }
    }
};

int main() {
    PC pc;
    thread t1(&PC::OutCache, &pc);
    thread t2(&PC::OutCache, &pc);
    thread t3(&PC::OutCache, &pc);

//    this_thread::sleep_for(chrono::seconds(2));
//    pc.InCache(3);
//
//    this_thread::sleep_for(chrono::seconds(3));
//    pc.InCache(5);
//
//    this_thread::sleep_for(chrono::seconds(3));
//    pc.InCache(5);

    t1.join();
    t2.join();
    t3.join();
}
