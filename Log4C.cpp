#include "tinystr.h"
#include "tinyxml.h"
#include <iostream>
#include <fcntl.h>
#include <sstream>
#include "LogUtil.h"
using namespace std;

#define SUCCESS 1

#define FAILED  0
//int loadXml()
//
//{
//
////创建两个个xml文档对象，一个为读取，一个为输出
//
//    TiXmlDocument *inXml = new TiXmlDocument();
//
//    TiXmlDocument *outXml = new TiXmlDocument();
//
//
//
////加载xml文件
//
//    if(!inXml->LoadFile("a.xml"))  //判断XML文件是否加载成功
//
//    {
//
//        cerr<<inXml->ErrorDesc()<<endl;
//
//        return 0;
//
//    }
//
////定义根节点，记录xml文件的起始节点
//
//    TiXmlElement *inRoot = inXml->FirstChildElement(); //root指向xml文档的第一个节点
//
//    inXml->Value();//获取的值为文件名
//
////定义根节点并连接,将输入的根节点传给输出的根节点
//
//    TiXmlElement *outRoot = new TiXmlElement(inRoot->Value());
//
//    outXml->LinkEndChild(outRoot);
//
//
//
//    if(NULL == inRoot) //判断文件是否有内容
//
//    {
//
//        cerr<<"No root element ！！！"<<endl;
//
//        inXml->Clear();
//
//        return 0;
//
//    }
//
////循环遍历每个节点
//
//    for(TiXmlElement *inElem = inRoot->FirstChildElement(); inElem != NULL; inElem = inElem->NextSiblingElement())
//
//    {
//
//        TiXmlElement *outElem = new TiXmlElement(inElem->Value());
//
//        outRoot->LinkEndChild(outElem);
//
//        const char *name = inElem->Value();//获取源文件中子节点的名字
//
//        outElem->SetValue(name);  //设置目的文件子节点的名字
//
////获取源文件的属性，设置目标文件的属性
//
//        const char *rName = inElem->Attribute("name");
//
//        outElem->SetAttribute("name",rName);
//
//        const char *rType = inElem->Attribute("type");
//
//        outElem->SetAttribute("type",rType);
//
//        const char *rSize = inElem->Attribute("size");
//
//        outElem->SetAttribute("size",rSize);
//
//        const char *rOdd = inElem->Attribute("odd");
//
//        outElem->SetAttribute("odd",rOdd);
//
//        if(strcmp(name,"0"))
//
//        {
//
//            for(TiXmlElement *inChild = inElem->FirstChildElement();inChild!=NULL;inChild=inChild->NextSiblingElement())
//
//            {
//
//                TiXmlElement *outChild = new TiXmlElement(inChild->Value());
//
//                outElem->LinkEndChild(outChild);
//
//                const char *cName = inChild->Attribute("name");
//
//                outChild->SetAttribute("name",cName);
//
//                const char *cType = inChild->Attribute("type");
//
//                outChild->SetAttribute("type",cType);
//
//                const char *cRatio = inChild->Attribute("ratio");
//
//                outChild->SetAttribute("ratio",cRatio);
//
//                const char *cLink = inChild->Attribute("link");
//
//                outChild->SetAttribute("link",cLink);
//
//            }
//
//        }
//
//    }
//
//    outXml->SaveFile("b.xml");
//
//    inXml->Clear();
//
//    outXml->Clear();
//
//    return true;
//
//}
int readXmlFile()
{
    TiXmlDocument mydoc("/home/zw/ClionProjects/XueXI2/LogConf.xml");//xml文档对象
    bool loadOk=mydoc.LoadFile();//加载文档
    if(!loadOk)
    {
        cout<<"could not load the test file.Error:"<<mydoc.ErrorDesc()<<endl;
        exit(1);
    }

    TiXmlElement *RootElement=mydoc.RootElement();  //根元素, Info
    cout<< "[root name]" << RootElement->Value() <<"\n";

    TiXmlElement *pEle=RootElement;

    //遍历该结点
    for(TiXmlElement *StuElement = pEle->FirstChildElement();//第一个子元素
        StuElement != NULL;
        StuElement = StuElement->NextSiblingElement())//下一个兄弟元素
    {
        // StuElement->Value() 节点名称
        cout<< StuElement->Value() <<" ";
        TiXmlAttribute *pAttr=StuElement->FirstAttribute();//第一个属性

        while( NULL != pAttr) //输出所有属性
        {
            cout<<pAttr->Name()<<":"<<pAttr->Value()<<" ";
            pAttr=pAttr->Next();
        }
        cout<<endl;

        //输出子元素的值
        for(TiXmlElement *sonElement=StuElement->FirstChildElement();
            sonElement;
            sonElement=sonElement->NextSiblingElement())
        {
            cout<<sonElement->FirstChild()->Value()<<endl;
        }
    }
    return 1;
}
int TestParse(){
//   readXmlFile();
//   int  fd =  open(mystr,O_RDWR|O_CREAT|O_APPEND);
//    while( NULL != pAttr) //输出所有属性
//    {
//        cout<<pAttr->Name()<<":"<<pAttr->Value()<<" ";
//        pAttr=pAttr->Next();
//    }
//    cout<<endl;
}