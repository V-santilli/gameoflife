#include <iostream>
#include <iomanip>
#include <vector>
#include <windows.h>
using namespace std;
int int_input(int max); // add max number input

class GOL
{
  const static int ROWS = 20;
  const static int COLS = 20;

  float row_prices[ROWS];
  bool field[ROWS][COLS]; // = {0}; // create 2d array
  // bool field[ROWS][COLS];// = {0}; // create 2d array

public:
  void display_field(int frame);
  void update_field();
  void display_field_H(int frame);
  void update_field_H();
  void init_sample();
  void init_random();
  int sumof(int r, int s);
  int sumof_H(int r, int s);
  bool check(int A)     // tried casting the bools to bools but they Really wanted to be ints, so we have this 
  {
    if (A==0)
    {return 0;}
    else{return 1;}
  }
};

int GOL::sumof(int r, int s)
{
  int sum = 0;

  if (r > 0)
  {
    sum = sum + check(field[r - 1][s]);
    if (s > 0)
    {
      sum = sum + check(field[r - 1][s - 1]);
    }
    if (s < COLS)
    {
      sum = sum + check(field[r - 1][s + 1]);
    }
  }

  if (s > 0)
  {
    sum = sum + check(field[r][s - 1]);
  }
  if (s < COLS)
  {
    sum = sum + check(field[r][s + 1]);
  }

  if (r < ROWS)
  {
    sum = sum + check(field[r + 1][s]);
    if (s > 0)
    {
      sum = sum + check(field[r + 1][s - 1]);
    }
    if (s < COLS)
    {
      sum = sum + check(field[r + 1][s + 1]);
    }
  }
  return sum;
}

void GOL::init_random()
{
 for (int r = 0; r < ROWS; r++)
  {
    // cout << "Row "<<  setw(2) << right << r + 1 << "    "; // row numbers
    for (int s = 0; s < COLS; s++)
    {
     field[r][s] = (rand()%3? 0 : 1 );

    }
   
  }


}

void GOL::init_sample()
{
for (int r = 0; r < ROWS; r++)
  {
    for (int s = 0; s < COLS; s++)
    {
     field[r][s] = 0;
    }
  }

   // insert glider 
int locx=2;
int locy=2;

field[locy-1][locx-1] = 1;
field[locy-1][locx+1] = 1;
field[locy][locx] = 1;
field[locy][locx+1] = 1;
field[locy+1][locx] = 1;

// blinker

 locx=15;
 locy=12;

field[locy-1][locx] = 1;
field[locy][locx] = 1;
field[locy+1][locx] = 1;


}

void GOL::display_field(int frame)
{
cout << "Generation: "<<frame <<endl;
  for (int r = 0; r < ROWS; r++)
  {
  
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
  int total=0;
  for (int r = 0; r < ROWS; r++)
  {
    // cout << "Row "<<  setw(2) << right << r + 1 << "    "; // row numbers
    for (int s = 0; s < COLS; s++)
    {
      //sumof(r,s)
      sum =sumof(r, s);
      total=total+sum;

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


  int stale =1;
 for (int r = 0; r < ROWS; r++)
{
    for (int s = 0; s < COLS; s++)
    {
      if(!(field[r][s]== temp[r][s]))
      {
        stale =0;
      }
    }
  }
//cout<<stale;

 for (int r = 0; r < ROWS; r++)
{
    for (int s = 0; s < COLS; s++)
    {
      field[r][s]= temp[r][s];
    }
  }

  //cout<<total;
if (stale==1)
  {
    init_random();
  }
}

int GOL::sumof_H(int r, int s)
{
    int sum = 0;

  if (s > 0)
        sum += field[r][s - 1];
    if (s < COLS - 1)
        sum += field[r][s + 1];
    if (r > 0)
    {
        if (r % 2 == 0)
        {
            if (s > 0)
                sum += field[r - 1][s - 1];

            sum += field[r - 1][s];
        }
        else
        {
            sum += field[r - 1][s];

            if (s < COLS - 1)
                sum += field[r - 1][s + 1];
        }
    }

    if (r < ROWS - 1)
    {
        if (r % 2 == 0)
        {
            if (s > 0)
                sum += field[r + 1][s - 1];

            sum += field[r + 1][s];
        }
        else
        {
            sum += field[r + 1][s];

            if (s < COLS - 1)
                sum += field[r + 1][s + 1];
        }
    }

    return sum;
}

void GOL::display_field_H(int frame )
{
  cout << "Generation: "<<frame <<endl;
    for (int r = 0; r < ROWS; r++)
    {
        if (r % 2 == 1)
            cout << " ";

        for (int s = 0; s < COLS; s++)
        {
            cout << (field[r][s] ? "O" : ".") << " ";
        }
        cout << endl;
    }
}

void GOL::update_field_H()
{
  bool temp[ROWS][COLS];
  int sum = 0;
  int total=0;
  for (int r = 0; r < ROWS; r++)
  {
    for (int s = 0; s < COLS; s++)
    {
      sum =sumof_H(r, s);
      total=total+sum;


      if(sum==3){ temp[r][s] = 1;} 
      else if (sum == 2 && field[r][s])
      {
        temp[r][s] = 1;
      }
      else
      {
        temp[r][s] = 0;
      }
    }    
  }
  for (int r = 0; r < ROWS; r++)
  {
    for (int s = 0; s < COLS; s++)
    {
      field[r][s] = temp[r][s];
    }
  }
  if (total==0)
  {
    init_random();
  }
}

/////////////////////////////////////////////

int main()
{
  int choice = 0;
  bool receive = false;
  do
  {

    cout << "enter 1 for base grid 2 for hex grid: ";
    cin >> choice;
    if(choice == 1 || choice == 2)receive=true;
  }while(receive==false);
  switch (choice)
  {
  case 1:
    GOL game;
    game.init_random();
    game.init_sample();
    for (int i =0;i<50;i++)
    {
      game.display_field(i);
      
      Sleep(800);
      system("cls");
      //cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
      game.update_field();
      
    }
    break;
  case 2:
    GOL gameH;
    gameH.init_random();
    for (int i =0;i<50;i++)
    {
      gameH.display_field_H(i);
      Sleep(800);
      system("cls");
      //cout<<"++++++++++++++++++++++++++++++++++++++"<<endl;
      gameH.update_field_H();
    }
    break;
  default:
    break;
  }
  
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
