#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;


template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        } catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            //system("pause");
            exit(1);
        }
    }

private:
    int fail_count = 0;
};



bool operator==(const Rational& a, const Rational& b){
    return (a.Denominator() == b.Denominator()) && (a.Numerator() == b.Numerator());
}

bool operator!=(const Rational& a, const Rational& b){
    return !(a == b);
}

Rational operator+(const Rational& a, const Rational& b){
    /*int g1 = gcd(abs(a.Denominator()), abs(b.Denominator()));
    int d1 = a.Denominator() / g1, d2 = b.Denominator() / g1;
    return {a.Numerator() * d2 + d1 * b.Numerator(), d1 * d2 * g1};*/
    return Rational {a.Numerator() * b.Denominator() + a.Denominator() * b.Numerator(), a.Denominator() * b.Denominator()};
}

Rational operator-(const Rational& a){
    return Rational(-a.Numerator(), a.Denominator());
}

Rational operator-(const Rational& a, const Rational& b){
    return a + (-b);
}

Rational operator*(const Rational& a, const Rational& b){
    /*int g1 = gcd(b.Numerator(), a.Denominator());
    int g2 = gcd(a.Numerator(), b.Denominator());
    return Rational((a.Numerator() / g2) * (b.Numerator() / g1), (a.Denominator() / g1) * (b.Denominator() / g2));*/
    return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
}

Rational operator/(const Rational& a, const Rational& b){
    //const string a = "zero divizion";
    domain_error ex("0");
    if(b.Numerator() == 0)
        throw ex;
    return a * Rational(b.Denominator(), b.Numerator());
}

istream& operator>>(istream& stream, Rational& a){
    int numerator = a.Numerator(), denominator = a.Denominator();
    stream >> numerator;
    stream.ignore(1);
    stream >> denominator;
    //stream.ignore(1);
    a = Rational(numerator, denominator);
    return stream;
}

ostream& operator<<(ostream& stream, const Rational& a){
    stream << a.Numerator() << '/'<< a.Denominator();
    return stream;
}

bool operator<(const Rational& a, const Rational& b){
    if((a - b).Numerator() < 0)
        return 1;
    return 0;
}
bool operator>(const Rational& a, const Rational& b){
    return !(a < b);
}



void TestZero(){
    {
        Rational a(0, 1);
        Rational b(0, 4);
        AssertEqual(a, b, "excepted(0, 4)");
    }

    {
        Rational a(0, 1);
        Rational b(0, 5);
        AssertEqual(a, b, "excepted(0, 5)");
    }

    {
        Rational a(0, 1);
        Rational b(0, -3);
        AssertEqual(a, b, "excepted(0, 3)");
    }
}

void TestReduction(){
    {
        Rational a(4, 2);
        Rational b(2, 1);
        AssertEqual(a, b, "excepted(2, 1)");
    }

    {
        Rational a(5, 5);
        Rational b(1, 1);
        AssertEqual(a, b, "excepted(1, 1)");
    }

    {
        Rational a(7, 1);
        Rational b(14, 2);
        AssertEqual(a, b, "excepted(14, 2)");
    }

    {
        Rational a(-34, -2);
        Rational b(17, 1);
        AssertEqual(a, b, "excepted(17, 1)");
    }
}

void TestNegative(){
    {
        Rational a(-1, 1);
        Rational b(1, -1);
        AssertEqual(a, b, "excepted(1, -1)");
    }

    {
        Rational a(-7, 3);
        Rational b(14, -6);
        AssertEqual(a, b, "excepted(14, -6)");
    }

    {
        Rational a(0, -1);
        Rational b(0, 4);
        AssertEqual(a, b, "excepted(0, 4)");
    }

    {
        Rational a(-1, -1);
        Rational b(1, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }
}

void TestConstructor(){
    {
        Rational a;
        Rational b(0, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }

    {
        Rational a;
        Rational b(0, 4);
        AssertEqual(a, b, "excepted(0, 1)");
    }

}

void TestOperators(){
    {
        Rational a(1, 3);
        Rational b(1, 3);
        AssertEqual(a + b, Rational(2, 3), "excepted(0, 1)");
    }

    {
        Rational b(7, 8);
        Rational a(1, 2);
        Assert(a < b, "");
    }

    {
        Rational a(4, 3);
        Rational b(3, 3);
        Assert((a - b == Rational(1, 3)), "excepted(0, 1)");
    }
}

void TestCritical(){
    {
        Rational a(2147483647, 2147483647);
        Rational b(1, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }

    {
        Rational a(2147483647, -2147483647);
        Rational b(-1, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }

    {
        Rational a(0, -2147483647);
        Rational b(0, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }

    {
        Rational a(2147483647, -2147483647);
        Rational b(-1, 1);
        AssertEqual(a, b, "excepted(0, 1)");
    }

    
}

void AllTest(){
    TestReduction();
    TestZero();
    TestConstructor();
    TestNegative();
    TestOperators();
    TestCritical();
}

int main() {
    TestRunner runner;
    runner.RunTest(TestReduction, "");
    runner.RunTest(TestZero, "");
    runner.RunTest(TestConstructor, "");
    runner.RunTest(TestNegative, "");
    runner.RunTest(TestOperators, "");
    runner.RunTest(TestCritical, "");
    return 0;
}
