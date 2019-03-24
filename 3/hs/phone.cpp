#include "phone_number.h"
#include <iostream>
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number){
        stringstream s(international_number);
        
        string str = "";
        if(s.peek() != '+')
            throw invalid_argument("invalid number");
        s.ignore(1);
        getline(s, str, '-');
        if(str == "")
            throw invalid_argument("invalid number");
        country_code_ = str;
        //s.ignore(1);
        str = "";
        getline(s, str, '-');
        if(str == "")
            throw invalid_argument("invalid number");
        city_code_ = str;
        str = "";
        //s.ignore(1);
        getline(s, str);
        if(str == "")
            throw invalid_argument("invalid number");
        local_number_ = str;
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}
