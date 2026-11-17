#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;
int int_input(int max); // add max number input

class GOL
{
  const static int ROWS = 20;
  const static int COLS = 40;

  float row_prices[ROWS];
  bool field[ROWS][COLS]; // = {0}; // create 2d array
  // bool field[ROWS][COLS];// = {0}; // create 2d array

public:
  void display_field();
  void update_field();
  bool check(int A)     // tried casting the bools to bools but they Really wanted to be ints, so we have this 
  {
    if (A==0)
    {return 0;}
    else{return 1;}
  }
};

void GOL::display_field()
{

  for (int r = 0; r < ROWS; r++)
  {
    // cout << "Row "<<  setw(2) << right << r + 1 << "    "; // row numbers
    for (int s = 0; s < COLS; s++)
    {
      cout << (field[r][s] ? "O" : ".");
    }
    cout << endl;
  }
}

void GOL::update_field()
{
  bool temp[ROWS][COLS];
  int sum = 0;
  for (int r = 0; r < ROWS; r++)
  {
    // cout << "Row "<<  setw(2) << right << r + 1 << "    "; // row numbers
    for (int s = 0; s < COLS; s++)
    {

      sum = check(field[r - 1][s - 1]) + check(field[r][s - 1]) + check(field[r + 1][s - 1] )
      +check( field[r][s - 1]) + check(field[r][s + 1] )
      + check(field[r + 1][s - 1]) + check(field[r + 1][s]) + check(field[r + 1][s + 1]);


      //cout<<sum <<"="<< check(field[r - 1][s - 1]) << check(field[r][s - 1]) << check(field[r + 1][s - 1] )<<check( field[r][s - 1]) << check(field[r][s + 1] )<< check(field[r + 1][s - 1]) << check(field[r + 1][s]) << check(field[r + 1][s + 1])<<endl;

      if(sum==3){ temp[r][s] = 1;} 
      else if (sum == 2 && field[r][s])
      {
        temp[r][s] = 1;
      }
      else
      {
        temp[r][s] = 0;
      }

      //cout << (field[r][s] ? "O" : ".");
    }
    
  }


 for (int r = 0; r < ROWS; r++)
{
    for (int s = 0; s < COLS; s++)
    {
      field[r][s]= temp[r][s];
    }
   
  }





}

//
int main()
{
  GOL game;
  for (int i =0;i<10;i++)
  {
  game.display_field();
  Sleep(1000);
  system("cls");
  //cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
  game.update_field();
  }




  // check for keyboard interrupt
}

int int_input(int max = INT_MAX)
{
  string input;

  do
  {
    bool baddata = 0;
    bool negative = 0;
    getline(cin, input);
    if (char(input[0]) == '-')
    {
      negative = 1;

      input[0] = '0';
    }

    for (char val : input) // loop thru the input
    {
      if (!isdigit(val))
      {
        baddata = 1;
      }
    }

    if (baddata)
    {
      cout << "invalid input: ";
      cout << input << endl;
      cin.clear();
    }
    else if (!((stoi(input) * (negative ? -1 : 1)) > 0 && (stoi(input) * (negative ? -1 : 1)) <= max))
    {
      cout << "invalid input: ";
      cout << input << endl;
      cin.clear();
    }
    else
    {
      // cout << "You entered the number: " << stoi(input) * (negative ? -1 : 1);

      return stoi(input);
    }
  } while (1);

  return 0;
}