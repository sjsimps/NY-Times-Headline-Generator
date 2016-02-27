
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

struct Markov_Edge;
struct Markov_State;

class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    //Add whole file to chain
    void Parse_File(std::string filename);

    //Add individual line to chain
    void Add_line_to_chain(std::string line);

    //Once all desired data has been added to the chain,
    //run this method to construct the markov chain.
    void Build_Chain();
    
    //Ouptut random sequence
    std::vector<std::string> Output_Chain (int output_size);
    
    //Data Access:
    // Every input data piece is stored in m_data
    // Every Markov chain state is indexed by m_map
    // Once the markov chain has been built using Build_Chain(), each input
    // data piece is mapped to a markov state.
    std::vector<std::string> m_data;
    std::map<std::string,Markov_State> m_map;

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


struct Markov_State
{
    std::string data;       //Data that corresponds to this state
    unsigned int num_events;//Number of times this state has occured given the input data
    Markov_Edge* edge_list; //List containing all edges to a next possible state
};

struct Markov_Edge
{
    unsigned int event_rate; //Number of time this edge has been taken from previous state given the input data
    Markov_State* next_state;//Next state corresponding to this edge
    Markov_Edge* next_edge;  //Next edge within the edge list
};

#endif
