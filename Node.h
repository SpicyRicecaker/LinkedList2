#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
//#include <String.h> Don't need this | Andy Li
#include "Student.h"

//Node Header

//using namespace std; Uneeded | Andy Li

class Node{
public:
  Node(Student*); //Initialize funcitons and variables
  ~Node();
  void setStudent(Student* newstudent);
  Student* getStudent();
  void setNext(Node* newnext);
  Node* getNext();
private:
  Student* student;
  Node* next;
};
#endif
