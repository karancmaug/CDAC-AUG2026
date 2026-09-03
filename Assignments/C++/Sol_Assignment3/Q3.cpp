#include <iostream>
#include <memory>
using namespace std;

class LogBuffer{

    char *buffer;
    int capacity;
    int size;
    static int Icount;

    public :

    LogBuffer() : buffer(nullptr), capacity(0), size(0) {
        Icount++;
    }

    LogBuffer(int capacity) : capacity(capacity), size(0) {
        buffer = new char[capacity];
        Icount++;
    }

    LogBuffer(const LogBuffer& other) {
        capacity = other.capacity;
        size = other.size;
        buffer = new char[capacity];

        for(int i = 0; i < size; i++){
            buffer[i] = other.buffer[i];
        }    
        Icount++;       
    }

    LogBuffer& operator=(const LogBuffer& other){
        if(this != &other){
            delete[] buffer;

            capacity = other.capacity;
            size = other.size;
            buffer = new char[capacity];

            memcpy(buffer, other.buffer , sizeof(other.buffer));
        }
        return *this;
    }

    ~LogBuffer(){
        delete[] buffer;
        Icount--;
        cout << "LogBuffer destroyed (Remaining: " << Icount << ")" << endl;
    }

    public :

    void append (const char* msg){
        if(!msg) return;
        while(*msg){
            if(size < capacity){
                buffer[size] = *msg;
                size++;
                msg++;
            }else{
                cout << " buffer is full !!!!!!" << endl;
                break;
            }
        }
    }

    void print() const{
        for(int i = 0; i < size; i++){
            cout << buffer[i];
        }
        cout << endl;
    }

    void clear(){
        size = 0;
    }

    static int getInstanceCount(){
        return Icount;
    }
};

int LogBuffer::Icount = 0;


int main() {
    // Objective 1 : Basic usage    
    LogBuffer log1(256);
    log1.append("Server started on port 8080");
    log1.append(" | Request received from 192.168.1.10");
    log1.print();
    // Objective 2 : Deep copy via copy constructor    
    LogBuffer log2 = log1;           // copy constructor
    log2.append(" | Cached response sent");
    cout << "log1 : "; log1.print(); // must NOT contain log2's append    
    cout << "log2 : "; log2.print();
    // Objective 3 : Copy assignment operator    
    LogBuffer log3(128);
    log3 = log1;                     // copy assignment    
    log3.print();
    // Objective 4 : Self-assignment guard    
    log1 = log1;                     // must not crash or corrupt data    
    log1.print();
    // Objective 5 : Static member    
    cout << "Live LogBuffer objects : " << LogBuffer::getInstanceCount() << endl;
    return 0;
    // All 3 objects destroyed here — destructors must print and decrement count
    }