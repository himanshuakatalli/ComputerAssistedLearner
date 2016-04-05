#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NO_OF_QUES 10
/*********************
Structures Declaration
*********************/
typedef struct _data{
  int numA;
  int numB;
  int result;
}Data;

enum DifficultyLevel { BEGINNER, AVERAGE, ADVANCED };

/*********************
Functions Declaration
*********************/

void displayBanner();
void playGame(enum DifficultyLevel obDifficulty);
void storeResult(Data *pdatObject, char *operatorString);
char* generateQuestion(Data *pdatObject,enum DifficultyLevel obDifficulty);
int evaluateAnswer(int inputAnswer, Data *pdatObject);
int generateRandomInRange(int range);
enum DifficultyLevel askDifficulty();
int postGameSessionComplete();

/*************
Main Function
*************/
int main(){
  enum DifficultyLevel obDifficulty;
  /***************************************************
  Displays initial instructions for using the program
  ***************************************************/
  displayBanner();
  obDifficulty = askDifficulty();
  while(1) {
    playGame(obDifficulty);
    if(!postGameSessionComplete()) {
      break;
    }
  }
}

/*******************************
Function definitions starts here
*******************************/
int postGameSessionComplete() {
  size_t option;
  puts("------------------------------------------------------------------------------------------------------------------");
  puts("Your session is completed. You can find your results in report generated in the same folder as that of the program");
  puts("------------------------------------------------------------------------------------------------------------------");
  puts("If you wish to quit enter 0 else enter 1");
  x:scanf("%zu",&option);
  if(option != 0 && option != 1) {
    puts ("Wrong option given please try again ...... ");
    goto x;
  }
  else if (option == 0) return 0;
  else if (option == 1) return 1;
}

void displayBanner(){
  puts("-------------------------------------");
  puts("Welcome to the Game of Mathematics : ");
  puts("-------------------------------------");
  puts("If you wish to quit type \"Quit\" and press enter.");
  puts(" ");
}

void playGame(enum DifficultyLevel obDifficulty){
  /***********************
  Variable Declaration
  ***********************/
  Data datObject;
  size_t correctAnswerFlag, quitFlag, quesNumber;
  int result[10];
  float inputAnswer;
  char *question, *rem, inpAns[5];
  // FILE *fResult;
  // if((fResult = fopen("result.txt","w+"))) {
  //   puts ("Done");
  // } else {
  //   puts ("No");
  // }

  quesNumber = 1;

  while(quesNumber <= NO_OF_QUES){
    correctAnswerFlag = 0;
    quitFlag = 0;
    question = generateQuestion(&datObject,obDifficulty);
    // fprintf(fResult,"%s%zu %s\n","Ques - ",quesNumber,question);
    // fprintf(fResult,"%s%d\n","Correct Answer = ",datObject.result);
    printf("\n%s",question);
    while(correctAnswerFlag == 0){
      printf("%s","Ans = ");
      scanf("%4s",inpAns);
      if(strcmp(inpAns,"Quit") == 0){
        puts("Thanks for playing with us. Come back soon.");
        quitFlag = 1;
        break;
      } else {
        inputAnswer = strtod(inpAns,&rem);
        if(evaluateAnswer(inputAnswer,&datObject) == 1){
          correctAnswerFlag = 1;
        } else {
          correctAnswerFlag = 0;
        }
      }

    }
    quesNumber++;
    if(quitFlag == 1){
      break;
    }
  }
}

char* generateQuestion(Data *pdatObject, enum DifficultyLevel obDifficulty){
  char numA[2], numB[2];
  static char *question = NULL;
  int indexForQuestion, indexForOperator, lengthOfString;

  if(question != NULL){
    free(question);
    question = NULL;
  }
  char *quesOptions[2] = {"What is ","How much is "};
  char *operatorOptions[4] = {" + "," - "," * "," / "};
  indexForQuestion = generateRandomInRange(2) - 1;
  pdatObject->numA = generateRandomInRange(9);
  pdatObject->numB = generateRandomInRange(9);

  switch (obDifficulty) {
    case BEGINNER:
      operatorOptions[0] = " + ";
      operatorOptions[1] = " - ";
      indexForOperator = generateRandomInRange(2) - 1;
      break;
    case AVERAGE:
      operatorOptions[0] = " * ";
      operatorOptions[1] = " / ";
      indexForOperator = generateRandomInRange(2) - 1;
      break;
    case ADVANCED:
      indexForOperator = generateRandomInRange(4) - 1;
  }

  sprintf(numA,"%d",pdatObject->numA);
  sprintf(numB,"%d",pdatObject->numB);

  storeResult(pdatObject,operatorOptions[indexForOperator]);

  // printf("%d %s %d %f\n",pdatObject->numA,operatorOptions[indexForOperator],pdatObject->numB, pdatObject->result);

  lengthOfString = strlen(quesOptions[indexForQuestion]) + 10;
  question = (char*)malloc(lengthOfString * sizeof(char));

  strcpy(question,quesOptions[indexForQuestion]);
  strcat(question,numA);
  strcat(question,operatorOptions[indexForOperator]);
  strcat(question,numB);
  strcat(question," ?\n");

  return question;
}

int generateRandomInRange(int range){
  static int shift = 100;
  srand(time(NULL)*shift + shift++);
  int number = rand() % range + 1;
  return number;
}

void storeResult(Data *pdatObject, char *operatorString){
  if(strcmp(operatorString," + ") == 0){
    pdatObject->result = pdatObject->numA + pdatObject->numB;
  } else if(strcmp(operatorString, " - ") == 0){
    pdatObject->result = pdatObject->numA - pdatObject->numB;
  } else if(strcmp(operatorString," * ") == 0){
    pdatObject->result = pdatObject->numA * pdatObject->numB;
  } else if(strcmp(operatorString," / ") == 0){
    pdatObject->result = pdatObject->numA / pdatObject->numB;
  }
}

int evaluateAnswer(int inputAnswer, Data *pdatObject){
  char *positiveRemarks[4] = {"Very good!","Excellent!","Nice work!","Keep up the good work!"};
  char *negativeRemarks[4] = {"No. Please try again","Wrong. Try once more","Wrong. Don't give up!","No. Keep trying"};

  int indexForRemarks = generateRandomInRange(4) - 1;
  if(inputAnswer == pdatObject->result){
    puts(positiveRemarks[indexForRemarks]);
    return 1;
  } else {
    puts(negativeRemarks[indexForRemarks]);
    return 0;
  }
}

enum DifficultyLevel askDifficulty(){
  int option;
  puts("Please select a difficulty level to start with : ");
  puts("1 - BEGINNER");
  puts("2 - AVERAGE");
  puts("3 - ADVANCED");
  printf("%s","? - ");
  scanf("%d",&option);
  switch(option){
    case 1:
      return BEGINNER;
    case 2:
      return AVERAGE;
    case 3:
      return ADVANCED;
  }
}
