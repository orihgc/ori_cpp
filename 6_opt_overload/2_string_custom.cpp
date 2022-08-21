
#include <iostream>
#include <string>

using namespace std;

///自实现一个字符串对象
class String {
public:
    String(const char *p = nullptr) {
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        } else {
            _pstr = new char[1];
            *_pstr = '\0';
        }
    }

    ~String() {
        delete[] _pstr;
        _pstr = nullptr;
    }

    String(const String &str) {
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }

    String &operator=(const String &str) {
        if (this == &str)return *this;
        delete[]_pstr;
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
        return *this;
    }


    bool operator>(const String &str) const {
        return strcmp(_pstr, str._pstr) > 0;
    }

    bool operator<(const String &str) const {
        return strcmp(_pstr, str._pstr) < 0;
    }

    bool operator==(const String &str) const {
        return strcmp(_pstr, str._pstr) == 0;
    }

    int length() const {
        return strlen(_pstr);
    }

    char &operator[](int index) {
        return _pstr[index];
    }

    const char &operator[](int index) const {
        return _pstr[index];
    }

    const char *c_str() const { return _pstr; }

    ///给String字符串类型提供迭代器的实现
    class iterator {
    public:
        explicit iterator(char *p = nullptr) : _p(p) {}

        bool operator!=(const iterator &it) {
            return _p != it._p;
        }

        void operator++() {
            ++_p;
        }

        char &operator*() {
            return *_p;
        }

    private:
        char *_p;
    };

    iterator begin() {
        return iterator(_pstr);
    }

    iterator end() {
        return iterator(_pstr + length());
    }


private:
    char *_pstr;

    friend ostream &operator<<(ostream &out, const String &str);

    friend String operator+(const String &lhs, const String &rhs);
};

String operator+(const String &lhs, const String &rhs) {

    ///拷贝两次 两次new 两次delete
//    char *pTmp = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
//    strcpy(pTmp, lhs._pstr);
//    strcat(pTmp, rhs._pstr);
//    String tmp(pTmp);
//    delete[] pTmp;
//    return tmp;
    /// 优化 
    String tmp;
    tmp._pstr = new char[strlen(lhs._pstr) + strlen(rhs._pstr) + 1];
    strcpy(tmp._pstr, lhs._pstr);
    strcat(tmp._pstr, rhs._pstr);
    return tmp;
}

ostream &operator<<(ostream &out, const String &str) {
    out << str._pstr;
    return out;
}


int fun1() {
    String str1;
    String str2 = "aaa";
    String str3 = "bbb";
    String str4 = str2 + str3 + str2;
    cout << str4 << endl;

    if (str3 > str2) {
        cout << str3 << ">" << str2 << endl;
    }

    for (int i = 0; i < str4.length(); ++i) {
        cout << str4[i] << " ";
    }

    cout << endl;

    /// string -> char*
    char buffer[1024] = {0};
    strcpy(buffer, str4.c_str());
    cout << "buf: " << buffer << endl;


    return 0;
}

void fun2() {
    String str1("hello");//str1是容器，底层放了一组char类型的字符数组
    auto it = str1.begin();
    while (it != str1.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    for (char ch: str1) {
        cout << ch << " ";
    }
    cout << endl;
}

int main() {
    fun2();
    return 0;
}
