#include <utility>

#include "map"
#include "unordered_map"
#include "string"
#include "iostream"

using namespace std;

class Client {


public:
    explicit Client(std::string name) : name_(std::move(name)) {}

private:
    std::string name_;
};

class Window {
public:
    explicit Window(std::string name) : name_(std::move(name)) {}

public:
    std::string name_;

};

class Key {
public:

    explicit Key(std::string name) : name_(std::move(name)) {}

    std::string name_;

};

class Value {
public:
    explicit Value(std::string name) : name_(std::move(name)) {}

    std::string name_;

};

int main() {
    unordered_map<int ,string> map;
    map.insert({1,"ori"});
    auto it=map.find(2);
    if (it!=map.end()){
        cout<<"success";
    }
}