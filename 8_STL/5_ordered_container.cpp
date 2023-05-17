//
// Created by ByteDance on 2023/4/11.
//
#include "iostream"
/// 无序关联容器
#include "unordered_set"
#include "unordered_map"

/// 有序关联容器
#include "set"
#include "map"

using namespace std;

class Student {
public:
    Student(int id, string name) : _id(id), _name(name) {

    }

    bool operator<(const Student &stu) const {
        return _id < stu._id;
    }

private:
    int _id;
    string _name;

    friend ostream &operator<<(ostream &out, const Student &stu);
};

ostream &operator<<(ostream &out, const Student &stu) {
    out << "id:" << stu._id << "name:" << stu._name << stu._name << endl;
    return out;
}

int main() {


    return 0;
}
