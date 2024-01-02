#include "Highscore.h"

bool operator < (HighscoreStruct hs1, HighscoreStruct hs2) {
  return hs1.points < hs2.points;
}

bool cmp (HighscoreStruct hs1, HighscoreStruct hs2) {
  return hs1.points > hs2.points;
}

Highscore::Highscore(std::string filePath) {
  this->path = filePath;
  std::ifstream highscoreFile(filePath, std::ios::binary | std::ios::in | std::ios::ate);
  if(!highscoreFile) {
    std::ofstream aux(filePath, std::ios::binary | std::ios::out);
    aux.close();
  } else {
    int size = highscoreFile.tellg() / sizeof(HighscoreStruct);
    highscoreFile.seekg(0);
    HighscoreStruct auxSt;
    for(int i = 0; i < size; ++i) {
      highscoreFile.read(reinterpret_cast<char *>(&auxSt), sizeof(HighscoreStruct));
      highscoreVector.push_back(auxSt);
    }
    highscoreFile.close();
  }
}

void Highscore::addScore(HighscoreStruct toAdd) {
  highscoreVector.push_back(toAdd);
  std::sort(highscoreVector.begin(), highscoreVector.end(), cmp);
  if(highscoreVector.size() > 10) { highscoreVector.resize(10); }
  this->saveFile();
}

void Highscore::cleanHighscores() {
  std::ofstream highscoreFile(path, std::ios::binary | std::ios::out | std::ios::trunc);
  highscoreVector.clear();
  highscoreFile.close();
}

std::vector <HighscoreStruct> Highscore::getHighscores() {
  return this->highscoreVector;
}

void Highscore::saveFile() {
  std::ofstream highscoreFile(path, std::ios::binary | std::ios::out | std::ios::trunc);
  if(!highscoreFile) {
    std::cerr<<"Error on highscore file"<<std::endl;
  } else {
    for (int i = 0; i < highscoreVector.size(); ++i){
      highscoreFile.write(reinterpret_cast<char *>(&highscoreVector[i]), sizeof(HighscoreStruct));
    }
    highscoreFile.close();
  }
}