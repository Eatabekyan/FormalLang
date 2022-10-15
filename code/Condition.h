#include <vector>

class Condition{
public:
  int Number;
  bool isStart;
  bool isFinal;
  bool isUsedForPDKA = false;
  std::vector<Condition*> includeConds;
  Condition(int Number, bool isStart, bool isFinal){
    this->Number = Number;
    this->isStart = isStart;
    this->isFinal = isFinal;
    this->includeConds.push_back(this);
  }
  Condition(bool isStart, bool isFinal){
    this->isStart = isStart;
    this->isFinal = isFinal;
  }
};