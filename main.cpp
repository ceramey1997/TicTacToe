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

std::vector<char> win1 = {'1', '2', '3'};
std::vector<char> win2 = {'1', '5', '9'};
std::vector<char> win3 = {'1', '4', '7'};
std::vector<char> win4 = {'2', '5', '8'};
std::vector<char> win5 = {'3', '6', '9'};
std::vector<char> win6 = {'3', '5', '7'};
std::vector<char> win7 = {'4', '5', '6'};
std::vector<char> win8 = {'7', '8', '9'};

std::vector<std::vector<char>> win_option = {win1, win2, win3, win4, win5, win6, win7, win8};

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

void Turn(char player)
{
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


std::vector<char> TakenPositions()
{
    std::vector<char> taken;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            char position = matrix[i][j];
            if (position == 'x')
            {
                char spot = Position(i, j);
                taken.push_back(spot);
            }
        }
    }
    return taken;
}

int GetDiff(std::vector<char> win_option, std::vector<char> taken)
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

    vector<char> taken = TakenPositions();
    int firstOption = GetDiff(win1, taken);
    if (firstOption != 10)
    {
        return firstOption;
    }
    int secondOption = GetDiff(win2, taken);
    if (secondOption != 10)
    {
        return secondOption;
    }
    int thirdOption = GetDiff(win3, taken);
    if (thirdOption != 10)
    {
        return thirdOption;
    }
    int fourthOption = GetDiff(win4, taken);
    if (fourthOption != 10)
    {
        return fourthOption;
    }
    int fifthOption = GetDiff(win5, taken);
    if (fifthOption != 10)
    {
        return fifthOption;
    }
    int sixthOption = GetDiff(win6, taken);
    if (sixthOption != 10)
    {
        return sixthOption;
    }
    int seventhOption = GetDiff(win7, taken);
    if (seventhOption != 10)
    {
        return seventhOption;
    }
    int eighthOption = GetDiff(win8, taken);
    if (eighthOption != 10)
    {
        return eighthOption;
    }
    else
    {
        return 10;
    }
}

void ComputerTurn()
{
    int position = NeedBlock();

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

int main() {
    Draw();
    Turn('x');
    Draw();
    Turn('x');
    Draw();
    ComputerTurn();
    Draw();
    return 0;
}
