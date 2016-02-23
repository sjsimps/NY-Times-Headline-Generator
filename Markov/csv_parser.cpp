
#include "csv_parser.h"

#include <iostream>
#include <fstream>

CSV_Parser::CSV_Parser(){}

CSV_Parser::~CSV_Parser(){}

std::string CSV_Parser::Get_Entry(int i)
{
    return m_data[i];
}

//Sets CSV data.
//Use column to select which CSV column is stored in data
//Set n_columns to select the number of data entries per row
//Setting column to zero parses all CSV data
void CSV_Parser::Set_Data(std::string filename, int column, int n_columns)
{
    bool in_paren = false;
    int end_of_line = false;

    std::ifstream file;
    std::string line;
    std::string entry;
    int entry_count = 0;
    int position = 0;
    int line_length;

    m_data.clear();

    file.open(filename);
    if (file.is_open())
    {
        while ( getline (file,line) )
        {
            line_length = line.length();
            position = 0;
            for (int i = 0; i < line_length; i++)
            {
                end_of_line = ((i+1) >= line_length) ? 1 : 0;

                if (line[i] == ',' || line[i] == 0xA || end_of_line)
                {
                    if(!in_paren)
                    {
                        if ((column == 0) || (entry_count % n_columns)+1 == column)
                        {
                            entry.append( line.substr(position, i - position + end_of_line) );
                            Handle_Quotes(&entry);
                            m_data.push_back(entry);
                        }
                        entry.clear();
                        position = i+1;
                        entry_count++;
                    }
                    else if (end_of_line)
                    {
                        entry.append( line.substr(position, i - position + end_of_line) );
                    }
                }
                else if (line[i] == '\"')
                {
                    if ( !( ((i+1) < line_length) && (line[i+1] == '\"') ) )
                    {
                        in_paren = !in_paren;
                    }
                    else i++;
                }
            }
            position = 0;
        }
        file.close();
    }
    else
    {
        std::cout << "File \"" << filename << "\" could not be opened!";
        exit(EXIT_FAILURE);
    }
    m_size = m_data.size();
}

void CSV_Parser::Handle_Quotes(std::string* str)
{
    for (unsigned int i = 0; i < str->length(); i++)
    {
        if ((*str)[i] == '\"')
        {
            str->erase(i,1);
            i--;
        }
    }
    //std::cout << "\n" << (*str);
}

