#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


void displayDescription();

void displayTeams (string[], const int);

void readFiles(ifstream &, string [], const int);

void listTeams();

string getTeam ();

void countOfWins (int);

int timesWon (string[], string, const int);


int main() 
{         


string team;
int wins;
const int ARRAYSIZE1 = 29;
const int ARRAYSIZE2 = 108;
string teams[ARRAYSIZE1] = {" "}; 
string winningTeams[ARRAYSIZE2] = {" "}; 

string teamsFile = "Teams.txt"; 
ifstream inTeams(teamsFile);

string winsFile = "WorldSeriesWinners.txt";
ifstream inWinningTeams(winsFile);


if (!inTeams)
    {
        cout << "ERROR: " << teamsFile << " was not found.\n\n";
        cout << "Terminating program";
        return 0;
    }

if (!inWinningTeams)
    {
        cout << "ERROR: " << winsFile << " was not found.\n\n";
        cout << "Terminating program.";
        return 0;
    }


    
displayDescription();


readFiles (inTeams, teams, ARRAYSIZE1);
readFiles (inWinningTeams, winningTeams, ARRAYSIZE2);

displayTeams(teams, ARRAYSIZE1);

team = getTeam();

wins = timesWon(winningTeams, team, ARRAYSIZE2);

countOfWins(wins);





return 0;             
}


// functions

void displayDescription()
{
    cout << "This program will display the teams and prompt the user to select one team, and the program will state how many times that team has won the series.\n\n";
}



void readFiles(ifstream &infile, string a[], const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
    {
        getline(infile, a[i]);
    }
}

void displayTeams (string a[], const int SIZE)
{
    for (int i = 0 ;i < SIZE; i++)
    {
        cout << (i+1) << ". ";
        cout << a[i] << "\n\n" ;
    }
}

void listTeams()
{
    cout << "The winning teams of the World Series:\n";
}

string getTeam()
{
    string team;
    cout << "\nEnter name of team:\n";
    getline(cin, team);
    return team;
}

int timesWon (string winners[], string team, const int SIZE)
{
    int count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (team == winners [i])
        {
            count++;
        }
    }
    return count;
}

void countOfWins (int wins)
{
    if (wins == 1)
    {
        cout << "\n\nThe team you inputted has won the World Series " << wins << " time.\n\n\n";
    }
    else
    {
        cout << "\n\nThe team has won the World Series " << wins << " times.\n\n\n";
    }
}