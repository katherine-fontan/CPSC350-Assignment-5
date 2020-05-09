#include "Faculty.h"
#include <iostream>


using namespace std;

Faculty::Faculty(){
  department = "";
}
Faculty::~Faculty(){
  delete adviseeList;
}

Faculty::Faculty(int fID, string fLevel, string fName, string fDepartment){

  id = fID;
  name = fName;
  level = fLevel;
  department = fDepartment;
  adviseeList = new DLinkedList<int>();

}

string Faculty:: getDepartment(){
  return department;
}


DLinkedList<int>* Faculty::getAdviseeList(){
  return adviseeList;
}

int Faculty:: getAdviseeListSize(){
    return adviseeList->getSize();
}

void Faculty::addAvisee(int id){

    adviseeList->insertFront(id);
}

void Faculty::removeAdvisee(int id){
    if(adviseeList->getSize() != 0){
        adviseeList->remove(id);
    }
}

int Faculty::deleteAdvisee(){

    if(adviseeList->getSize()== 0){
      return 0;
    }
    else{
      return adviseeList->removeBack();
    }
}

void Faculty::printFaculty(){

  cout << "Faculty ID: " << id <<endl;
  cout<< "Name: " << name << endl;
  cout<< "Level: " << level << endl;
  cout<< "Departent: " << department << endl;
  cout<< "Advisee IDs: ";

  adviseeList->printList();
  cout << endl;
}


bool Faculty::operator == (const Faculty &fac){
  return(this->id ==fac.id);
}

bool Faculty:: operator !=(const Faculty &fac){
  return(this->id !=fac.id);
}
bool Faculty::operator >=(const Faculty &fac){
  return(this->id >=fac.id);
}
bool Faculty::operator <=(const Faculty &fac){
  return(this->id <=fac.id);
}
bool Faculty::operator < (const Faculty &fac){
  return(this->id < fac.id);
}
bool Faculty::operator > (const Faculty &fac){
  return(this->id > fac.id);
}
