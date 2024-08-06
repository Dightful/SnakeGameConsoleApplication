#include<windows.h>
#include<conio.h>
#include<iostream>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

using namespace std;

bool gameover;
const int height = 20;
const int width = 60;

int x, y, foodx, foody, score;

enum edirection { STOP = 0, UP, DOWN, LEFT, RIGHT };
edirection dir;

int tailLengthx[100], tailLengthy[100], ntail;



// Function to draw the game screen
void draw()
{
    //system("CLS");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    // Draw top border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << "#";
        else
            cout << "-";
    }
    cout << endl;

    // Draw game area
    for (int i = 0; i <= height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Draws left and right borders
            if (j == 0 || j == width)
                cout << "|";
            // Draws snake head
            else if (i == y && j == x)
                cout << "O";
            // Draws food
            else if (i == foody && j == foodx)
                cout << "*";
            else
            {
                // Draw tail segments
                bool print = false;
                for (int k = 0; k < ntail; k++)
                {
                    if (i == tailLengthy[k] && j == tailLengthx[k])
                    {
                        cout << "O";
                        print = true;
                    }

                    // Draw empty space if no snake or food
                }
                if (!print)
                    cout << " ";
            }

        }
        cout << endl;
    }

    // Draw bottom border
    for (int i = 0; i <= width; i++)
    {
        if (i == 0 || i == width)
            cout << "#";
        else
            cout << "-";
    }
    cout << endl;

    // Display the score
    cout << "Score : " << score << endl;
}

// Function that initializes the game state
void setup()
{
    gameover = false;
    x = width / 2;
    y = height / 2;
    foodx = rand() % width;
    foody = rand() % height;
    score = 0;
}

// Function to handle player input
void input()
{
    if (_kbhit())
    {
        char key = _getch();
        switch (key)
        {
        case 'w':
        case 'W':
        case 72: // ASCII code for up arrow key
            if (dir != DOWN)
            {
                dir = UP;
            }
            break;
        case 's':
        case 'S':
        case 80: // ASCII code for down arrow key
            if (dir != UP)
            {
                dir = DOWN;
            }
            break;
        case 'a':
        case 'A':
        case 75: // ASCII code for left arrow key
            if (dir != RIGHT)
            {
                dir = LEFT;
            }
            break;
        case 'd':
        case 'D':
        case 77: // ASCII code for right arrow key
            if (dir != LEFT)
            {
                dir = RIGHT;
            }
            break;
        default:
            break;
        }
    }
}

// Function to update game logic
void logic()
{

    // Update tail positions
    for (int i = ntail - 1; i > 0; --i)
    {
        tailLengthx[i] = tailLengthx[i - 1];
        tailLengthy[i] = tailLengthy[i - 1];
    }

    // Move the head to the new position
    tailLengthx[0] = x;
    tailLengthy[0] = y;


    // Move the head based on the direction
    switch (dir)
    {
    case UP:
        sleep(0.03);
        y--;
        break;
    case DOWN:
        sleep(0.03);
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    default:
        break;
    }

    // Check for collisions with the borders
    if (x < 0 || x > width || y < 0 || y > height)
    {
        gameover = true;
    }

    // Check for collisions with the tail
    for (int i = 0; i < ntail; i++)
    {
        if (x == tailLengthx[i] && y == tailLengthy[i])
        {
            gameover = true;
        }
    }

    // Check for collision with food and update score
    if (x == foodx && y == foody)
    {
        score += 10;
        foodx = rand() % width;
        foody = rand() % height;
        ntail++;
    }
}

int main()
{

    cout << "Use arrow keys to move the snake." << endl;
    cout << "Press 1: Difficult mode | Press 2 : Easy mode." << endl;
    int mode;
    cin >> mode;

    setup(); // Initialize the game

    while (!gameover)
    {
        draw();
        input();
        logic();
        Sleep((mode == 1) ? 30 : 100); // Adjust sleep duration based on mode
    }

    cout << "GAME OVER" << endl;

    return 0;
}


