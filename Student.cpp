#include <iostream>
#include <cstring>
#include "Student.h"
#include "Node.h"

Student::Student(char* newFNm, char* newLNm, int* newId, float* newGpa){
  //Have to string copy since we're passing this in from a function
  fNm = new char[strlen(newFNm)];
  strcpy(fNm, newFNm);
  lNm = new char[strlen(newLNm)];
  strcpy(lNm, newLNm);
  id = new int (*newId);
  gpa = new float (*newGpa);
}

Student::~Student(){
  delete[] fNm;
  fNm = NULL;
  delete[] lNm;
  lNm = NULL;
  delete id;
  id = NULL;
  delete gpa;
  gpa = NULL;
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
