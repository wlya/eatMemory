#include <jni.h>
#include <string>

#include <pthread.h>

#define NUM_THREADS 5      //线程个数

void eatMem(){
    char* cc;
    while (1){
        cc = (char*)malloc(0x1000);
    }
    cc=(char*)1;

}
void readyEat(){
    pthread_t tids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, reinterpret_cast<void *(*)(void *)>(eatMem), (void*)NULL);
        if (ret != 0) {
            printf("pthread_create error: error_code = %d\n", ret);
        }
    }
}
extern "C" JNIEXPORT jstring JNICALL
Java_eat_memory_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    readyEat();
    return env->NewStringUTF(hello.c_str());
}