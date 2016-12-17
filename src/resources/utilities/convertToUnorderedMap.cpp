#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

/* Converts Windows Format text file (exported from Excel) containing item ID's and names into an array. */
int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cout << "Usage: ./convert <source> <destination>";
    return -1;
  }

  std::stringstream parser;
  std::ifstream src(argv[1]);   // Source file location
  std::ofstream dest(argv[2]);  // Destination file location

  if (src.fail()) std::cout << "Invalid source file." << std::endl;
  if (dest.fail()) std::cout << "Invalid destination file." << std::endl;

  parser << src.rdbuf();

  static const std::string prefix = "static const std::unordered_map<int, std::string> items = {";
  static const std::string suffix = "};";

  std::string ID;
  std::string name;
  std::string* output = new std::string(prefix);

  while (parser >> ID)
  {
    std::getline(parser, name); // Grab the rest of the line
    name.erase(std::remove(name.begin(), name.end(), '\t'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
    *(output) += "{" + ID + ",\"" + name + "\"},";
  }

  output->pop_back();       // Remove extra comma
  output->append(suffix);   // Append the suffix
  dest << *(output);        // Store the output in dest
  dest.close();
  delete output;
}
