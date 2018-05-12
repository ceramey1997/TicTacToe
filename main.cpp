//
// Created by Cole Ramey on 4/23/18.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

char matrix[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

std::vector<vector<char> > WinOptions()
{
    std::vector<char> win1 = {'1', '2', '3'};
    std::vector<char> win2 = {'1', '5', '9'};
    std::vector<char> win3 = {'1', '4', '7'};
    std::vector<char> win4 = {'2', '5', '8'};
    std::vector<char> win5 = {'3', '6', '9'};
    std::vector<char> win6 = {'3', '5', '7'};
    std::vector<char> win7 = {'4', '5', '6'};
    std::vector<char> win8 = {'7', '8', '9'};

    std::vector<std::vector<char> > win_option = {win1, win2, win3, win4, win5, win6, win7, win8};
    return win_option;
}

std::vector<vector<char> > MatrixChanged()
{
    std::vector<char> win1 = {matrix[0][0], matrix[0][1], matrix[0][2]};
    std::vector<char> win2 = {matrix[0][0], matrix[1][1], matrix[2][2]};
    std::vector<char> win3 = {matrix[0][0], matrix[1][0], matrix[2][0]};
    std::vector<char> win4 = {matrix[0][1], matrix[1][1], matrix[2][1]};
    std::vector<char> win5 = {matrix[0][2], matrix[1][2], matrix[2][2]};
    std::vector<char> win6 = {matrix[0][2], matrix[1][1], matrix[2][0]};
    std::vector<char> win7 = {matrix[1][0], matrix[1][1], matrix[1][2]};
    std::vector<char> win8 = {matrix[2][0], matrix[2][1], matrix[2][2]};

    std::vector<std::vector<char> > win_option = {win1, win2, win3, win4, win5, win6, win7, win8};
    return win_option;
}

void Draw()
{

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Turn()
{
    char player = 'x';
    char position;
    std::cout <<  "What position would you like to play?" << std::endl;
    std::cin >> position;
    switch(position)
    {
        case '1' :
            matrix[0][0] = player;
            break;
        case '2' :
            matrix[0][1] = player;
            break;
        case '3' :
            matrix[0][2] = player;
            break;
        case '4' :
            matrix[1][0] = player;
            break;
        case '5' :
            matrix[1][1] = player;
            break;
        case '6' :
            matrix[1][2] = player;
            break;
        case '7' :
            matrix[2][0] = player;
            break;
        case '8' :
            matrix[2][1] = player;
            break;
        case '9' :
            matrix[2][2] = player;
            break;
        default :
            break;
    }

}

char Position(int i, int j)
{
    if (i == 0)
    {
        if (j == 0)
        {
            return '1';
        }
        if (j == 1)
        {
            return '2';
        }
        if (j == 2)
        {
            return '3';
        }
    }
    if (i == 1)
    {
        if (j == 0)
        {
            return '4';
        }
        if (j == 1)
        {
            return '5';
        }
        if (j == 2)
        {
            return '6';
        }
    }
    if (i == 2)
    {
        if (j == 0)
        {
            return '7';
        }
        if (j == 1)
        {
            return '8';
        }
        if (j == 2)
        {
            return '9';
        }
    }
    return 'n';

}


std::vector<char> TakenPositions(char player)
{
    std::vector<char> taken;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char position = matrix[i][j];
            if (position == player)
            {
                char spot = Position(i, j);
                taken.push_back(spot);
            }
        }
    }
    return taken;
}

char GetDiff(std::vector<char> win_option, std::vector<char> taken)
{
    std::vector<char> diff;
    std::set_difference(win_option.begin(), win_option.end(), taken.begin(), taken.end(),
                        std::inserter(diff, diff.begin()));
    if (diff.size() == 1)
    {
        return diff[0];
    }
    return 10;
}

int NeedBlock()
{
    vector<char> taken_player = TakenPositions('x');
    vector<char> taken_computer = TakenPositions('o');
    vector<vector<char> > win_option = WinOptions();
    for (std::vector<char> win : win_option)
    {
        char option = GetDiff(win, taken_player);
        if (option != 10)
        { if (std::find(taken_player.begin(), taken_player.end(), option) == taken_player.end())
            {
                if (std::find(taken_computer.begin(), taken_computer.end(), option) == taken_computer.end())
                    return option;
            }
        }
    }
    return 10;
}

int WinOpertunities()
{
    std::vector<vector<char> > win_options = MatrixChanged();
    char positions[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int wins = 0;
    char bestPos;
    for (char posit : positions)
    {
        int wins_with_pos = 0;
        for (vector<char> win_op : win_options)
        {
            if (std::find(win_op.begin(), win_op.end(), posit) != win_op.end())
            {
                if (std::find(win_op.begin(), win_op.end(), 'x') != win_op.end())
                {
                    continue;
                }
                if (std::find(win_op.begin(), win_op.end(), 'o') != win_op.end())
                    {
                        wins_with_pos+=2;
                    }
                else
                {
                    wins_with_pos++;
                }
            }
            if (wins_with_pos > wins)
            {
                wins = wins_with_pos;
                bestPos = posit;
            }
        }
    }
    return bestPos;
}

bool CanWin()
{
    std::vector<vector<char> > winPositions = MatrixChanged();
    for (vector<char> win : winPositions)
    {
        int canwin = 0;
        for (char position : win)
        {
            if (position == 'o')
            {
                canwin++;
            }
            if (canwin == 2)
            {
                return true;
            }
        }
    }
    return false;
}

char CanWinPosition()
{
    char winposition;
    std::vector<vector<char> > winPositions = MatrixChanged();
    for (vector<char> win : winPositions)
    {
        int canwin = 0;
        for (char position : win)
        {
            if (position == 'o')
            {
                canwin++;
            }
            else if (canwin == 2)
            {
                canwin++;
            }
            if (canwin == 3)
            {
                return position;
            }
        }
    }
    char position = '0';
    return position;
}

void ComputerTurn()
{
    int position;
    bool canwin = CanWin();
    position = NeedBlock();
    if (position == 10)
    {
        position = WinOpertunities();
    }
    if (canwin)
    {
        position = CanWinPosition();
        if (position == '0')
        {
            position = NeedBlock();
            if (position == 10)
            {
                position = WinOpertunities();
            }
        }
    }
    char player = 'o';
    switch(position)
    {
        case '1' :
            matrix[0][0] = player;
            break;
        case '2' :
            matrix[0][1] = player;
            break;
        case '3' :
            matrix[0][2] = player;
            break;
        case '4' :
            matrix[1][0] = player;
            break;
        case '5' :
            matrix[1][1] = player;
            break;
        case '6' :
            matrix[1][2] = player;
            break;
        case '7' :
            matrix[2][0] = player;
            break;
        case '8' :
            matrix[2][1] = player;
            break;
        case '9' :
            matrix[2][2] = player;
            break;
        default :
            break;
    }

}

bool StillPositions()
{
    int positions = 9;
    bool still_positions = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (matrix[i][j] == 'o' or matrix[i][j] == 'x')
            {
                positions--;
                if (positions == 0)
                {
                    still_positions = false;
                }
            }
        }
    }
    return still_positions;
}

bool Won()
{
    std::vector<std::vector<char> > options = MatrixChanged();
    int count_o;
    int count_x;
    bool still_playing = true;
    for (std::vector<char> game : options)
    {
        count_x = 0;
        count_o = 0;
        for (char element : game)
        {
            if (element == 'x')
            {
                count_x++;
            }
            if (element == 'o')
            {
                count_o++;
            }
            if (count_x == 3)
            {
                still_playing = false;
            }
            if (count_o == 3)
            {
                still_playing = false;
            }
        }
    }
    return still_playing;
}

void Game()
{
    bool draw = false;
    bool playing = true;
    while(playing)
    {
        Draw();
        Turn();
        ComputerTurn();
        playing = Won();
        if (! StillPositions())
        {
            draw = true;
            playing = false;
        }
    }
    Draw();
    if (draw)
    {
        std::cout << "It is a Draw.  ¯\\_(ツ)_/¯ " << std::endl;
    }
    std::cout << "Game over." << std::endl;
}


int main() {
    Game();
    return 0;
}
