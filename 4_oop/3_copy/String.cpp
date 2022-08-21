#include <cstring>

//
// Created by orihgc on 2022/8/11.
//
class String {
private:
    char *m_data;
public:
    String(const char *str = nullptr) {
        if (str == nullptr) {
            m_data = new char[1];
            *m_data = '\0';
        } else {
            m_data = new char[strlen(str) + 1];
        }
    }

    String(const String &other) {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }

    ~String() {
        delete[]m_data;
        m_data = nullptr;
    }

    //String& 是为了支持连续的operator赋值操作
    String &operator=(const String &other) {
        if (this == &other)return *this;
        delete[]m_data;
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }

};

int main() {
    String str1;
    String str2("hello");
    String str3 = "world";
    String str4 = str3;
    String str5(str3);

    /**
     * str1 = str2;
     * str1.operator(str2)=>void
     * */
    str1 = str2 = str3;
}
