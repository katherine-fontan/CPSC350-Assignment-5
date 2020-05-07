#include "Person.h"
#include <iostream>
class Student{

  public:
    Student();
    ~Student();
    Student(int id, string name, string level, string major, double gpa, int advisorID)

    string major;
    double gpa;
    int advisorID; // contain a faculty id as their advisor

    string getMajor();
    double getGPA();

    void setAdvisor(int advisorID);
    int getAdvisor();

    void printStudent();


    //overload equality to compare students

    bool operator == (const Student& stu)
    bool operator != (const Student& stu);
    //bool operator >= (const Student& stu);
    //bool operator <= (const Student& stu);
    bool operator < (const Student& stu);
    bool operator > (const Student& stu);

};
