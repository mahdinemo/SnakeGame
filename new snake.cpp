#include <ctime>
#include <conio.h>
#include <iostream>

#include <windows.h>
using namespace std;

class SnakeGame{
   private:
      static int width;
      static int height;
      int x, y, fruitCordX, fruitCordY, snakeTailLen, playerScore, dfc;
      int snakeTailX[100], snakeTailY[100];
      enum Direction { STOP , LEFT, RIGHT, UP, DOWN };
      Direction Dir;

    public:

        bool GameOver;
        SnakeGame(){
        GameOver = false;
        Dir = STOP;
        x = width / 2;
        y = height / 2;
        Randomfruit();
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        playerScore = 0;
        snakeTailLen = 0;
        }
void Randomfruit(){
    srand(time(0));
}
void GameRender(string playerName)
{
    for (int i = 0; i < width +1; i++){
        cout << "_";
    }
    cout << endl;
    for (int i =0; i <= height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width){
                cout << "|";
            }
            if (i == y && j == x){
                cout << static_cast<char>(2);
                }else if (i == fruitCordY && j == fruitCordX){
                cout << static_cast<char>(254);
                }else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width + 1; i++){
        cout << "_";
    }
    cout << endl;
    cout<<"Difficulty : ";
    if(dfc==130){
        cout<<"Easy";
    }else if(dfc==60){
        cout<<"Medium";
    }else{
        cout<<"Hard";
    }
    cout<<endl;
    cout << playerName << "'s Score: " << playerScore<< endl;
  }
  void UpdateGame()
{
    int prevX, prevY;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prevX = snakeTailX[i];
        prevY = snakeTailY[i];
        snakeTailX[i] = snakeTailX[i-1];
        snakeTailY[i] = snakeTailY[i-1];
        snakeTailX[i-1] = prevX;
        snakeTailY[i-1] = prevY;
    }
    switch (Dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    if (x >= width || x < 0 || y >= height+1 || y < 0){
        GameOver = true;
        cout<<"You Hit The Wall.";
    }
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y){
            GameOver = true;
            cout<<"You Hit Yourselfe.";
        }
    }
    if (x == fruitCordX && y == fruitCordY) {
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
        if(dfc==130){
            playerScore += 5;
        }else if(dfc==60){
            playerScore += 10;
        }else{
            playerScore += 15;
        }
    }
    Sleep(dfc);
}
void UserInput()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            Dir = LEFT;
            break;
        case 'd':
            Dir = RIGHT;
            break;
        case 'w':
            Dir = UP;
            break;
        case 's':
            Dir = DOWN;
            break;
        case 'x':
            GameOver = true;
            break;
        }
    }
}
static void cls(){
    system("cls");
}
char SetDifficulty()
{
char choice;
cout<<"\nSet difficulty : \n1 : Easy \n2 : Medium \n3 : Hard";
cout<<"\nEnter your choice : ";
cin>>choice;

switch(choice)
{
case '1':
dfc = 130;
break;

case '2':
dfc = 60;
break;

case '3':
dfc = 10;
break;

default:
cout<<"Wrong input! Please inter a number between 1 and 3."<<endl;
return SetDifficulty();
}
return dfc;
}
};

int SnakeGame::width = 45;
int SnakeGame::height = 15;

int main()
{
    SnakeGame* game = new SnakeGame;
    string playerName;
    cout << "enter your name: ";
    cin >> playerName;
    game->SetDifficulty();
    game->Randomfruit();
    while (!game->GameOver) {
        SnakeGame::cls();
        game->GameRender(playerName);
        game->UserInput();
        game->UpdateGame();
    }
    delete game;
    cin.ignore();
    cin.get();
    return 0;
}
