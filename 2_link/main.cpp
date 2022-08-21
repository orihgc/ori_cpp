//
// Created by orihgc on 2022/8/5.
//

extern int gdata;
int data = 20;

static int sData=10;

int sub(int a, int b);

int main() {
    int a = data;
    int b = gdata;
    int res = sub(a, b);
    return 0;
}
