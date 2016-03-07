
#ifndef MARKOV_CHAIN__BUILDER_H
#define MARKOV_CHAIN_BUILDER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

#include "markov_chain.h"

class Markov_Chain_Builder
{
public:
    Markov_Chain_Builder();
    ~Markov_Chain_Builder();

    //Add whole file to chain
    void Add_File_To_Chain(std::string filename);

    //Add individual line to chain
    void Add_Line_To_Chain(std::string line);

    //Once all desired data has been added to the chain,
    //run this method to construct the markov chain.
    void Build_Chain();
    
    //Ouptut random sequence
    std::vector<std::string> Output_Chain (int output_size);
    
    std::vector<std::string> m_data;

    Markov_Chain<std::string> m_chain;

    //Configurations:
    struct Markov_Cfg
    {
        //Data filter settings:
        bool accept_all;          //Set to true to accept all input, unfiltered
        std::string accept_regex; //Set to filter input strings. Regex is set using Set_Regex()

        //This character separates input elements
        char delimiter;

        //Set to true to separate data lines with newline characters
        bool split_lines;

        //CSV Options
        bool use_csv;      //Set to True to parse input file as CSV
        int csv_column;    //Set column number to only accept data from certain CSV column
        int csv_n_columns; //Set to the number of columns within the CSV file
    } m_cfg;
    void Set_Regex(std::string regex_str);

private:
    bool Is_Valid_Word(std::string word);
    void Initialize_Cfg();
    std::regex m_match_word;
};

#endif
