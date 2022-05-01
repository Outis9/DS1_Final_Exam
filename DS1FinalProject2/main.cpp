#include "people.h"

int main() {
    char c;
    ReadInitQueueData(people_id);         //从文件中读取人员代码等信息
    auto *p = new People[sum];  //初始化对象数组
    for(int i = 0;i < sum; i++){p[i].Get_personal_id(people_id[i]);}

    std::string x;
    while (c != '0'){
        std::cout<<std::endl;
        std::cout<<"1.Automatically Select Test Method(0-Mix,1-Single)."<<std::endl;
        std::cout<<"2.Check Person's Check Method."<<std::endl;
        std::cout<<"3.Check Personal State."<<std::endl;
        std::cout<<"4.Check Mix Queue."<<std::endl;
        std::cout<<"5.Check Personal Queue."<<std::endl;
        std::cout<<"6.Check Tube ID."<<std::endl;
        std::cout<<"7.Input Test Tubes' Info from file."<<std::endl;
        std::cout<<"8.Show All Negative."<<std::endl;
        std::cout<<"9.Show All Positive."<<std::endl;
        std::cout<<"A.Show All Suspect."<<std::endl;
        std::cout<<"B.Show All Close Contact."<<std::endl;
        std::cout<<"C.Show All Sub Close Contact."<<std::endl;
        std::cout<<"D.Show Person Location."<<std::endl;
        std::cout<<"0.Exit and Have a Nice Day!."<<std::endl;
        std::cin>>c;

        switch (c) {
            case '1':
                for (int i = 0; i < sum; i++)   p[i].Select_check_method(i,p[i]); //确定检测的方式
                break;
            case '2':
                std::cout<<"The Personal ID You want to check.(xxxyyyyz): ";
                std::cin>>x;
                for (int i = 0;i < sum; i++){if(p[i].personal_id == x)   std::cout<<p[i].check_method<<std::endl;}
                break;
            case '3':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                std::cout<<"The Personal ID You want to check.(xxxyyyyz): ";
                std::cin>>x;
                for(int i = 0;i < sum; i++){
                    if(p[i].personal_id == x)
                        ShowPCR_Result(p[i]);
                }
                break;
            case '4':
                MixQueue(p);
                break;
            case '5':
                SingleQueue(p);
                break;
            case '6':
                MixQueue(p);
                SingleQueue(p);
                std::cout<<"The Personal ID You want to check.(xxxyyyyz): ";
                std::cin>>x;
                for(int i = 0;i < sum; i++){if(p[i].personal_id == x)   std::cout<<p[i].tube.tube_id<< std::endl;}
                break;
            case '7':
                InputTestResult(p);
                break;
            case '8':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                ShowAllNegative(p);
                break;
            case '9':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                ShowAllPositive(p);
                break;
            case 'A':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                ShowAllSuspect(p);
                break;
            case 'B':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                ShowAllCloseContact(p);
                break;
            case 'C':
                MixQueue(p);
                SingleQueue(p);
                InputTestResult(p);     //从文件输入测试结果
                ConfirmPeopleState(p);  //确定每个人状态，从tube_state变成人的state
                ShowAllSubCloseContact(p);
                break;
            case 'D':
                std::cout<<"The Personal ID You want to check.(xxxyyyyz): ";
                std::cin>>x;
                for(int i = 0;i < sum; i++){if(p[i].personal_id == x) ShowLocation(p[i].personal_id);}
                break;
        }
    }

    return 0;
}