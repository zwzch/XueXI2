# cmake_minimum_required(VERSION <specify CMake version here>)
project(XueXI2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ADD_SUBDIRECTORY( process )
include_directories(/home/zw/user/java/jdk1.7.0_80/include)
include_directories(/home/zw/user/java/jdk1.7.0_80/include/linux)
set(SOURCE_FILES  io.cpp inode1.cpp DataType.h seqtest.cpp Log4C.cpp tinyxml.h tinystr.cpp tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp LogUtil.h process/process.cpp ZwSh.h process/sem.cpp process/daemon.cpp test/demo.cpp thread.cpp main.cpp main.cpp sockettest.cpp  demo2.cpp boosttest.cpp jni/HelloNative.cpp jni/demo.c jni/Cthread.cpp process/daemon_thread.cpp process/synchorized.cpp process/semTest.cpp Tomcat/HttpTest.cpp process/epoll.cpp process/ClientDemo.cpp jni/Test.cpp jni/Test.h NioTest/selector.cpp DataStruct/ArrayandLink.cpp DataStruct/Statck.cpp DataStruct/String.cpp DataStruct/HashTest.cpp DataStruct/orderorderorder.cpp DataStruct/quickSort.cpp DataStruct/mergeSort.cpp  DataStruct/binary_search.cpp DataStruct/Tree.cpp  DataStruct/BPlusTree.cpp DataStruct/BPlusTree.h DataStruct/avltree.cpp DataStruct/avltree.h DataStruct/RDTree.cpp DataStruct/Queue.cpp DataStruct/MapMapMap.cpp DataStruct/QueueAndStack.cpp DataStruct/leetcode.cpp DataStruct/Greedy.cpp OJoffer/MyCode.cpp)

find_package(Threads REQUIRED)
include_directories(/usr/local/include/boost)

add_executable(XueXI2 ${SOURCE_FILES} seqtest.cpp Log4C.cpp LogUtil.h process/process.cpp ZwSh.h process/daemon.cpp thread.cpp sockettest.cpp  demo2.cpp boosttest.cpp jni/HelloNative.cpp  jni/demo.c jni/Cthread.cpp process/daemon_thread.cpp process/synchorized.cpp process/semTest.cpp Tomcat/HttpTest.cpp process/epoll.cpp process/ClientDemo.cpp jni/Test.cpp jni/Test.h NioTest/selector.cpp DataStruct/ArrayandLink.cpp DataStruct/Statck.cpp DataStruct/String.cpp)
target_link_libraries(XueXI2 boost_thread pthread boost_system boost_filesystem)