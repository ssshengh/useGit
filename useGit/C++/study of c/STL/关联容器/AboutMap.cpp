#include <iostream>
#include <string>
#include <map>
#include <algorithm>

typedef int KeyType;
typedef std::pair<const KeyType , std::string> Pair;//C++使用pair将两个值储存在一个对象中，前者为键后者为值
typedef std::multimap<KeyType , std::string> MapCode;

int main(){
    using namespace std;
    MapCode codes;

    codes.insert(Pair(415 , "Beijing"));
    codes.insert(Pair(510 , "Sahnghai"));
    codes.insert(Pair(718 , "Kunming"));
    codes.insert(Pair(718 , "Chengdu"));
    codes.insert(Pair(415 , "Tianjin"));
    codes.insert(Pair(510 , "XIan"));

    cout<<"Number of cities with area of 415 :"
            <<codes.count(415)<<endl;
    cout<<"Number of cities with area of 718 :"
            <<codes.count(718)<<endl;
    cout<<"Number of cities with area of 510 :"
            <<codes.count(510)<<endl;
    
    cout<<"Area Code       City\n" ;
    MapCode::iterator it;
    for(it = codes.begin() ; it != codes.end() ; it++)
            cout<<"           " << (*it).first<<"            "
                    <<(*it).second<<endl;
    
    pair<multimap<KeyType , string>::iterator ,
                multimap<KeyType , string>::iterator> range = codes.equal_range(718);
    
    for(it = range.first ; it!= range.second ; it++)
        cout<<(*it).second<<endl;
}
