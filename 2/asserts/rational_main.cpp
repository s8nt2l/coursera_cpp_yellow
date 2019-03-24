class Rational {
private:
    int numerator, denominator;
        
    bool isLow(int a, int b){
        if(a < 0)
            if(b < 0)
                return 0;
            else
                return 1;
        else 
            if(b < 0)
                return 1;
        return 0;
    }

    int gcd(int a, int b){
        if(a == 0)
            return 1;
        while(a > 0 && b > 0){
            if(a > b)
                a = a % b;
            else 
                b = b % a;
        }
        return a + b;
    }
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int numerator, int denominator) {
        invalid_argument ex("0");
        if(denominator == 0)
            throw ex;
        int g = gcd(abs(numerator), abs(denominator));
        this->numerator = (int)(isLow(numerator, denominator)) ? (-abs(numerator) / g) : (abs(numerator) / g);
        this->denominator = (numerator == 0) ? 1 : (abs(denominator) / g);
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }
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
