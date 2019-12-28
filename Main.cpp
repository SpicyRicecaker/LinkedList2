#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

//Try more ethical coding, like char pointer for return state in get input
char* getInput();
void doCommand(char*, Node**);
void addStudent(Node**);
void addNode(Node**, Node**, Student*);
void print(Node**, Node**);
void del(Node**, Node**);
void help();

int main(){

  Node* head = NULL;
  Node** headptr = &head;

  bool running = true;

  while(running){
    cout << "Please enter a command." << endl;
    doCommand(getInput(), headptr);
  }
  //Add
  //Print
  //Delete
  return 0;
}

char* getInput(){
  char tempIn[99];
  while(true){
    cin.get(tempIn, 99);
    cin.clear();
    cin.ignore(999, '\n');

    for(int a = 0; a < strlen(tempIn); ++a){
      tempIn[a] = toupper(tempIn[a]);
    }

    if(strcmp(tempIn, "ADD") == 0 || strcmp(tempIn, "PRINT") == 0 ||  strcmp(tempIn, "DELETE") == 0){
      char* temp = (char*) tempIn;
      return temp;
      break;
    }
    help();
  }
}

void doCommand(char* input, Node** headptr){
  if(strcmp("ADD", input) == 0){
    addStudent(headptr);
  }else if(strcmp(input, "PRINT") == 0){
    print(headptr, headptr);
  }else if(strcmp(input, "DELETE") == 0){
    del(headptr, headptr);
  }
}

void addStudent(Node** headptr){
  char fNm[99];
  char lNm[99];
  int id = 0;
  float gpa = 0;

  cout << "First Name?" << endl;
  cin >> fNm;
  cin.clear();
  cin.ignore(999, '\n');
  cout << "Last Name?" << endl;
  cin >> lNm;
  cin.clear();
  cin.ignore(999, '\n');
  cout << "Id?" << endl;
  cin >> id;
  cin.clear();
  cin.ignore(999,'\n');
  cout << "Gpa?" << endl;
  cin >> gpa;
  cin.clear();
  cin.ignore(999, '\n');

  addNode(headptr, headptr, new Student(fNm, lNm, id, gpa));
}

void addNode(Node** hptr, Node** curptr, Student* newStudent){
  if((*curptr) == NULL){
    (*curptr) = new Node(newStudent);
  }
  if((*curptr)->getNext() != NULL){
    //Basically we want least to greatest.
    //If it is less than the current we can just tie it to the current
    //Otherwise we just knot it to the end
    if(*(((*curptr)->getNext())->getStudent()->getId()) < (*(*curptr)->getStudent()->getId())){
      
    }
    Node* next = (*curptr)->getNext();
    addNode(hptr, &next, newStudent);
  }
}

void del(Node** headptr, Node** currentptr){
  
}

void print(Node** headptr, Node** currentptr){
  if((*currentptr) == (*headptr)){
    cout << "List: " << endl;
  }
  if((*currentptr) != NULL){
    Student* s = (*currentptr)->getStudent();
    cout << s->getFNm() << ", " << s->getLNm() << ", " << *(s->getId()) << ", " << *(s->getGpa()) << endl;
    Node* n;
    if((n = (*currentptr)->getNext()) != NULL){
      print(headptr, &n);
    }
  }
}

void help(){
  cout << "Type \"add\" to add a student. Type \"print\" to print out a list of all students. Type \"delete\" to delete a student from the list by id." << endl;
}

