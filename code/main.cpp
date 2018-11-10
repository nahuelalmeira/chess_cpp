#include "stringFunctions.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {

    string pgn_dir = "../pgn";
    string data_dir = "../data";

    string pgn_file_name = pgn_dir + "/" + argv[1];

    cout << "Reading file " << pgn_file_name << endl;
    removePlys(pgn_file_name, data_dir);
    buildMetadataFile(pgn_file_name, data_dir);

    return 0;
}
