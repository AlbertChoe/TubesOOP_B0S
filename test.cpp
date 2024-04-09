#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class A {
protected:
    int num;
public:
    A(int _num) : num(_num) {}
    virtual ~A() = default;
    int getNum() {
        return num;
    }
    void setNum(int _num) {
        num = _num;
    }
    virtual int getType() = 0;
};

class B : public A {
public:
    B(int _num) : A(_num) {}
    int getType() override {
        return 1;
    }
};

class C : public A {
public:
    C(int _num) : A(_num) {}
    int getType() override {
        return 2;
    }
};

int main() {
    auto b = make_shared<B>(100);
    vector<shared_ptr<A>> list;  // Store pointers to A
    list.push_back(b);
    auto c = list[0];
    c->setNum(3);

    // Directly access functions
    cout << "Num: " << c->getNum() << ", Type: " << c->getType() << endl;
    cout << "Num: " << list[0]->getNum() << ", Type: " << list[0]->getType() << endl;
    list.pop_back();
    cout << list.size() << endl;
}
