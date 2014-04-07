#include <string>	

class AbstractCodeGenerator {
public:
  AbstractCodeGenerator() {}
  virtual ~AbstractCodeGenerator() {}
  
  virtual std::string generateCode() = 0;
  virtual std::string someCodeRelatedThing() = 0;
};  

class JAVA : public AbstractCodeGenerator {
  std::string generateCode();
  std::string someCodeRelatedThing();
};

class C_PLUS_PLUS : public AbstractCodeGenerator {
  std::string generateCode();
  std::string someCodeRelatedThing();
};

class PHP : public AbstractCodeGenerator {
  std::string generateCode();
  std::string someCodeRelatedThing();
};

int main () {

}