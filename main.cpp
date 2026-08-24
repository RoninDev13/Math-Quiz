#include <iostream>
#include <cstdlib>
#include <string>
#include <Windows.h>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, MixLvl = 4 };
enum enOperations { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct QuizStats
{
    int NumberOfQuestions = 0, UserAnswer = 0, RightAnswer = 0,
        QuestionFirstNum = 0, QuestionSecondNum = 0,
        TotalRightAnswers = 0, TotalWrongAnswers = 0;
    short RangeFrom = 0, RangeTo = 0; 
    string FinalDecision, QuestionLevelName, OperationTypeName;
    char Operator;
    enQuestionsLevel QuestionLevel;
    enOperations QuestionOperation;
};

int RandomNumber(int From, int To)
{
    int RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}

int UserChoice(string Message, int From, int To)
{
    int R;

    do
    {
        cout << Message << endl;
        cout << "=> ";
        cin >> R;
    } while (R < From || R > To);

    return R;
}

int ReadNumber(string Message)
{
    int R;

    do
    {
        cout << Message << endl;
        cout << "=> ";
        cin >> R;
    } while (R <= 0);

    return R;
}

void Delay(int ms)
{
    Sleep(ms);
}

void TerminalClear()
{
    system("cls");
    system("Color 0F");
}

void GetNumberOfQuestions(QuizStats& QuizStats)
{
    QuizStats.NumberOfQuestions = ReadNumber("How many questions you want to answer ?");
}

enQuestionsLevel ReadQuestionsLevel()
{
    int Level = UserChoice("Please Enter Questions Level [1]-Easy, [2]-Med, [3]-Hard, [4]-Mix", 1, 4);

    return (enQuestionsLevel) Level;
}

void GetNumbersRange(QuizStats& QuizStats)
{
    switch (ReadQuestionsLevel())
    {
    case enQuestionsLevel::Easy: 
        QuizStats.QuestionLevelName = "Easy";
        QuizStats.RangeFrom = 1, QuizStats.RangeTo = 10;
        break;  
    case enQuestionsLevel::Med:
        QuizStats.QuestionLevelName = "Med";
        QuizStats.RangeFrom = 11, QuizStats.RangeTo = 50;
        break;
    case enQuestionsLevel::Hard:
        QuizStats.QuestionLevelName = "Hard";
        QuizStats.RangeFrom = 51, QuizStats.RangeTo = 100;
        break;
    case enQuestionsLevel::MixLvl: 
        QuizStats.QuestionLevelName = "Mix";
        QuizStats.RangeFrom = 1, QuizStats.RangeTo = 100;
        break;
    } 
}

enOperations ReadQuestionsOperation()
{
    int Operation = UserChoice("Please Enter Questions Operation [1]-Add, [2]-Sub, [3]-Mul, [4]-Div, [5]-Mix", 1, 5);

    return (enOperations) Operation;
}

void GetQuestionOperation(QuizStats& QuizStats)
{
    switch (ReadQuestionsOperation())
    {
    case enOperations::Add: 
        QuizStats.OperationTypeName = "Add";
        QuizStats.Operator = '+';
        break;
    case enOperations::Sub: 
        QuizStats.OperationTypeName = "Sub";
        QuizStats.Operator = '-';
        break;
    case enOperations::Mul: 
        QuizStats.OperationTypeName = "Mul";
        QuizStats.Operator = '*';
        break;
    case enOperations::Div: 
        QuizStats.OperationTypeName = "Div";
        QuizStats.Operator = '/';
        break;
    case enOperations::MixOp: 
        QuizStats.OperationTypeName = "Mix";
        QuizStats.Operator = 'M';
        break;
    }
}

char GetRandomOperator()
{
    char Ops[4] = { '+', '-', '*', '/' };
    char Op = Ops[RandomNumber(0, 3)];
    return Op;
}

void GetTheRightAnswer(QuizStats& QuizStats)
{
    switch (QuizStats.Operator)
    {
    case '+': QuizStats.RightAnswer = QuizStats.QuestionFirstNum + QuizStats.QuestionSecondNum;
        break;
    case '-': QuizStats.RightAnswer = QuizStats.QuestionFirstNum - QuizStats.QuestionSecondNum;
        break;
    case '*': QuizStats.RightAnswer = QuizStats.QuestionFirstNum * QuizStats.QuestionSecondNum;
        break;
    case '/': QuizStats.RightAnswer = QuizStats.QuestionFirstNum / QuizStats.QuestionSecondNum;
        break;
    }
}

void GenerateQuestion(short CurrentQuestion, QuizStats& QuizStats)
{
    // Get operator
    if (QuizStats.OperationTypeName == "Mix") QuizStats.Operator = GetRandomOperator();

    // Num1 and Num2
    QuizStats.QuestionFirstNum = RandomNumber(QuizStats.RangeFrom, QuizStats.RangeTo);
    QuizStats.QuestionSecondNum = RandomNumber(QuizStats.RangeFrom, QuizStats.RangeTo);
    
    cout << "Question [" << CurrentQuestion << "/" << QuizStats.NumberOfQuestions << "]" << "\n\n";
    cout << QuizStats.QuestionFirstNum << endl;
    cout << QuizStats.QuestionSecondNum << " " << QuizStats.Operator << endl;
    cout << "--------------" << endl;
}

void ReadUserAnswer(QuizStats& QuizStats)
{
    cin >> QuizStats.UserAnswer;
}

bool IsAnswerCorrect(QuizStats QuizStats)
{
    return QuizStats.UserAnswer == QuizStats.RightAnswer;
}

void UpdateScore(QuizStats& QuizStats, bool Decision)
{
    if (Decision)
    {
        QuizStats.TotalRightAnswers++;
    }
    else
    {
        QuizStats.TotalWrongAnswers++;
    }
}

void ScreenEffects(bool Decision)
{
    if (Decision)
    {
        system("color 27");
    }
    else 
    {
        system("color 47");
        cout << "\a";
    }
}

void ScreenMessage(QuizStats QuizStats, bool Decision)
{
    if (Decision)
    {
        cout << "Right Answer :)" << endl;
    }
    else
    {
        cout << "Wrong Answer :(" << endl;
        cout << "The right Answer was: " << QuizStats.RightAnswer << endl;
    }
}

void ResetValues(QuizStats& QuizStats)
{
    QuizStats.NumberOfQuestions = 0;
    QuizStats.UserAnswer = 0;
    QuizStats.RightAnswer = 0;
    QuizStats.QuestionFirstNum = 0;
    QuizStats.QuestionSecondNum = 0;
    QuizStats.TotalRightAnswers = 0;
    QuizStats.TotalWrongAnswers = 0;
    QuizStats.RangeFrom = 0;
    QuizStats.RangeTo = 0;
    QuizStats.FinalDecision = " ";
    QuizStats.QuestionLevelName = " ";
    QuizStats.OperationTypeName = " ";
    QuizStats.Operator = ' ';
    QuizStats.QuestionLevel;
    QuizStats.QuestionOperation;
}

void PlayRound(short CurrentQuestion, QuizStats& QuizStats)
{
    // clear terminal
    TerminalClear();

    // Generate One Question
    GenerateQuestion(CurrentQuestion, QuizStats);

    // Read the User Answer
    ReadUserAnswer(QuizStats);

    // Calculate the right Answer 
    GetTheRightAnswer(QuizStats);

    // Determine if the answer is right
    bool RoundDecision = IsAnswerCorrect(QuizStats);

    // Update game score based on desicion
    UpdateScore(QuizStats, RoundDecision);

    // Show screen effect
    ScreenEffects(RoundDecision);
    ScreenMessage(QuizStats, RoundDecision);

    // Delay (in ms)
    Delay(3000);
}

bool IsPassed(QuizStats& QuizStats)
{
    return QuizStats.TotalRightAnswers > QuizStats.TotalWrongAnswers;
}

void DisplayEndOfGameStats(QuizStats QuizStats, bool Decision)
{
    TerminalClear();

    if (Decision) QuizStats.FinalDecision = "You Passed :)";
    else QuizStats.FinalDecision = "You Failed :(";

    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << "    Final Result Is: " << QuizStats.FinalDecision << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << "Number of Questions  : " << QuizStats.NumberOfQuestions << endl;
    cout << "Questions Level      : " << QuizStats.QuestionLevelName << endl;
    cout << "Operation Type       : " << QuizStats.OperationTypeName << endl;
    cout << "Total Right Answer   : " << QuizStats.TotalRightAnswers << endl;
    cout << "Total Wrong Answers  : " << QuizStats.TotalWrongAnswers << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;
    cout << endl;
}

void GameStart()
{
    int Choice = 0;
    QuizStats QuizStats;

    do
    {
        TerminalClear();

        // Get number of Questions
        GetNumberOfQuestions(QuizStats);

        // Set the Numbers ranges and question level name
        GetNumbersRange(QuizStats);

        // Set the Operation Operator
        GetQuestionOperation(QuizStats);

        for (int i = 1; i <= QuizStats.NumberOfQuestions; i++)
        {
            PlayRound(i, QuizStats);
        }

        // Check if the user passed the quiz
        bool EndOfGameDecision = IsPassed(QuizStats);

        // Display end of quiz results
        DisplayEndOfGameStats(QuizStats, EndOfGameDecision);

        // End Of Game Screen Effects
        ScreenEffects(EndOfGameDecision);

        // Reset Value
        ResetValues(QuizStats);
        
        // ask the player if he wants to play again
        Choice = UserChoice("Do you want to play again [1]: Yes, [2]: No: ", 1, 2);
    } while (Choice == 1);
}

int main()
{
    srand((unsigned)time(NULL));

    GameStart();
}