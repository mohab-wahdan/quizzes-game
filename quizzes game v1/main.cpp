#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <random>
#include <time.h>
#include <fstream>
#include <cstdlib>
#include <ctime>

static int NumberOfQuestions=0;   //generate unique question id
static int NumberOfQuizzes=0;     //generate unique quiz id
using namespace std;

class user{
    protected:
    string UserName,password,FirstName,LastName,role;
    int id;
    public:
    bool operator==(string inputuser){
    if(this->UserName!=inputuser)return false;
    else return true;
    }
        void UpdateName(string FirstName,string LastName){
        this->FirstName=FirstName;
        this->LastName=LastName;
    }
};

class admin : public user{

public:
    void WelcomeAdmin(){
    cout<<"welcome "<<this->FirstName<<" "<<this->LastName<<" "<<"("<<this->role<<"), please choose from the following options:"<<endl;
    }

    bool UserFind(string InputUserName,string InputPssword){
        if(this->UserName==InputUserName && this->password==InputPssword){
                return true;
        }
        else return false;
    }
    //display user informations
    friend ostream& operator<<(ostream& out,const admin& users){
    out<<users.FirstName<<"         "<<users.LastName<<"         "<<users.UserName<<"         "<<users.role<<endl;
    return out;
    }


    void SetValuesAdmin(string UserName,string password,string FirstName,string LastName,string RoleType){
        this->UserName=UserName;
        this->password=password;
        this->FirstName=FirstName;
        this->LastName=LastName;
        this->role=RoleType;

    }
};

class question{
protected:
    string QuestionText,CorrectAnswer;
    int id;
};

class CQuestion:public question{
public:
    bool operator==(int id){
    if(this->id==id)return true;
    else return false;
    }
    string ShowCForQuiz(){
        cout<<"("<<this->id<<") "<<this->QuestionText<<endl;
        return this->CorrectAnswer;
    }
    static void readQuestionFromFile(vector<CQuestion> &CQuestions,ifstream& file){
        CQuestion storec;
        string QuestionC,AnswerC;
        getline(file,QuestionC);
        getline(file,AnswerC);
        for(unsigned int i=0;i<CQuestions.size();i++){
            if(CQuestions[i]==QuestionC) return;
        }
        storec.SetValuesC(QuestionC,AnswerC);
        CQuestions.push_back(storec);

    }
    static void AddQuestion(vector<CQuestion> &CQuestions ){
        CQuestion storec;
        string QuestionC,AnswerC;
        cout<<"enter your question: "<<endl;
        getline(cin,QuestionC);
        for(unsigned int i=0;i<CQuestions.size();i++){
            if(CQuestions[i]==QuestionC){
                cout<<"this question already exist please add new question "<<endl;
                return;
            }
        }
        cout<<"enter the answer: "<<endl;
        getline(cin,AnswerC);
        storec.SetValuesC(QuestionC,AnswerC);
        CQuestions.push_back(storec);

    }
    bool CheckAnswer(string useranswer){
    if(CorrectAnswer==useranswer)return true;
    else return false;
    }
    void SetValuesC(string questiontext,string rightanswer){
    QuestionText=questiontext;
    CorrectAnswer=rightanswer;
    NumberOfQuestions++;
    this->id=NumberOfQuestions;
    }
    bool operator==(string inputquestion){
    if(this->QuestionText==inputquestion)return true;
    else return false;
    }
    friend ostream& operator<<(ostream& out ,const CQuestion& c){
        out<<"(ID:"<<c.id<<") "<<c.QuestionText<<"(answer:"<<c.CorrectAnswer<<")"<<endl;
        return out;
    }
    void operator=(const CQuestion& cq){
    this->QuestionText=cq.QuestionText;
    this->CorrectAnswer=cq.CorrectAnswer;
    this->id=cq.id;
    }

};

class MCQuestion:public question{
string answer1,answer2,answer3;
public:
    bool operator==(int id){
    if(this->id==id)return true;
    else return false;
    }
    char ShowMCForQuiz(int RandNum[4]){
        char CorrectAnswerChar;
        string choises[4];
        choises[0]=this->CorrectAnswer;
        choises[1]=this->answer1;
        choises[2]=this->answer2;
        choises[3]=this->answer3;
        cout<<"("<<this->id<<") "<<this->QuestionText<<endl;
        cout<<"[a]"<<choises[RandNum[0]]<<endl;
        cout<<"[b]"<<choises[RandNum[1]]<<endl;
        cout<<"[c]"<<choises[RandNum[2]]<<endl;
        cout<<"[d]"<<choises[RandNum[3]]<<endl;
        //find the correct answer
        if(choises[RandNum[0]]==this->CorrectAnswer)CorrectAnswerChar='a';

		if(choises[RandNum[1]]==this->CorrectAnswer)CorrectAnswerChar='b';

		if(choises[RandNum[2]]==this->CorrectAnswer)CorrectAnswerChar='c';

		if(choises[RandNum[3]]==this->CorrectAnswer)CorrectAnswerChar='d';

        return CorrectAnswerChar;
    }
    static void readQuestionFromFile(vector<MCQuestion> &MCQuestions,ifstream& file){
        MCQuestion storemc;
        string QuestionMC ,CorrectAnswerMCQ,Answer1MCQ,Answer2MCQ,Answer3MCQ;
        getline(file,QuestionMC);
        getline(file,CorrectAnswerMCQ);
        getline(file,Answer1MCQ);
        getline(file,Answer2MCQ);
        getline(file,Answer3MCQ);
        for(unsigned int i=0;i<MCQuestions.size();i++){
            if(MCQuestions[i]==QuestionMC)return;
        }
        storemc.SetValuesMC(QuestionMC,CorrectAnswerMCQ,Answer1MCQ,Answer2MCQ,Answer3MCQ);
        MCQuestions.push_back(storemc);

    }
    static void AddQuestion(vector<MCQuestion> &MCQuestions){
        MCQuestion storemc;
        string QuestionMC ,CorrectAnswerMCQ,Answer1MCQ,Answer2MCQ,Answer3MCQ;
        cout<<"enter your question: "<<endl;
        getline(cin,QuestionMC);
        for(unsigned int i=0;i<MCQuestions.size();i++){
            if(MCQuestions[i]==QuestionMC){
                cout<<"this question already exist please add new question "<<endl;
                return;
            }
        }
        cout<<"enter the correct answer: "<<endl;
        getline(cin,CorrectAnswerMCQ);
        cout<<"enter the second answer: "<<endl;
        getline(cin,Answer1MCQ);
        cout<<"enter the third answer: "<<endl;
        getline(cin,Answer2MCQ);
        cout<<"enter the forth answer: "<<endl;
        getline(cin,Answer3MCQ);
        storemc.SetValuesMC(QuestionMC,CorrectAnswerMCQ,Answer1MCQ,Answer2MCQ,Answer3MCQ);
        MCQuestions.push_back(storemc);

    }

    void SetValuesMC(string questions, string rightanswer,string first,string second,string third ){
    QuestionText=questions;
    CorrectAnswer=rightanswer;
    answer1=first;
    answer2=second;
    answer3=third;
    NumberOfQuestions++;
    this->id=NumberOfQuestions;
    }
    bool operator==(string inputquestion){
    if(this->QuestionText==inputquestion)return true;
    else return false;
    }
    friend ostream& operator<<(ostream& out ,const MCQuestion& mc){
        out<<"(ID:"<<mc.id<<") "<<mc.QuestionText<<endl;
        out<<"    *[a]"<<mc.CorrectAnswer<<"    [b]"<<mc.answer1<<"    [c]"<<mc.answer2<<"    [d]"<<mc.answer3<<endl;
        return out;
    }
    void operator=(const MCQuestion& cq){
    this->QuestionText=cq.QuestionText;
    this->CorrectAnswer=cq.CorrectAnswer;
    this->answer1=cq.answer1;
    this->answer2=cq.answer2;
    this->answer3=cq.answer3;
    this->id=cq.id;
    }

};

class TFQuestion:public question{
public:
    bool operator==(int id){
    if(this->id==id)return true;
    else return false;
    }
    string ShowTFForQuiz(){
        cout<<"("<<this->id<<") "<<this->QuestionText<<endl;
        return this->CorrectAnswer;
    }
    static void readQuestionFromFile(vector<TFQuestion> &TFQuestions,ifstream& file){
        TFQuestion storetf;
        string QuestionTF,AnswerTF;
        getline(file,QuestionTF);
        getline(file,AnswerTF);
        for(unsigned int i=0;i<TFQuestions.size();i++){
            if(TFQuestions[i]==QuestionTF) return;
        }
        storetf.SetValuesTF(QuestionTF,AnswerTF);
        TFQuestions.push_back(storetf);
    }
    static void AddQuestion(vector<TFQuestion> &TFQuestions){
        TFQuestion storetf;
        string QuestionTF,AnswerTF;
        cout<<"enter your question: "<<endl;
        getline(cin,QuestionTF);
        for(unsigned int i=0;i<TFQuestions.size();i++){
            if(TFQuestions[i]==QuestionTF){
                cout<<"this question already exist please add new question "<<endl;
                return;
            }
        }
        ReChooseAnswer:
        cout<<"enter the answer: "<<endl;
        getline(cin,AnswerTF);
        if(AnswerTF != "true" && AnswerTF != "false"){
            cout<<"your answer must be [true/false]"<<endl;
            goto ReChooseAnswer;
        }
        storetf.SetValuesTF(QuestionTF,AnswerTF);
        TFQuestions.push_back(storetf);

    }
    void readQuestionFromFile(){}
    void SetValuesTF(string questiontext,string rightanswer){
    QuestionText=questiontext;
    CorrectAnswer=rightanswer;
    NumberOfQuestions++;
    this->id=NumberOfQuestions;
    }

    bool operator==(string inputquestion){
    if(this->QuestionText==inputquestion)return true;
    else return false;
    }
    friend ostream& operator<<(ostream& out ,const TFQuestion& tf){
        out<<"(ID:"<<tf.id<<") "<<tf.QuestionText<<"(answer:"<<tf.CorrectAnswer<<")"<<endl;
        return out;
    }
    void operator=(const TFQuestion& cq){
    this->QuestionText=cq.QuestionText;
    this->CorrectAnswer=cq.CorrectAnswer;
    this->id=cq.id;
    }
};
class quiz{
    public:
    int RandMC,RandC[2],RandTF[2],RandMCAnswers[4];
    string UserInputs[5][2];
    MCQuestion MCQ;
    TFQuestion TFQ1,TFQ2;
    CQuestion  CQ1,CQ2;
    int score=0,NumOfRight=0,NumOfWrong=0,MCScore=0,CScore=0,TFScore=0;
    string CorrectAnswer,UserAnswer;
    string CorrectAnswerChar,UserChar;

    void start(vector<MCQuestion> &MCQuestions,vector<CQuestion> &CQuestions,vector<TFQuestion> &TFQuestions){
        //check if the questions if enough to start a quiz
        if(MCQuestions.size()<1||CQuestions.size()<2||TFQuestions.size()<2){
            cout<<"there is no enough questions to start quiz! please add more questions"<<endl;
            return;
        }
    score=0;
    MCScore=0;
    CScore=0;
    TFScore=0;
    int RandomAnswer,RandomQ;
    srand(time(0));
    //set the element to -1 that when the object is called twice it will have it's past values
    for(int i=0;i<2;i++){
        RandC[i]=-1;
        RandTF[i]=-1;
    }
    for(int i=0;i<4;i++){
        RandMCAnswers[i]=-1;
    }
    //generate random numbers
   for(int i=0;i<4;i++){
        ReRandom:       //if the random number is repeated it will be generated again
		RandomAnswer=rand()%4;
        for(int j=0;j<4;j++){
            if(RandomAnswer==RandMCAnswers[j])goto ReRandom;
        }
        RandMCAnswers[i]=RandomAnswer;
	}
    RandMC=rand()% (MCQuestions.size());
	for(int i=0;i<2;i++){
        ReRandomC:       //if the random number is repeated it will be generated again
		RandomQ=rand()% (CQuestions.size());
        for(int j=0;j<2;j++){
            if(RandomQ==RandC[j])goto ReRandomC;
        }
        RandC[i]=RandomQ;
	}
	for(int i=0;i<2;i++){
        ReRandomTf:       //if the random number is repeated it will be generated again
		RandomQ=rand()% (TFQuestions.size());
        for(int j=0;j<2;j++){
            if(RandomQ==RandTF[j])goto ReRandomTf;
        }
        RandTF[i]=RandomQ;
	}
	MCQ=MCQuestions[RandMC];
	cout<<"[1]id=";
    CorrectAnswerChar= MCQuestions[RandMC].ShowMCForQuiz(RandMCAnswers);
    getline(cin,UserChar);
    UserInputs[0][0]=UserChar;
    UserInputs[0][1]="wrong";
    if(UserChar==CorrectAnswerChar){
        UserInputs[0][1]="right";
        score+=2;
        MCScore++;
    }
    CQ1=CQuestions[RandC[0]];
    cout<<"[2]id=";
    CorrectAnswer=CQuestions[RandC[0]].ShowCForQuiz();
    getline(cin,UserAnswer);
    UserInputs[1][0]=UserAnswer;
    UserInputs[1][1]="wrong";
    if(UserAnswer==CorrectAnswer){
        score+=3;
        CScore++;
        UserInputs[1][1]="right";
    }
    CQ2=CQuestions[RandC[1]];
    cout<<"[3]id=";
    CorrectAnswer=CQuestions[RandC[1]].ShowCForQuiz();
    getline(cin,UserAnswer);
    UserInputs[2][0]=UserAnswer;
    UserInputs[2][1]="wrong";
    if(UserAnswer==CorrectAnswer){
        score+=3;
        CScore++;
        UserInputs[2][1]="right";
    }
    TFQ1=TFQuestions[RandTF[0]];
    cout<<"[4]id=";
    CorrectAnswer=TFQuestions[RandTF[0]].ShowTFForQuiz();
    getline(cin,UserAnswer);
    UserInputs[3][0]=UserAnswer;
    UserInputs[3][1]="wrong";
    if(UserAnswer==CorrectAnswer){
        score+=1;
        TFScore++;
        UserInputs[3][1]="right";
    }
    TFQ2=TFQuestions[RandTF[1]];
    cout<<"[5]id=";
    CorrectAnswer=TFQuestions[RandTF[1]].ShowTFForQuiz();
    getline(cin,UserAnswer);
    UserInputs[4][0]=UserAnswer;
    UserInputs[4][1]="wrong";
    if(UserAnswer==CorrectAnswer){
        score+=1;
        TFScore++;
        UserInputs[4][1]="right";
    }
    NumOfRight=MCScore+TFScore+CScore;
    NumOfWrong=5-NumOfRight;
    cout<<"your score = "<<score<<endl;
    cout<<"number of right answers = "<<NumOfRight<<endl;
    cout<<"number of wrong answers = "<<NumOfWrong<<endl;

    }
};
class player : public user{

    vector<int> QuizTakeId;
    int NumOfQuizTake=0;

public:
    void DisplayScoreStat(vector<quiz> quizzes){
        if(NumOfQuizTake==0){
            cout<<"You haven't done any tests yet "<<endl;
            return;
        }
        float AverageMCQuestions=0,AverageCQuestions=0,AverageTFQuestions=0,AverageScore=0;
        int maxscore=0,minscore=quizzes[QuizTakeId[0]].score;
        for(unsigned int i=0;i<QuizTakeId.size();i++){
            if(maxscore<quizzes[QuizTakeId[i]].score)maxscore=quizzes[QuizTakeId[i]].score;
            if(minscore>quizzes[QuizTakeId[i]].score)minscore=quizzes[QuizTakeId[i]].score;
            AverageScore+=quizzes[QuizTakeId[i]].score;
            AverageMCQuestions+=quizzes[QuizTakeId[i]].MCScore;
            AverageTFQuestions+=quizzes[QuizTakeId[i]].TFScore;
            AverageCQuestions+=quizzes[QuizTakeId[i]].CScore;
        }
        AverageScore=(AverageScore/(NumOfQuizTake*10))*10;
        AverageCQuestions=(AverageCQuestions/(NumOfQuizTake*2))*3;
        AverageMCQuestions=(AverageMCQuestions/NumOfQuizTake)*2;
        AverageTFQuestions=(AverageTFQuestions/(NumOfQuizTake*2));

        cout<<"Your score statistics per quiz:"<<endl;
        cout<<"     - Number of Quizzes taken: "<<NumOfQuizTake<<endl;
        cout<<"     - Highest quiz score: "<<maxscore<<"/10"<<endl;
        cout<<"     - Lowest quiz score: "<<minscore<<"/10"<<endl;
        cout<<"     - Average quiz score: "<<AverageScore<<"/10"<<endl;
        cout<<"Your score statistics per question:"<<endl;
        cout<<"     - Number of MC questions: "<<NumOfQuizTake<<endl;
        cout<<"     - Number of Complete questions: "<<NumOfQuizTake*2<<endl;
        cout<<"     - Number of T/F Questions: "<<NumOfQuizTake*2<<endl;
        cout<<"     - Average grade for MC questions: "<<AverageMCQuestions<<"/2"<<endl;
        cout<<"     - Average grade for Complete questions: "<<AverageCQuestions<<"/3"<<endl;
        cout<<"     - Average grade for T/F questions: "<<AverageTFQuestions<<"/1"<<endl;
    }
    void SetQuizInfo(int QuizId){
    QuizTakeId.push_back(QuizId);
    NumOfQuizTake++;
    }
    //display user informations
    void WelcomePlayer(){
    cout<<"welcome "<<this->FirstName<<" "<<this->LastName<<" "<<"("<<this->role<<"), please choose from the following options:"<<endl;
    }

    void SetValuesPlayer(string UserName,string password,string FirstName,string LastName,string RoleType){
        this->UserName=UserName;
        this->password=password;
        this->FirstName=FirstName;
        this->LastName=LastName;
        this->role=RoleType;

    }
    bool UserFind(string InputUserName,string InputPssword){
        if(this->UserName==InputUserName && this->password==InputPssword){
                return true;
        }
        else return false;
    }
    friend ostream& operator<<(ostream& out,const player& users){
    out<<users.FirstName<<"         "<<users.LastName<<"         "<<users.UserName<<"         "<<users.role<<endl;
    return out;
    }
    void DisplayAllScores(vector<quiz> quizzes){
        if(NumOfQuizTake==0){
            cout<<"You haven't done any tests yet "<<endl;
            return;
        }
        cout<<"the total number of quizzes you finished: "<<NumOfQuizTake<<endl;
        cout<<"for each quiz: "<<endl;
        for(unsigned int i=0;i<QuizTakeId.size();i++){
            cout<<"    quiz "<<i+1<<endl;
            cout<<"    number of right answers: "<<quizzes[QuizTakeId[i]].NumOfRight<<endl;
            cout<<"    number of wrong answers: "<<quizzes[QuizTakeId[i]].NumOfWrong<<endl;
            cout<<"    quiz score: "<<quizzes[QuizTakeId[i]].score<<endl;
        }
    }
    void DisplayLast2(vector<quiz> quizzes){
        if(NumOfQuizTake<2){
            cout<<"You haven't done 2 tests yet "<<endl;
            return;
        }
        cout<<"for the last 2 quizzes: "<<endl;
        for(int i=1;i<3;i++){
            cout<<"for quiz "<<i<<":"<<endl;
            cout<<"all the questions in the quiz and their answers: "<<endl;
            cout<<quizzes[QuizTakeId[NumOfQuizTake-i]].MCQ.ShowMCForQuiz(quizzes[QuizTakeId[NumOfQuizTake-i]].RandMCAnswers)<<" is the correct answer"<<endl;
            cout<<"your answer was "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[0][0]<<" "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[0][1]<<endl;
            cout<<"and your score for this question: "<<quizzes[QuizTakeId[NumOfQuizTake-i]].MCScore*2<<"/2"<<endl;
            cout<<quizzes[QuizTakeId[NumOfQuizTake-i]].CQ1<<endl;
            cout<<"your answer was "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[1][0]<<" "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[1][1]<<endl;
            cout<<quizzes[QuizTakeId[NumOfQuizTake-i]].CQ2<<endl;
            cout<<"your answer was "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[2][0]<<" "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[2][1]<<endl;
            cout<<"and your score for this question: "<<quizzes[QuizTakeId[NumOfQuizTake-i]].CScore*3<<"/6"<<endl;
            cout<<quizzes[QuizTakeId[NumOfQuizTake-i]].TFQ1<<endl;
            cout<<"your answer was "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[3][0]<<" "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[3][1]<<endl;
            cout<<quizzes[QuizTakeId[NumOfQuizTake-i]].TFQ2<<endl;
            cout<<"your answer was "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[4][0]<<" "<<quizzes[QuizTakeId[NumOfQuizTake-i]].UserInputs[4][1]<<endl;
            cout<<"and your score for this question: "<<quizzes[QuizTakeId[NumOfQuizTake-i]].TFScore<<"/2"<<endl;
            cout<<"this quiz score: "<<quizzes[QuizTakeId[NumOfQuizTake-i]].score<<endl;
        }


    }
};

int main()
{
    int PresentUserId,UserChoiseInt;
    string PresentUserRule,UserChoiseStr;
    vector<CQuestion> CQuestions;
    vector<MCQuestion> MCQuestions;
    vector<TFQuestion> TFQuestions;
    vector<quiz> quizzes;
    quiz StoreQuiz;
    string  StoreUserName, Storepassword, StoreFirstName, StoreLastName, StoreRoleType;
    vector<admin> admins;
    admin StoreAdmin;
    vector<player> players;
    player StorePlayer;
    StoreAdmin.SetValuesAdmin("admin","admin","user","user","admin");
    StorePlayer.SetValuesPlayer("player","player","user","user","player");
    admins.push_back(StoreAdmin);
    players.push_back(StorePlayer);
    ReStart:                     //the main menu
    PresentUserRule="none";      //when user switches account his past role will be deleted
    cout<<"*******************************************************************"<<endl;
    cout<<"Welcome to the Quiz game program V2.0!"<<endl;
    cout<<"*******************************************************************"<<endl;
    cout<<"Please enter your username: "<<endl;
    getline(cin,StoreUserName);
    cout<<"Please enter your password:"<<endl;
    getline(cin,Storepassword);
    for(unsigned int i=0;i<admins.size();i++){         //search for the user in admins accounts
        if(admins[i].UserFind(StoreUserName,Storepassword)){
            PresentUserRule="admin";
            PresentUserId=i;
        }
    }
    for(unsigned int i=0;i<players.size();i++){       //search for the user in players accounts
        if(players[i].UserFind(StoreUserName,Storepassword)){
            PresentUserRule="player";
            PresentUserId=i;
        }
    }
    if(PresentUserRule!="admin"&&PresentUserRule!="player"){
        cout<<"wrong username or password"<<endl;
        goto ReStart;
    }
    if(PresentUserRule=="admin"){
        AdminMainMenu:
        admins[PresentUserId].WelcomeAdmin();
        cout<<"[1] Switch accounts"<<endl;
        cout<<"[2] Update your name"<<endl;
        cout<<"[3] View all users"<<endl;
        cout<<"[4] Add new user"<<endl;
        cout<<"[5] View all questions"<<endl;
        cout<<"[6] Add new question"<<endl;
        cout<<"[7] Load questions from file"<<endl;
        cout<<"[8] Exit the program"<<endl;
        getline(cin,UserChoiseStr);
        if(isdigit(UserChoiseStr[0])==false){      //make sure the input is integer
            cout<<"invalid input!"<<endl;
            goto AdminMainMenu;
        }
        UserChoiseInt=stoi(UserChoiseStr);
        switch(UserChoiseInt){
            case 1:{
                goto ReStart;
                break;}
            case 2:
                {string first,last;
                cout<<"enter the new first name: "<<endl;
                getline(cin,first);
                cout<<"enter the new last name: "<<endl;
                getline(cin,last);
                admins[PresentUserId].UpdateName(first,last);
                goto AdminMainMenu;}
            case 3:
                {string choise3;
                cout<<"Existing users in the system:"<<endl;
                cout<<"first name    last name    username    role"<<endl;
                for(unsigned int i=0;i<admins.size();i++)cout<<admins[i];
                for(unsigned int i=0;i<players.size();i++)cout<<players[i];
                ReChoise3:   //take the input again
                cout<<"Press [n] if you want to add a new user or [b] to go back to the main menu."<<endl;
                getline(cin,choise3);
                if(choise3!="n"&&choise3!="N"&&choise3!="b"&&choise3!="B"){
                    cout<<"you must choose from these answers [n/b]"<<endl;
                    goto ReChoise3;
                }
                if(choise3=="b"||choise3=="B"){
                    goto AdminMainMenu;
                }
                }
            case 4:
                {ReUsername:
                cout<<"enter the username: "<<endl;
                getline(cin,StoreUserName);
                for(unsigned int i=0;i<admins.size();i++){
                    if(admins[i]==StoreUserName){     //check if this username is used or not
                        cout<<"this username already exists please add a new username"<<endl;
                        goto ReUsername;
                    }
                }
                for(unsigned int i=0;i<players.size();i++){
                    if(players[i]==StoreUserName){     //check if this username is used or not
                        cout<<"this username already exists please add a new username"<<endl;
                        goto ReUsername;
                    }
                }
                cout<<"enter the password: "<<endl;
                getline(cin,Storepassword);
                cout<<"enter the first name: "<<endl;
                getline(cin,StoreFirstName);
                cout<<"enter the last name: "<<endl;
                getline(cin,StoreLastName);
                ReRole:
                cout<<"enter the role: "<<endl;
                getline(cin,StoreRoleType);
                if(StoreRoleType!="admin"&&StoreRoleType!="player"){
                    cout<<"you must choose from these options [admin/player]"<<endl;
                    goto ReRole;
                }
                if(StoreRoleType=="admin"){
                    StoreAdmin.SetValuesAdmin(StoreUserName,Storepassword,StoreFirstName,StoreLastName,StoreRoleType);
                    admins.push_back(StoreAdmin);
                }
                if(StoreRoleType=="player"){
                    StorePlayer.SetValuesPlayer(StoreUserName,Storepassword,StoreFirstName,StoreLastName,StoreRoleType);
                    players.push_back(StorePlayer);
                }
                goto AdminMainMenu;}
            case 5:
                {if(NumberOfQuestions<1){
                cout<<"there is no questions to show!"<<endl;
                goto AdminMainMenu;
                }
                //another way
                /*if(MCQuestions.size()==0||&&CQuestions.size()==0&&TFQuestions.size()==0){
                cout<<"there is no questions to show!"<<endl;
                goto AdminMainMenu;
                }*/
                ReDisplay:
                cout<<"Number of questions available: "<<(MCQuestions.size()+CQuestions.size()+TFQuestions.size())<<endl;
                cout<<"--------------------"<<endl;
                cout<<"MC Questions list (Total: "<<MCQuestions.size()<<" Questions)"<<endl;
                cout<<"--------------------"<<endl;
                for(unsigned int i=0;i<MCQuestions.size();i++){
                    cout<<"["<<i+1<<"]"<<MCQuestions[i]<<endl;
                }
                cout<<"--------------------"<<endl;
                cout<<"TF Questions list (Total: "<<TFQuestions.size()<<" Questions)"<<endl;
                cout<<"--------------------"<<endl;
                for(unsigned int i=0;i<TFQuestions.size();i++){
                    cout<<"["<<i+1<<"]"<<TFQuestions[i]<<endl;
                }
                cout<<"--------------------"<<endl;
                cout<<"Complete Questions list (Total: "<<CQuestions.size()<<" Questions)"<<endl;
                cout<<"--------------------"<<endl;
                for(unsigned int i=0;i<CQuestions.size();i++){
                    cout<<"["<<i+1<<"]"<<CQuestions[i]<<endl;
                }
                cout<<"--------------------"<<endl;
                cout<<"Press [d] if you want to delete a question"<<endl;
                cout<<"Press [b] if you want to go back to the main menu"<<endl;
                string UserChoise,DeleteIdStr;
                int DeleteId;
                ReTakeCoise:       //take the input again
                getline(cin,UserChoise);
                if(UserChoise=="b"||UserChoise=="B")goto AdminMainMenu;
                if(UserChoise=="d"||UserChoise=="D"){
                    ReId:
                    cout<<"enter the id of the question you want to delete"<<endl;
                    getline(cin,DeleteIdStr);
                    if(isdigit(DeleteIdStr[0])==false){     //check if the input is integer
                    cout<<"invalid input!"<<endl;
                    goto ReId;
                    }
                    DeleteId=stoi(DeleteIdStr);
                    if(DeleteId<0||DeleteId>NumberOfQuestions){    //check if the id exist
                    cout<<"this id is out of range"<<endl;
                    goto ReId;
                    }
                    //delete the question
                    for(unsigned int i=0;i<MCQuestions.size();i++){
                        if(MCQuestions[i]==DeleteId)MCQuestions.erase(MCQuestions.begin()+i);
                    }
                    for(unsigned int i=0;i<TFQuestions.size();i++){
                        if(TFQuestions[i]==DeleteId)TFQuestions.erase(TFQuestions.begin()+i);
                    }
                    for(unsigned int i=0;i<CQuestions.size();i++){
                        if(CQuestions[i]==DeleteId)CQuestions.erase(CQuestions.begin()+i);
                    }
                    goto ReDisplay;
                }
                if(UserChoise!="b"&&UserChoise!="B"&&UserChoise!="d"&&UserChoise!="D"){
                    cout<<"you must choose from these options [d/b]"<<endl;
                    goto ReTakeCoise;
                }
                }
            case 6:
                {string type;
                ReChooseType:
                cout<<"what is the type of the question you want to add? [C,TF,MCQ]"<<endl;
                getline(cin,type);
                if(type!="C"&&type!="TF"&&type!="MCQ"){
                    cout<<"you must write your answer in capital letters and choose from these options [C,TF,MCQ]"<<endl;
                    goto ReChooseType;
                }
                if(type=="C"){
                      CQuestion::AddQuestion(CQuestions);
                }
                if(type=="TF"){
                    TFQuestion::AddQuestion(TFQuestions);
                }
                if(type=="MCQ"){
                    MCQuestion::AddQuestion(MCQuestions);
                }
                goto AdminMainMenu;}
            case 7:
                {ifstream file;
                string FileName;
                bool check=true;
                //check if the file is opened or not
                while(check){
                check=false;
                cout<<"inter the file name  (add .txt at the end of the name)"<<endl;
                getline(cin,FileName);
                file.open(FileName.c_str());
                if(!file) {
                cout << "Cannot open input file please write the correct file name.\n";
                check=true;
                }
                }
                string QuestionType ;
                while(true){
                    getline(file,QuestionType);
                if(QuestionType=="MCQ")
                    MCQuestion::readQuestionFromFile(MCQuestions,file);

                if(QuestionType=="TF")
                    TFQuestion::readQuestionFromFile(TFQuestions,file);

                if(QuestionType=="COMPLETE")
                    CQuestion::readQuestionFromFile(CQuestions,file);

                if(QuestionType!="MCQ"&&QuestionType!="TF"&&QuestionType!="COMPLETE"){
                    cout<<"sorry this type of questions is not supported!"<<endl;
                    file.close();
                    goto AdminMainMenu;
                    }

                    if(file.eof())break; //check if the file ends or not
                }
                file.close();
                goto AdminMainMenu;}
            case 8:
               {exit(1);}
            default:
                cout<<"you must choose from these options [1,2,3,4,5,6,7,8]"<<endl;
                goto AdminMainMenu;
                break;
            }

    }
   if(PresentUserRule=="player"){
        PlayerMainMenu:
        players[PresentUserId].WelcomePlayer();
        cout<<"[1] Switch accounts"<<endl;
        cout<<"[2] Update your name"<<endl;
        cout<<"[3] Start a new quiz"<<endl;
        cout<<"[4] Display your scores statistics"<<endl;
        cout<<"[5] Display all your scores"<<endl;
        cout<<"[6] Display details of your last 2 quizzes"<<endl;
        cout<<"[7] Exit the program"<<endl;
        getline(cin,UserChoiseStr);
        if(isdigit(UserChoiseStr[0])==false){   //check if the input is integer or not
            cout<<"invalid input!"<<endl;
            goto PlayerMainMenu;
        }
        UserChoiseInt=stoi(UserChoiseStr);
        switch(UserChoiseInt){
            case 1:{
                goto ReStart;
                break;}
            case 2:
                {string first,last;
                cout<<"enter the new first name: "<<endl;
                getline(cin,first);
                cout<<"enter the new last name: "<<endl;
                getline(cin,last);
                players[PresentUserId].UpdateName(first,last);
                goto PlayerMainMenu;}
            case 3:{
                //check if the user have taken 2 quizzes or not
                if(MCQuestions.size()<1||CQuestions.size()<2||TFQuestions.size()<2){
                cout<<"there is no enough questions to start quiz! please add more questions"<<endl;
                goto PlayerMainMenu;
                }
                players[PresentUserId].SetQuizInfo(NumberOfQuizzes); //give the user the id of the quiz
                NumberOfQuizzes++;
                StoreQuiz.start(MCQuestions,CQuestions,TFQuestions);
                quizzes.push_back(StoreQuiz);
                goto PlayerMainMenu;
                }
            case 4:{
                string ScopeChoise;
                players[PresentUserId].DisplayScoreStat(quizzes);
                ReScopeChoise:
                cout<<"Press [b] if you want to go back to the main menu or [e] to exit"<<endl;
                getline(cin,ScopeChoise);
                if(ScopeChoise!="b"&&ScopeChoise!="B"&&ScopeChoise!="e"&&ScopeChoise!="E"){
                    cout<<"you must choose from these options [b/e]"<<endl;
                    goto ReScopeChoise;
                }
                if(ScopeChoise=="b"||ScopeChoise=="B"){
                    goto PlayerMainMenu;
                }
                if(ScopeChoise=="e"||ScopeChoise=="E"){
                    exit(1);
                }
                goto PlayerMainMenu;}
            case 5:{
                players[PresentUserId].DisplayAllScores(quizzes);
                goto PlayerMainMenu;}
            case 6:{
                players[PresentUserId].DisplayLast2(quizzes);
                goto PlayerMainMenu;}
            case 7:{exit(1);}
            default:{
                cout<<"you must choose from these options [1,2,3,4,5,6,7]"<<endl;
                goto PlayerMainMenu;
            }
        }
    }
    return 0;
}
