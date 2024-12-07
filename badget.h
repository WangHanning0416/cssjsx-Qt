#ifndef BADGET_H
#define BADGET_H
#include <map>
#include <QString>

namespace Ui{
class Badget;
}

class Badget
{
private:
    double total_badget;//记录每月总预算
    double rest[5];//记录每月剩余预算 rest[i]对应i+5月的剩余预算 (只使用rest[0~2])
public:
    //构造与析构
    Badget();
    Badget(const Badget& b);
    ~Badget();
    //接口
    double& get_total_badget();
    double& get_rest_of_month(int month);//输入月份
};

extern std::map<QString,Badget> badgets;
extern double editing_badget;
extern QString editing_type;

#endif // BADGET_H
