#ifndef GUARD_stringFunctions_h
#define GUARD_stringFunctions_h
#include <string>
#include <vector>
#include <map>


std::string::size_type getFieldWidth(std::vector<std::string> fields);
std::string::size_type getFieldWidth(std::map<std::string, std::string> fields);
bool space(char c); 
std::string getField(std::string line);
std::string getData(std::string line);
void removePlys(std::string file_name, std::string data_dir);
std::string getKeys(std::map<std::string, std::string> fields);
std::string getOutputLine(std::map<std::string, std::string> fields);
void buildMetadataFile(std::string file_name, std::string data_dir);

#endif