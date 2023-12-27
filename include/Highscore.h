#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

struct HighscoreStruct {
  char username[20];
  int points;

  HighscoreStruct(char name[20], int p) {
    for(int i = 0; i < 20 ; ++i) {
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