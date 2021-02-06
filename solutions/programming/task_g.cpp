#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

struct TimeStamp {
    unsigned h, m, s;

    TimeStamp(unsigned _h = 0, unsigned _m = 0, unsigned _s = 0):
        h(_h), m(_m), s(_s) {}

    TimeStamp(std::string string) {
        std::replace(string.begin(), string.end(), ':', ' ');
        std::istringstream iss(string);

        iss >> h >> m >> s;
    }

    constexpr bool operator<(const TimeStamp &rhs) const {
        if (h == rhs.h) {
            if (m == rhs.m) {
                return s < rhs.s;
            } else {
                return m < rhs.m;
            }
        } else {
            return h < rhs.h;
        }
    }

    constexpr bool operator==(const TimeStamp &rhs) const {
        return (h == rhs.h && m == rhs.m && s == rhs.s);
    }

    constexpr bool operator<=(const TimeStamp &rhs) const {
        return (*this == rhs || *this < rhs);
    }

    std::string to_string() const {
        return std::to_string(h) + ":" + std::to_string(m) + ":" + std::to_string(s);
    }
};

struct Period {
    TimeStamp start, end;

    Period(const TimeStamp &s, const TimeStamp &e):
        start(s), end(e) {}

    constexpr bool operator<(const Period &rhs) const {
        return start < rhs.start;
    }

    std::string to_string() const {
        return start.to_string() + " " + end.to_string();
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream input("input.txt");

    int n = -1;

    std::string line;
    std::vector <Period> orders;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        if (n == -1) {
            if (!(iss >> n)) {
                break; // error
            }
            orders.reserve(n);
        } else {
            std::string start_s, end_s;
            if (!(iss >> start_s >> end_s)) {
                break; // error
            }

            orders.push_back(
                Period(
                    TimeStamp(start_s),
                    TimeStamp(end_s)
                )
            );
        }
    }

    std::vector <TimeStamp> available_at(n);

    std::sort(orders.begin(), orders.end());

    unsigned used_couriers = 0;

    for (int order_id = 0; order_id < n; ++order_id) {
        int available_courier = -1;

        for (int courier_id = 0; courier_id < n; ++courier_id) {
            if (available_at[courier_id] <= orders[order_id].start) {
                available_courier = courier_id;
                break;
            } 
        }

        if (available_at[available_courier] == TimeStamp()) {
            ++used_couriers;
        }

        available_at[available_courier] = orders[order_id].end;
    }

    std::cout << used_couriers << std::endl;

    return 0;
}