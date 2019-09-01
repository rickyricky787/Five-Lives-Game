/*
Five Lives Game

Author: Ricky Rodriguez

A handman-like game, just replacing the handman with hearts.
You lose a life for every incorrect answer.
You win if you guess all the letters of the mystery word.
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

string selectWord(ifstream& infile, int rand_num);      //Selects a random word from text file
bool mysteryChecker(string mys_word, char guess);       //Checks if the letter you guessed is right
void displayLives(int lives);                           //Displays number of lives
void displayWord(vector<char> bank, string mys_word);   //Displays word selected from file
int addToCount(string mys_word, char guess);            //Adds your number of correct letters

int main()
{
  const int WORDS_IN_FILE = 5;				// The total number of words included in the file
  char guess;
  int correct = 0, lives = 6;
  string mys_word;
  char level;

  cout << "FIVE LIVES GAME\n\nA game where you have to guess a word." << endl;
  cout << "The word can be an item, name, or place.\nFive mistakes and you lose.\n" << endl;
  
  cout << "What level do you want to play?" << endl;

  do {
    cout << "Enter \"E\" for Easy, \"M\" for Medium, or \"H\" for Hard " << endl; 
    cin >> level;
    level = toupper(level);
  } while( (level != 'E') && (level != 'M') && (level != 'H') );

  ifstream infile;

  if (level == 'E')
  {
    infile.open("easy.txt");
  }
  else if (level == 'M')
  {
    infile.open("medium.txt");
  }
  else if (level == 'H')
  {
    infile.open("hard.txt");
  }

  srand(time(0));
  int mys_num = (rand() % WORDS_IN_FILE);   // Generates a random number

  mys_word = selectWord(infile, mys_num);

  vector<char> entered;   //Vector filled with entered letters (correct and incorrect)
  
  for (int i = 0; i < mys_word.length(); i++)  //Adds a point for each space in mys_word. This would 
  {                                            //give a free point for a space in the word
    if (mys_word[i] == ' ')                    //since you cannot add a space as a char.
    {
      correct++;                               //correct = one point
    }
  }

  while (correct < mys_word.length())   //Loop will end when user enters all correct letters
  {
    bool goodToGo = true;   //Used to check if user entered the same letter or a non-letter char

    displayWord(entered, mys_word);
    cout << endl;
    displayLives(lives);

    cout << endl << "Enter a letter: ";
    cin >> guess;
    cout << endl;

    for (int i = 0; i < entered.size(); i++)
    {
      if (entered[i] == guess || entered[i] == toupper(guess) || entered[i] == tolower(guess) )
      {
        cout << "Already entered. Guess another letter." << endl;
        goodToGo = false;
      }
    }

    if ( !((guess >= 'A' && guess <= 'Z') || (guess >= 'a' && guess <= 'z') ))
    {
      cout << "Do not enter numbers nor special characters." << endl;
      goodToGo = false;
    }

    if (goodToGo == true)
    {
      entered.push_back(guess);
      bool found = mysteryChecker(mys_word, guess); 

      if (found == true)
      { 
        correct = correct + addToCount(mys_word, guess);
        if (correct == mys_word.length())
        {
          displayWord(entered, mys_word);
          cout << endl << "You WON!" << endl;
          break;
        }

        cout << "The letter \"" << guess << "\" is in the mystery word." << endl;
      }

      else
      {
        lives--;
        if (lives == 0)
        {
          cout << "💀  You lost. GAME OVER  💀" << endl;
          cout << "The mystery word was \"" << mys_word << "\"." << endl;
          break;
        }
        
        cout << "Sorry, try another letter." << endl;
      }

    }

    cin.clear();
  }

  infile.close();
  
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

string selectWord(ifstream& infile, int rand_num) //Selects a random word from text file
{
  string word_;

  for (int i = 0; i < rand_num; i++)
  {
    infile.ignore(INT_MAX, '\n');;
  }

  getline(infile, word_);

  return word_;
}

bool mysteryChecker(string mys_word, char guess)  //Checks if the letter you guessed is right
{
  for (int i = 0; i < mys_word.length(); i++)
  {
    if (mys_word[i] == guess || mys_word[i] == toupper(guess) || mys_word[i] == tolower(guess) )
    {
      return true;
    }
  }
  return false;
}

void displayLives(int lives)   //Displays number of lives
{
  cout << "Lives left: ";
  for (int x = 0; x < lives; x++)
  {
    cout << "💛 ";
  }
}

void displayWord(vector<char> bank, string mys_word)  //Displays word selected from file
{
  
  cout << "Mystery word: ";
  for (int y = 0; y < mys_word.length(); y++)
  {
    bool found = false;
    for (int z = 0; z < bank.size(); z++)
    {
      if (mys_word[y] == bank[z] || mys_word[y] == toupper(bank[z]) || mys_word[y] == tolower(bank[z]) )
      {
        cout << mys_word[y]; //Reveals a letter if you have entered a correct one previously
        found = true;
      }
    }

    if (mys_word[y] == ' ')
    {
      cout << " ";    //If there is a space in the word, shows a space
      found = true;
    }

    if (found == false)
    {
      cout << "-";    //Displays empty lines for unsolved letters
    }
  }
}

int addToCount(string mys_word, char guess)  //Adds your number of correct letters
{
  int count = 0;

  for (int i = 0; i < mys_word.length(); i++)
  {
    if (mys_word[i] == guess || mys_word[i] == toupper(guess) || mys_word[i] == tolower(guess) )
    {
      count++;
    }
  }

  return count;
}