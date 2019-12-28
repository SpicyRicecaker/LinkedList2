#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <cstring>

class Student{
 public:
  Student(char[99], char[99], int, float);
  ~Student();
  Student* getStudent();
  char* getFNm();
  char* getLNm();
  int* getId();
  float* getGpa();
 private:
  char* fNm;
  char* lNm;
  int* id;
  float* gpa;
};
#endif
