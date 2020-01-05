#include <iostream>
#include <pthread.h>
#include <zconf.h>

#define NUM_THREADS 5
struct thread_data{
    int thread_id;
    char *message;
};

class Thread{
public:
    void funcation1();
    void funcation2();
    void funcation3();
    void funcation4();

    static void* say_hello(void* args);
    static void* PrintHello(void *threadid);
    static void* PrintHello1(void *threadarg);
    static void* wait(void *t);
};

void Thread::funcation1(){
    pthread_t tids[NUM_THREADS];
    for(size_t i = 0; i < NUM_THREADS; ++i){
        int ret = pthread_create(&tids[i], NULL, say_hello, this);
        if(ret != 0){
            std::cout << "pthread_create error: error_code=" << ret << std::endl;
        }
    }
    //pthread_exit(NULL);
}

void Thread::funcation2(){
    pthread_t threads[NUM_THREADS];
    int indexes[NUM_THREADS];
    int rc;
    for(size_t i = 0; i < NUM_THREADS; i++){
        std::cout << "main() : 创建线程,　"<< i << std::endl;
        indexes[i] = i;
        rc = pthread_create(&threads[i], NULL,
                PrintHello, (void*)&(indexes[i]));
        if(rc){
            std::cout << "Error: 无法创建线程," << rc << std::endl;
            exit(-1);
        }
    }
    //pthread_exit(NULL);
}

void Thread::funcation3(){
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];
    int rc;

    for(size_t i = 0; i < NUM_THREADS; i++){
        std::cout << "main() : creating thread, " << i << std::endl;
        td[i].thread_id = i;
        td[i].message = (char*)"This is message";
        rc = pthread_create(&threads[i], NULL,
                PrintHello1, (void*)&td[i]);
        if(rc){
            std::cout << "Error: unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }
    pthread_exit(NULL);
}

void Thread::funcation4(){
    int rc;

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(size_t i = 0; i < NUM_THREADS; i++){
        std::cout << "main() : creating thread, " << i << std::endl;
        rc = pthread_create(&threads[i], NULL, wait, (void *)&i);
        if(rc){
            std::cout << "Error:unable to create thread, " << rc << std::endl;
            exit(-1);
        }
    }
    pthread_attr_destroy(&attr);
    for(size_t i = 0; i < NUM_THREADS; i++){
        rc = pthread_join(threads[i], &status);
        if(rc){
            std::cout << "Error:unable to join, " << rc << std::endl;
            exit(-1);
        }
        std::cout << "Main: completed thread id: " << i;
        std::cout << " exiting with status :" << status << std::endl;
    }
    std::cout << "Main: program exiting." << std::endl;
    pthread_exit(NULL);
}

void* Thread::say_hello(void* args){
    std::cout << "Hello World !" << std::endl;
    return 0;
}

void* Thread::PrintHello(void *threadid){
    int tid = *((int*)threadid);
    std::cout << "Hello Runoob! 线程 ID, " << tid << std::endl;
    //pthread_exit(NULL);
}

void* Thread::PrintHello1(void *threadarg){
    struct thread_data *my_data;
    my_data = (struct thread_data *)threadarg;
    std::cout << "Thread ID: " << my_data->thread_id;
    std::cout << "Message : " << my_data->message << std::endl;
    //pthread_exit(NULL);
}

void* Thread::wait(void *t){
    int i;
    long tid;

    tid = (long)t;

    sleep(1);
    std::cout << "Sleeping in thread " << std::endl;
    std::cout << "Thread with id : " << tid << "   ...exiting " << std::endl;
    pthread_exit(NULL);
}

int main() {
    Thread thread;
    //thread.funcation1();
    //thread.funcation2();
    //thread.funcation3();
    thread.funcation4();
    //std::cout << "Hello, World!" << std::endl;
}