// header library: capture the flag
/// processes positional arguments first. Once the first flag appears, the tool will interpret every following argument as flag and parameters


#pragma once
#include <string>
#include <vector>


struct structured_arg{
    bool is_flag = false;
    std::string flag;
    std::string content;
};

// args and flags struct = the main return product
struct flag_content{
    std::vector<std::string> v;
    bool no_args = false;
    bool valid = true;
    bool version = false;
    bool help = false;
    std::vector<structured_arg> arg_lst;

    void process_loop();
    std::string dump_args();
};

structured_arg make_arg(bool is_flg, std::string flg, std::string cont) {
    return structured_arg{is_flg, flg, cont};
}

/// for debugging
// returns a formatted string ready for printing that contains all the args and flags
std::string flag_content::dump_args() {
    std::string result_string = "";
    std::vector<structured_arg> vec = this->arg_lst;
    result_string += "Found the following arguments:\n";
    for (int i = 0; i < this->arg_lst.size(); i++) {
        if (!vec[i].is_flag) {
            std::string position = std::to_string(i);
            result_string += "Positional Arg No. " + position + ": " + vec[i].content + "\n";
        } else {
            result_string += "Flag " + vec[i].flag + ": " + vec[i].content + "\n";
        }
    }
    return result_string;
}

/// The main process loop for transforming the initial args into a vector of structured arg objects
// Interprets everything before the first flag as a positional arg. Then processes flags
void flag_content::process_loop() {
    // Initial setup
    // this function can end at any time, leaving the struct in its configuration until that point
    if (this->v.size() < 1) {
        this->no_args = true;
        return;
    }
    int initial_length = this->v.size();
    int current_idx = 0;
    // find args that preceed the flags
    bool found_flag = false;
    while (!found_flag) {
        // end the function if there are no more args to process
        if (current_idx >= initial_length) {
            return;
        }
        // load the current arg and see if its a flag
        std::string current = this->v[current_idx];
        if (current[0] == '-') {
            found_flag = true;
            continue;
        }
        // turn into a structured arg
        auto new_arg = make_arg(false, "", current);
        this->arg_lst.push_back(new_arg);
        current_idx++;
    }
    // positional done
    // process flags
    while (current_idx < initial_length) {
        // collect the flag content and verify it is a flag
        std::string current_flag = this->v[current_idx];
        if (current_flag[0] != '-') {current_idx++; continue;}
        // see if it contains a parameter
        std::string current_content = "";
        if (current_idx + 1 < initial_length) {
            if (this->v[current_idx + 1][0] != '-') {
                current_content = this->v[current_idx + 1];
                current_idx++;
            }
        }
        // assemble the structured arg entry
        auto new_arg = make_arg(true, current_flag, current_content);
        this->arg_lst.push_back(new_arg);
        current_idx++;
    }
    return;
}

// Main entry point for processing cli arguments
flag_content process_cli_arguments(int length, char *ptrs[]) {
    // transform into a vector of strings
    std::vector<std::string> arg_vector;
    for (int i = 1; i < length; i++) {
        std::string s = ptrs[i];
        arg_vector.push_back(s);
    }
    //make the flag_content object that gets passed around.
    flag_content result{arg_vector};
    // main positional arg processing loop
    result.process_loop();

    return result;
}
