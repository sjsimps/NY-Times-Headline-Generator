
#ifndef MARKOV_CHAIN_H
#define MARKOV_CHAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

struct Edge;
struct State;

class Markov_Chain
{
public:
    Markov_Chain();
    ~Markov_Chain();

    void Parse_File(std::string filename);
    void Build_Chain();
    void Output_Chain (int output_size);

    struct Markov_Cfg
    {
        //Set to true to accept all input, unfiltered
        bool accept_all;

        //Set to true to separate input data by newline
        //characters
        bool split_lines;

        //CSV Options
        bool use_csv;
        int csv_column;
        int csv_n_columns;
    } m_cfg;

    std::vector<std::string> m_data;
    std::map<std::string,State> m_map;

private:
    bool Is_Valid_Word(std::string word);
    void Add_line_to_chain(std::string line);
    void Initialize_Cfg();
};

struct State
{
    std::string data;
    unsigned int num_events;
    Edge* edge_list;
};

struct Edge
{
    unsigned int event_rate;
    State* next_state;
    Edge* next_edge;
};

#endif
