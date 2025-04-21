#include <string>
#include "extensions/String.h"
#include <algorithm>
#include <cctype>

namespace stho {
    std::string String::toLower(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return input;
    }

    std::string String::toUpper(std::string input) {
        std::transform(input.begin(), input.end(), input.begin(),
               [](unsigned char c) { return std::toupper(c); });
        return input;
    }

    std::string String::trim(std::string input) {
        input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        input.erase(std::find_if(input.rbegin(), input.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), input.end());
        return input;
    }

    std::string String::trimLeft(std::string input) {
        input.erase(input.begin(), std::find_if(input.begin(), input.end(), [](unsigned char ch) { return !std::isspace(ch); }));
        return input;
    }

    std::string String::trimRight(std::string input) {
        input.erase(std::find_if(input.rbegin(), input.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), input.end());
        return input;
    }
}