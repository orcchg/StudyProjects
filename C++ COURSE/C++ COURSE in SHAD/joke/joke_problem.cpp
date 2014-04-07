#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;
 
string comment_erase(string str) {
  int  id;
  string::iterator tmp, last;
  for (string::iterator iter = str.begin(); iter != str.end(); ++iter) {
    if (*iter == '"') {
      iter += 1;
      while (*iter == '"' && iter != str.end()) {
        ++iter;
      }
    }

    if (*iter == '/') {  
      if (*(iter + 1) == '/') { 
        last = iter + 1;
        while (*last != '\n' && last != str.end()) {
          ++last;
        }

        tmp = iter - 1;
        str.erase(iter, last);  
        iter = tmp;
      } else if (*(iter + 1) == '*') { 
        id = 0;
        for (last = iter + 1; last + 1 != str.end(); ++last) {
          if (*last == '*' && *(last + 1) == '/') {  
            id = 1;
            last += 2;
            break;    
          }
        }

        if (id) { 
          tmp = iter - 1; 
          str.erase(iter, last);  
          iter = tmp; 
        }
      }
    }
  }
  return str;
}

int main(){
  char filename[255];
  char outname[255];
  strcpy(filename, "program.cpp");
  strcpy(outname, "program_wo_comments.cpp"); 

  fstream fp(filename, fstream::in);
  if (!fp.is_open()) {
    return 1;
  }
  long long size;
  string  str;
  fp.seekg(0L, ios::end);  
  size = fp.tellg(); 
  fp.seekg(0L, ios::beg);  
  if (!size) {  
    fp.close();
    return 2;
  }
  char* buf = new char[size]; 
  if (buf == NULL) { 
    fp.close();
    return 3;
  }
  fp.read(buf, size); 
  fp.clear();
  fp.close();

  buf[size - 1] = '\0';
  str.assign(buf);  
  delete [] buf; 
  buf = NULL;

  str = comment_erase(str); 

  fp.open(outname, fstream::out); 
  if (!fp.is_open()) {
    return 4;
  }
  fp.write(str.c_str(), str.length());
  fp.flush();
  fp.clear();
  fp.close();
  return 0;
}
