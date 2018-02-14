//Created by Aaron Zhang

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char * father;
    char * mother;
    char * name;
}person;

person* createRootNode();
void initializeNode(person ** node);
person* createPerson(char *name, char *mother, char *father);
void beginFamilyTreeInput();
char *receiveLineOfInputSTDIN(int length);

int main(int argc, const char * argv[]){
    person* rootPerson = createRootNode();
    beginFamilyTreeInput();
}

void beginFamilyTreeInput(){
    while(1){
        printf("Please specify whether to add or delete an entry, or print the tree\n");
        char *userInput = receiveLineOfInputSTDIN(8);
        printf("%s\n",userInput);
        if(strcmp(userInput,"add")==0){
            printf("add");
        }else if(strcmp(userInput,"delete")==0){
            printf("delete");
        }else if(strcmp(userInput,"print")==0){
            printf("print");
        }else if(strcmp(userInput,"quit")==0){
            printf("Program Terminating\n");
            exit(0);
        }else{
            //Invalid input
            fprintf(stderr,"Invalid Input, Valid commands: add, delete, print, and quit.");
        }
    }
}

char *receiveLineOfInputSTDIN(int length){
    //receives a line of user input of a given length
    char *userInp = malloc(sizeof(char)*length);
    if(fgets(userInp,length,stdin)==NULL){
        fprintf(stderr,"Error with receiving user input.");
    }
    //strip newline
    userInp[strlen(userInp)-1] = 0;
    return userInp;
}

person* createRootNode(){
    //Name take in user input from stdin
    printf("Please enter your name:");
    char *userInpFamilyName = receiveLineOfInputSTDIN(33);
    return createPerson(userInpFamilyName,NULL,NULL);
}

person* createPerson(char *name, char *mother, char *father){
    //allocate space for a person, set its respective values
    person *nodePerson =  malloc(sizeof(person));
    initializeNode(&nodePerson);
    nodePerson->name = name;
    nodePerson->mother = mother;
    nodePerson->father = father;
    return nodePerson;
}

void initializeNode(person ** node){
    //set all values of person to null
    (*node)->name = NULL;
    (*node)->father = NULL;
    (*node)->mother = NULL;
}
