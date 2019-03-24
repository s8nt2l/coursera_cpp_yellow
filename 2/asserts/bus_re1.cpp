#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
using namespace std;



enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string type;
    cin >> type;
    map<string, QueryType> types = {
        {"NEW_BUS",        QueryType::NewBus},
        {"BUSES_FOR_STOP", QueryType::BusesForStop},
        {"STOPS_FOR_BUS",  QueryType::StopsForBus},
        {"ALL_BUSES",      QueryType::AllBuses}
    };
    q.type = types[type];
    switch (q.type){
        case QueryType::NewBus:
            cin >> q.bus;
            int stop_count;
            cin >> stop_count;
            q.stops.resize(stop_count);
            for(auto& stop : q.stops)
                cin >> stop;
            break;
        case QueryType::BusesForStop:
            cin >> q.stop;
            break;
        case QueryType::StopsForBus:
            cin >> q.bus;
            break;
        case QueryType::AllBuses:
            break;
        default:
            break;
    }
    return is;
}

struct BusesForStopResponse {
    bool is_found = 1;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if(!r.is_found){
        os << "No stop";
    } else {
        for(const auto& bus : r.buses)
            os << bus << ' ';
    }
    return os;
}

struct StopsForBusResponse {
    bool is_found = 1;
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_bus;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if(!r.is_found){
        os << "No bus";
        return os;
    }
    for(const auto& stop : r.stops){
        os << "Stop " << stop << ": ";
        if(r.stops_bus.at(stop).size() == 1){
            os << "no interchange";

            if(stop != r.stops.back())
                os << endl;
        } else {
            for(const auto& bus : r.stops_bus.at(stop))
                if(bus != r.bus)
                    os << bus << ' ';
            if(stop != r.stops.back())
                os << endl;
        }
    }
    return os;
}

struct AllBusesResponse {
    bool is_found = 1;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if(!r.is_found)
        os << "No buses";
    else{
        for(const auto& bus_item : r.stops_to_buses) {
            os << "Bus " << bus_item.first << ": ";
            for(const auto& stop : bus_item.second) {
                os << stop << " ";
            }
            if(bus_item.first != r.stops_to_buses.rend()->first)
                os << endl;
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        stops_to_buses[bus] = stops;
        for(const auto stop : stops){
            buses_to_stops[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        BusesForStopResponse result;
        if(buses_to_stops.count(stop) == 0)
            result.is_found = 0;
        else {
            result.is_found = 1;
        //result.is_found = (buses_to_stops.find(stop) == buses_to_stops.end()) ? 0 : 1;
            result.buses = buses_to_stops.at(stop);
        }
        return result;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        StopsForBusResponse result;
        result.bus = bus;
        if(stops_to_buses.count(bus) == 0)
            result.is_found = 0;
        else {
            result.is_found = 1;
            result.stops = stops_to_buses.at(bus);
        }
        //os << result.is_found << endl;
        result.stops_bus = buses_to_stops;
        return result;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse result;
        if(stops_to_buses.size() == 0)
            result.is_found = 0;
        else 
            result.is_found = 1;
        result.stops_to_buses = stops_to_buses;
        return result;
    }
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
    system("pause");
    return 0;
}
