#include <string>
#include <vector>

#include "Jump.h"

class Automat {
 public:
  std::vector<char> Alphabeth;
  std::vector<Condition*> Q;
  Condition* start;
  std::vector<Jump> delta;

  Automat(std::vector<char> Alphabeth, std::vector<Condition*> Q,
          Condition* start, std::vector<Jump> delta) {
    this->Q = Q;
    this->start = start;
    this->delta = delta;
    this->Alphabeth = Alphabeth;
  }

  void AddCondition(bool isStart, bool isFinal);
  void AddJump(int Number1, int Number2);
  void AddJump(int Number1, int Number2, std::string word);
  void PrintKA();
  void TurnIntoDKA();
  void TurnIntoPDKA();
  void TurnIntoAdditionPDKA();
  void TurnIntoMinPDKA();

 private:
  bool isDKA = false;
  bool isPDKA = false;
  bool isMinPDKA = false;
  bool isAdditionPdka = false;

  void DeleteEpsilons();
  void MakeOneLetterWords();
};