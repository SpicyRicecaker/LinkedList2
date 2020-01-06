/*
  Author: Andy Li
  Project: Linked List Part II
  Date: 12/28/2019
  Description: Linked List Part II is a program that mimics the earlier student list, including the add, print, delete, and quit functions, in addition to a new average function. These functions allow the user to input a new student with first name, last name, id, and gpa, delete all students in the list by id, print all students, and even find the average of all of the students' gpa, all without the use of vectors.
*/


#include <iostream>
#include <cstring>
#include "Node.h"
#include "Student.h"

using namespace std;

void getInput(char*&);
void doCommand(char*, Node**, bool*);
void addStudent(Node**);
void addNode(Node**, Node**, Student*);
void print(Node**, Node**);
void del(Node**, Node**, int);
void help();
void average(Node**, Node**, float, int);
int listLength(Node**, Node**, int);
void quit(bool*);
int charToInt(char*);

//Main function for Linked List Part 2. Basically continuously gets user input and executes commands until the quit function is accessed.
int main(){

  //Setting float output to nearest two decimal places
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  //Init of head of the list, along with a pointer to it so it can be modified from other funcs
  Node* head = NULL;
  Node** headptr = &head;

  //Running, and a pointer to be accessed by the quit function
  bool running = true;
  bool* runningptr = &running;

  //Input, to be passed into get input
  char in[99];
  char* input = &in[0];

  //Main loop of the program
  while(running){
    //Prompt user for command
    cout << "Please enter a command." << endl;
    //Get command
    getInput(input);
    //Do command based off of input
    doCommand(input, headptr, runningptr);
  }
  return 0;
}

//The get input function takes in a char pointer to an array of characters and references that, then gets the userin and modifies the passed in char pointer
void getInput(char* (&in)){
  char tempIn[99];
  while(true){
    cin.get(tempIn, 99);
    cin.clear();
    cin.ignore(999, '\n');
    int inputLength = strlen(tempIn);

    for(int a = 0; a < inputLength; ++a){
      tempIn[a] = toupper(tempIn[a]);
    }

    if(strlen(tempIn) != 0){
      strcpy(in, (char*)tempIn);
      return;
    }
    cout << "\nNo input detected..." << endl;
  }
}

//Takes in the input and decides if a command can be run
void doCommand(char* input, Node** headptr, bool* runningptr){
  if(strcmp("ADD", input) == 0){
    addStudent(headptr);
  }else if(strcmp(input, "PRINT") == 0){
    print(headptr, headptr);
  }else if(strcmp(input, "DELETE") == 0){
    //A count of the current length of list so we can display how many students are removed later
    int oldLength = listLength(headptr, headptr, 0);
    //If delete, we need to prompt and get the id from the user
    cout << "Please enter an id..." << endl;
    char tmp[99];
    char* temp = &tmp[0];
    getInput(temp);
    //atoi to convert from char array to integer
    int inId = charToInt(temp);
    //Then delete!
    del(headptr, headptr, inId);
    cout << "Successfully removed *" << oldLength - listLength(headptr, headptr, 0) << "* student(s)." << endl;
  }else if(strcmp("AVERAGE", input) == 0){
    average(headptr, headptr, 0, 0);
  }else if(strcmp("QUIT", input) == 0){
    quit(runningptr); 
  }else{
    cout << "\nInvalid command.\n" << endl;
    help();
  }
}

//The add student prompts the user for the first name, last name, id, and gpa of a student, and runs the addNode() function to add this new student to the list
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
  /* Scrapped in favor of setf
  int temp = (int)(gpa * 100 + .5);
  gpa = (float)(temp) / 100;
  */
  
  addNode(headptr, headptr, new Student((char*)fNm, (char*)lNm, idptr, gpaptr));
}

//The addnode function tries to add in the student into the list, in order of least to greatest id
void addNode(Node** currentptr, Node** headptr, Student* newStudent){
  //If the list is empty, just add the student
  if((*currentptr) == NULL){
    (*currentptr) = new Node(newStudent);
    return;
  }
  //We have to check if it is less than the head first
  //Then we compare our newStudent to the student of the next node
  //If it is in fact less than that, we bind current next to a new temp node, then that to the next node
  //Then, if we get to a point where the next is actually NULL, we can straight up connect our current to the next node.
  //Think of a slinky, it starts slow with the head, then progresses to regular movement, then stalls again at the end
  //LOL??

  //If we're comparing the student with the beginning of the list
  if((*currentptr)==(*headptr)){
    //And if it is actually less than that of the head
    if(*(newStudent->getId()) < *((*currentptr)->getStudent()->getId())){
      //Make a new node that points to the old head, then set the new node to the head
      Node* temp = new Node(newStudent);
      temp->setNext((*headptr));
      *headptr = temp;
      return;
    }
  }
  //If there's another student
  if((*currentptr)->getNext() != NULL){
    //If it is actually less than that student
    if(*(newStudent->getId()) < *((*currentptr)->getNext()->getStudent()->getId())){
      //Store the next student, point the current node to a new node, then point the new node to the (now) next next student
      Node* nextNext = (*currentptr)->getNext();
      (*currentptr)->setNext(new Node(newStudent));
      (*currentptr)->getNext()->setNext(nextNext);
      return;
    }
    //Otherwise move onto the next student and recurse
    Node* next = (*currentptr)->getNext();
    addNode(&next, headptr, newStudent);
  }else{
    //Otherwise, if we've reached the end of the list without finding a bigger id, just add that to the end of the list
    (*currentptr)->setNext(new Node(newStudent));
  }
}

//The del() function tries to get rid of students based off of the user inputted id
void del(Node** currentptr, Node** headptr, int inId){
  //Make sure that the list is not empty
  if((*headptr) == NULL){
    cout << "Empty list!" << endl;
    return;
  }
  //CHANGE: removed counter removed in favor of a listLength() function to calculate students removed
  //If we're looking at the beginning of the list
  if((*currentptr)==(*headptr)){
    //If we should delete the head
    if(*((*headptr)->getStudent()->getId()) == inId){
      //Check if there is anything connected to the head. If yes,
      if((*headptr)->getNext() != NULL){
        //Remember the node connected to the head
        Node* temp = (*headptr)->getNext();
        //Get rid of the head
        delete (*headptr);
        //Set the current and head to the node before the head
        (*headptr) = temp;
        (*currentptr) = temp;
        //Increment amount of students removed and recurse
        del(headptr, headptr, inId);
        //Otherwise, make the list empty
      }else{
        delete (*headptr);
        (*headptr) = NULL;
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
        del(&next, headptr, inId);
      }else{
        if(next->getNext() != NULL){
          Node* nextNext = (next->getNext());
          delete next;
          (*currentptr)->setNext(nextNext);
          del(currentptr, headptr, inId);
        }else{
          delete (*currentptr)->getNext();
          (*currentptr)->setNext(NULL);
          del(headptr, headptr, inId);
        }
      }
    }
  }
}

//Print function prints the entire list
void print(Node** currentptr, Node** headptr){
  //If we're at the head, give an indication
  if((*currentptr) == (*headptr)){
    cout << "List: " << endl;
  }
  //As long as the current does not equal null
  if((*currentptr) != NULL){
    //Print out current node
    Student* s = (*currentptr)->getStudent();
    cout << s->getFNm() << ", " << s->getLNm() << ", " << *(s->getId()) << ", " << *(s->getGpa()) << endl;
    Node* n;
    //Recurse if there are more students
    if((n = (*currentptr)->getNext()) != NULL){
      print(&n, headptr);
    }
  }
}

//Prints list of commands
void help(){
  cout << "Type \"add\" to add a student.\n Type \"print\" to print out a list of all students\n. Type \"delete\" to delete a student from the list by id.\n Type \"average\" for the average of the gpa of all students in the list.\n" << endl;
}

//Loops through entire list, keeping track of all the gpas, then averages them all at the end. The recursion is similar to add & delete
void average(Node** currentptr, Node** headptr, float total, int studentCount){
  if((*currentptr)==(*headptr)){
    total += *((*headptr)->getStudent()->getGpa());
    ++studentCount;
  }
  Node* n;
  if((n = (*currentptr)->getNext()) != NULL){
    total += *(n->getStudent()->getGpa());
    ++studentCount;
    average(&n, headptr, total, studentCount);
  }else{
    cout << total/studentCount << endl;
  }
}

//Loops through the list and returns the length
int listLength(Node** currentptr, Node** headptr, int studentCount){
  if((*headptr) == NULL){
    return 0;
  }
  if((*currentptr)==(*headptr)){
    ++studentCount;
  }
  Node* n;
  if((n = (*currentptr)->getNext()) != NULL){
    ++studentCount;
    return listLength(&n, headptr, studentCount);
  }else{
    return studentCount;
  }
}

//Quits by setting running to false
void quit(bool* runningptr){
  *runningptr = false; 
}

int charToInt(char* input){
  int output = 0;
  int inputLength = strlen(input);
  for(int a = 0; a < inputLength; ++a){
    output += (input[a]-'0');
    if(a == inputLength-1){
      break;
    }
    output *= 10;
  }
  return output;
}

