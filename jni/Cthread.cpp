//
// Created by zw on 17-11-12.
//

#include <zconf.h>
#include <pthread.h>
#include "jni.h"
#include "jni_Cthread_Cthread.h"
struct Arg_type{
    JNIEnv *env;
    jobject jobj;
};
void* run(void* args){
    Arg_type arg_type = *(Arg_type*)args;
    JNIEnv *env = arg_type.env;
    jobject jobj = arg_type.jobj;
    printf("=======================\n");
    jclass jcls = env->GetObjectClass(jobj);
    //2.通过class类找到对应的method id
    jmethodID jmid = env->GetStaticMethodID(jcls,"Crun","()I");
    //3.静态方法通过class获得对应的method
    env->CallStaticIntMethod(jcls,jmid);
}
JNIEXPORT void JNICALL Java_jni_Cthread_Cthread_start(JNIEnv * env, jobject jobj){
    //	printf("alhfkahdflajhlkajshdfed");
    //        printf("heihei");
    //1.获得实例对应的class类
    printf("##################");
    pthread_t tid;
    printf("THIS TID %ld",tid);
    Arg_type args;
    args.env = env;
    args.jobj=jobj;
    int iRet = pthread_create(&tid, NULL, run, &args);
    /*参数依次是：创建的线程id，线程参数，调用函数名，传入的函数参数*/
    if (iRet){
        printf("error: iRet=%d\n",iRet);
    }
}
