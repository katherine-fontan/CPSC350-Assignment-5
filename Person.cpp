#include "Person.h"

using namespace std;

Person::Person(){

}

Person::~Person(){

}

void Person:: setID(int idNum){
  id = idNum;
}

int Person:: setID(){
  return id;
}

void Person::setName(string pName){
  name = pName;
}

string Person::getName(){
  return name;
}

void Person:: setLevel(string pLevel){
  level = pLevel;
}

string Person:: getLevel(){
  return level;
}
