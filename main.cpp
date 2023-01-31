#include <iostream>
#include <fstream>
#include "automata.h"

bool Test1 () {
        Automata a ("Test.txt");
        std::vector<std::string> test1;
        test1.push_back("111110110110");
        test1.push_back("000001001001");
        test1.push_back("010101");
        test1.push_back("101010");
        test1.push_back("00111100");
        test1.push_back("11110000");
        if (a.execute() == test1) {
            std::cout << "Test1 successfully passed!" << std::endl;
            return 1;
        } else {
            std::cout << "Test1 finished unsuccessfully!" << std::endl;
            return 0;
        }
    }

int main() {
    std::cout << "Enter the path of the input file!" << std::endl;
    Test1();
    return 0;
}