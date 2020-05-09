#include "DLinkedList.h"
#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Faculty : public Person{

  public:
    Faculty();
    Faculty(int fID, string fLevel, string fName, string fDepartment);
    ~Faculty();

    string department;
    DLinkedList<int> *adviseeList;
    int maxSize; // max number of students the faculty memmber can advisees
    int adviseeCount;


    string getDepartment();

    //advisee list functions

    DLinkedList<int>* getAdviseeList();
    int getAdviseeListSize();
    void addAvisee(int adviseeID);
    void removeAdvisee(int adviseeID);
    int deleteAdvisee();


    void printFaculty();
    void printAdvisees();



    int getSize();

    //bool operators done by comparing ids

    bool operator ==(const Faculty &fac);

    bool operator !=(const Faculty &fac);
    bool operator >=(const Faculty &fac);
    bool operator <=(const Faculty &fac);
    bool operator < (const Faculty &fac);
    bool operator > (const Faculty &fac);
};
