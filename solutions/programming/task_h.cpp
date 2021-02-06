#include <algorithm>
#include <fstream>
#include <set>
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

/* 
    Representation of (timestamp, +) and (timestamp, -)
    Time period of [timestamp_s, timestamp_e] can be represented 
    as an intersection of 2 timebeams: (timestamp_s, +) and (timestamp_e, -) 

    carry = +1 represents "+"
    carry = -1 represents "-"
*/
struct TimeBeam {
    TimeStamp point;
    int carry;

    TimeBeam(const TimeStamp &ts, char sign): point(ts) {
        carry = sign == '+' ? +1 : -1;
    }

    constexpr bool operator<(const TimeBeam &rhs) const {
        // we have to put + before - in case of equity
        return (point < rhs.point || (point == rhs.point && carry < rhs.carry));
    }

    constexpr bool operator==(const TimeBeam &rhs) const {
        // we have to put + before - in case of equity
        return (point == rhs.point && carry == rhs.carry);
    }

    std::string to_string() const {
        std::string end = (carry > 0) ? "+)" : "-)";
        return "({" + point.to_string() + "}, " + end;
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream input("input.txt");

    int n = -1;

    std::string line;
    std::vector <TimeBeam> timebeams;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        if (n == -1) {
            if (!(iss >> n)) {
                break; // error
            }
            timebeams.reserve(2 * n);
        } else {
            std::string start_s, end_s;
            if (!(iss >> start_s >> end_s)) {
                break; // error
            }

            timebeams.push_back({start_s, '+'});
            timebeams.push_back({end_s, '-'});
        }
    }

    std::sort(timebeams.begin(), timebeams.end());

    int couriers = 0, max_couriers_at_a_time = 0;

    for (auto &timebeam : timebeams) {
        couriers += timebeam.carry;

        if (couriers > max_couriers_at_a_time) {
            max_couriers_at_a_time = couriers;
        }

        //std::cout << timebeam.to_string() << " " << couriers << " " << max_couriers_at_a_time << std::endl;
    }

    std::cout << max_couriers_at_a_time << std::endl;

    return 0;
}

/*

Let's use + to denote the start of a segment and − to denote the end. For each segment, create two pairs, one for each endpoint:

Segment1: (-2, +), (3, -)
Segment2: (1, +), (5, -)
Segment3: (-3, +), (1, -)

Sort the 2N pairs by their first coordinate (in case of equality, put + before -). 
You can do this in time O(NlogN) with any reasonable sorting algorithm, or in time O(N+K) using key-indexed counting. In the example, we get:

(-3, +)
(-2, +)
(1, +)
(1, -)
(3, -)
(5, -)

Now process the endpoints in order. Maintain a count of the number of active segments, which is initially 0. 
Every time you process a +, increase the count by 1. Every time you process a −, decrease the count by 1. After processing each endpoint, check if the new count is higher than the largest count so far; if it is, update your solution.

(-3, +) -> count=1, max_count=0, sol=-3
(-2, +) -> count=2, max_count=1, sol=-2
(1, +) -> count=3, max_count=2, sol=1
(1, -) -> count=2, max_count=3, sol=1
(3, -) -> count=1, max_count=3, sol=1
(5, -) -> count=0, max_count=3, sol=1
This second phase of the algorithm takes time proportional N. The whole algorithm takes time O(NlogN) with a generic sort, or O(N+K) with key-indexed counting.

*/