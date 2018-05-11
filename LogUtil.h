//
// Created by zw on 17-10-10.
//
#include "tinystr.h"
#include "tinyxml.h"
#include <iostream>
using namespace std;
#ifndef XUEXI2_LOGUTIL_H
#define XUEXI2_LOGUTIL_H
#endif //XUEXI2_LOGUTIL_H
#define log_file 1
#define log_std  2
#define L_DEBUG 1
#define L_INFO 2
#define L_WARNING 3
#define L_ERROR 4
#define  STRINGIFY(x) #x
#define  TOSTRING(x) STRINGIFY(x)
#define  AT __FILE__ ":" TOSTRING(__LINE__)
typedef  struct Appender{
    string name;
    string type;
    string time;
} Apder;
class Log{
protected:
    string log_name;
    string log_path;
    bool isStd;
    bool isFile;
    int Pori;

public:
    Apder apder;
    bool isIsStd()  {
        return isStd;
    }

    void setIsStd(bool isStd) {
       this->isStd = isStd;
    }

    bool isIsFile() {
        return isFile;
    }

    void setIsFile(bool isFile) {
        Log::isFile = isFile;
    }

    void setLogName(string name){
        this->log_name = name;
    }
    void setLogPath(string path){
        this->log_path = path;
    }
    string getLog_name(){
        return this->log_name;
    }
    string getlog_path(){
        return this->log_path;
    }
    int getPori() {
        return this->Pori;
    }

    void setPori(int Pori) {
        this->Pori = Pori;
    }

};
class Logger{
public:
    int Init(){
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
        TiXmlElement *StuElement = pEle->FirstChildElement();
        TiXmlElement *sonElement=StuElement->FirstChildElement();
//      cout<<sonElement->FirstChild()->Value();
        log.setLogName(sonElement->FirstChild()->Value());
        StuElement = StuElement->NextSiblingElement();
        sonElement = StuElement->FirstChildElement();
        string log_pori = sonElement->FirstChild()->Value();
//      cout<<log_pori;
        if(log_pori.compare("DEBUG")==0){
            log.setPori(L_DEBUG);
        } else if(log_pori.compare("INFO")==0){
            log.setPori(L_INFO);
        } else if (log_pori.compare("WARNING")==0){
            log.setPori(L_WARNING);
        } else{
            log.setPori(L_ERROR);
        }
        sonElement=sonElement->NextSiblingElement();
        string isStd = sonElement->FirstChild()->Value();
//      cout<<isStd;
        if(isStd.compare("true")==0){
            log.setIsStd(true);
        } else{
            log.setIsStd(false);
        }
        sonElement=sonElement->NextSiblingElement();
        string isFile = sonElement->FirstChild()->Value();
//      cout<<isFile;
        if(isFile.compare("true")==0){
            log.setIsFile(true);
        } else{
            log.setIsFile(false);
        }
        cout<<log.getLog_name()<<log.getPori()<<log.isIsFile()<<log.isIsStd()<<endl;
        StuElement = StuElement->NextSiblingElement();
        TiXmlAttribute *pAttr=StuElement->FirstAttribute();
        log.apder.name = pAttr->Value();
        pAttr = pAttr->Next();
        log.apder.type=pAttr->Value();
        pAttr = pAttr->Next();
        log.apder.time = pAttr->Value();
        cout<<log.apder.name<<log.apder.time<<log.apder.type<<endl;
        string path = log.getLog_name();
        path+=log.apder.name;
        path+=".log";
        const char * mystr=path.c_str();
        fp = fopen(mystr,"a+");
        if(fp==NULL)
            return 1;
//        fclose(fp);
    }
    int Debug(const char * at,const char * msg){
        fseek(fp, 0, SEEK_END);
        if (L_DEBUG<log.getPori())
            return 0;
        string things;
        stringstream ss;
        ss<<"[DEBUG]location=>";
        ss<<at;
        ss<<"---";
        if(log.apder.time.compare("true")==0){
        ss<<__TIME__;}
        ss<<"----msg==>";
        ss<<msg;
        ss<<"\n";
        ss>>things;
        if(log.isIsStd())
            cout<<things<<endl;
        fputs(things.c_str(), fp);
        fputc('\n', fp);
//        fputs(things.c_str(), fp);
//        fprintf(fp,"%s",things);
    }
    int Info(const char * at,const char * msg){
        fseek(fp, 0, SEEK_END);
        if (L_INFO<log.getPori())
            return 0;
        string things;
        stringstream ss;
        ss<<"[INFO]location=>";
        ss<<at;
        ss<<"---";
        if(log.apder.time.compare("true")==0){
            ss<<__TIME__;}
        ss<<"----msg==>";
        ss<<msg;
        ss<<"\n";
        ss>>things;
        if(log.isIsStd())
            cout<<things<<endl;
        fputs(things.c_str(), fp);
        fputc('\n', fp);
    }
    int Warning(const char * at,const char * msg){
        if (L_WARNING<log.getPori())
            return 0;
        fseek(fp, 0, SEEK_END);
        string things;
        stringstream ss;
        ss<<"[WARNING]location=>";
        ss<<at;
        ss<<"---";
        if(log.apder.time.compare("true")==0){
            ss<<__TIME__;}
        ss<<"----msg==>";
        ss<<msg;
        ss<<"\n";
        ss>>things;
        if(log.isIsStd())
            cout<<things<<endl;
        fputs(things.c_str(), fp);
        fputc('\n', fp);
    }
    int Error(const char * at,const char * msg){
        if (L_ERROR<log.getPori())
            return 0;
        string things;
        stringstream ss;
        ss<<"[ERROR]location=>";
        ss<<at;
        ss<<"---";
        if(log.apder.time.compare("true")==0){
            ss<<__TIME__;}
        ss<<"----msg==>";
        ss<<msg;
        ss<<"\n";
        ss>>things;
        if(log.isIsStd())
            cout<<things<<endl;
        fputs(things.c_str(), fp);
        fputc('\n', fp);
    }
    int close(){
        fclose(fp);
    }
protected:
    Log log;
    FILE *fp;
};
