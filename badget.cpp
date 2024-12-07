#include "badget.h"

Badget::Badget()
{
    total_badget=0;
    for(int i=0;i<5;i++)
        rest[i]=0;
}
Badget::Badget(const Badget& b)
{
    total_badget=b.total_badget;
    for(int i=0;i<5;i++)
        rest[i]=b.rest[i];
}
Badget::~Badget() {}

double& Badget::get_total_badget() {return total_badget;}
double& Badget::get_rest_of_month(int month) {return rest[month-5];}

std::map<QString,Badget> badgets={{"三餐",Badget()},{"零食",Badget()},{"衣服",Badget()},{"交通",Badget()},{"日用品",Badget()},{"医疗",Badget()},{"学习/工作",Badget()},{"娱乐",Badget()},{"其他",Badget()}};
double editing_badget=0;
QString editing_type="";
