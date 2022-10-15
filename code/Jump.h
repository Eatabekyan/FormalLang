#include "Condition.h"
#include <string>

class Jump{
public:
  Condition* Cond1;
  Condition* Cond2;
  bool isEpsilon;
  std::string word;
  Jump(Condition* Cond1, Condition* Cond2){
    this->Cond1 = Cond1;
    this->Cond2 = Cond2;
    this->isEpsilon = true;
    this->word = "";
  }
  Jump(Condition* Cond1, Condition* Cond2, std::string word){
    this->Cond1 = Cond1;
    this->Cond2 = Cond2;
    this->isEpsilon = false;
    this->word = word;
  }
};