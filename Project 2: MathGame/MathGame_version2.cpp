#include <iostream>
#include <iostream>

using namespace std;

enum en_QuestionLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};

enum en_OperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix_Op = 5};


string ft_Tabs(int NbrOfTabs) {
    string t = "\t";
    for(short tabs = 1; tabs <= NbrOfTabs; tabs++) {
        t += "\t"; 
    }
    return t;
}

string ft_NewLine(int NbrOfTabs) {
    string n = "\n";
    for(short tabs = 1; tabs <= NbrOfTabs; tabs++) {
        n += "\n"; 
    }
    return n;
}

int ft_HowManyQuestion() {
    int nbr = 1;
    cout << ft_NewLine(4) << ft_Tabs(3) << "====================================================" << ft_NewLine(2);
    do {
        cout << ft_NewLine(2) << ft_Tabs(4) << "How many question do you want to ansower? ";
        cout << ft_NewLine(4) << ft_Tabs(3) << "====================================================" << ft_NewLine(2);
        cout << ft_Tabs(6) << " => ";
        cin >> nbr;
    } while (nbr < 1);
    return nbr;
}

en_QuestionLevel ft_ReadQuestionLevel() {
    int nbr = 1;
    cout << ft_NewLine(4) << ft_Tabs(3) << "=======================================================" << ft_NewLine(2);
    do {
        cout << ft_NewLine(2) << ft_Tabs(5) << "Enter question level ::";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [1]: Easy Level";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [2]: Meduem Level";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [3]: Hard Level";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [4]: Mix level ";
        cout << ft_NewLine(2) << ft_Tabs(3) << "=======================================================" << ft_NewLine(2);
        cout << ft_Tabs(6) << " => ";
        cin >> nbr;
    } while(nbr < 1 || nbr > 4);
    return (en_QuestionLevel)nbr;
}

en_OperationType ft_ReadOperationType() {
    int nbr = 1;
    cout << ft_NewLine(4) << ft_Tabs(3) << "=======================================================" << ft_NewLine(2);
    do {
        cout << ft_NewLine(2) << ft_Tabs(5) << "Enter Operation type ::";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [1]:+: Addition";
        cout << ft_NewLine(2) << ft_Tabs(5) << "  [2]:-: Substraction";
        cout << ft_NewLine(2) << ft_Tabs(5) << " [3]:*:Multiplication";
        cout << ft_NewLine(2) << ft_Tabs(5) << "    [4]:/: Division";
        cout << ft_NewLine(2) << ft_Tabs(5) << "   [5]:+ - * /: Mix";
        cout << ft_NewLine(4) << ft_Tabs(3) << "=======================================================" << ft_NewLine(2);
        cout << ft_Tabs(6) << " => ";
        cin >> nbr;
    } while (nbr < 1 || nbr > 5);
    return (en_OperationType)nbr;
}


void ft_ReasetScreen() {
    cout << "\033[0m";// set color of background to default on lunix system
    system ("color");//set color of background to default on windows system
    cout << "\033[2J\033[H";//clear screen in linix and mac os system
    system("cls");// clear screen in windows system
}

struct st_Question {
    int Number1 = 0;
    int number2 = 0;
    en_OperationType OperationType;
    en_QuestionLevel QuestionLevel;
    int CorrectAnsower = 0;
    int  PlayerAnsower = 0;
    bool AnswerResult = false;
};

struct st_Quizz {
    st_Question QuestionList[100];
    short NumberOfQuestion;
    en_QuestionLevel QuestionLevel;
    en_OperationType OperationType;
    short NumberOfRightAnswer = 0;
    short NumberofWrongAnswer = 0;
    bool IsPass = false;
};

int ft_RandomNumber(short from, short to) {
    int RandomNumber = rand() % (to - from + 1) + from;
    return RandomNumber;
}

char ft_GetOperationTypeSymbol(en_OperationType Op_Type) {
    char Op_Taypes[4] = {'+', '-', '*', '/'};
    return Op_Taypes[Op_Type - 1];
}

void ft_SetScreenColor(bool IsPass) {
    switch (IsPass) {
        case false:
            cout << '\a';// ring the bell
            system ("color 4F"); //change color to red in windows System
            cout << "\033[41;37m";// change color to red and text to white in linix or mac OS system
            break;
        case true:
            system ("color 2F"); //change color to green in windows System
            cout << "\033[42;37m";// change color to green and text to white in linix or mac OS system
            break;
    }
}

int ft_GetGetNumberDependingLevel(en_QuestionLevel QuestionLevel) {
    switch(QuestionLevel) {
        case en_QuestionLevel::EasyLevel:
            return ft_RandomNumber(1, 10);
        case en_QuestionLevel::MedLevel:
            return ft_RandomNumber(11, 50);
        case en_QuestionLevel::HardLevel:
            return ft_RandomNumber(51, 99);
        case en_QuestionLevel::Mix:
            return ft_RandomNumber(1, 99);
        
    }
    return ft_RandomNumber(1, 99);
}

int ft_GetQuestionResoult(st_Question Question) {
    switch(Question.OperationType) {
        case en_OperationType::Add:
            return Question.Number1 + Question.number2;
        case en_OperationType::Sub:
            return Question.Number1 - Question.number2;
        case en_OperationType::Mul:
            return Question.Number1 * Question.number2;
        case en_OperationType::Div:
            return Question.Number1 / Question.number2;
    }
    return 0;
}

st_Question ft_GetQuestion(st_Quizz Quiz,st_Question Question) {
    
    Question.Number1 = ft_GetGetNumberDependingLevel(Quiz.QuestionLevel);
    Question.number2 = ft_GetGetNumberDependingLevel(Quiz.QuestionLevel);
    Question.OperationType = Quiz.OperationType;
    
    if(Question.OperationType == en_OperationType::Mix_Op)
    Question.OperationType = en_OperationType(ft_RandomNumber(1,4));
    
    Question.CorrectAnsower = ft_GetQuestionResoult(Question);
    return Question;
}

void ft_GetQuestionQuiz(st_Quizz &Quiz) {
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestion; QuestionNumber++) {
    st_Question Question;
        Quiz.QuestionList[QuestionNumber] = ft_GetQuestion(Quiz, Question);
    }
}

int ft_GetAnsower(){
    int Answer;
    cin >> Answer;
    return Answer;
}

void ft_PressAnyKeyAndEntreeToContunue() {
    char AnyKey = '0';
    while (AnyKey == '0') {
        cout << ft_NewLine(0) << ft_NewLine(0) << ft_Tabs(3) << "Press any key to contunue and entree Without entre 0...";
        cin >> AnyKey;
    }
}

void ft_CorrectAnswer(st_Quizz &Quiz, st_Question &Question){
    Question.AnswerResult = Question.PlayerAnsower == Question.CorrectAnsower;
    ft_SetScreenColor(Question.AnswerResult);
    cout << ft_NewLine(0) << ft_Tabs(6);
    if (Question.AnswerResult) {
        cout << "Right Ansower: -)\n";
        Quiz.NumberOfRightAnswer ++;
        ft_PressAnyKeyAndEntreeToContunue();
    }

    else {
        cout << "Wrong Ansower: -(\n";
        cout << ft_NewLine(0) << ft_Tabs(6) << "The right answer is: " << Question.CorrectAnsower << ft_NewLine(1);
        Quiz.NumberofWrongAnswer ++;
        ft_PressAnyKeyAndEntreeToContunue();
    }
    ft_ReasetScreen();
}

void ft_PrintQuestionQuiz(st_Quizz &Quiz) {
    for(short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestion; QuestionNumber++) {
        cout << ft_NewLine(4) << ft_Tabs(3) << "=======================================================\n\n";

        st_Question Question = Quiz.QuestionList[QuestionNumber];
        cout << ft_Tabs(5) << " ___________________\n";
        cout << ft_Tabs(5) << "|| Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestion << "] ||\n";
        cout << ft_NewLine(2) << ft_Tabs(6) << Question.Number1 << '\n';
        cout << ft_Tabs(6) << Question.number2 << ' ' << ft_GetOperationTypeSymbol(Question.OperationType);
        cout << ft_NewLine(0) << ft_Tabs(6) << "_____________\n";
        cout << ft_NewLine(0) << ft_Tabs(6);
        Question.PlayerAnsower = ft_GetAnsower();
        cout << ft_NewLine(1) << ft_Tabs(3) << "=======================================================\n\n";
        ft_CorrectAnswer(Quiz, Question);
    }
}

bool ft_ChekIsPassOrFail(short N_RightAnsower, short N_WrongAnsower) {
    return (N_RightAnsower >= N_WrongAnsower);
}

string PassOrFailText(bool IsPass) {
    string IsPassText[2] = {"Fail: -(", "Pass: -)"};
    return IsPassText[IsPass];
}

void ft_ShowFinalResoltScreen(st_Quizz Quiz) {
    cout << ft_NewLine(4) << ft_Tabs(3) << "======================================================="
   << ft_NewLine(1) << ft_Tabs(5) << "Final resoult is " << PassOrFailText(ft_ChekIsPassOrFail(Quiz.NumberOfRightAnswer, Quiz.NumberofWrongAnswer));
    cout << ft_NewLine(1) << ft_Tabs(3) << "=======================================================" << ft_NewLine(2);
}

string ft_GetOperationTypeText(en_OperationType choice) {
    string Op_Types[5] = {"Add", "Sub", "Mul" , "Div", "Mix"};
    return Op_Types[choice - 1];
}

string ft_GetQuestionLevelText(en_QuestionLevel choice) {
    string QuetionsLevel[4] = {"Easy", "Med", "Hard", "Mix"};
    return QuetionsLevel[choice - 1];
}

void ft_showFinalGameResoult(st_Quizz Quiz) {
    cout << ft_Tabs(5) << "Number of Question_____: " << Quiz.NumberOfQuestion << '\n';
    cout << ft_Tabs(5) << "Question level_________: " << ft_GetQuestionLevelText(Quiz.QuestionLevel) << '\n';
    cout << ft_Tabs(5) << "Operation Type_________: " << ft_GetOperationTypeText(Quiz.OperationType) << '\n';
    cout << ft_Tabs(5) << "Number of Right Ansower: " << Quiz.NumberOfRightAnswer << "\n";
    cout << ft_Tabs(5) << "Number of wrong ansower: " << Quiz.NumberofWrongAnswer << '\n';
    cout << ft_NewLine(1) << ft_Tabs(3) << "########################################################" << endl;
}

void ft_PrintMathGameResoult(st_Quizz Quiz) {
    ft_ShowFinalResoltScreen(Quiz);
    ft_showFinalGameResoult(Quiz);
}

void ft_StartMathGame() {
    st_Quizz Quiz;

    Quiz.NumberOfQuestion = ft_HowManyQuestion();
    ft_ReasetScreen();
    Quiz.QuestionLevel = ft_ReadQuestionLevel();
    ft_ReasetScreen();
    Quiz.OperationType = ft_ReadOperationType();
    ft_ReasetScreen();

    ft_GetQuestionQuiz(Quiz);
    ft_PrintQuestionQuiz(Quiz);
    ft_PrintMathGameResoult(Quiz);
}


void ft_PlayGame() {
    char PlayAgain = 'Y';
    do {
        ft_ReasetScreen();
        ft_StartMathGame();
        cout << ft_NewLine(1) << ft_Tabs(5) << "Do you want to play again? ";
        cin >> PlayAgain;
    } while(PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(NULL));
    ft_PlayGame();
    return 0;
}