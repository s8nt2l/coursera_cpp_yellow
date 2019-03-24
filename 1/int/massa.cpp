#include <iostream>
#include <vector>
using namespace std;

int main(){
    uint32_t n, r;
    cin >> n >> r;
    vector<uint64_t> results(n);
    uint64_t x, y, z;
    for(uint64_t& c : results){
        cin >> x >> y >> z;
        c = x * y * z * r;
    }
    uint64_t result = 0;
    for(const uint64_t& c : results)
        result += c;
    cout << result;
    system("pause");
    return 0;
}