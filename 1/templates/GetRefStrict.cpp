#include <iostream>
#include <map>
using namespace std;

template <typename First, typename Second>
Second& GetRefStrict(map<First, Second>& m, First key){
    if(!m.count(key))
        throw runtime_error("");
    return m.at(key);
}

int main(){
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
    return 0;
}