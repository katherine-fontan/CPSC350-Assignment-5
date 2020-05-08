#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(){
  major = "";
  gpa = 0.0;
  advisorID = 0;

}

Student::Student(int sID, string sName, string sLevel, string sMajor, double sGPA, int sAdvisorID){
  id = sID;
  name = sName;
  level = sLevel;
  major = sMajor;
  gpa = sGPA;
  advisorID = sAdvisorID;

}
Student::~Student(){}

string Student::getMajor(){
  return major;
}

double Student::getGPA(){
  return gpa;
}

void Student::setAdvisor(int sAdvisorID){
  advisorID = sAdvisorID;
}
int Student::getAdvisor(){
  return advisorID;
}
