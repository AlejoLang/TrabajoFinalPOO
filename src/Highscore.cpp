#include <string>
#include <vector>
#include "Highscore.h"
#include <fstream>
#include <iostream>
#include <algorithm>

bool operator < (HighscoreStruct hs1, HighscoreStruct hs2) {
  return hs1.points < hs2.points;
}

bool cmp (HighscoreStruct hs1, HighscoreStruct hs2) {
  return hs1.points > hs2.points;
}

Highscore::Highscore(std::string filePath) {
  this->path = filePath;

  /* Try opening the highscores file */
  std::ifstream highscoreFile(filePath, std::ios::binary | std::ios::in | std::ios::ate);

  if(!highscoreFile) {
    /* If the file is not created, create an empty file in the path */
    std::ofstream aux(filePath, std::ios::binary | std::ios::out);
    aux.close();
  } else {
    /* If the file exist, get all the data into the highscoreVector */
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
  /* Add a score, then sort all the vector using the points*/
  highscoreVector.push_back(toAdd);
  std::sort(highscoreVector.begin(), highscoreVector.end(), cmp);

  /* Keep only the 10 greater items and save the file */
  if(highscoreVector.size() > 10) { highscoreVector.resize(10); }
  this->saveFile();
}

void Highscore::cleanHighscores() {
  /* Create a new empty file in the Highscores path overwriting the old one*/
  std::ofstream highscoreFile(path, std::ios::binary | std::ios::out | std::ios::trunc);
  highscoreVector.clear();
  highscoreFile.close();
}

std::vector <HighscoreStruct> Highscore::getHighscoresVector() {
  return this->highscoreVector;
}

void Highscore::saveFile() {
  /* Save the highscoreVector into the Highscores file*/
  std::ofstream highscoreFile(path, std::ios::binary | std::ios::out | std::ios::trunc);
  if(!highscoreFile) {
    std::cerr<<"Error on highscore file"<<std::endl;
  } else {
    for (size_t i = 0; i < highscoreVector.size(); ++i){
      highscoreFile.write(reinterpret_cast<char *>(&highscoreVector[i]), sizeof(HighscoreStruct));
    }
    highscoreFile.close();
  }
}