#include <iostream>
#ifndef included
#define included

using namespace std;

class Person{

  public:
    int id;
    string name;
    string level;

    Person();
    ~Person();

    string getName();
    void setName(string n);

    string getLevel();
    void setLevel(string l);

    int getID();
    void setID(int v);

};
#endif
