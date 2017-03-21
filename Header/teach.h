
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MaxQuestions 100
#define MaxLinesPerQuestion 20
#define MaxAnswerPerQuestion 10
#define EndMarker "-----"

#include "genlib.h"
#include "simpio.h"
#include "strlib.h"

typedef struct{
    string ans;
    int nextq;
}answerT;
typedef struct{
    string qtext[MaxLinesPerQuestion+1];
    answerT answers[MaxAnswerPerQuestion];
    int nAnswer;
}*questionT;

typedef struct{
    string title;
    questionT questions[MaxQuestions+1];
}*courseDB;

 courseDB ReadDataBase(void);
 bool ReadOneQuestion(FILE* infile, courseDB course);
 void ReadQuestionText(FILE* infile, questionT q);
 void ReadAnswers(FILE* infile, questionT q);
 FILE *OpenUserFile(string prompt, string mode);
 void ProcessCourse(courseDB course);
 void AskQuestion(questionT q,int flag);
 int FindAnswer(string ans, questionT q);