#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

struct HighscoreStruct {
  char username[20];
  int points;

  HighscoreStruct(std::string name, int p) {
    for(int i = 0; i < name.size() ; ++i) {
      username[i] = name[i];
    }
    points = p;
  }
  HighscoreStruct() {}
};

class Highscore {
  private:
    std::vector <HighscoreStruct> highscoreVector;
    std::string path;
  public:
    Highscore(std::string filePath);
    void addScore(HighscoreStruct toAdd);
    std::vector <HighscoreStruct> getHighscores();
    void saveFile();
};