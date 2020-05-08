#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

Database::Database(){

  masterStudent = new BinarySearchTree<Student>();
  studentRollBackStack = new GenStack<BinarySearchTree<Student>*>(5);

  masterFaculty = new BinarySearchTree<Faculty>();
  facultyRollBackStack = new GenStack<BinarySearchTree<Faculty>*>(5);
}

Database::~Database(){

}

void Database::importFiles(){

  cout<< "Importing files..."<<endl;

  ifstream studentFile;
  ifstream facultyFile;
  string input = "";

  int sCount = 0;
  int switchCount = 1;

  //variables for student and faculty

  int sID = 0;
  string sName = "";
  string sLevel = "";
  string sMajor = "";
  double gpa = 0.0;
  int advisor = 0;


  int fID = 0;
  string fName = "";
  string fLevel = "";
  string department = "";
  int adviseeID = 0;
  int adviseeNum = 0;
  int facCreated = 0;

  studentFile.open("studentTable.txt");

  //opening and importing from student file
  string fileName;

  if(studentFile.is_open()){


    getline(studentFile,input);

    if(input!= ""){
      sCount =stoi(input);
      sCount *=7;
    }


    //each block of 7 lines is a new student, after 7 lines create a new student object
    for(int s = 0; s < sCount; ++s){

      getline(studentFile,input);

        switch (switchCount) {
          case 1:

              if(input != "--"){
                cout<< "INCORRECT FORMAT"<<endl;
              }
              break;

          case 2:

              try{
                sID = stoi(input);
              }
              catch(exception e){
                cout<< "INCORRECT FORMAT"<<endl;
              }
              break;

          case 3:
              sName = input;
              break;

          case 4:

              sLevel = input;
              break;

          case 5:
              sMajor = input;
              break;

          case 6:
              try{
                gpa = stoi(input);
              }
              catch(exception e){
                cout<< "INCORRECT FORMAT"<<endl;
              }
              break;

          case 7:

              try{
                advisor = stoi(input);

                Student *s  = new Student(sID,sName, sLevel, sMajor, gpa, advisor);
                TreeNode<Student> *sNode = new TreeNode<Student>(s, sID);
                masterStudent->add(sNode);
              }
              catch(exception e){
                cout<< "INCORRECT FORMAT"<<endl;
              }
              break;


        }


        ++switchCount;
        switchCount%=7; //makes cases repeat ater each student
    }

  }

  else{
    cout<< "Student table was not found. Starting application with no sutdents in the database."<<endl;

  }


  cout << "Students filled"<<endl;

  studentFile.close();


  //opening and importing faculty files

  switchCount = 1;

  int fCount = 0;
  DLinkedList<int> *adviseeList = new DLinkedList<int>();
  facultyFile.open("facultyTable.txt");


  if(studentFile.is_open()){

    getline(facultyFile,input);

    if(input!= ""){
      fCount =stoi(input);
      fCount *=7;
    }

    while(facultyFile.eof()){

      getline(facultyFile,input);

      switch (switchCount) {
        case 1:

            if(input != "--"){
              cout<< "INCORRECT FORMAT"<<endl;
            }
            break;

        case 2:

            try{
              fID = stoi(input);
            }
            catch(exception e){
              cout<< "INCORRECT FORMAT"<<endl;
            }
            break;

        case 3:
            fName = input;
            break;

        case 4:

            fLevel = input;
            break;

        case 5:
            department = input;
            break;


        case 6:

            try{

              adviseeNum = stoi(input);
            }
            catch(exception e){
            cout<< "INCORRECT FORMAT"<<endl;
            }

            Faculty *f  = new Faculty(fID,fLevel, fLevel, department);

            ++facCreated;

            for(int a = 0; a < adviseeNum; ++a){
              getline(facultyFile, input);

              try{
                adviseeID = stoi(input);
              }
              catch(exception e){
                cout<< "INCORRECT FORMAT"<<endl;
              }

              f->addAvisee(adviseeID);
            }

            TreeNode<Faculty> *fNode = new TreeNode<Faculty>(f, fID);
            masterFaculty->add(fNode);

            break;


      }

      ++switchCount;
      if(facCreated == fCount)
        break;



      if(switchCount > 6)
        switchCount = 1;


    }

  }

  else{
    cout<< "Faculty table was not found. Starting application with no faculty in the database."<<endl;
  }


  cout << "Faculty filled"<<endl;

  facultyFile.close();

}


void Database::exportFiles(){


  ofstream facultyFile;
  ofstream studentFile;
  string sFileName = "studentTable.txt";
  string fFileName = "facultyTable.txt";

  //EXPORT STUDENTS

  studentFile.open(sFileName);

  if(studentFile.is_open()){
    studentFile << masterStudent->getSize() <<endl;

    TreeNode<Student> *s = masterStudent->getRoot();

    outputStudent(s, sFileName);
  }

  studentFile.close();

  //EXPORT FAUCULTY

  if(facultyFile.is_open()){

    facultyFile << masterFaculty->getSize()<<endl;
    TreeNode<Faculty> *f = masterFaculty->getRoot();

    outputFaculty(f, fFileName);
  }
  facultyFile.close();


  cout<< "DATABASE WAS UPDATED" << endl;

}

void Database::outputStudent(TreeNode<Student> *s, string file){

    ofstream out;

    //student tree:

    out.open(file);

    if(out.is_open()){

      if(s != NULL){
        out<< "--" << endl;

        //output student to file

        out << s->data->getID() <<endl;
        out << s->data->getName() <<endl;
        out << s->data->getLevel() <<endl;
        out << s->data->getMajor() <<endl;
        out << s->data->getGPA() <<endl;
        out << s->data->getAdvisor() <<endl;

        if(s->left != NULL)
          outputStudent(s->left,file);

        if(s->right != NULL)
          outputStudent(s->right,file);


      }
    }
    else{
      cout<< "Student tree is empty."<<endl;
    }


    out.close();
    cout<< "Students were saved in the database."<<endl;

}

void Database::outputFaculty(TreeNode<Faculty> *f, string file){

  ofstream out;

  out.open(file);

  if(out.is_open()){

    if(f != NULL){

      out<< "--"<<endl;

      out<< f->data->getID()<<endl;
      out<< f->data->getName()<<endl;
      out<< f->data->getLevel()<<endl;
      out<< f->data->getDepartment()<<endl;

      //output the number of advisees

      out<< f->data->getAdviseeListSize()<<endl;

      //output doubly linked list to file

        DLinkedList<int> *a = f->data->getAdviseeList();
        while(! a->isEmpty()){
          int i = a->removeFront();

          out << i << endl;
        }


      if(f->left != NULL)
        outputFaculty(f->left,file);

      if(f->right != NULL)
        outputFaculty(f->right,file);



    }
    else{
      cout << "Faculty tree is empty"<<endl;
    }
    out.close();

    cout<< "Faculty were saved in the database."<<endl;

  }

}
