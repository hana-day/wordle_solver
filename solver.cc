#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

constexpr char REJECT[] = "reject";
constexpr char MATCH_CHAR_POS = 'o';
constexpr char FINISH[] = "ooooo";
constexpr char MATCH_CHAR = 'y';
constexpr char MATCH_NONE = 'x';

static bool isresult(const std::string &s) {
    if (s == REJECT)
        return true;
    if (s.length() != 5)
        return false;
    for (auto c : s) {
        if (c != MATCH_CHAR_POS && c != MATCH_CHAR && c != MATCH_NONE) {
            return false;
        }
    }
    return true;
}

static void print_guess(const std::string &guess) {
    std::cout << "I guess the word is ...: " << guess << std::endl;
}

static std::string receive_result() {
    std::string result;
    do {
        std::cout << "Enter result in 5 length string or \"reject\""
                  << std::endl;
        std::cout
            << "(o=match character&position, y=match character only, x=other):";
    } while (!(std::getline(std::cin, result) && isresult(result)));
    return result;
}

static void remove_from_candidates(std::vector<std::string> &candidates,
                                   const std::string &guess,
                                   const std::string &result) {
    for (int i = 0; i < 5; i++) {
        char c = guess.at(i);
        char r = result.at(i);
        if (r == MATCH_CHAR_POS) {
            for (auto it = candidates.begin(); it != candidates.end();) {
                if (it->at(i) != c)
                    candidates.erase(it);
                else
                    ++it;
            }
        } else if (r == MATCH_CHAR) {
            for (auto it = candidates.begin(); it != candidates.end();) {
                if (it->find(c) == std::string::npos || it->at(i) == c)
                    candidates.erase(it);
                else
                    ++it;
            }
        } else if (r == MATCH_NONE) {
            for (auto it = candidates.begin(); it != candidates.end();) {
                if (it->find(c) != std::string::npos)
                    candidates.erase(it);
                else
                    ++it;
            }
        }
    }
}

int main() {
    std::ifstream ifs;
    ifs.open("words.txt");
    if (!ifs) {
        std::cerr << "words.txt not found" << std::endl;
        return 1;
    }
    std::vector<std::string> candidates;
    std::string word;
    while (ifs >> word) {
        candidates.push_back(word);
    }
    std::string guess, result;
    while (1) {
        if (candidates.size() == 0) {
            std::cout << "Sorry, we cannot guess the word.." << std::endl;
            return 0;
        }
        guess = candidates.at(0);
        print_guess(guess);
        result = receive_result();
        if (result == REJECT) {
            candidates.erase(candidates.begin());
            continue;
        } else if (result == FINISH) {
            return 0;
        }
        remove_from_candidates(candidates, guess, result);
    }

    return 0;
}