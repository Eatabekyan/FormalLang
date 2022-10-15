#include <iostream>
#include "Automat.cpp"

int main(){
  std::vector<char> Alphabeth;
  int lettersNum;
  std::cin >> lettersNum;
  for(int i = 0 ;i < lettersNum ;i++){
    char letter;
    std::cin >> letter;
    Alphabeth.push_back(letter);
  }
  std::vector<Condition*> Q;
  std::vector<Jump> Delta;
  Automat KA = Automat(Alphabeth,Q,nullptr,Delta); 
  int CondNum;
  std::cin >> CondNum;
  for(int i = 0 ;i < CondNum ;i++){
    bool isStart, isFinal;
    std::cout << "q" << i <<std::endl;
    std::cout << "isStart: ";
    std::cin >> isStart;
    std::cout << "isFinal: ";
    std::cin >> isFinal;
    KA.AddCondition(isStart,isFinal);
  }
  int JumpNum;
  std::cin >> JumpNum;
  for(int i = 0 ;i < JumpNum ;i++){
    int first ,second;
    std::string word;
    std::cin >> first;
    std::cin >> word;
    std::cin >> second;
    if(word == "-"){
      KA.AddJump(first,second);
    }else{
      KA.AddJump(first,second,word);
    }
  }
  KA.PrintKA();
  KA.TurnIntoDKA();
  KA.PrintKA();
  KA.TurnIntoPDKA();
  KA.PrintKA();
  KA.TurnIntoAdditionPDKA();
  KA.PrintKA();
  return 0;
}