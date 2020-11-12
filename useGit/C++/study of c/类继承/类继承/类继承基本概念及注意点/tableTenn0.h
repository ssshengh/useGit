#ifndef  TABLETENN0_H_
#define TABLETENN0_H_


#include <string>
using std::string;

class tableTennisPlayer
{
private:
    string firstName;
    string lastName;
    bool hasTable;//是否有球卓
public:
    tableTennisPlayer  (const string & fn = "none" , const string & ln = "none" ,bool ht = false);
    void Name() const;
    bool HasTable() const { return hasTable ;}
    void reSetTable(bool v){ hasTable = v;}
    ~tableTennisPlayer ();
};

//简单的继承
class RatedPlayer : public tableTennisPlayer
{
private:
    unsigned int rating;//得分
public:
    RatedPlayer(unsigned int r = 0, const string & fn = "none" , const string & ln = "none" ,bool ht = false);//参数列表中需要有所有父类的参数
    RatedPlayer(unsigned int r , const tableTennisPlayer & tp);
    unsigned int RateGet() const { return rating ; }
    void reSetRating(unsigned int r){rating = r;}
    ~RatedPlayer();
};




#endif
