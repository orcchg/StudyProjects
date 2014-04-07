#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;
using std::ofstream;
using std::remove;

int clear_comments (ofstream * const destination, ifstream &source, const char * const &destination_name) {
  destination->open(destination_name, ofstream::out);

  if (destination->fail()) {
    cout << "Fail opening file " << destination_name << endl;
    return -1;
  }
  
  source.seekg (0, ifstream::end);
  const ifstream::streampos source_length = source.tellg();
  source.seekg (0, ifstream::beg);

  while (source.good()) {
    char symbol = source.get();

    if (symbol == '\"' || symbol == '\'') {
      const char closing_quotes = symbol;
      destination->put(symbol);
      while (source.good()) {
        symbol = source.get();
        if (source.good()) {
          destination->put(symbol);
        }
        if (symbol == '\\') {
          char next_symbol = source.get();
          if (source.good()) {
            destination->put(next_symbol);
          }
          continue;
        }
        if (symbol == closing_quotes) {
          break;
        }
      }
      continue;      
    }

    if (symbol == '/') {
      char next_symbol = source.get();
      
      if (next_symbol == '/') {
        source.ignore(source_length - source.tellg(), '\n');
        destination->put('\n');
        continue;
      } 
      
      if (next_symbol == '*') {
        while (source.good()) {
          if (source.get() == '*') {
            if (source.get() == '/') {
              break;
            } else {
              source.seekg (-1, ifstream::cur);
            }
          }
        }
        continue;
      }
    }

    if (source.good()) {
      destination->put(symbol);
    }
  }

  destination->close();
  return 0;
}


int main (int argc, char *argv[]) {

  if (argc < 2) {
    cout << "Enter filename and try again" << endl;
    return 0;
  }

  ifstream source (argv[1], ifstream::in);

  if (source.fail()) {
    cout << "Fail with opening file " << argv[1] << endl;
    return 0;
  }

  ofstream buffer;

  char* buffer_name = "buffer_file.txt";

  if (clear_comments (&buffer, source, buffer_name) == -1) {
    return -1;
  }

  source.close();

  if (remove(argv[1]) != 0) {
    cout << "Error deleting file";
    return -1;
  }

  if (rename(buffer_name, argv[1]) != 0) {
    cout << "Error renaming file";
    return -1;
  }

  return 0;
} 