#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Automat.h"
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::DeleteEpsilons() {
  for (int i = 0; i < this->delta.size(); i++) {
    if (this->delta[i].isEpsilon) {
      this->delta[i].Cond1->isFinal |= this->delta[i].Cond2->isFinal;
      for (int j = 0; j < this->delta.size(); j++) {
        if (this->delta[j].Cond1 == this->delta[i].Cond2) {
          if (this->delta[j].isEpsilon) {
            this->delta.push_back(
                Jump(this->delta[i].Cond1, this->delta[j].Cond2));
          } else {
            this->delta.push_back(Jump(this->delta[i].Cond1,
                                       this->delta[j].Cond2,
                                       this->delta[j].word));
          }
        }
      }
      this->delta.erase(this->delta.begin() + (i--));
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::MakeOneLetterWords() {
  for (int i = 0; i < this->delta.size(); i++) {
    if (this->delta[i].word.length() > 1) {
      AddCondition(false, false);
      this->delta.push_back(Jump(this->delta[i].Cond1,
                                 this->Q[this->Q.size() - 1],
                                 this->delta[i].word.substr(0, 1)));
      this->delta.push_back(Jump(
          this->Q[this->Q.size() - 1], this->delta[i].Cond2,
          this->delta[i].word.substr(1, this->delta[i].word.length() - 1)));
      this->delta.erase(this->delta.begin() + (i--));
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::AddCondition(bool isStart, bool isFinal) {
  this->Q.push_back(new Condition(this->Q.size(), isStart, isFinal));
  if (isStart) {
    this->start = this->Q[this->Q.size() - 1];
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::AddJump(int Num1, int Num2) {
  this->delta.push_back(Jump(this->Q[Num1], this->Q[Num2]));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::AddJump(int Num1, int Num2, std::string word) {
  this->delta.push_back(Jump(this->Q[Num1], this->Q[Num2], word));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::TurnIntoDKA() {
  if (!this->isDKA) {
    this->MakeOneLetterWords();
    this->DeleteEpsilons();
    this->isDKA = true;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::TurnIntoPDKA() {
  if (!this->isPDKA) {
    this->isPDKA = true;
    this->TurnIntoDKA();
    std::vector<Condition*> curr;
    std::vector<Jump> currdelta;
    curr.push_back(this->start);
    for (int i = 0; i < curr.size(); i++) {
      curr[i]->isUsedForPDKA = true;
      for (int let = 0; let < this->Alphabeth.size(); let++) {
        Condition* c = new Condition(-1, false, false);
        c->includeConds.pop_back();
        for (int j = 0; j < this->delta.size(); j++) {
          if (this->delta[j].Cond1 == curr[i] &&
              this->delta[j].word[0] == this->Alphabeth[let]) {
            c->includeConds.push_back(this->delta[j].Cond2);
            c->isFinal = c->isFinal | this->delta[j].Cond2->isFinal;
          }
        }
        bool tf = false;
        for (int j = 0; j < this->Q.size(); j++) {
          if (c->includeConds == this->Q[j]->includeConds) {
            delete c;
            c = this->Q[j];
            tf = true;
            break;
          }
        }
        if (curr[i]->Number != -1) {
          currdelta.push_back(
              Jump(curr[i], c, std::string(1, this->Alphabeth[let])));
        }
        if (!c->isUsedForPDKA) {
          curr.push_back(c);
          if (!tf) {
            if (c->includeConds.size() != 0) {
              c->Number = Q.size();
            }
            this->Q.push_back(c);
            for (int k = 0; k < c->includeConds.size(); k++) {
              for (int j = 0; j < this->delta.size(); j++) {
                if (c->includeConds[k] == this->delta[j].Cond1) {
                  this->delta.push_back(
                      Jump(c, this->delta[j].Cond2, this->delta[j].word));
                }
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < this->Q.size(); i++) {
      if (!this->Q[i]->isUsedForPDKA) {
        delete this->Q[i];
        this->Q.erase(this->Q.begin() + (i--));
      }
    }
    this->Q = curr;
    this->delta = currdelta;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::PrintKA() {
  std::cout << "---------------Loading--------------" << std::endl;
  std::cout << "---------------Start--------------" << std::endl;
  for (int i = 0; i < this->Q.size(); i++) {
    if (this->Q[i]->isStart) {
      std::cout << "q" << this->Q[i]->Number << std::endl;
      break;
    }
  }
  std::cout << "---------------Finals--------------" << std::endl;
  for (int i = 0; i < this->Q.size(); i++) {
    if (this->Q[i]->isFinal) {
      std::cout << "q" << this->Q[i]->Number << " ";
    }
  }
  std::cout << std::endl;
  std::cout << "---------------GET AUTOMAT--------------" << std::endl;
  for (int i = 0; i < this->delta.size(); i++) {
    std::cout << "q" << this->delta[i].Cond1->Number << "--"
              << this->delta[i].word << "-->q" << this->delta[i].Cond2->Number
              << std::endl;
  }
  std::cout << "-------------------END-----------------" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Automat::TurnIntoAdditionPDKA() {
  for (int i = 0; i < this->Q.size(); i++) {
    this->Q[i]->isFinal = !this->Q[i]->isFinal;
  }
}
///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
