#include "automata.h"
#include <algorithm>

int Automata::alphabet_validation(std::string alphabet) {
    for (int i = 0; i < alphabet.size(); ++i) {
        if (i%2 == 1) {
            if (alphabet[i] != ',') {
                std::cerr << "Characters must be delimited with commas!" << std::endl;
                exit(1);
            }
        } else {
            if (alphabet[i] == ',') {
                std::cerr << "Comma can't be an element of the input alphabet!" << std::endl;
                exit(2);
            }
        }
    }

    std::sort(alphabet.begin(), alphabet.end());
    for (int i = 0; i < alphabet.size() - 1; ++i) {
        if (alphabet[i] == ',') {
            continue;
        }
        if (alphabet[i] == alphabet[i+1]) {
            std::cerr << "Every element of the alphabet should appear only once!" << std::endl;
            exit(3);
        }
    }
    return 0;
}

int Automata::states_validation () {
    for (int i = 0; i < states_length; ++i) {
       for (int j = 0; j < states_length; ++j) {
            if (automata_states[i] == automata_states[j] && (i != j)) {
                std::cerr << "Two different states are not allowed to have the same name!" << std::endl;
                exit(4);
            }
       }
    }

    return 0;
}

int Automata::config_validation (std::string str) {
    int vbar_count = 0;
    int comma_count = 0;
    int i = 0;
    bool other = true;
    while (i < str.size()) {
        for (int j = 0; j < output_length; ++j) {
            if (str[i] == output_alphabet[j]) {
                other = false;
                break;
            }
        }
        if (other) {
            std::cout << "Configuration contains a symbol which doesn't belong to the output alphabet!" << std::endl;
            exit(5);
        }
        ++i;
        if (str[i] != ',') {
            std::cout << "The format of the config is violated (',' symbol not found in the right place)!" << std::endl;
            exit(6);
        }
        comma_count++;
        ++i;
        std::string s = "";
        while ((str[i] != '|') && (str[i] != '\0')) {
            s += str[i];
            ++i;
        }
        if (str[i] == '\0') {
            if (comma_count != input_length) {
                std::cerr << "The format of the config is violated !" << std::endl;
                exit(8);
            }

            if (vbar_count != (input_length - 1)) {
                std::cerr << "The format of the config is violated !" << std::endl;
                exit(9);
            }
            
            return 0;
        }
        vbar_count++;
        ++i;
    
        other = true;
        for (int k = 0; k < states_length; ++k) {
            if (s == automata_states[k]) {
                other = false;
            }
        }
        if (other) {
            std::cerr << "Either there's a state that doesn't belong to the state alphabet or the format of the config is violated( '|' symbol not found in the right place)!" << std::endl;
            exit(7);
        }
    }  
    return 0;
}

int Automata::tape_validation(std::string tape) {
    bool other;
    for (int i = 0; i < tape.size(); ++i) {
        other = true;
        for (int j = 0; j < input_length; ++j) {
            if (tape[i] == input_alphabet[j]) {
                other = false;
                break;
            }
        }
        if (other) {
            std::cerr << "There's no '"<< tape[i] << "' in the input alphabet!" << std::endl;
            exit(10);
        }
    }
    return 0;
}

std::string Automata::remove_whitespaces(std::string a) {
    std::string res_no_ws;
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != ' ') {
            res_no_ws += a[i];
        }
    } 
    return res_no_ws;
}

Automata::Automata (std::string file_path) {
    std::ifstream fin(file_path);
    std::string input;
    std::string output;
    std::string states;

    if (fin.fail()) {
        std::cerr << "Unable to open the file. Make sure that such file exists. \n" << std::endl;
        exit(-1);
    } 

    while (getline(fin, input)) {
        if(input != "") {
            break;
        } 
    }

    input_length = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == ',') {
            input_length++;
        }
    }
    input_length++;
    input = remove_whitespaces(input);
    alphabet_validation(input);

    while (getline(fin, output)) {
        if(output != "") {
            break;
        } 
    }

    output_length = 0;
    for (int i = 0; i < output.size(); ++i) {
        if (output[i] == ',') {
            output_length++;
        }
    }
    output_length++;
    output = remove_whitespaces(output);
    alphabet_validation(output);

    while (getline(fin, states)) {
        if(states != "") {
            break;
        } 
    }

    states_length = 0;
    for (int i = 0; i < states.size(); ++i) {
        if (output[i] == ',') {
            states_length++;
        }
    }
    states_length++;
    states = remove_whitespaces(states);

    
    input_alphabet = new char [input_length];
    output_alphabet = new char [output_length];
    automata_states = new std::string [states_length];

    for (int i = 0; i < input.size(); i += 2) {
        input_alphabet[i/2] = input[i];
    }
    if (input_alphabet[input_length-1] == '\0') {
        input_length--;
    }


    for (int i = 0; i < output.size(); i += 2) {
        output_alphabet[i/2] = output[i]; 
    }
     if (output_alphabet[output_length-1] == '\0') {
        output_length--;
    }


    int step = 0;
    for (int i = 0; i < states_length; ++i) {
        for (int j = step; j < states.size(); ++j) {
            if (states[j] == ',') {
                step = ++j;
                break;
            }
            automata_states[i] += states[j];
        }
    }
    if (automata_states[states_length-1] == "\0") {
        states_length--;
    } 
    
    states_validation();

    current_state = automata_states[0];

    

    std::string table;
    for (int i = 0; i < states_length; ++i) {
        while (getline(fin, table)) {
            if(table != "") {
                break;
            } 
        }
        table = remove_whitespaces(table);
        config_validation(table);
        bool indicator = 1;
        int count = 0;
        std::string out = "";
        std::string st = "";
        for (int j = 0; j < table.size(); ++j) {
            if (table[j] == ',') {
                indicator = 0;
                continue;
            }
            if (table[j] == '|') {
                count++;
                indicator = 1;
                continue;
            }
            if (indicator) {
                lambda [std::make_pair(input_alphabet[count],automata_states[i])] = table[j];
            } else {
                delta [std::make_pair(input_alphabet[count], automata_states[i])] += table[j];
            }
        }
    }

    std::string input_tape;
    while (!fin.eof()) {
        while (getline(fin, input_tape)) {
            if(input_tape != "") {
                tape_validation(input_tape);
                input_tapes.push_back(input_tape);
                break;
            }   
        }
        
    }
}

std::vector<std::string> Automata::execute () {
    std::string output_tape;
    for (int i = 0; i < input_tapes.size(); ++i) {
        output_tape = run_tape(input_tapes[i]);
        output_tapes.push_back(output_tape);
    }

    for (int i = 0; i < output_tapes.size(); ++i) {
        std::cout << output_tapes[i] << std::endl;
    }
    return output_tapes;
}

std::string Automata::run_tape (std::string tape) {
   std::string cur_state = automata_states[0];
   std::string out_tape = "";
   for (int i = 0; i < tape.size(); ++i) {
        out_tape += lambda[std::make_pair(tape[i], cur_state)];
        cur_state = delta[std::make_pair(tape[i], cur_state)];
    }
    return out_tape;
}

Automata::~Automata(){
    delete[] input_alphabet;
    delete[] output_alphabet;
    delete[] automata_states;
}

