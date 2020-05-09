#include "Database.h"
#include <iostream>
#include <fstream>

using namespace std;

Database::Database(){

  masterStudent = new BinarySearchTree<Student>();
  //studentRollBackStack = new GenStack<BinarySearchTree<Student>*>(5);

  masterFaculty = new BinarySearchTree<Faculty>();
  //facultyRollBackStack = new GenStack<BinarySearchTree<Faculty>*>(5);
}

Database::~Database(){


}



void Database::importFiles(){

  cout<< "Importing files..."<<endl;

  ifstream studentFile;
  ifstream facultyFile;
  string input = "";

  //variables for student and faculty

  int sID = 0;
  string sName = "";
  string sLevel = "";
  string sMajor = "";
  double gpa = 0.0;
  int advisor = 0;
  int stuCreated = 0;
  int line = 1;

  studentFile.open("studentTable.txt");

  if(studentFile.is_open()){

    while(getline(studentFile,input)){

        switch (line) {
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
                  gpa = stod(input);
                }
                catch(exception e){
                  cout<< "INCORRECT FORMAT"<<endl;
                }
                break;

            case 7:
                try{

                  advisor = stoi(input);
                }
                catch(exception e){
                cout<< "INCORRECT FORMAT"<<endl;
                }

                Student *s = new Student(sID,sName, sLevel, sMajor, gpa, advisor);

                ++stuCreated;

                masterStudent-> add(sID,s);
                cout<< "student added"<<endl;
                break;
       }
       ++line;

       if(line >=8)
         line = 1;

    }
  }
  else{
    cout<< "Student table was not found. Starting application with no student in the database."<<endl;
  }

  cout << "student filled"<<endl;




  int fID = 0;
  string fName = "";
  string fLevel = "";
  string department = "";
  int adviseeID = 0;
  int adviseeNum = 0;
  int facCreated = 0;




  //opening and importing faculty files

  int switchFaculty= 1;

  int fCount = 0;

  facultyFile.open("facultyTable.txt");


  if(facultyFile.is_open()){


    while(getline(facultyFile,input)){



      switch (switchFaculty) {
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

              f->addAdvisee(adviseeID);
            }

            masterFaculty->add(fID,f);
            cout<< "faculty added"<<endl;

            break;
      }

      ++switchFaculty;

      if(switchFaculty > 6)
        switchFaculty = 1;
    }
  }

  else{
    cout<< "Faculty table was not found. Starting application with no faculty in the database."<<endl;
  }

  cout << "Faculty filled"<<endl;

  facultyFile.close();
  studentFile.close();

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
void Database::addStudent(){

    //studentRollBackStack->push(masterStudent);
    //facultyRollBackStack->push(masterFaculty);

    string input, name, year, major;
    int id, advID;
    double gpa;


    cout<< "Enter the student's ID "<<endl;
    cin>> input;
    id = stoi(input);

    bool checkID;
    while(checkID){
      Student temp;
      temp.setID(id);

      if(masterStudent->contain(id)){

        cout<< "That ID is already in the system. Choose another: "<<endl;
        cin>>input;

        id = stoi(input);

      }
      else{
        checkID = false;
      }
    }

    cout<<"Enter the student's name " <<endl;
    cin >> name;

    cout << "Enter the student's year "<<endl;
    cin>>year;

    cout<< "Enter the studen's major "<<endl;
    cin>>major;

    cout<< "Enter the Student's GPA? "<<endl;
    cin >>gpa;

    //gpa check

    while(gpa<0.0 || gpa>=4.0){
      cout << "Enter valid GPA "<<endl;
      cin>>gpa;

    }



    if(masterFaculty->isEmpty())
      advID = -1;

    if(advID != -1){

      while(true){
        cout<< "Enter student's advisor ID "<<endl;
        cin>> advID;

        if(masterFaculty->contain(advID)){
          Faculty *fac = masterFaculty->search(advID);

          fac->addAdvisee(id);
          break;
        }
        else{
          cout<<"Invalid Id, try again "<<endl;
        }
      }
    }

    Student *student = new Student(id, name, year, major, gpa, advID);

    masterStudent->add(id, student);

    cout<< "Student added! "<<endl;


}

void Database::addFaculty(){

  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);


  string input, name, level, department;
  int id, adviseeID, answerInt, numAdvisees;



  cout<< "Enter the faculty's ID "<<endl;
  cin>> input;
  id = stoi(input);

  bool checkID;
  while(checkID){


    if(masterFaculty->contain(id)){

      cout<< "That ID is already in the system. Choose another: "<<endl;
      cin>>input;

      id = stoi(input);

    }
    else{
      checkID = false;
    }
  }

  cout<<"Enter the faculty's  name " <<endl;
  cin >> name;

  cout << "Enter the faculty's level "<<endl;
  cin>>level;

  cout<< "Enter the faculty's department "<<endl;
  cin>>department;


  Faculty *fac = new Faculty(id, level, name, department);


  cout<< "Does this faculty member have advisees?\n1- Yes\n2- no "<<endl;
  cin>>answerInt;


  if(answerInt == 1 && !masterStudent->isEmpty()){
    cout << "How many student does this faculty member advises? "<<endl;
    cin>>input;

    numAdvisees = stoi(input);

    for(int i = 0; i<numAdvisees; ++i){

      while(true){
        cout<< "Please enter a Student ID("<<numAdvisees - i << "remaining): "<<endl;

        cin>>input;

        try{
          adviseeID = stoi(input);

          if(masterStudent->contain(adviseeID)){
            fac->addAdvisee(adviseeID);

            masterStudent->search(adviseeID)->setAdvisor(id);

            break;
          }

          else{
            cout<< "Student not found "<<endl;
          }
        }
        catch(exception e){
          cout<< "Please enter an integer"<<endl;
        }

      }
    }

  }


  masterFaculty->add(id, fac);


}

void Database::deleteFaculty(int facID, int advTranferID){


  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);




  Faculty *f = masterFaculty->search(facID);



  masterFaculty->remove(facID);

  Faculty *advTrandfer = masterFaculty->search(advTranferID);

  while(f->getAdviseeListSize()!=0){
    int frontID = f->deleteAdvisee();

    changeAdvisor(frontID, advTranferID);
  }
  masterFaculty->remove(facID);




}


int Database:: changeAdvisor(int stuID, int facID){

  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);

  Student *s = masterStudent->search(stuID);



  Faculty *f = masterFaculty->search(facID);

  if(s->getAdvisor()!=0){
    s->setAdvisor(0);
  }

  s->setAdvisor(facID);
  f->addAdvisee(stuID);


}

void Database::deleteStudent(int stuID){
  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);

  Student *s = masterStudent->search(stuID);

  masterStudent->remove(stuID);
  removeAdvisee(stuID);

}

void Database:: removeAdvisee(int stuID){

  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);

  Student *s = masterStudent->search(stuID);

  int advID  = s->getAdvisor();
  Faculty *f = masterFaculty->search(advID);

  f->removeAdvisee(stuID);


}


void Database::printStudent(){

  if(masterStudent->isEmpty()){

    cout<< "There are no students"<<endl;

  }

  else{
    int id;
    cout<< "What student would you like to print? "<<endl;
    cin>> id;

    masterStudent->search(id)->printStudent();

  }
}

void Database::printFaculty(){

  if(masterFaculty->isEmpty()){

    cout<< "There are no faculty"<<endl;

  }

  else{
    int id;
    cout<< "What faculty member would you like to print? "<<endl;
    cin>> id;

    masterFaculty->search(id)->printFaculty();

  }

}


void Database::findStudent(int id){

  if(masterStudent->isEmpty()){

    cout<< "There are no students"<<endl;

  }

  else{
    if(masterStudent->search(id))
      masterStudent->search(id)->printStudent();

  }
}

void Database::findFaculty(int id){

  if(masterFaculty->isEmpty()){

    cout<< "There are no faculty"<<endl;

  }

  else{
    if(masterFaculty->search(id))

      masterFaculty->search(id)->printFaculty();
  }

}

void Database::printAllStudents(){
  if(masterStudent->isEmpty())
    cout<< "there are no students on display"<<endl;

  else{
    printMasterStudent(masterStudent->getRoot());
  }
}

void Database:: printAllFaculty(){

  if(masterFaculty->isEmpty())
    cout<< "There are no faculty on display"<<endl;


  else
    printMasterFaculty(masterFaculty->getRoot());


}

void Database::printMasterStudent(TreeNode<Student> *stu){

    if(stu != NULL){
      if(stu->left != NULL)
        printMasterStudent(stu->left);

      stu->data->printStudent();

      if(stu->right != NULL){
        printMasterStudent(stu->right);
      }
  }
  else{
    cout<< "Student tree is empty"<<endl;
  }


}

void Database:: printMasterFaculty(TreeNode<Faculty> *fac){

  if(fac != NULL){
    if(fac->left != NULL){
      printMasterFaculty(fac->left);
    }

    fac->data->printFaculty();

    if(fac->right != NULL){
      printMasterFaculty(fac->right);
    }
  }
  else{
    cout << "Faculty tree is empty"<<endl;
  }

}

void Database::printAdvisor(int stuID){

  if(masterFaculty->isEmpty())
    cout<< "Faculty tree is empty"<<endl;

  if(masterStudent->isEmpty())
    cout<< "Student tree is empty"<<endl;


  if(!masterStudent->isEmpty() && ! masterFaculty->isEmpty()){

    if(masterStudent->contain(stuID)){

          Student *s = masterStudent->search(stuID);

          return findFaculty(s->getAdvisor());
    }
    else
      cout<< "Invalid ID. Try again."<<endl;

  }

}

void Database::printAdvisees(int facID){
  if(masterFaculty->isEmpty())
    cout<< "Faculty tree is empty"<<endl;

  if(masterStudent->isEmpty())
    cout<< "Student tree is empty"<<endl;

    if(masterFaculty->contain(facID)){
      Faculty *f = masterFaculty->search(facID);

      cout<< "\n Advisee list: "<<endl;
      //f->adviseeList->printList();
    }
}


void Database::exit(){

  exportFiles();
  cout<< "bye!"<<endl;

}

void Database::run(){


  bool running = true;

  int studentID, facultyID, newFaculty, newAdvisor, adviseeID;
  while(running){
    int response;


    cout<< "Please choose an option from the menu: "<<endl;
    cin>>response;

    switch (response) {
      case 1:
        printAllStudents();
        break;

      case 2:
        printAllFaculty();
        break;

      case 3:
        cout<< "What is the id number of the student you are looking for? "<<endl;
        cin>> studentID;
        findStudent(studentID);
        break;

      case 4:
        cout<< "What is the id number of the faculty you are looking for? "<<endl;
        cin>> facultyID;
        findFaculty(facultyID);
        break;

      case 5:
        cout<<"What is the student's ID number? "<<endl;
        cin>> studentID;
        printAdvisor(studentID);
        break;

      case 6:
        cout<< "What is the faculty's id number? "<<endl;
        cin>>facultyID;
        printAdvisees(facultyID);
        break;

      case 7:
        addStudent();
        break;

      case 8:

        cout<< "What is the id of the student you want to delete? "<<endl;
        cin>> studentID;
        deleteStudent(studentID);
        break;

      case 9:

        addFaculty();
        break;

      case 10:


        cout<< "What is the ID of the faculty member? "<<endl;
        cin>> facultyID;

        cout<< "What is the ID of the faculty that is taking its place? "<<endl;
        cin>> newFaculty;

        deleteFaculty(facultyID, newFaculty);
        break;

      case 11:


        cout<< "What is the student's id to change adisor? "<<endl;
        cin>>studentID ;
        cout<< "What is the new advisor's id? "<<endl;
        cin>>newAdvisor;

        changeAdvisor(studentID,newAdvisor);
        break;

      case 12:

        cout<< "What is the id of the advisee you want to remove? "<<endl;
        cin>>adviseeID;
        removeAdvisee(adviseeID);
        break;

      case 13:
        //rollBack();
        break;

      case 14:
        exit();

        running = false;
        break;

    default:
      Menu m;
      m.displayMenu();
      break;


    }
  }
}
