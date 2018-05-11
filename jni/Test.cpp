//
// Created by zw on 17-12-12.
//

#include "TestJni.h"
#include  <jni.h>

JNIEXPORT void JNICALL Java_TestJni_yyy(JNIEnv *, jobject){
    printf("You are my hero");
}