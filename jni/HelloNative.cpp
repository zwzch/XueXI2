
#include <linux/jni_md.h>
#include <jni.h>
JNIEXPORT void JNICALL Java_HelloNative_printHello
(JNIEnv *, jobject)
{
printf("Hello, Native!");
return ;
}

