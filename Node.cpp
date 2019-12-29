#include <iostream>
#include <cstring>
//#include <String.h> don't need this lol
#include "Node.h"
#include "Student.h"

//Node class

using namespace std;

Node::Node(Student* newstudent) { //New student
  student = newstudent;
  next = NULL;
}

Node::~Node() { //Delete student
  delete student; //ONE CHANGE!!!
  student = NULL;
}

void Node::setStudent(Student* newstudent) { //Set student
  student = newstudent;
}

Student* Node::getStudent() { //Get student
  return student;
}

Node* Node::getNext() { //Get next node
  return next;
}

void Node::setNext(Node* newnext){ //Sets the next node
  next = newnext;
}


