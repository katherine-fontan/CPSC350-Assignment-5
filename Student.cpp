#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(){
  major = "";
  gpa = 0.0;
  advisor = 0;

}

Student::Student(ind sID, string sName, string sLevel, string sMajor, double sGPA, int sAdvisorID){
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

void Student::printStudent(){
  cout << "Name: " <<name <<"; ";
  cout << " ID: "<<id<< "; ";
  cout<< " Major: "<<major<<"; ";
  cout<< " GPA: "<<gpa<<"; ";
  cout<<" Grade: "<<level<< "; ";
  cout<< " Advisor ID: "<<advisorID << endl;
}

bool Student:: operator == (const Student &stu){
  return(this->id == stu.id);
}

bool Student::operator != (const Student &stu){
  return(this->id != stu.id);
}

bool Student:: operator >= (const Student &stu){
  return(this->id >= stu.id);
}
bool Student::operator <= (const Student &stu){
  return(this->id <= stu.id);
}
bool Student:: operator < (const Student &stu){
  return(this->id < stu.id);
}
bool Student:: operator > (const Student &stu){
  return(this->id > stu.id);
}