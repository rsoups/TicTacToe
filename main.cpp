//Author : Remi Ethun
//Date   : 04/16/2023
//Desc   : Tic-Tac-Toe

#include <iostream>

int miniMax(char board[3][3], bool maximizing);
void resetBoard(char board[3][3]);
void playGame();


using namespace std;

//2d array, makes board
char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
char player = 'X';
char computer = 'O';

void displayBoard(char board[3][3])
{
    cout << "   " << "   0" << " | 1 | " << "2 " << endl;
    cout << "    +---+---+---+" << endl;
    cout << "  0 |"<<" "<<board[0][0]<<" | "<<board[0][1]<<" | "  <<board[0][2]<<" |  " << endl;
    cout << "    +---+---+---+" << endl;
    cout << "  1 |" << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |  " << endl;
    cout << "    +---+---+---+" << endl;
    cout << "  2 |" << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |  " << endl;
    cout << "    +---+---+---+" << endl;
}

void resetBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

int fullBoard(char board[3][3])
{
    int empty = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                empty--;
            }
        }
    }

    return empty;
}

void displayWinner(char winner, char board[3][3])
{
    if (winner == player)
    {
        cout << endl << "Player Wins (X)!" << endl << endl;
    }
    else if (winner == computer)
    {
        cout << endl << "Computer Wins (O)!" << endl << endl;
    }
}

char checkWin(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        //check rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return board[i][0];
        }
        //check columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    //check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }

    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

void playerMove(char board[3][3])
{
    //player input for moves
    int x, y;

    cout << endl << "Player's Turn! (X)" << endl << endl << "Enter x and y: " << endl;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    cout << endl;

    if (board[x][y] == ' ')
    {
        board[x][y] = player;
        displayBoard(board);
        cout << endl << "--------------------------------" << endl;
    }
    else
    {
        while (board[x][y] != ' ')
        {
            cout << "Invalid move. Try again:" << endl << endl << "Enter x and y: " << endl;
            cout << "x: ";
            cin >> x;
            cout << "y: ";
            cin >> y;
            cout << endl;
        }

        board[x][y] = player;
        displayBoard(board);
        cout << endl << "--------------------------------" << endl;
    }
}

void computerMove(char board[3][3])
{
    int rMove;
    int cMove;
    int bestScore = -5;

    cout << endl << "Computer's Turn! (O)" << endl << endl;

    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == ' ')
            {
                board[r][c] = computer;
                int score = miniMax(board, false);
                board[r][c] = ' ';

                if (score > bestScore)
                {
                    bestScore = score;
                    rMove = r;
                    cMove = c;
                }
            }
        }
    }

    board[rMove][cMove] = computer;
    displayBoard(board);
    cout << endl << "--------------------------------" << endl;
}

int miniMax(char board[3][3], bool maximizing)
{
    char winner = checkWin(board);

    if (winner != ' ' || fullBoard(board) == 0)
    {
        if (winner == player)
        {
            return -1;
        }
        else if (winner == computer)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }

    if (maximizing)
    {
        int bestScore = -5;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = computer; 
                    int score = miniMax(board, false);
                    board[r][c] = ' ';

                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }

        return bestScore;
    }
    else
    {
        int bestScore = 5;
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = player;
                    int score = miniMax(board, true);
                    board[r][c] = ' ';

                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }

        return bestScore;
    }

}

int playAgain()
{
    int choice;

    cout << "1. Play Again" << endl;
    cout << "2. Quit Game" << endl;
    cout << "Play Again?: ";
    cin >> choice;
    cout << endl;
    if (choice == 1)
    {
        playGame();
    }
    
    return 0;
}

void playGame()
{
    char winner = ' ';
    int firstMove;
    resetBoard(board);

    displayBoard(board);

    cout << endl << "1. Player (X)" << endl;
    cout << "2. Computer (O)" << endl;
    cout << "Who goes first?: ";

    cin >> firstMove;
    cout << endl;
    while (winner == ' ' || fullBoard(board) != 0)
    {
        if (firstMove == 1)
        {
            displayBoard(board);
            playerMove(board);
            winner = checkWin(board);
            if (winner != ' ' || fullBoard(board) == 0)
            {
                break;
            }

            displayBoard(board);
            computerMove(board);
            winner = checkWin(board);
            if (winner != ' ' || fullBoard(board) == 0)
            {
                break;
            }
        }
        else if (firstMove == 2)
        {
            displayBoard(board);
            computerMove(board);
            winner = checkWin(board);
            if (winner != ' ' || fullBoard(board) == 0)
            {
                break;
            }

            displayBoard(board);
            playerMove(board);
            winner = checkWin(board);
            if (winner != ' ' || fullBoard(board) == 0)
            {
                break;
            }
        }
    }

    displayBoard(board);
    if (fullBoard(board) == 0)
    {
        cout << endl << "Tie!" << endl << endl;
    }
    displayWinner(winner, board);
    playAgain();
}

int main()
{
    playGame();
    return 0;
}