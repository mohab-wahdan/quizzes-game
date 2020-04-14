#include <iostream>                    //name:mohab abdul salam mohamed
#include <stdlib.h>                    //id:20180294
#include <vector>                      //group:11
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int NumberOfQuizzes=0;       //to know the number of quizzes taken

void ShowQuestions(vector<string> &questions,vector<string> &answers){
    if(questions.size()==0){
        cout<<"there is no questions to display please add more questions"<<endl;
        return;
    }
    bool repeat=true;     //to handle the wrong input
    while(repeat){
    repeat=false;
    char UserOrder;                            //to get the order from the user [delete/back].
    cout<<"Number of questions available: "<<questions.size()<<endl;
    cout<<"Questions list: \n"<<"-------------------"<<endl;
    for(unsigned int i=0;i<questions.size();i++){
        cout<<"["<<i+1<<"]"<<questions[i]<<endl;
        cout<<"     *[a]"<<answers[i*4]<<"     [b]"<<answers[i*4+1];
        cout<<"     [c]"<<answers[i*4+2]<<"     [d]"<<answers[i*4+3]<<endl<<endl;
    }
    cout<<"Press [d] if you want to delete a question "<<endl;
    cout<<"Press [b] if you want to go back to the main menu"<<endl;
    cin>>UserOrder;
    if(UserOrder!='b'&&UserOrder!='B'&&UserOrder!='d'&&UserOrder!='D'){
        cout<<"you must choose from these options [b/d]"<<endl;
        system("pause");
        repeat=true;
    }
    if(UserOrder=='b'||UserOrder=='B')return;
    if(UserOrder=='d'||UserOrder=='D'){
         unsigned int QuestionDeleteId;
        cout<<"inter the id of the question that you want to delete:  [1,2,3,...]"<<endl;
        cin>>QuestionDeleteId;
        if(QuestionDeleteId>0&&QuestionDeleteId<=questions.size()){
            QuestionDeleteId=QuestionDeleteId-1;    //to erase the right question ex:question 2 for user is 1 in vector.
            questions.erase(questions.begin()+QuestionDeleteId);
            answers.erase(answers.begin()+(QuestionDeleteId*4),answers.begin()+(QuestionDeleteId*4+4));
            repeat=true;
        }
        else cout<<"the number is out of the range."<<endl;
        system("pause");
        repeat=true;
    }

    }
}
void AddQuestions(vector<string> &questions,vector<string> &answers){
    string TakeData;                                 //to take data from user and store it in vector
    char AddMore='y';
    while(AddMore=='Y'||AddMore=='y'){
    cout<<"inter the question: "<<endl;
    cin>>TakeData;  questions.push_back(TakeData);
    cout<<"inter the correct answer: "<<endl;
    cin>>TakeData;  answers.push_back(TakeData);
    cout<<"inter the second answer: "<<endl;
    cin>>TakeData;  answers.push_back(TakeData);
    cout<<"inter the third answer: "<<endl;
    cin>>TakeData;  answers.push_back(TakeData);
    cout<<"inter the forth answer: "<<endl;
    cin>>TakeData;  answers.push_back(TakeData);
    ReChoise:        //if the user inter a wrong input he will write it again
    cout<<"do you want to add more questions?  [Y/N] :"<<endl;
    cin>>AddMore;
    if(AddMore!='Y'&&AddMore!='y'&&AddMore!='N'&&AddMore!='n'){
        cout<<"you must choose from these answers [Y/N]"<<endl;
        goto ReChoise;      //take the input again line 70
    }
    }

}
void Loadquestion(vector<string> &questions,vector<string> &answers){
    ifstream file;
    string FileName;
    bool check=true;
    while(check){
    check=false;
    cout<<"inter the file name  (add .txt at the end of the name)"<<endl;
    cin>>FileName;
    file.open(FileName.c_str());
    if(!file) {
    cout << "Cannot open input file please write the correct file name.\n";
    check=true;
    }
  }
  string TakeData ;                     //to take data from the file and store it in vector.
  int counter=0;                 //to know the number of lines in the file.
  while(getline(file,TakeData)){counter++;}
  file.close();
  file.open(FileName.c_str());
  for(int i=0;i<counter/5;i++){
  getline(file,TakeData);
  questions.push_back(TakeData);      //store the question.
  getline(file,TakeData);
  answers.push_back(TakeData);        //first and the correct answer.
  getline(file,TakeData);
  answers.push_back(TakeData);
  getline(file,TakeData);
  answers.push_back(TakeData);
  getline(file,TakeData);
  answers.push_back(TakeData);
  }
}
void UpdateName(string &name){
    cout<<"inter your name : "<<endl;
    cin>>name;

}
void StartNewQuiz(vector<string> &questions,vector<string> &answers,vector<int> &score,vector<int> &wrong,vector<int> &right){
    if(questions.size()<5){
    cout<<"the number of questions in the questions pool is not enough for the quiz please add more questions"<<endl;
    return;}                           //if there is no enough questions it will return
    srand(time(0));                  //to generate different random numbers for every run
    int QuizScore=0,RightAnswers=0,WrongAnswers=0;
	string UserQuestion;
	char UserAnswer;
	char CorrectAnswerChar;
	int QuestionTurn=0;
    int* RandomQuestionsRange = new int[questions.size()-1];
    int RandomQuestionsChosen[5];
    int RandomAnswersChosen[4] ;


    for(unsigned int i=0;i<questions.size();i++)        //fill the vector with numbers within range to shuffle between them
        RandomQuestionsRange[i]=i;

    for(int i=0;i<5;i++){                            //fill the vector with non repeated numbers
        int SelectQuestion=rand()%(questions.size()-i);
        RandomQuestionsChosen[i]=RandomQuestionsRange[SelectQuestion];
        RandomQuestionsRange[SelectQuestion]=RandomQuestionsRange[questions.size()-i-1];

    }
    delete []RandomQuestionsRange;
    int RandomAnswer;
    for(int i=0;i<5;i++){

	for(int i=0;i<4;i++){
        ReRandom:       //if the random number is repeated it will be generated again
		RandomAnswer=rand()%4+RandomQuestionsChosen[QuestionTurn]*4;
        for(int j=0;j<4;j++){
            if(RandomAnswer==RandomAnswersChosen[j])goto ReRandom;
        }
        RandomAnswersChosen[i]=RandomAnswer;
	}

        //find the correct answer
		if(answers[RandomAnswersChosen[0]]==answers[RandomQuestionsChosen[QuestionTurn]*4])CorrectAnswerChar='a';

		if(answers[RandomAnswersChosen[1]]==answers[RandomQuestionsChosen[QuestionTurn]*4])CorrectAnswerChar='b';

		if(answers[RandomAnswersChosen[2]]==answers[RandomQuestionsChosen[QuestionTurn]*4])CorrectAnswerChar='c';

		if(answers[RandomAnswersChosen[3]]==answers[RandomQuestionsChosen[QuestionTurn]*4])CorrectAnswerChar='d';



	cout<<questions[RandomQuestionsChosen[QuestionTurn]]<<endl;
	cout<<"[a]"<<answers[RandomAnswersChosen[0]]<<endl;
    cout<<"[b]"<<answers[RandomAnswersChosen[1]]<<endl;
	cout<<"[c]"<<answers[RandomAnswersChosen[2]]<<endl;
	cout<<"[d]"<<answers[RandomAnswersChosen[3]]<<endl;
	ReWriteAnswer:    //if the user write wrong input he will write it again

	cout<<"write your answer in small letter [a,b,c,d] :"<<endl;
	cin>>UserAnswer;
	if(UserAnswer!='a'&&UserAnswer!='b'&&UserAnswer!='c'&&UserAnswer!='d'){
        cout<<"you must choose from these options [a,b,c,d]"<<endl;
        goto ReWriteAnswer; //re write the answer

	}
	if(UserAnswer==CorrectAnswerChar){
		QuizScore++;
		RightAnswers++;
	}
	else WrongAnswers++;
    QuestionTurn++;
    }
	cout<<"your score is: "<<QuizScore<<"/5"<<endl;
	cout<<"the number of right answers is: "<<RightAnswers<<endl;
	cout<<"the number of wrong answers is: "<<WrongAnswers<<endl;
	NumberOfQuizzes++;
	score.push_back(QuizScore);
	right.push_back(RightAnswers);
	wrong.push_back(WrongAnswers);

}
void DisplayScoresStatics(vector<int> &score,float &average,int &heigh,int &low){
    if(score.size()==0){
        cout<<"you haven't taken any quizzes yet"<<endl;
        return;
    }
    float sum=0;
    low=score[0];
    for(unsigned int i=0;i<score.size();i++){
        if(score[i]>heigh)heigh=score[i];
        if(score[i]<low) low=score[i];
        sum+=score[i];
    }
    average=sum/NumberOfQuizzes;

}
void DisplayAllScores(vector<int> &score,vector<int> &wrong,vector<int> &right){
    if(score.size()==0){
        cout<<"you haven't taken any quizzes yet"<<endl;
        return;
    }
    cout<<"Total number of Quizzes you finished is : "<<NumberOfQuizzes<<endl;
    for(int i=0;i<NumberOfQuizzes;i++){
        cout<<"      "<<"for quiz "<<i+1<<" :"<<endl;
        cout<<"      "<<"the number of wrong answers is : "<<wrong[i]<<"/5"<<endl;
        cout<<"      "<<"the number of right answers is : "<<right[i]<<"/5"<<endl;
        cout<<"      "<<"the score is : "<<score[i]<<"/5"<<endl;
        cout<<"*****************************"<<endl;
    }


}


int main()
{
    vector<string> question,answer;
    vector<int> score,WrongAnswers,RightAnswers;
    string name="USER";
    int heighest=0,lowest=0;     //heighest score and lowest score
    float AverageScore;
    int BigSwitch,SmallSwitch;    // the big is for the main menu and the small is for admin menu

    MainMenu:
    cout<<"Welcome "<<name<<", please choose from the following options: "<<endl;
    cout<<"      "<<"[1] Go to administration menu"<<endl;
    cout<<"      "<<"[2] Update your name"<<endl;
    cout<<"      "<<"[3] Start a new quiz"<<endl;
    cout<<"      "<<"[4] Display your scores statistics"<<endl;
    cout<<"      "<<"[5] Display all your scores"<<endl;
    cout<<"      "<<"[6] Exit"<<endl;
    cin>>BigSwitch;

    switch(BigSwitch){

    case 1:
        AdminMenu:
        cout<<"Welcome to the administration menu, please choose from the following options:"<<endl;
        cout<<"      "<<"[1] View all questions"<<endl;
        cout<<"      "<<"[2] Add new question"<<endl;
        cout<<"      "<<"[3] Load questions from file"<<endl;
        cout<<"      "<<"[4] Go back to main menu"<<endl;
        cin>>SmallSwitch;
        if(SmallSwitch==1){
            ShowQuestions(question,answer);
            goto MainMenu;
            }
        if(SmallSwitch==2){
            AddQuestions(question,answer);
            goto AdminMenu;
            }
        if(SmallSwitch==3){
            Loadquestion(question,answer);
            goto AdminMenu;
            }
        if(SmallSwitch==4){
            goto MainMenu;
            }
        else{
            cout<<"invalid input you must choose from these options [1,2,3,4]"<<endl;
            goto AdminMenu;
            }
    case 2:
        UpdateName(name);
        goto MainMenu;

    case 3:
        StartNewQuiz(question,answer,score,WrongAnswers,RightAnswers);
        goto MainMenu;

    case 4:
        DisplayScoresStatics(score,AverageScore,heighest,lowest);
        if(score.size()>0){        //if there is no scores yet ignore this
        cout<<"Your score statistics:"<<endl;
        cout<<"        "<<"- Number of Quizzes taken: "<<NumberOfQuizzes<<endl;
        cout<<"        "<<"- Highest score: "<<heighest<<"/5"<<endl;
        cout<<"        "<<"- Lowest  score: "<<lowest<<"/5"<<endl;
        cout<<"        "<<"- Average  score: "<<setprecision(2)<<AverageScore<<"/5"<<endl;
        ReInter:                //if the user write wrong answer
        cout<<"Press [b] if you want to go back to the main menu or [e] to exit"<<endl;
        cout<<"my choice:" ;
        char MenuOrExit;
        cin>>MenuOrExit;
        if(MenuOrExit=='b')goto MainMenu;
        else if(MenuOrExit=='e')exit(1);
        else {
            cout<<"you must choose from these options [b,e]"<<endl;
            goto ReInter;           //go and take the input again line 289
        }
        }

        goto MainMenu;

    case 5:
        DisplayAllScores(score,WrongAnswers,RightAnswers);
        goto MainMenu;

    case 6:
        exit(1);

    default:
        cout<<"invalid input you must choose from [1,2,3,4,5,6]"<<endl;
        goto MainMenu;

        break;

    }

    return 0;
}
