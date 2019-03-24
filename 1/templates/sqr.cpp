#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename First, typename Second> pair<First, Second> operator*(const pair<First, Second>& a, const pair<First, Second>& b);
template <typename First, typename Second> map<First, Second> operator*(const map<First, Second>& a, const map<First, Second>& b);
template <typename T> vector<T> operator*(const vector<T>& a, const vector<T>& b);
template <typename T> T Sqr(const T& a);


template <typename First, typename Second>
pair<First, Second> operator*(const pair<First, Second>& a, const pair<First, Second>& b){
    return make_pair(a.first * b.first, a.second * b.second);
}

template <typename First, typename Second>
map<First, Second> operator*(const map<First, Second>& a, const map<First, Second>& b){
    map<First, Second> result;
    for( auto& c : a)
        result[c.first] = c.second * c.second;
    return result;
}

template <typename T>
vector<T> operator*(const vector<T>& a, const vector<T>& b){
    vector<T> result;
    for(size_t i = 0; i < a.size(); i++)
        result.push_back(a[i] * b[i]);
    return result;
}

template <typename T>
T Sqr(const T& a){
    return a * a;
}


int main(){
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
    cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    system("pause");
}