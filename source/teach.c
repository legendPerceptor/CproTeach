//
// Created by heisi on 3/20/17.
//


#include "teach.h"

 courseDB ReadDataBase(void) {
    FILE *infile;
    courseDB course;

    infile = OpenUserFile("Enter name of course: ", "r");
    course = New(courseDB);
    course->title = ReadLine(infile);
    while (ReadOneQuestion(infile, course));
    fclose(infile);
    return course;
}

 bool ReadOneQuestion(FILE *infile, courseDB course) {
    questionT question;
    string line;
    int qnum;

    line = ReadLine(infile);
    if (line == NULL || StringLength(line)==0){
        //printf("reading finished\n");
        return false;}
    qnum = StringToInteger(line);
    if (qnum < 1 || qnum > MaxQuestions) {
        Error("Question number %d out of range", qnum);
    }
    question = New(questionT);
    ReadQuestionText(infile, question);
    ReadAnswers(infile, question);
    course->questions[qnum] = question;
    return true;
}

 void ReadQuestionText(FILE *infile, questionT q) {
    string line;
    int nlines;

    nlines = 0;
    while (true) {
        line = ReadLine(infile);
        //printf("%s\n",line);
        if (StringEqual(line, EndMarker))break;
        if (nlines >= MaxLinesPerQuestion) {
            Error("Too many lines");
        }
        q->qtext[nlines] = line;
        nlines++;
    }
    q->qtext[nlines] = NULL;

}

 void ReadAnswers(FILE *infile, questionT q) {
    string line, ans;
    int cpos, nextq, nAnswers;
    size_t len;
    nAnswers = 0;
    while ((line = ReadLine(infile)) != NULL && (len = StringLength(line)) != 0) {
        cpos = FindChar(':', line, 0);
        if (cpos == -1)Error("Illegal answer format");
        ans = SubString(line, 0, (size_t) cpos - 1);
        nextq = StringToInteger(SubString(line, (size_t) cpos + 1, len - 1));
        q->answers[nAnswers].ans = ConvertToUpperCase(ans);
        q->answers[nAnswers].nextq = nextq;
       // printf("%s,%d\n",ans,nextq);
        nAnswers++;
    }
    q->nAnswer = nAnswers;
}

 FILE *OpenUserFile(string prompt, string mode) {
    string filename;
    FILE *result;

    while(true){
        printf("%s", prompt);
        filename= GetLine();
        result=fopen(filename,mode);
        if(result!=NULL)break;
        printf("Can't open the file \"%s\"\n",filename);

    }
    return result;
}

 void ProcessCourse(courseDB course){
    questionT q;
    int qnum;
    string ans;
    int index;
    printf("%s\n", course->title);
    qnum=1;
    int flag=0;
    while(qnum!=0){
        q=course->questions[qnum];
        AskQuestion(q,flag);
        ans=ConvertToUpperCase(GetLine());
        index=FindAnswer(ans,q);
        if(index==-1){
            printf("I don't understand that.\n");
            flag=1;
        }else{
            qnum=q->answers[index].nextq;
            flag=0;
        }
    }
    printf("Thank you for using\n");
    printf("-------programmed by heisi-------\n");
}

 void AskQuestion(questionT q,int flag){
    int cpos=-1,dpos=-1;
    for(int i=0;q->qtext[i]!=NULL;i++){
       if(flag){
            cpos=FindChar(':',q->qtext[i],0);
            dpos=FindChar('?',q->qtext[i],0);
            if(cpos==-1&&dpos==-1)continue;
        }
        printf("%s\n",q->qtext[i]);
    }
}

 int FindAnswer(string ans, questionT q){

    for(int i=0;i<q->nAnswer;i++){
        if(StringEqual(ans,q->answers[i].ans))return i;
    }
    return -1;
}

