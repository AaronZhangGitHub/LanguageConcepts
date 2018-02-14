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
    printf("%s",rootPerson->name);
    beginFamilyTreeInput();
}

void beginFamilyTreeInput(){
    printf("Please specify whether to add or delete an entry, or print the tree\n");
    
}

char *receiveLineOfInputSTDIN(int length){
    //receives a line of user input of a given length
    char *userInp = malloc(sizeof(char)*length);
    if(fgets(userInp,length,stdin)==NULL){
        fprintf(stderr,"Error with receiving user input.");
    }
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
