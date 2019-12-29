#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

//Try more ethical coding, like char pointer for return state in get input
void getInput(char*&);
void doCommand(char*, Node**);
void addStudent(Node**);
void addNode(Node**, Node**, Student*);
void print(Node**, Node**);
void del(Node**, Node**, int, int);
void help();
void average(Node**, Node**);
void quit();

int main(){

  Node* head = NULL;
  Node** headptr = &head;

  bool running = true;

  char in[99];
  char* input = &in[0];

  while(running){
    cout << "Please enter a command." << endl;
    getInput(input);
    doCommand(input, headptr);
  }
  //Add
  //Print
  //Delete
  return 0;
}

void getInput(char* (&in)){
  char tempIn[99];
  while(true){
    cin.get(tempIn, 99);
    cin.clear();
    cin.ignore(999, '\n');

    for(int a = 0; a < strlen(tempIn); ++a){
      tempIn[a] = toupper(tempIn[a]);
    }

    if(strlen(tempIn) != 0){
      strcpy(in, (char*)tempIn);
      return;
    }
    cout << "\nNo input detected..." << endl;
  }
}

void doCommand(char* input, Node** headptr){
  if(strcmp("ADD", input) == 0){
    addStudent(headptr);
  }else if(strcmp(input, "PRINT") == 0){
    print(headptr, headptr);
  }else if(strcmp(input, "DELETE") == 0){
    cout << "Please enter an id..." << endl;
    //store to inId after debut
    char tmp[99];
    char* temp = &tmp[0];
    getInput(temp);
    int inId = atoi(temp);
    del(headptr, headptr, inId, 0);
  }else if(strcmp("AVERAGE", input) == 0){
    average(headptr, headptr);
  }else if(strcmp("QUIT", input) == 0){
    quit(); 
  }else{
    cout << "\nInvalid command.\n" << endl;
    help();
  }
}

void addStudent(Node** headptr){
  char fNm[99];
  char lNm[99];
  int id = 0;
  int* idptr = &id;
  float gpa = 0;
  float* gpaptr = &gpa;

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

  addNode(headptr, headptr, new Student((char*)fNm, (char*)lNm, idptr, gpaptr));
}

void addNode(Node** currentptr, Node** headptr, Student* newStudent){
  if((*currentptr) == NULL){
    (*currentptr) = new Node(newStudent);
    return;
  }
  //We have to check if it is less than the head first
  //Then we compare our newStudent to the student of the next node
  //If it is in fact less than that, we bind current next to a new temp node, then that to the next node
  //Then, if we get to a point where the next is actually NULL, we can straight up connect our current to the next node.
  //Think of a slinky, it starts slow with the head, then progresses to regular movement, then stalls again at the end
  if((*currentptr)==(*headptr)){
    if(*(newStudent->getId()) < *((*currentptr)->getStudent()->getId())){
      Node* temp = new Node(newStudent);
      temp->setNext((*headptr));
      *headptr = temp;
      return;
    }
  }
  if((*currentptr)->getNext() != NULL){
    if(*(newStudent->getId()) < *((*currentptr)->getNext()->getStudent()->getId())){
      Node* nextNext = (*currentptr)->getNext();
      (*currentptr)->setNext(new Node(newStudent));
      (*currentptr)->getNext()->setNext(nextNext);
      return;
    }
    Node* next = (*currentptr)->getNext();
    addNode(&next, headptr, newStudent);
  }else{
    (*currentptr)->setNext(new Node(newStudent));
  }
}

void del(Node** currentptr, Node** headptr, int inId, int removed){
  if((*headptr) == NULL){
    cout << "Empty list!" << endl;
    return;
  }
  if((*currentptr)==(*headptr)){
    if(*((*headptr)->getStudent()->getId()) == inId){
      if((*headptr)->getNext() != NULL){
        Node* temp = (*headptr)->getNext();
        delete (*headptr);
        (*headptr) = temp;
        (*currentptr) = temp;
        ++removed;
        del(headptr, headptr, inId, removed);
      }else{
        delete (*headptr);
        (*headptr) = NULL;
        ++removed;
      }
    }
  }
  //We want to see if the next node should be deleted
  //If it should be, we need to see if it is connected to a next next node
  //If it is, we store the next next node, delete the next node, and link the current node to the next next node
  //If it isn't, we can straight up just delete the next node, and return
  if(*currentptr != NULL){
    Node* next;
    if((next = (*currentptr)->getNext()) != NULL){
      if(*((*currentptr)->getNext()->getStudent()->getId()) != inId){
        del(&next, headptr, inId, removed);
      }else{
        if(next->getNext() != NULL){
          Node* nextNext = (next->getNext());
          delete next;
          (*currentptr)->setNext(nextNext);
          ++removed;
          del(currentptr, headptr, inId, removed);
        }else{
          delete (*currentptr)->getNext();
          (*currentptr)->setNext(NULL);
          ++removed;
          del(headptr, headptr, inId, removed);
        }
      }
    }
  }
}


void print(Node** currentptr, Node** headptr){
  if((*currentptr) == (*headptr)){
    cout << "List: " << endl;
  }
  if((*currentptr) != NULL){
    Student* s = (*currentptr)->getStudent();
    cout << s->getFNm() << ", " << s->getLNm() << ", " << *(s->getId()) << ", " << *(s->getGpa()) << endl;
    Node* n;
    if((n = (*currentptr)->getNext()) != NULL){
      print(&n, headptr);
    }
  }
}

void help(){
  cout << "Type \"add\" to add a student. Type \"print\" to print out a list of all students. Type \"delete\" to delete a student from the list by id.\n" << endl;
}

void average(Node** headptr, Node** currentptr){
  
}

void quit(){
  exit(0);
}

