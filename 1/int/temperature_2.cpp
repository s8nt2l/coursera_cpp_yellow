#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> t(n);
    for(auto& c : t)
        cin >> c;
    int64_t avg  = 0;
    for(const  auto& c : t)
        avg += c;
    avg /= static_cast<int>(t.size());
    vector<size_t> positions;
    for(int i = 0; i < t.size(); i++){
        if(t[i] > avg)
            positions.push_back(i);
    }
    cout << positions.size() << endl;
    for(const auto& c : positions)
        cout << c << ' ';
    system("pause");
    return 0;
}