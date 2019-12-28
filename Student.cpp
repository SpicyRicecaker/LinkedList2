#include <iostream>
#include <cstring>
#include "Student.h"
#include "Node.h"

Student::Student(char newFNm[99], char newLNm[99], int newId, float newGpa){
  //Have to string copy since we're passing this in from a function
  fNm = (char*) newFNm;
  lNm = (char*) newLNm;
  id = &newId;
  std::cout << (*id) << std::endl;
  gpa = &newGpa;
  std::cout << (*gpa) << std::endl;
}

Student::~Student(){
  delete fNm;
  delete lNm;
  delete id;
  delete gpa;
}

Student* Student::getStudent(){
  return this;
}

char* Student::getFNm(){
  return fNm;
}

char* Student::getLNm(){
  return lNm;
}

int* Student::getId(){
  return id;
}

float* Student::getGpa(){
  return gpa;
}
