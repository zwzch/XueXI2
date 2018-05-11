//
// Created by zw on 17-11-12.
//
//#include "jni.h"
//#include "demo1.h"
//jint JNICALL Java_demo1_accessStaticMethod( JNIEnv* env, jobject jobj){
//    //1.获得实例对应的class类
//    jclass jcls = env->GetObjectClass(jobj);
//
//    //2.通过class类找到对应的method id
//    jmethodID jmid = env->GetStaticMethodID(jcls,"getHeight","()I");
//
//    //3.静态方法通过class获得对应的method
//    return env->CallStaticIntMethod(jcls,jmid);
//}