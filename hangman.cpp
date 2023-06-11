#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Hangman {
  public:
    string wrongGuess;
    char guess;
    bool wrongGuessActivated = false;
    int i, turns, attempts;
    string getWord();
    string getStringHangman();
    char getGuess();
    int getLenWord();
    int getTurns();
    void clearWindow();
    void isActivated();
    void game();
    void getUserHangman();
    void setUserWord();
    void verifyGuess(char guess);

  private:
    string word;
    char *hangman;
    int lenWord;
    void setHangman(char charc);
    void setHangmanSize();
    void setLenWord(int len);
    void setTurns();
};

void Hangman::clearWindow() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

string Hangman::getWord() {
  return word;
}

int Hangman::getLenWord() {
  return lenWord;
}

void Hangman::setLenWord(int len) {
  lenWord = len;
}

string Hangman::getStringHangman() {
  return hangman;
}

void Hangman::getUserHangman() {
  for (i = 0; i < getLenWord(); i++) {
    cout << hangman[i] << ' ';
  }
}

void Hangman::setHangmanSize() {
  hangman = new char[getLenWord()];    
}

void Hangman::setHangman(char charc) {
  word = getWord();
  for (i = 0; i < getLenWord(); i++) {
    if (charc != '_') {
      if (guess == word[i]) {
        hangman[i] = charc;
      }
    } else {
      hangman[i] = '_';
    }
  }
}

int Hangman::getTurns() {
  return turns;
}

void Hangman::setTurns() {
  turns = getLenWord() + 2;
}

void Hangman::setUserWord() {
  cout << "Inform a word: ";
  cin >> word;

  setLenWord(word.length());
  setHangmanSize();
  setHangman('_');
  setTurns();
  
  clearWindow();
}

char Hangman::getGuess() {
  return guess;
}

void Hangman::verifyGuess(char guess) {
  bool found = false;
  word = getWord();
  for (i = 0; i < getLenWord(); i++) {
    if (guess == word[i]) {
      setHangman(guess);
      found = true;
    }
  }
  if (!found) {
    turns--;
    wrongGuessActivated = true;
    if (wrongGuess.find(guess) == string::npos) {
      wrongGuess += guess;
    }
  }
}

void Hangman::isActivated() {
  if (wrongGuessActivated) {
    cout << '\n';
    for (i = 0; i < wrongGuess.length(); i++) {
      cout << wrongGuess[i];
    }
    cout << '\n';
  }
}

void Hangman::game() {
  cout << "The word has " << getLenWord() << " letters" << '\n';
  cout << '\n';
  getUserHangman();
  if (!wrongGuessActivated) {
    cout << '\n';
  }
  isActivated();
  cout << '\n';
  cout << "You have " << turns << " chances left!" << '\n';
  cout << "Take a guess: "; cin >> guess;
  clearWindow();

  verifyGuess(guess);
}

int main() {
  Hangman game;

  string hangman, word;
  char response;
  int turns;

  game.clearWindow();
  cout << "Inform 0 to exit the game!" << "\n\n";
  game.setUserWord();

  do {
    turns = game.getTurns();
    hangman = game.getStringHangman();
    word = game.getWord();
    char guess = game.getGuess();
    if (guess == '0') {
      game.clearWindow();
      cout << "See you later alligator!!" << '\n';
      break;
    } else if (hangman == word) {
      cout << word;
      cout << '\n' << "You Won!!" << "\n\n";
    } else if (turns == 0) {
      cout << "The word was " << word << '\n';
      cout << "You lost!" << "\n\n";
    } else {
      game.game();
    }
  } while (turns > 0 && hangman != word);
}
