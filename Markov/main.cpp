
#include <vector>
#include <getopt.h>

#include "csv_parser.h"
#include "markov_chain_builder.h"

static std::string file = "";
static Markov_Chain_Builder* chain;
static int out_size = 25;
static bool print_debug = false;

static void set_config(int argc, char* argv[])
{
    int option_index;
    static struct option options[] =
    {
        {"file",       required_argument, 0, 'f'},
        {"size",       required_argument, 0, 's'},
        {"regex",      required_argument, 0, 'r'},
        {"all",        no_argument, 0, 'a'},
        {"csv",        no_argument, 0, 'c'},
        {"line",       no_argument, 0, 'l'},
        {"debug",      no_argument, 0, 'd'},
        {"help",       no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((option_index = getopt_long(argc, argv, "calhdf:s:r:", options, NULL)) != -1)
    {
        switch (option_index){
            case 'f':
                file = optarg;
                break;
            case 's':
                out_size = strtoul(optarg, NULL, 10);
                break;
            case 'r':
                chain->Set_Regex(optarg);
                break;
            case 'a':
                chain->m_cfg.accept_all = true;
                break;
            case 'l':
                chain->m_cfg.split_lines = true;
                break;
            case 'c':
                chain->m_cfg.use_csv = true;
                break;
            case 'd':
                print_debug = true;
                break;
            case 'h':
                std::cout << "\nUsage: markov [options]"
                          << "\nGenerates Markov chain from text input and generates new text sequence."
                          << "\n"
                          << "\n\t[-f | --file ] <filename>  Generate chain from file."
                          << "\n\t[-r | --regex] <regex>     Set new regex string filter."
                          << "\n\t[-s | --size ] <size>      Set number of words generated."
                          << "\n\t[-c | --csv  ]             Parse input file as CSV file."
                          << "\n\t[-a | --all  ]             Accept all input without regex filter."
                          << "\n\t[-l | --line ]             Use newlines as chain entries."
                          << "\n\t[-d | --debug]             Print out the status of the chain."
                          << "\n\t[-h | --help ]             Display help and exit."
                          << "\n\n";
                exit(EXIT_SUCCESS);
                break;
            default:
                std::cout<< "\nInvalid option. Program exiting.\n";
                exit(EXIT_FAILURE);
                break;
        }
    }
    if (file == "")
    {
        std::cout<< "\nError: Input file must be selected.\n";
        exit(EXIT_FAILURE);
    }
}

template<typename T>
static void Print_Vector(std::vector<T> arr)
{
    const int size = arr.size();
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main (int argc, char* argv[])
{
    std::vector<std::string> sequence;
    chain = new Markov_Chain_Builder();

    set_config(argc, argv);

    chain->Add_File_To_Chain(file);
    chain->Build_Chain();
    sequence = chain->m_chain.Output_Random_Sequence(out_size);
    Print_Vector<std::string>(sequence);
    if (print_debug) chain->m_chain.To_String();

    delete chain;
    return EXIT_SUCCESS;
}
