#include <iostream>
#include <cstdlib>

using namespace std;

enum en_QuestionLevel {Easy = 1, Med = 2, Hard = 3, Mix_Q = 4};

enum en_Op_Type {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix_Op = 5};

enum en_PassOrFail{Pass = 1, Fail = 2, Drow = 3};

struct st_GameResoult {
    short NumberTotalOfQuetions = 0;
    en_QuestionLevel QuestionLevel;
    en_Op_Type Op_Type;
    short NumberOfRightAnsower = 0;
    short NumberOfWrongAnsower = 0;
    en_PassOrFail PassOrFail;
    string QuestionLevelName = "";
    string Op_TypeName = "";
    string PassOrFailName = "";
};

struct st_QRoundInfo {
    short firstNumber = 0;
    short SecandNumber = 0;
    int Resoult = 0;
    en_Op_Type  Op_Type;
};

int ft_HowManyQuestion() {
    int nbr = 1;
    do {
        cout << "How many question do you want to ansower? ";
        cin >> nbr;
    } while (nbr < 1);
    return nbr;
}

en_QuestionLevel ft_ReadQuestionLevel() {
    int nbr = 1;
    do {
        cout << "Enter question level [1]: Easy, [2]: Med, [3]: Hard, [4]: Mix ? ";
        cin >> nbr;
    } while(nbr < 1 || nbr > 4);
    return (en_QuestionLevel)nbr;
}

en_Op_Type ft_ReadOperationType() {
    int nbr = 1;
    do {
        cout << "Enter operation types [2]: Add, [2]: Sub, [3]: Mul, [4]: Div, [5]: Mix? ";
        cin >> nbr;
    } while (nbr < 1 || nbr > 5);
    return (en_Op_Type)nbr;
} 

int ft_RandomNumber(short from, short to) {
    int RandomNumber = rand() % (to - from + 1) + from;
    return RandomNumber;
}

string ft_Op_TypeName(en_Op_Type choice) {
    string Op_Types[5] = {"Add", "Sub", "Mul" , "Div", "Mix"};
    return Op_Types[choice - 1];
}

string ft_QuestionLevelName(en_QuestionLevel choice) {
    string QuetionsLevel[4] = {"Easy", "Med", "Hard", "Mix"};
    return QuetionsLevel[choice - 1];
}

int ft_CalculOp_Round(st_QRoundInfo QRoundInfo) {
    switch(QRoundInfo.Op_Type) {
        case en_Op_Type::Add:
            return QRoundInfo.firstNumber + QRoundInfo.SecandNumber;
        case en_Op_Type::Sub:
            return QRoundInfo.firstNumber - QRoundInfo.SecandNumber;
        case en_Op_Type::Mul:
            return QRoundInfo.firstNumber * QRoundInfo.SecandNumber;
        case en_Op_Type::Div:
            return QRoundInfo.firstNumber / QRoundInfo.SecandNumber;
    }
    return 0;
}


st_QRoundInfo ft_FillRoundInfo(en_Op_Type Op_Type, short from, short to) {
    st_QRoundInfo QRoundInfo;
    QRoundInfo.firstNumber = ft_RandomNumber(from, to);
    QRoundInfo.SecandNumber = ft_RandomNumber(from, to);
    QRoundInfo.Op_Type = Op_Type;
    QRoundInfo.Resoult = ft_CalculOp_Round(QRoundInfo);
    return QRoundInfo;
}

char ft_Op_TypeSymbol(en_Op_Type choice) {
    char Op_Taypes[4] = {'+', '-', '*', '/'};
    return Op_Taypes[choice - 1];
}

int ft_ShowRound(st_QRoundInfo QRoundInfo) {
    int Ansower;
    cout << '\n' << QRoundInfo.firstNumber << '\n'
    << QRoundInfo.SecandNumber << ' ' << ft_Op_TypeSymbol(QRoundInfo.Op_Type)
    << "\n___________\n\n";
    cin >> Ansower;
    return Ansower;
}

void ft_SetWinnerScreenColor(en_PassOrFail PassOrFail) {
    switch (PassOrFail) {
        case en_PassOrFail::Fail:
            cout << '\a';// ring the bell
            system ("color 4F"); //change color to red in windows System
            cout << "\033[41;37m";// change color to red and text to white in linix or mac OS system
            break;
        case en_PassOrFail::Pass:
            system ("color 2F"); //change color to green in windows System
            cout << "\033[42;37m";// change color to green and text to white in linix or mac OS system
            break;
        default:
            system ("color 4E"); //change color to yellow in windows System
            cout << "\033[43;37m";// change color to yellow and text to white in linix or mac OS system
            break;
    }
}

void ft_CheckAnsower(int PlayerAnsower, int RightResoult, st_GameResoult &GameResoult) {
    
    if(PlayerAnsower == RightResoult) {
        ft_SetWinnerScreenColor(en_PassOrFail::Pass);
        cout << "\nRight Ansower : -)\n";
        GameResoult.NumberOfRightAnsower ++;
    }
    else {
        ft_SetWinnerScreenColor(en_PassOrFail::Fail);
        cout << "\nWrong ansower : -(\n"
        << "The right ansower is: " << RightResoult << "\n\n";
        GameResoult.NumberOfWrongAnsower ++;
    }
}

st_GameResoult ft_FillAndShowRoundResoult(st_GameResoult &GameResoult, short from, short to) {
    st_QRoundInfo QRoundInfo;
    int PlayerAnsower;
    QRoundInfo = ft_FillRoundInfo(GameResoult.Op_Type, from, to);
    PlayerAnsower = ft_ShowRound(QRoundInfo);
    ft_CheckAnsower(PlayerAnsower, QRoundInfo.Resoult, GameResoult);
    return GameResoult;
}


st_GameResoult ft_CheckOperationType(st_GameResoult &GameResoult, short from, short to) {
    if (GameResoult.Op_Type == en_Op_Type::Mix_Op) {
        GameResoult.Op_Type = (en_Op_Type)ft_RandomNumber(1, 4);
    }
    return ft_FillAndShowRoundResoult(GameResoult, from, to);
}

st_GameResoult ft_StartOperation(st_GameResoult &GameResoult) {
    switch(GameResoult.QuestionLevel) {
        case en_QuestionLevel::Easy:
            return ft_CheckOperationType(GameResoult, 1, 10);
        case en_QuestionLevel::Med:
            return ft_CheckOperationType(GameResoult, 11, 50);
        case en_QuestionLevel::Hard:
            return ft_CheckOperationType(GameResoult, 51, 99);
        case en_QuestionLevel::Mix_Q:
            return ft_CheckOperationType(GameResoult, 1, 19);
        
    }
    return ft_CheckOperationType(GameResoult, 1, 99);
}

en_PassOrFail ft_ChekIsPassOrFail(short N_RightAnsower, short N_WrongAnsower) {
    if (N_RightAnsower >= N_WrongAnsower){
        ft_SetWinnerScreenColor(en_PassOrFail::Pass);
        return en_PassOrFail::Pass;
    }
    else {
        ft_SetWinnerScreenColor(en_PassOrFail::Fail);
        return en_PassOrFail::Fail;
    }
}

string ft_PassOrFailString(en_PassOrFail IsPass) {
    string PassOrFail[2] = {"Pass: -)", "Fail: -("};
    return PassOrFail[IsPass - 1];
}

st_GameResoult ft_fillGameResoult(short NumberOfRound) {
    st_GameResoult GameResoult;
    GameResoult.NumberTotalOfQuetions = NumberOfRound;
    GameResoult.QuestionLevel = ft_ReadQuestionLevel();
    GameResoult.QuestionLevelName = ft_QuestionLevelName(GameResoult.QuestionLevel);
    GameResoult.Op_Type = ft_ReadOperationType();
    GameResoult.Op_TypeName = ft_Op_TypeName(GameResoult.Op_Type);
    return GameResoult;
}

void ft_ShowFinalResoultScreen(string IsPass) {
    cout << "\n________________________________________________\n"
    << "\nFinal resoult is " << IsPass;
    cout << "\n________________________________________________\n\n";
}

void ft_showFinalGameResoult(st_GameResoult GameResoult) {
    ft_ShowFinalResoultScreen(GameResoult.PassOrFailName);
    cout << "Number of Question_____: " << GameResoult.NumberTotalOfQuetions << '\n';
    cout << "Question level_________: " << GameResoult.QuestionLevelName << '\n';
    cout << "Operation Type_________: " << GameResoult.Op_TypeName << '\n';
    cout << "Number of Right Ansower: " << GameResoult.NumberOfRightAnsower << "\n";
    cout << "Number of wrong ansower: " << GameResoult.NumberOfWrongAnsower << '\n';
    cout << "________________________________________________" << endl;
}

void ft_PlayGame() {
    st_GameResoult GameResoult;
    int NumberOfRound = ft_HowManyQuestion();
    GameResoult.NumberTotalOfQuetions = NumberOfRound;
    GameResoult = ft_fillGameResoult(NumberOfRound);
    for (short NumberOfQuestion = 1; NumberOfQuestion <= NumberOfRound; NumberOfQuestion++) {
        cout << "Question [" << NumberOfQuestion << "/" << NumberOfRound << "]\n";
        ft_StartOperation(GameResoult);
    }
    GameResoult.PassOrFail = ft_ChekIsPassOrFail(GameResoult.NumberOfRightAnsower, GameResoult.NumberOfWrongAnsower);
    GameResoult.PassOrFailName = ft_PassOrFailString(GameResoult.PassOrFail);
    ft_showFinalGameResoult(GameResoult);
}

void ft_ReasetScreen() {
    cout << "\033[0m";// set color of background to default on lunix system
    system ("color");//set color of background to default on windows system
    cout << "\033[2J\033[H";//clear screen in linix and mac os system
    system("cls");// clear screen in windows system
}

void ft_startGame() {
    char PlayAgain = 'Y';
    do {
        ft_ReasetScreen();
        ft_PlayGame();
        cout << "Do you want to play again? Y/N ";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    ft_startGame();

    return 0;
}

