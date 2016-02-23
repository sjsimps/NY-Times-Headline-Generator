
#include <string>
#include <vector>

#ifndef CSV_PARSER_H
#define CSV_PARSER_H

class CSV_Parser
{
public:
    CSV_Parser();
    ~CSV_Parser();

    //CSV data accessor
    std::string Get_Entry(int i);
    
    //Sets CSV data.
    //Use column to select which CSV column is stored in data
    //Set n_columns to select the number of data entries per row
    //Setting column to zero parses all CSV data
    void Set_Data(std::string filename, int column, int n_columns);

    int m_size;

private:
    void Handle_Quotes(std::string* str);
    std::vector<std::string> m_data;
    std::string m_filename;
};

#endif
