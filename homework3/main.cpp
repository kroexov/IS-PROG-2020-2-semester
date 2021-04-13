#include "pugixml.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>


void maxcount(const std::multiset<std::string> &s) {
    std::string res;
    int max = 0;
    for (const auto &type : s) {
        if (s.count(type) > max) {
            max = s.count(type);
            res = type;
        }
    }
    std::cout << "номер маршрута: " << res << std::endl;
    std::cout << "количество остановок: " << max << std::endl << std::endl;
}

void stopscount(const std::multiset<std::string> &s) {
    std::string res;
    int max = 0;
    for (const auto &type : s) {
        if (s.count(type) > max) {
            max = s.count(type);
            res = type;
        }
    }
    std::cout << "название улицы: " << res << std::endl;
    std::cout << "количество остановок: " << max << std::endl << std::endl;
}

double hypotenuse(double x1, double x2, double y1, double y2) {
    double l, y, x;
    x = x2 - x1;
    y = y2 - y1;
    l = sqrt(pow(fabs(x), 2) + pow(fabs(y), 2));
    return l;
}

void longest(const std::unordered_map<std::string, std::vector<std::pair<double, double>>> &paths) {
    std::unordered_map<std::string, std::pair<std::string, double>> maximum_route;
    for (const auto &i: paths) {
        std::pair<std::string, std::string> v;
        auto ss = std::istringstream(i.first);
        std::string line;
        getline(ss, v.first, ' ');
        getline(ss, v.second, ' ');
        double R;
        double k1 = i.second[0].first, k2 = i.second[0].second;
        for (auto qw: i.second) {
            if (k1 != qw.first and k2 != qw.second) {
                R += hypotenuse(k1, k2, qw.first, qw.second);
                k1 = qw.first;
                k2 = qw.second;
            }
        }
        if (R > maximum_route[v.second].second) {
            maximum_route[v.second].second = R;
            maximum_route[v.second].first = v.first;
        }
    }
    for (const auto &i: maximum_route)
        std::cout << "Маршрут: " << i.second.first << std::endl << "Длина: " << i.second.second << std::endl;
    std::cout << std::endl;
}

void Routes_with_the_most_stops(const pugi::xml_document &doc) {

    std::cout << std::endl
              << "=== ЗАДАНИЕ 1: МАРШРУТЫ С НАИБОЛЬШИМ КОЛИЧЕСТВОМ ОСТАНОВОК ПО ОТДЕЛЬНЫМ ВИДАМ ТРАНСПОРТА ==="
              << std::endl << std::endl;

    auto object = doc.child("dataset").child("transport_station");

    std::multiset<std::string> busstops;
    std::multiset<std::string> trolstops;
    std::multiset<std::string> tramstops;

    while (object) {
        std::string type = object.child("type_of_vehicle").text().as_string();
        if (type == "Автобус") {
            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            auto sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                busstops.insert(wrd);
        }
        if (type == "Троллейбус") {
            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            auto sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                trolstops.insert(wrd);
        }
        if (type == "Трамвай") {
            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            auto sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                tramstops.insert(wrd);
        }
        object = object.next_sibling();
    }

    std::cout << "тип транспорта: Автобус" << std::endl;
    maxcount(busstops);
    std::cout << "тип транспорта: Троллейбус" << std::endl;
    maxcount(trolstops);
    std::cout << "тип транспорта: Трамвай" << std::endl;
    maxcount(tramstops);

}

void Street_with_max_stops(const pugi::xml_document &doc) {

    std::cout << std::endl << "=== ЗАДАНИЕ 2: УЛИЦА С НАИБОЛЬШИМ ЧИСЛОМ ОСТАНОВОК ==="
              << std::endl << std::endl;

    std::multiset<std::string> stops;

    auto object = doc.child("dataset").child("transport_station");
    while (object) {
        std::string street = object.child_value("location");
        if (!street.empty()) {
            if (street.find(',') != std::string::npos)
                stops.insert(street);
            else {
                std::string stop;
                auto sstream = std::istringstream(street);
                while (getline(sstream, stop, ',')) {
                    stops.insert(stop);
                }
            }
        }
        object = object.next_sibling();
    }
    stopscount(stops);
}

void The_longest_routes(const pugi::xml_document &doc) {
    std::cout << std::endl << "=== ЗАДАНИЕ 3: НАИБОЛЕЕ ДЛИННЫЙ МАРШРУТ ПО ОТДЕЛЬНЫМ ВИДАМ ТРАНСПОРТА ==="
              << std::endl << std::endl;

    auto object = doc.child("dataset").child("transport_station");

    std::unordered_map<std::string, std::vector<std::pair<double, double>>> buspaths;
    std::unordered_map<std::string, std::vector<std::pair<double, double>>> trolpaths;
    std::unordered_map<std::string, std::vector<std::pair<double, double>>> trampaths;

    while (object) {
        std::string type = object.child("type_of_vehicle").text().as_string();
        if (type == "Автобус") {
            std::string temp = object.child("coordinates").text().as_string();
            std::pair<double, double> v;
            auto sstream = std::istringstream(temp);
            std::string line;
            getline(sstream, line, ',');
            v.first = stod(line);
            getline(sstream, line, ',');
            v.second = stod(line);

            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            std::vector<std::string> route;
            sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                route.push_back(wrd);
            for (const auto &r: route)
                buspaths[r].push_back(v);
        }
        if (type == "Троллейбус") {
            std::string temp = object.child("coordinates").text().as_string();
            std::pair<double, double> v;
            auto sstream = std::istringstream(temp);
            std::string line;
            getline(sstream, line, ',');
            v.first = stod(line);
            getline(sstream, line, ',');
            v.second = stod(line);

            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            std::vector<std::string> route;
            sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                route.push_back(wrd);
            for (const auto &r: route)
                trolpaths[r].push_back(v);
        }
        if (type == "Трамвай") {
            std::string temp = object.child("coordinates").text().as_string();
            std::pair<double, double> v;
            auto sstream = std::istringstream(temp);
            std::string line;
            getline(sstream, line, ',');
            v.first = stod(line);
            getline(sstream, line, ',');
            v.second = stod(line);

            std::string wrd;
            std::string routes = object.child_value("routes");
            char k = (routes.find(',') != std::string::npos) ? ',' : '.';
            std::vector<std::string> route;
            sstream = std::istringstream(routes);
            while (getline(sstream, wrd, k))
                route.push_back(wrd);
            for (const auto &r: route)
                trampaths[r].push_back(v);
        }
        object = object.next_sibling();
    }

    std::cout << "тип транспорта: Автобус" << std::endl;
    longest(buspaths);
    std::cout << "тип транспорта: Троллейбус" << std::endl;
    longest(trolpaths);
    std::cout << "тип транспорта: Трамвай" << std::endl;
    longest(trampaths);

}

int main() {
    system("chcp 65001");
    pugi::xml_document doc;
    doc.load_file("data.xml");
    Routes_with_the_most_stops(doc);
    Street_with_max_stops(doc);
    The_longest_routes(doc);
    return 0;
}
