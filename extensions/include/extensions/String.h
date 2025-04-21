//
// Created by stenm on 21.04.2025.
//

#pragma once

namespace stho {

    class String {
    public:
        static std::string toLower(std::string input);
        static std::string toUpper(std::string input);
        static std::string trim(std::string input);
        static std::string trimLeft(std::string input);
        static std::string trimRight(std::string input);
    };

}
