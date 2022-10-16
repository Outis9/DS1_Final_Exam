//
// Created by Kevin on 2022/4/11.
//


#ifndef DS1FINALPROJECT2_PEOPLE_H
#define DS1FINALPROJECT2_PEOPLE_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <utility>
#include "seq_queue.h"
#include "Tube.h"

#define MAX_SIZE 10000

int mixNum,personNum,sum;  //全局变量
std::string people_id[MAX_SIZE]; //记录从文件中读取的所有人员的代号
std::string tubeID[MAX_SIZE];//记录从文件读入的试管信息



//将数据按行读入
void ReadInitQueueData(std::string peopleId[]) {
    std::string input_file=R"(D:\GitHubFiles\DS1FinalProject2\line_up.in)";
    std::string query;
    std::ifstream in(input_file);
    std::getline(in,query);
    mixNum = atoi(query.c_str());    //读入第一行为混合测试人数
    std::getline(in,query);
    personNum = atoi(query.c_str());    //读入第二行为个人检测人数
    sum = mixNum + personNum;           //求得人数之和
    for (int i = 0;i<=sum-1;i++){
        std::getline(in,query);
        peopleId[i]=query;                 //将所有人的id存入people_id中
    }
}


class People{
public:
    std::string personal_id;
    std::string buildingID;
    Result PCR_test_result;
    int check_method;
    Tube tube;


    People();
    void Get_personal_id(std::string id);
    static void Select_check_method(int i,People& p);//选择核酸测试的方式 0-混合 1-单人
    friend std::ostream & operator<<(std::ostream &out, const People &p) {  //遍历队列只输出id，后期可以改
        out << p.personal_id << "\t"  << std::endl;
        return out;
    }
};

People::People() = default;

void People::Get_personal_id(std::string id) {
    personal_id = std::move(id);
}

void People::Select_check_method(int i,People& p) {
    if(i< mixNum && i >=0){
        p.check_method = 0;
    }
    else if (i >= mixNum && i <= sum-1)
        p.check_method = 1;
}


// 非成员函数
void ShowLocation(const std::string& personalID) {
    std::string buildingID = personalID.substr(0,3);
    std::string roomID = personalID.substr(3,4);
    std::string memberID= personalID.substr(7,1);
    std::cout<<"This the NO. "<<memberID<<" person lives in the building "<<buildingID<<" and room "<<roomID<<std::endl;
}

//获取楼号为寻找次密接做准备
std::string getBuildingID(const std::string& personalID){
    std::string buildingID = personalID.substr(0,3);
    return buildingID;
}

void InputTestResult(People people[]) {
    std::string input_file=R"(D:\GitHubFiles\DS1FinalProject2\TestTubeInfo.txt)";
    std::string query;
    std::ifstream in(input_file);
    for (int i = 0;i<=43;i++){
        std::getline(in,query);
        tubeID[i]=query;
        std::getline(in,query);
        for (int j = 0; j < sum; j++) {
            if(people[j].tube.tube_id == tubeID[i]){
                people[j].tube.tube_state = query;
            }
        }
    }
}

void ConfirmPeopleState(People p[]) {
    //单人管直接标明结果
    for (int i = sum - 1; i >= mixNum; i--) {
        if (p[i].tube.tube_state == "1") { p[i].PCR_test_result = POSITIVE; }
        else if (p[i].tube.tube_state == "0") { p[i].PCR_test_result = NEGATIVE; }
    }
    for (int i = sum - 1; i >= mixNum; i--) {
        if (p[i].PCR_test_result == POSITIVE) {
            for (int j = i; j > i - 10 && j > mixNum; j--) {
                if (p[j].PCR_test_result == POSITIVE) continue;
                p[j].PCR_test_result = CLOSECONTACT;
            }
            for (int j = i; j < sum; j++) {
                if (p[j].PCR_test_result == POSITIVE) continue;
                p[j].PCR_test_result = CLOSECONTACT;
            }
        }
    }
    //混合管标阴性和可疑
    for (int j = 0; j < mixNum; j++) {
        if (p[j].tube.tube_state == "0") { p[j].PCR_test_result = NEGATIVE; }
        else if (p[j].tube.tube_state == "1") { p[j].PCR_test_result = SUSPECT; }
    }
    //同一栋楼判断次密接
    for (int k = 0; k < sum; k++) { p[k].buildingID = getBuildingID(p[k].personal_id); } //给每人一个楼号
    for (int k = 0; k < sum; k++) {
        if (p[k].PCR_test_result == POSITIVE) {
            for (int m = 0; m < sum; m++) {
                if(p[m].buildingID == p[k].buildingID){
                    if(p[m].PCR_test_result == POSITIVE) continue;
                    p[m].PCR_test_result = SUB_CLOSECONTACT; //最后一个人就是次密接
                }
            }
        }
    }
}

void ShowAllNegative(People p[]){
    std::cout<<"NEGATIVE: "<<std::endl;
    for (int i = 0; i < sum; i++) {
        if (p[i].PCR_test_result == NEGATIVE){
            std::cout<<p[i].personal_id<<std::endl;
        }
    }
}

void ShowAllPositive(People p[]){
    std::cout<<"POSITIVE: "<<std::endl;
    for (int i = 0; i < sum; i++) {
        if (p[i].PCR_test_result == POSITIVE){
            std::cout<<p[i].personal_id<<std::endl;
        }
    }
}

void ShowAllSuspect(People p[]){
    std::cout<<"SUSPECT: "<<std::endl;
    for (int i = 0; i < sum; i++) {
        if (p[i].PCR_test_result == SUSPECT){
            std::cout<<p[i].personal_id<<std::endl;
        }
    }
}

void ShowAllCloseContact(People p[]){
    std::cout<<"CLOSECONTACT: "<<std::endl;
    for (int i = 0; i < sum; i++) {
        if (p[i].PCR_test_result == CLOSECONTACT){
            std::cout<<p[i].personal_id<<std::endl;
        }
    }
}

void ShowAllSubCloseContact(People p[]){
    std::cout<<"SUB_CLOSECONTACT: "<<std::endl;
    for (int i = 0; i < sum; i++) {
        if (p[i].PCR_test_result == SUB_CLOSECONTACT){
            std::cout<<p[i].personal_id<<std::endl;
        }
    }
}

void MixQueue(People p[]) {
    SeqQueue<People> seqQueue = SeqQueue<People>(11);
    int count = 0;
    for (int i = 0; i < 10; i++) {
        seqQueue.EnQueue(p[i]);
        p[i].tube.tube_id = "00000";
        p[i].PCR_test_result=INQUEUE;
    }
    for (int i = 0; i < mixNum / 10 * 10 - 10; i++) {
        seqQueue.DelQueue(p[i]);
        p[i].PCR_test_result = WAITING;
        count ++;
        seqQueue.EnQueue(p[i+10]);
        p[i+10].tube.tube_id = "00001";
        p[i+10].PCR_test_result = INQUEUE;
    }
//    seqQueue.Traverse(Write<People>);
}



void ShowPCR_Result(const People& people) {
    if(people.PCR_test_result == 0)std::cout<<"NEGATIVE"<<std::endl;
    if(people.PCR_test_result == 1)std::cout<<"POSITIVE"<<std::endl;
    if(people.PCR_test_result == 2)std::cout<<"SUSPECT"<<std::endl;
    if(people.PCR_test_result == 3)std::cout<<"CLOSECONTACT"<<std::endl;
    if(people.PCR_test_result == 4)std::cout<<"SUB_CLOSECONTACT"<<std::endl;
    if(people.PCR_test_result == 5)std::cout<<"WAITING"<<std::endl;
    if(people.PCR_test_result == 6)std::cout<<"INQUEUE"<<std::endl;
    if(people.PCR_test_result == 7)std::cout<<"NOTCHECKED"<<std::endl;
}


void SingleQueue(People p[]){
    SeqQueue<People> seqQueue2 = SeqQueue<People>(personNum +1);
    int tubeId,count=0;
    for (int i = mixNum; i < sum; i++) {
        seqQueue2.EnQueue(p[i]);
        p[i].PCR_test_result = INQUEUE;
        tubeId = 10000 + count;
        p[i].tube.tube_id = std::to_string(tubeId);
        count++;
    }
//    seqQueue2.Traverse(Write<People>);
}

#endif //DS1FINALPROJECT2_PEOPLE_H
