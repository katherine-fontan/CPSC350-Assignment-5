#include "Person.h"
#include <iostream>


using namespace std;

class Student : public Person{

  public:
    Student();
    ~Student();
    Student(int id, string name, string level, string major, double gpa, int advisorID);

    string major;
    double gpa;
    int advisorID; // contain a faculty id as their advisor

    string getMajor();
    double getGPA();

    void setAdvisor(int advisorID);
    int getAdvisor();




    //overload equality to compare students

    bool operator == (const Student &stu){
      return(this->id == stu.id);
    }

    bool operator != (const Student &stu){
      return(this->id != stu.id);
    }

    bool operator >= (const Student &stu){
      return(this->id >= stu.id);
    }
    bool operator <= (const Student &stu){
      return(this->id <= stu.id);
    }
    bool operator < (const Student &stu){
      return(this->id < stu.id);
    }
    bool operator > (const Student &stu){
      return(this->id > stu.id);
    }

};
