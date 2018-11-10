#include "stringFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::getline;
using std::isspace;
using std::find_if;
using std::ios;
using std::vector;
using std::map;
using std::pair;
using std::max;
using std::make_pair;

map<string, string > FIELDS_MAP = {
    make_pair("Black", "None"),
    make_pair("BlackElo", "None"),
    //make_pair("BlackTeam", "None"),
    //make_pair("BlackTeamCountry", "None"),
    make_pair("Date", "None"),
    make_pair("ECO", "None"),
    make_pair("Event", "None"),
    make_pair("EventCountry", "None"),
    make_pair("EventDate", "None"),
    make_pair("EventRounds", "None"),
    make_pair("EventType", "None"),
    make_pair("PlyCount", "None"),
    make_pair("Result", "None"),
    make_pair("Round", "None"),
    make_pair("Site", "None"),
    make_pair("Source", "None"),
    make_pair("SourceDate", "None"),
    make_pair("SourceTitle", "None"),
    make_pair("White", "None"),
    make_pair("WhiteElo", "None"),
    //make_pair("WhiteTeam", "None"),
    //make_pair("WhiteTeamCountry", "None")
};

vector<string > FIELDS = {
    "Black",
    "BlackElo",
    "BlackTeam",
    "BlackTeamCountry",
    "Date",
    "ECO",
    "Event",
    "EventCountry",
    "EventDate",
    "EventRounds",
    "EventType",
    "PlyCount",
    "Result",
    "Round",
    "Site",
    "Source",
    "SourceDate",
    "SourceTitle",
    "White",
    "WhiteElo",
    "WhiteTeam",
    "WhiteTeamCountry"                  
};

string::size_type getFieldWidth(vector<string> fields) {
    string::size_type max_size = 0;
    for(string s : fields)
        max_size = max(s.size(), max_size);
    return max_size;
}

string::size_type getFieldWidth(map<string, string> fields) {
    string::size_type max_size = 30;
    map<string, string>::iterator it = fields.begin();
    while(it != fields.end()) {
        max_size = max(it->first.size(), max_size);
        ++it;
    }
    return max_size;
}

bool space(char c) {
    return isspace(c);
}

bool doubleQuote(char c) {
    return c == '\"';
}

string getField(string line) {
    string::iterator it, b;
    b = line.begin(); 
    it = find_if(b, line.end(), space);
    return string(b+1, it); // +1 to avoid '['
}

string getData(string line) {
    string::iterator it, b;
    b = line.begin();
    it = find_if(b, line.end(), doubleQuote);
    b = it + 1;
    it = find_if(b, line.end(), doubleQuote);
    return string(b, it);
}

void removePlys(string file_name, string data_dir) {
    fstream pgn_file, output_file;
    pgn_file.open(file_name, ios::in);
    output_file.open(data_dir + "/noPly.txt", ios::out);
    string line, field, data, output_line;

    string::size_type field_width = getFieldWidth(FIELDS_MAP);

    int game = 0;
    bool new_game = false;
    output_file << "Game " << game++ << endl;
    while(getline(pgn_file, line)) {
        if(line[0] != '[') {
            if(new_game) {
                output_file << "Game " << game++ << endl;
                new_game = false;
            }
        } else {
            field = getField(line);
            data = getData(line);
            //cout << field << string(field_width - field.size() + 1, ' ') 
            //     << " " << data << endl;
            //getchar();
            //output_file << line << endl;
            output_line = field + string(field_width - field.size() + 1, ' ') + 
                          " " + data;
            output_file << output_line << endl;
            new_game = true;
        }
    }
}

string getOutputLine(map<string, string> fields) {
    map<string, string>::iterator it = fields.begin();
    string output_line;
    while(it != fields.end()) {
        output_line =  output_line + it->second + "|";
        ++it;
    }
    return output_line;
}

string getKeys(map<string, string> fields) {
    map<string, string>::iterator it = fields.begin();
    string output_line;
    while(it != fields.end()) {
        output_line =  output_line + it->first + "|";
        ++it;
    }
    return output_line;
}

/* Take a pgn file and build a CSV file with metadata (no ply sequence) */
void buildMetadataFile(string file_name, string data_dir) {
    fstream pgn_file, output_file;
    pgn_file.open(file_name, ios::in);
    output_file.open(data_dir + "/metadata.csv", ios::out);

    string field, data, line, output_line;
    map<string, string> fields_map = FIELDS_MAP;
    bool new_game = false;
    output_file << getKeys(fields_map) << endl;
    while(getline(pgn_file, line)) {
        //cout << line << endl;
        if(line[0] == '[') {
            field = getField(line);
            data = getData(line);
            fields_map[field] = data;
            new_game = true;
        } else if(new_game){
            output_line = getOutputLine(fields_map);
            output_file << output_line << endl;
            map<string, string> fields_map = FIELDS_MAP;
            new_game = false;
        }
    }
}

