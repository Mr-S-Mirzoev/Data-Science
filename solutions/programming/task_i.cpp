#include <algorithm>
#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <iostream>

enum ThrowType {
    NEAR,
    FAR,
    PENALTY
};

enum Team {
    FIRST,
    SECOND
};

struct Throw {
    int8_t _team;
    int8_t _throw;
    Throw (int8_t team = Team::FIRST, int distance = 0): _team(team) {
        if (distance == -1) {
            _throw = ThrowType::PENALTY;
        } else if (distance <= 6) {
            _throw = ThrowType::NEAR;
        } else {
            _throw = ThrowType::FAR;
        }
    }
};

class MatchScore {
    std::array <int, 2> _score {};
public:
    void add_throw(const Throw &t) {
        switch (t._throw)
        {
        case ThrowType::PENALTY:
            ++_score[t._team];
            break;
        
        case ThrowType::NEAR:
            _score[t._team] += 2;
            break;
        
        case ThrowType::FAR:
            _score[t._team] += 3;
            break;

        default:
            throw std::logic_error("Wrong enum value");
            break;
        }
    }

    std::string to_string() const {
        return std::to_string(_score[0]) + ":" + std::to_string(_score[1]);
    }
};

int main(int argc, char const *argv[])
{
    std::ifstream input("input.txt");

    int n = -1;
    MatchScore score;

    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        if (n == -1) {
            if (!(iss >> n)) {
                break; // error
            }
        } else {
            int team, distance;
            if (!(iss >> team >> distance)) {
                break; // error
            }

            score.add_throw(Throw(team - 1, distance));
        }
    }

    std::cout << score.to_string() << std::endl;

    return 0;
}