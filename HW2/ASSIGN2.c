//Created by Aaron Zhang

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct person
{
    struct person* father;
    struct person* mother;
    struct person* child;
    char* name;
}person;

struct person* createRootNode();
void initializeNode(person ** node);
struct person* createPerson(char *name);
void beginFamilyTreeInput(person *root);
void receiveLineOfInputSTDIN(char* userInp, int length);
void addRelation(person *root);
struct person *search(char *name, person *root);
int print(struct person *root, int tabNumber);
void deleteHandler(person* root);
int delete(person* root);
int main(int argc, const char * argv[]){
    struct person* rootPerson = createRootNode();
    beginFamilyTreeInput(rootPerson);
}

int delete(person* root){
    //Check if child pointer exists
    if(root->child!=NULL){
        person* child = root->child;
        if(child->mother!=NULL && child->father!=NULL){
            if(strcmp(child->mother->name,root->name)==0){
                //Mother of child
                child->mother=NULL;
                root->child=NULL;
            }else if(strcmp(child->father->name,root->name)==0){
                //Father of child
                child->father=NULL;
                root->child=NULL;
            }
        }else if(child->mother!=NULL){
            child->mother=NULL;
        }else if(child->father!=NULL){
            child->father=NULL;
        }
    }
    //Get parents
    person* mother = root->mother;
    person* father = root->father;
    free(root);
    if(mother!=NULL && father!=NULL){
        //Leaf
        mother->child=NULL;
        father->child=NULL;
        delete(mother);
        delete(father);
    }else if(father!=NULL){
        //Father is null
        father->child=NULL;
        delete(father);
    }else if(mother!=NULL){
        //Mother is
        mother->child=NULL;
        delete(mother);
    }
    return 1;
}

void deleteHandler(person* root){
    printf("Please specify the name to delete\n");
    //Take input of user
    char *userInpName = malloc(sizeof(char)*33);
    receiveLineOfInputSTDIN(userInpName,33);
    //Search for node to delete
    person* nodeToDelete = search(userInpName, root);
    if(nodeToDelete==NULL){
        //Node was not found
        printf("Person not found\n");
    }else{
        delete(nodeToDelete);
    }
    free(userInpName);
}
int print(struct person* root, int tabNumber){
    if(root!=NULL){
        for(int i = 0;i<tabNumber;i++){
            printf("\t");
        }
        printf("%s\n",root->name);
    }
    if(root->father!=NULL){
        print(root->father,++tabNumber);
    }else{
        return 0;
    }
    if(root->mother!=NULL){
        if(tabNumber==0){
            print(root->mother,++tabNumber);
        }else{
            print(root->mother,tabNumber--);
        }
    }else{
        return 0;
    }
    return 0;
}
void beginFamilyTreeInput(struct person* root){
    while(1){
        printf("Please specify whether to add or delete an entry, or print the tree\n");
        char *userInput = malloc(sizeof(char)*8);
        receiveLineOfInputSTDIN(userInput,8);
        if(strcmp(userInput,"add")==0){
            addRelation(root);
        }else if(strcmp(userInput,"delete")==0){
            deleteHandler(root);
        }else if(strcmp(userInput,"print")==0){
            printf("\n");
            print(root,0);
        }else if(strcmp(userInput,"quit")==0){
            printf("Program Terminating\n");
            delete(root);
            exit(0);
        }else{
            //Invalid input
            fprintf(stderr,"Invalid Input, Valid commands: add, delete, print, and quit.\n");
        }
        free(userInput);
    }
}

void addRelation(struct person* root){
    printf("Please specify a relation to add\n");
    //User input
    char* userInput = malloc(sizeof(char)*65);
    receiveLineOfInputSTDIN(userInput,65);
    //Check if the user wants to quit
    if(strcmp(userInput,"quit")==0){
        printf("Program Terminating\n");
        exit(0);
    }
    //Parse input
    char* relation = strtok(userInput,"(");
    //Allocate for parent name
    char* parent = strtok(NULL,",");
    char* mallocParent = malloc(strlen(parent)*sizeof(char)+1);
    strcpy(mallocParent,parent);
    char* child = strtok(NULL,"");
    child[strlen(child)-1] = 0;
    
    //Get node of child
    person* childNode = search(child, root);
    if(childNode==NULL){
        //Node was not found
        printf("Person not found\n");
    }else{
        //Node found
        //Determine if mother or father
        if(strcmp(relation,"father")==0){
            //Check if node has a father
            if(childNode->father==NULL){
                //Create parent node
                person* parentNode = createPerson(mallocParent);
                childNode->father=parentNode;
                childNode->father->child = childNode;
            }else{
                //Already has a father
                printf("Already has a father\n");
            }
        }else if(strcmp(relation,"mother")==0){
            //Check if node has a mother
            if(childNode->mother==NULL){
                //Create parent node
                person* parentNode = createPerson(mallocParent);
                childNode->mother=parentNode;
                childNode->mother->child = childNode;
            }else{
                //Already has a mother
                printf("Already has a mother\n");
            }
        }else{
            //error
            printf("Error with adding");
        }
    }
    free(userInput);
}

struct person* search(char *name, struct person* root){
    //Given a name returns the node if found or null if not
    if(strcmp(root->name,name)==0){
        //found
        return root;
    }else{
        if(root->mother!=NULL){
            //printf("Searching for mother %s,%s\n",root->name,root->mother->name);
            person* temp = search(name,root->mother);
            if(temp!=NULL){
                return temp;
            }
        }
        if(root->father!=NULL){
            //printf("Searching for father");
            person* tempF = search(name,root->father);
            if(tempF!=NULL){
                return tempF;
            }
        }
    }
    return NULL;
}

void receiveLineOfInputSTDIN(char* userInp, int length){
    //receives a line of user input of a given length
    //char *userInp = malloc(sizeof(char)*length);
    if(fgets(userInp,length,stdin)==NULL){
        fprintf(stderr,"Error with receiving user input.");
    }
    //strip newline
    userInp[strlen(userInp)-1] = 0;
}

struct person* createRootNode(){
    //Name take in user input from stdin
    printf("Please enter your name:");
    char *userInpFamilyName = malloc(sizeof(char)*33);
    receiveLineOfInputSTDIN(userInpFamilyName,33);
    return createPerson(userInpFamilyName);
}

struct person* createPerson(char *name){
    //allocate space for a person, set its respective values
    person *nodePerson =  malloc(sizeof(person));
    initializeNode(&nodePerson);
    nodePerson->name = name;
    return nodePerson;
}

void initializeNode(person ** node){
    //set all values of person to null
    (*node)->name = NULL;
    (*node)->father = NULL;
    (*node)->mother = NULL;
    (*node)->child = NULL;
}
