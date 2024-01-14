#pragma once

struct HighscoreStruct {
  char username[21] = "";
  int points = 0;

  HighscoreStruct(std::string name, int p) {
    for(size_t i = 0; i < name.size(); ++i) {
      username[i] = name[i];
    }
    username[name.size()] = '\0';
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
    void cleanHighscores();
    std::vector <HighscoreStruct> getHighscoresVector();
    void saveFile();
    ~Highscore() {};
};