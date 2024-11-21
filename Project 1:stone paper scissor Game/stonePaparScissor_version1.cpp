#include <iostream>
#include <cstdlib>

using namespace std;

enum en_Winer{Desktop = 1, Player = 2, NoWinner = 3};

struct st_PlayersChoices{
    int Desktop;
    int Player;
};

struct st_GameChoices{
    int stone = 1;
    int paper = 2;
    int scissor = 3;
};

int ft_ReadLimitedNumber(string message, int from, int to) {
    int nbr = -1;
    while (nbr < from || nbr > to) {
        cout << message;
        cin >> nbr;
    }
    return nbr;
}

int ft_randomNumber(int from, int to) {
    int RandomNumber = rand() % (to - from + 1) + from;
    return RandomNumber;
}

st_PlayersChoices ft_PlayersChoices(st_PlayersChoices &PlayersChoises) {
    cout << "choice : [1]: stone || [2]: paper || [3]: scissor?\n your chois is :=> ";
    cin >> PlayersChoises.Player;
    PlayersChoises.Desktop = ft_randomNumber(1,3);

    return PlayersChoises;
}

en_Winer ft_GameRule(st_PlayersChoices PlayersChoices) {
    st_GameChoices GameChoices;
    if(PlayersChoices.Player == GameChoices.stone && PlayersChoices.Desktop == GameChoices.paper)
        return en_Winer::Desktop;
    else if(PlayersChoices.Player == GameChoices.stone && PlayersChoices.Desktop == GameChoices.scissor)
        return en_Winer::Player;
    else if(PlayersChoices.Player == GameChoices.paper && PlayersChoices.Desktop == GameChoices.stone)
        return en_Winer::Player;
    else if(PlayersChoices.Player == GameChoices.paper && PlayersChoices.Desktop == GameChoices.scissor)
        return en_Winer::Desktop;
    else if(PlayersChoices.Player == GameChoices.scissor && PlayersChoices.Desktop == GameChoices.stone)
        return en_Winer::Desktop;
    else if(PlayersChoices.Player == GameChoices.scissor && PlayersChoices.Desktop == GameChoices.paper)
        return en_Winer::Player;
    else 
        return en_Winer::NoWinner;
}

en_Winer ft_SelectWiner(st_PlayersChoices PlayersChoices) {
    return ft_GameRule(PlayersChoices);
}

string ft_convertNumberToChoice(int numberOfChoice) {
    st_GameChoices GameChoices;
    if (numberOfChoice == GameChoices.stone)
        return "Stone";
    else if (numberOfChoice == GameChoices.paper)
        return "Paper";
    else
        return "Sissor";
}

void ft_PrintResoultOfRound(st_PlayersChoices PlayersChoices, int countNbrRound, int numberOfRound, int &drowTimes, int &DesktopWonTimes, int &PlayerWonTimes) {
    if(ft_SelectWiner(PlayersChoices) == en_Winer::Desktop) {
        cout << "\a";// Rin Bell
        system ("color 4F"); //change color to red in windows System
        cout << "\033[41;37m";// change color to red and text to white in linix or mac OS system
        DesktopWonTimes++;
        cout << "________________Round [" << countNbrRound+1 << "]________________\n\n";
        cout << "Player1 choice : " << ft_convertNumberToChoice(PlayersChoices.Player) << endl;
        cout << "Computer choice: " << ft_convertNumberToChoice(PlayersChoices.Desktop) << endl;
        cout << "Round Winer : [Computer]" << endl;
  
    }
    else if(ft_SelectWiner(PlayersChoices) == en_Winer::Player) {
        system ("color 2F"); //change color to green in windows System
        cout << "\033[42;37m";// change color to green and text to white in linix or mac OS system
        PlayerWonTimes++;
        cout << "________________Round [" << countNbrRound+1 << "]________________\n\n";
        cout << "Player1 choice : " << ft_convertNumberToChoice(PlayersChoices.Player) << endl;
        cout << "Computer choice: " << ft_convertNumberToChoice(PlayersChoices.Desktop) << endl;
        cout << "Round Winer : [Player 1]" << endl;

    }
    else {
        system ("color 4E"); //change color to yellow in windows System
        cout << "\033[43;37m";// change color to yellow and text to white in linix or mac OS system
        cout << "________________Round [" << countNbrRound+1 << "]________________\n\n";
        cout << "Player1 choice : " << ft_convertNumberToChoice(PlayersChoices.Player) << endl;
        cout << "Computer choice: " << ft_convertNumberToChoice(PlayersChoices.Desktop) << endl;
        cout << "Round Winer : [No Winner]" << endl;
        drowTimes++;
    }
    cout << "___________________________________________________\n";
}

void ft_StartRound(st_PlayersChoices PlayersChoices, int NumberOfRounds, int &drowTimes, int &DesktopWonTimes, int &PlayerWonTimes) {
    st_GameChoices GameChoices;
    int i = 0;
    while(i < NumberOfRounds) {
        cout << "\nRound [" << i+1 << "] begins:\n\n";
        ft_PlayersChoices(PlayersChoices);
        ft_PrintResoultOfRound(PlayersChoices, i, NumberOfRounds, drowTimes, DesktopWonTimes, PlayerWonTimes);
        i++; 
    }    
}

void ft_PrintGameResoult(int NumberOfRounds, int drowTimes, int DesktopWonTimes, int PlayerWonTimes) {
    cout << "\t\t\t\t_____________________________________________________\n";
    cout << "\t\t\t\t                                                     \n";
    cout << "\t\t\t\t\t\t+++ Games Over +++                           \n";
    cout << "\t\t\t\t_____________________________________________________\n";
    cout << "\t\t\t\t__________________ Game Resoult______________________\n";
    cout << "\t\t\t\tGame Round         : " << NumberOfRounds << "\t\t\t\t\t\n";
    cout << "\t\t\t\tPlayer 1 won times : " << PlayerWonTimes << "\t\t\t\t\t\n";
    cout << "\t\t\t\tComputer won times : " << DesktopWonTimes << "\t\t\t\t\t\t\t\n";
    cout << "\t\t\t\tDrow times         : " << drowTimes << "\t\t\t\t\t\t\t\n";
    if (DesktopWonTimes > PlayerWonTimes)
    cout << "\t\t\t\tFinal winner       : [Computer]"  << "\t\t\t\t\t\t\n";
    else if (DesktopWonTimes < PlayerWonTimes)
    cout << "\t\t\t\tFinal winner       : [Player 1]"  << "\t\t\t\t\t\t\t\n";
    else 
    cout << "\t\t\t\tFinal winner       : [No Winner]"  << "\t\t\t\t\t\t\t\n";
}

void ft_startGame() {
    st_PlayersChoices PlayersChoices;
    int drowTimes = 0,
    DesktopWonTimes = 0,
    PlayerWonTimes = 0;
    int NumberOfRound;
    char PlayAgain = 'Y';
    while (PlayAgain == 'Y' || PlayAgain == 'y') {
        NumberOfRound = ft_ReadLimitedNumber("How many Round you want to play select  1 to 10: ", 1, 10);
        ft_StartRound(PlayersChoices, NumberOfRound, drowTimes,DesktopWonTimes, PlayerWonTimes);
        ft_PrintGameResoult(NumberOfRound, drowTimes, DesktopWonTimes, PlayerWonTimes);
        cout << "\t\t\t\tDo you want to play again? Y/N? ";
        NumberOfRound = 0;
        drowTimes = 0,
        DesktopWonTimes = 0,
        PlayerWonTimes = 0;
        cin >> PlayAgain;
        system ("color");//set color of background to default on windows system
        cout << "\033[0m";// set color of background to default on lunix system
    }
}

int main() {
    srand((unsigned)time(NULL));
    ft_startGame();
    return 0;
}