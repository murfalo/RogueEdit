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

  static const std::string prefix = "static const QStringList itemList = {";
  static const std::string suffix = "};";

  std::string word;
  std::string* output = new std::string(prefix);

  while (parser >> word)
  {
    std::getline(parser, word);  // Grab the rest of the line
    word.erase(std::remove(word.begin(), word.end(), '\t'), word.end());
    word.erase(std::remove(word.begin(), word.end(), '\n'), word.end());
    word.erase(std::remove(word.begin(), word.end(), '\r'), word.end());
    *(output) += "\"" + word + "\",";
  }

  output->pop_back();
  output->append(suffix);   // Append the suffix
  dest << *(output);        // Store the output in dest
  dest.close();
  delete output;
}
