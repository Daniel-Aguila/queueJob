#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
using namespace std;

int jobC = 0;

struct job{
    int length;//Time needed
    int beg_time;
    int w_time;
    int ending_time;
    job* next;
};

class queue{
private:
    job* back;
    job* front;
public:
    queue(){back = nullptr; front = nullptr;}
    void enqueue(int,int,int,int);
    void dequeue(ofstream&);
    bool isEmpty();
    int first();
    int last();
};

bool queue::isEmpty() {
    if(front == NULL)
        return true;
    return false;
}
void queue::enqueue(int len,int beg, int wait, int end) {
    job* p = new job;
    p->length = len;
    p->beg_time = beg;
    p->w_time = wait;
    p->ending_time = end;
    if(isEmpty()){
        front = p;
        back = p;
    }
    else{
        back->next = p;
        back = p;
    }
}

void queue::dequeue(ofstream &w) {
    jobC++;
    if(isEmpty()){
        cout << "Queue is Empty" << endl;
    }
    else {
        job *p = front;
        int len = p->length;
        int beg = p->beg_time;
        int wait = p->w_time;
        int end = p->ending_time;
        front = front->next;
        free(p);
        w << "Job" << jobC << ":" << " length: " << len << "  beginning: "  << beg << "  wait " << wait << "  end " << end << endl;
    }
}


int main() {
    clock_t Cloctime = clock();
    queue queue1;
    ofstream write;
    write.open("output.txt");
    srand(time(NULL));
    int rnumber = rand()%20+1;
    for(int i = 0; i < rnumber;i++){
        queue1.enqueue(rand()%20,rand()%20,rand()%20,rand()%20);
    }
    for(int j =0;j<rnumber;j++){
        queue1.dequeue(write);
    }

    write << "Time it took for the Program to perform " << Cloctime - clock();
    write.close();
    return 0;
}