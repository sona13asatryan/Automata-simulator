#include <iostream>
#include <fstream> 
#include <map>
#include <vector>


class Automata {
    private:
        int input_length;
        int output_length;
        int states_length;
        char* input_alphabet;
        char* output_alphabet;
        std::string * automata_states;
        std::map < std::pair<char, std::string>, std::string > delta;
        std::map < std::pair<char, std::string>, char > lambda;

        std::vector<std::string> input_tapes;
        std::vector<std::string> output_tapes;
        std::string current_state;

        int alphabet_validation(std::string);
        int states_validation();
        int config_validation(std::string);
        int tape_validation(std::string);
        std::string remove_whitespaces(std::string);

    public:
       Automata (std::string);
        ~Automata();


        std::vector<std::string> execute();
        std::string run_tape (std::string);
};