#include <iostream>
#include <cstdlib>

using namespace std;

enum en_Choices {
    stone = 1,
    paper = 2,
    csissor = 3,
};

enum en_Winner {
    Player1 = 1,
    computer = 2,
    Drow = 3,
};

struct st_RoundInfo {
    short RoundNumber = 0;
    en_Choices Player1Choice;
    en_Choices ComputerChoice;
    en_Winner Winner;
    string WinnerName = "";
};

struct st_GameInfo {
    short GameRound = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrowTimes = 0;
    en_Winner Winner;
    string WinnerName = "";
};

int ft_RandomNumber(int from, int to) {
    int RandomNumber = rand() % (to - from + 1) + from;
    return RandomNumber;
}

en_Choices ft_GetComputerChoice() {
    return (en_Choices)ft_RandomNumber(1,3);
}

en_Choices ft_ReadPlayer1Choice() {
    int choice = 1;
    do {
        cout << "your choice:[1]: stone, [2]: paper, [3]: csissor: ";
        cin >> choice;
    } while(choice < 1 || choice > 3);
    return en_Choices(choice);
}

en_Winner ft_WhoWonTheRound(st_RoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return en_Winner::Drow;
    switch (RoundInfo.Player1Choice)
    {
    case en_Choices::stone:
        if (RoundInfo.ComputerChoice == en_Choices::paper)
            return en_Winner::computer;
        break;
    case en_Choices::paper:
        if (RoundInfo.ComputerChoice == en_Choices::csissor)
            return en_Winner::computer;
        break;
    case en_Choices::csissor:
        if (RoundInfo.ComputerChoice == en_Choices::stone)
            return en_Winner::computer;
        break;
    }

    // if the no past condition true so the Player 1 win the round
    return en_Winner::Player1; 
}

string ft_WinnerName(en_Winner Winner) {
    string WinnersName[3] = {"Player1", "Computer", "No Winner"};
    return WinnersName[Winner - 1];
}

void ft_SetWinnerScreenColor(en_Winner Winner) {
    switch (Winner) {
        case en_Winner::computer:
            cout << '\a';
            system ("color 4F"); //change color to red in windows System
            cout << "\033[41;37m";// change color to red and text to white in linix or mac OS system
            break;
        case en_Winner::Player1:
            system ("color 2F"); //change color to green in windows System
            cout << "\033[42;37m";// change color to green and text to white in linix or mac OS system
            break;
        case en_Winner::Drow:
            system ("color 4E"); //change color to yellow in windows System
            cout << "\033[43;37m";// change color to yellow and text to white in linix or mac OS system
            break;
    }
}

st_RoundInfo ft_FillRoundInfo(short RoundNumber) {
    st_RoundInfo RoundInfo;
    
    RoundInfo.RoundNumber = RoundNumber;
    RoundInfo.Player1Choice = ft_ReadPlayer1Choice();
    RoundInfo.ComputerChoice = ft_GetComputerChoice();
    RoundInfo.Winner = ft_WhoWonTheRound(RoundInfo);
    RoundInfo.WinnerName = ft_WinnerName(RoundInfo.Winner);
    ft_SetWinnerScreenColor(RoundInfo.Winner);
    return RoundInfo;
}

string ft_ChoiceName(en_Choices choice) {
    string choisesName[3] = {"stone", "paper", "csissor"};
    return choisesName[choice - 1];
}

void ft_PrintRoundResoult(st_RoundInfo RoundInfo) {
    cout << "___________________Round[" << RoundInfo.RoundNumber << "]_________________\n"
    << "Player 1 choice :" << ft_ChoiceName(RoundInfo.Player1Choice) << endl
    << "Computer choice :" << ft_ChoiceName(RoundInfo.ComputerChoice) << endl
    << "Round Winner : [" << RoundInfo.WinnerName << "]\n";
    cout << "______________________________________________\n";
}

int ft_HowManyRound() {
    int choice = 1;
    do {
        cout << "How many round you want to play 1 to 10: ";
        cin >> choice;
    } while (choice < 1 || choice > 10);
    return choice;
}

en_Winner ft_WhoWinTheGame(st_GameInfo GameInfo) {
    if (GameInfo.ComputerWinTimes > GameInfo.Player1WinTimes)
        return en_Winner::computer;
    if (GameInfo.ComputerWinTimes < GameInfo.Player1WinTimes)
        return en_Winner::Player1;
    else 
        return en_Winner::Drow;
}

st_GameInfo ft_FillGameResoult(short GameRound, short Player1WinTimes, short ComputerWinTimes, short DrowTimes) {
    st_GameInfo GameInfo;
    GameInfo.GameRound = GameRound;
    GameInfo.Player1WinTimes = Player1WinTimes;
    GameInfo.ComputerWinTimes = ComputerWinTimes;
    GameInfo.DrowTimes = DrowTimes;
    GameInfo.Winner = ft_WhoWinTheGame(GameInfo);
    GameInfo.WinnerName = ft_WinnerName(GameInfo.Winner);
    return GameInfo;
}

string ft_Tabs(int NbrOfTabs) {
    string t = "\t";
    for(short tabs = 1; tabs <= NbrOfTabs; tabs++) {
        t += "\t"; 
    }
    return t;
}

void ft_GameOverScreen() {
    cout << ft_Tabs(2) << "_____________________________________________\n\n"
    << ft_Tabs(4) << "+++ Game Over +++\n"
    << ft_Tabs(2) << "_____________________________________________\n";
}

void ft_ShowFinalGameResoult(st_GameInfo GameInfo) {
    ft_GameOverScreen();
    cout << ft_Tabs(2) << "________________[Game Resoult] _________________\n"
    << ft_Tabs(2) << "Game Rounds        :" << GameInfo.GameRound << endl
    << ft_Tabs(2) << "Player 1 Won times :" << GameInfo.Player1WinTimes << endl
    << ft_Tabs(2) << "Computer Won times :" << GameInfo.ComputerWinTimes << endl
    << ft_Tabs(2) << "Drow times :" << GameInfo.DrowTimes << endl
    << ft_Tabs(2) << "Final winner : [" << GameInfo.WinnerName << "]" << endl
    << ft_Tabs(2) << "_________________________________________________\n";
}

st_GameInfo ft_PlayGame(int HowManyRound) {
    short GameRound = 0,
    Player1WinTimes = 0,
    ComputerWinTimes = 0,
    DrowTimes = 0;
    st_RoundInfo RoundInfo;
    for (short CountRound = 1; CountRound <= HowManyRound; CountRound++) {
        RoundInfo = ft_FillRoundInfo(CountRound);
        ft_PrintRoundResoult(RoundInfo);

        if (RoundInfo.Winner == en_Winner::Player1)
            Player1WinTimes ++;
        else if (RoundInfo.Winner == en_Winner::computer)
            ComputerWinTimes ++;
        else
            DrowTimes ++;
        GameRound ++;
    }
    return ft_FillGameResoult(GameRound, Player1WinTimes, ComputerWinTimes, DrowTimes);
}

void ft_ReasetScreen() {
    cout << "\033[0m";// set color of background to default on lunix system
    system ("color");//set color of background to default on windows system
    cout << "\033[2J\033[H";//clear screen in linix and mac os system
    system("cls");// clear screen in windows system
}

void ft_StartGame() {
    char PlayAgain = 'Y';
    st_GameInfo GameInfo;
    do {
        ft_ReasetScreen();
        GameInfo = ft_PlayGame(ft_HowManyRound());
        ft_ShowFinalGameResoult(GameInfo);
        cout << ft_Tabs(2) << "Do you Want to play again? Y/N ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    // called only  one time in your program
    srand((unsigned)time(NULL));
    ft_StartGame();
}
