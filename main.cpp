#include <iostream>

using namespace std;

class tNode {
public:
    int v;
    tNode *old;
    tNode *next;
};

class tFIFO {
public:
    void push(int);
    int pop();
    int operator[](int);
    tNode *operator()(int);
    void operator=(int);
    void operator+=(int);
    void operator-=(int);
    int operator--();
    int length();
    tFIFO();
    tFIFO(int, int);
    ~tFIFO();
private:
    tNode *ankerOld;
    tNode *ankerNext;
    int len;
};

tFIFO::tFIFO() {
    ankerOld = 0;
    ankerNext = 0;
    len = 0;
}

tFIFO::tFIFO(int val, int leng) {
    ankerOld = 0;
    ankerNext = 0;
    len = 0;
    for(int i = 0; i < leng; ++i) push(val);
}

tFIFO::~tFIFO() {
    tNode *node = ankerOld;
    while(ankerOld) {
        node = ankerOld;
        ankerOld = ankerOld->old;
        delete node;
    }
}

int tFIFO::operator[](int index) {
    int counter = 0;
    tNode *ankerSave = ankerNext;
    if(index >= 0 && index < len) {
        tNode *current;
        if(ankerNext) {
            do {
                current = ankerSave;
                ankerSave = current->next;
            } while(++counter <= index);
        }
        return current->v;
    }
    cout<<"Error: Index out of Bounds"<<endl;
    return 0;
}

tNode *tFIFO::operator()(int index) {
    int counter = 0;
    tNode *ankerSave = ankerNext;
    if(index >= 0 && index < len) {
        tNode *current;
        if(ankerNext) {
            do {
                current = ankerSave;
                ankerSave = current->next;
            } while(++counter <= index);
        }
        return current;
    }
    cout<<"Error: Index out of Bounds"<<endl;
    return 0;
}

void tFIFO::push(int v) {
    ++len;

    tNode *node = new tNode;
    node->v = v;
    node->old = ankerOld;
    ankerOld = node;

    node->next = 0;

    if(!ankerNext) ankerNext = node;
    else {
        tNode *oldNote = node->old;
        oldNote->next = node;
    }
}

void tFIFO::operator+=(int v) {
    ++len;

    tNode *node = new tNode;
    node->v = v;
    node->old = ankerOld;
    ankerOld = node;

    if(!ankerNext) ankerNext = node;
    else {
        tNode *oldNote = node->old;
        oldNote->next = node;
    }
}

int tFIFO::pop() {
    int val = 0;
    if(ankerNext != ankerOld->next) {
        --len;
        tNode *node = ankerNext;
        val = node->v;
        ankerNext = node->next;
        delete node;
        return val;
    }
    cout<<"Error: List is already empty"<<endl;
    return 0;
}

int tFIFO::operator--() {
    int val = 0;
    if(ankerNext != ankerOld->next) {
        --len;
        tNode *node = ankerNext;
        val = node->v;
        ankerNext = node->next;
        delete node;
        return val;
    }
    cout<<"Error: List is already empty"<<endl;
    return 0;
}

void tFIFO::operator-=(int v) {
    tNode *currentNode = ankerNext;
    tNode *nextNode;
    int n = 0;
    if(currentNode->v == v) pop();
    for(int i = 0; i < len-1; ++i) {
        if(currentNode->next) {
            nextNode = currentNode->next;
            if(nextNode->v != v) currentNode = nextNode;
            else {
                ++n;
                currentNode->next = nextNode->next;
            }
        }
    }
    len -= n;
}

void tFIFO::operator=(int v) {
    tNode *currentNode = ankerNext;
    for(int i = 0; i < len; ++i) {
        currentNode->v = v;
        currentNode = currentNode->next;
    }
}

int tFIFO::length() {
    return len;
}

ostream& operator<<(ostream& os, tFIFO& arr) {
    os<<"[";
    os<<arr[0];
    for(int i = 1; i < arr.length(); ++i) {
        os<<","<<arr[i];
    }
    os<<"]";
    return os;
}

int main()
{
    tFIFO arr;

    arr += 3;
    arr += 2;

    arr.push(3);
    arr.push(5);
    arr.push(7);

    cout<<"Length:\t\t"<<arr.length()<<endl;

    cout<<"arr[0]:\t\t"<<arr[0]<<endl;

    cout<<"arr:\t\t"<<arr<<endl;

    arr-=2;

    cout<<"arr:\t\t"<<arr<<endl;

    arr = 2;

    cout<<"arr:\t\t"<<arr<<endl;

    arr(6)->v = 5;

    cout<<"arr:\t\t"<<arr<<endl;

    cout<<"arr[6]:\t\t"<<arr[6]<<endl;

    tFIFO arr2 = tFIFO(5, 20);

    cout<<"arr2:\t\t"<<arr2<<endl;

    cout<<"arr2 Length:\t"<<arr2.length()<<endl;

    arr2.pop();

    --arr;

    cout<<"arr:\t\t"<<arr<<endl;

    cout<<"arr2:\t\t"<<arr2<<endl;

    return 0;
}
