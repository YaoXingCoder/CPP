/*************************************************************************
    > File Name: 04_observe_mode.cpp
    > Author: JiaZiChunQiu
    > Created Time: 2024年09月12日 星期四 21时19分58秒
    > Mail: JiaZiChunQiu@163.com
    > Title: 观察者模式
    > Content:
 ************************************************************************/

#include <iostream>
#include <list>
#include <memory>
#include <string>

class Observer {
  public:
    virtual void update(int status) = 0;
    virtual ~Observer() {}
};

class ConcreateObserverA : public Observer {
  public:
    ConcreateObserverA(const std::string &name) : _name(name) {}

    void update(int status) override {
        std::cout << "ConcreateObserverA" << _name << ", " << status
                  << std::endl;
    }

    ~ConcreateObserverA() override {}

  private:
    std::string _name;
};

class ConcreateObserverB : public Observer {
  public:
    ConcreateObserverB(const std::string &name) : _name(name) {}

    void update(int status) override {
        std::cout << "ConcreateObserverB" << _name << ", " << status
                  << std::endl;
    }
    ~ConcreateObserverB() override {}

  private:
    std::string _name;
};

class Subject {
  public:
    virtual void attach(Observer *pObserver) = 0; // 添加
    virtual void detach(Observer *pObserver) = 0; // 删除
    virtual void notify() = 0;                    // 通知
    virtual ~Subject() {}
};

class ConSubject : public Subject {
  public:
    ConSubject() {}
    void setStatus(int status) { _status = status; }
    void getStatus(int status) { _status = status; }

  public:
    void attach(Observer *pObserver) {
        if (pObserver) {
            _Oblist.push_back(pObserver);
        }
    } // 添加
    void detach(Observer *pObserver) {
        if (pObserver) {
            _Oblist.remove(pObserver);
        }
    } // 删除
    void notify() {
        for (Observer *pobs : _Oblist) {
            pobs->update(_status);
        }
    } // 通知
    ~ConSubject() {
        if (!_Oblist.empty()) {
            for (Observer *pobs : _Oblist) {
                if (pobs) {
                    delete pobs;
                    pobs = nullptr;
                    // _Oblist.remove(pobs); // 会使迭代器失效, for循环会出错
                }
            }
        }
        std::cout << "~ConSubject()" << std::endl;
    }

  private:
    std::list<Observer *> _Oblist; // 观察主题的观察者列表
    int _status;                   // 状态
};

/* =============== test =============== */
void test0() {
    std::unique_ptr<ConSubject> up_subj(new ConSubject());
    up_subj->attach(new ConcreateObserverA("lili"));
    up_subj->attach(new ConcreateObserverB("lucy"));

    up_subj->setStatus(1);
    up_subj->notify();
}
/* =============== main =============== */
int main(int argc, char *argv[]) {
    test0();
    return 0;
}
