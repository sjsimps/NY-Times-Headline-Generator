
#include <fstream>
#include <vector>
#include <regex>
#include <stdlib.h>

#include "markov_chain_builder.h"
#include "csv_parser.h"

Markov_Chain_Builder::Markov_Chain_Builder()
{
    Initialize_Cfg();
}

Markov_Chain_Builder::~Markov_Chain_Builder()
{
}

void Markov_Chain_Builder::Set_Regex(std::string regex_str)
{
    m_cfg.accept_regex = regex_str;
    m_match_word = std::regex (m_cfg.accept_regex, std::regex_constants::basic);
}

void Markov_Chain_Builder::Initialize_Cfg()
{
    m_cfg.accept_all = false;
    Set_Regex( "[a-zA-Z,\\.\\\"\\']*" );
    m_cfg.delimiter = ' ';
    m_cfg.split_lines = false;
    m_cfg.use_csv = false;
    m_cfg.csv_column = 3;
    m_cfg.csv_n_columns = 9;
}


bool Markov_Chain_Builder::Is_Valid_Word(std::string word)
{
    return m_cfg.accept_all || std::regex_match(word, m_match_word);
}


void Markov_Chain_Builder::Add_File_To_Chain(std::string filename)
{
    std::ifstream file;
    std::string line;


    file.open(filename);
    if (! m_cfg.use_csv)
    {
        if (file.is_open())
        {
            while ( getline (file,line) )
            {
                Add_Line_To_Chain(line);
            }
            file.close();
        }
        else
        {
            std::cout << "File \"" << filename << "\" could not be opened!";
            exit(EXIT_FAILURE);
        }
    }
    else //Parse input as CSV
    {
        CSV_Parser* csv = new CSV_Parser();
        csv->Set_Data(filename, m_cfg.csv_column, m_cfg.csv_n_columns);
        for (int i = 0; i < csv->m_size; i++)
        {
            line = csv->Get_Entry(i);
            Add_Line_To_Chain(line);
        }
        delete csv;
    }

}

void Markov_Chain_Builder::Build_Chain()
{
    const int data_size = m_data.size();
    std::string last_event = "";
    std::string current_event = m_data[0];

    m_chain.Add_Event(current_event);

    for (int i = 1; i < data_size; i++)
    {
        last_event = current_event;
        current_event = m_data[i];
        m_chain.Add_Event(last_event, current_event);
    }
}

void Markov_Chain_Builder::Add_Line_To_Chain(std::string line)
{
    int position = 0;
    int is_end;
    std::string word;
    int line_length = line.length();

    for (int i = 0; i < line_length; i++)
    {
        is_end = (i == line_length - 1) ? 1 : 0;

        if (line[i] == m_cfg.delimiter || is_end)
        {
            word = line.substr(position, i - position + is_end);
            position = (++i) % line_length;

            if (Is_Valid_Word(word))
            {
                m_data.push_back(word);
            }
        }
    }
    if (m_cfg.split_lines) m_data.push_back("\n");
}

