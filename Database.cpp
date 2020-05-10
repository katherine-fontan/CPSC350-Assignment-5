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
  delete masterStudent;
  delete masterFaculty;

}



void Database::importFiles(){

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
                //cout<< "INCORRECT FORMAT"<<endl;
                }

                Student *s = new Student(sID,sName, sLevel, sMajor, gpa, advisor);

                ++stuCreated;

                masterStudent-> add(sID,s);
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

  cout << "Student's from file added!"<<endl;




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


    while(getline(facultyFile, input)){

      switch (switchFaculty) {
        case 1:

            /*if(input != "--"){

              cout<< "INCORRECT FORMAT"<<endl;

            }*/
            break;

        case 2:

            try{
              fID = stoi(input);
            }
            catch(exception e){
              //cout<< "INCORRECT FORMAT"<<endl;
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
            //cout<< "INCORRECT FORMAT"<<endl;
            }

            Faculty *f  = new Faculty(fID,fLevel, fName, department);

            ++facCreated;

            for(int a = 0; a < adviseeNum; ++a){
              getline(facultyFile, input);

              try{
                adviseeID = stoi(input);
              }
              catch(exception e){
                //cout<< "INCORRECT FORMAT"<<endl;
              }

              f->addAdvisee(adviseeID);
            }

            masterFaculty->add(fID,f);
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
  cout << "Faculty from file was added!"<<endl;

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

    TreeNode<Student> *s = masterStudent->getRoot();

    outputStudent(s, studentFile);
  }

  studentFile.close();

  //EXPORT FACULTY

  if(facultyFile.is_open()){

    facultyFile << masterFaculty->getSize()<<endl;
    TreeNode<Faculty> *f = masterFaculty->getRoot();

    outputFaculty(f, facultyFile);
  }
  facultyFile.close();


  cout<< "DATABASE WAS UPDATED" << endl;

}

void Database::outputStudent(TreeNode<Student> *s, ofstream &out){


      if(s == NULL)
        return;

        outputStudent(s->left,out);

        out<< "--" << endl;

        //output student to file

        out << s->data->getID() <<endl;
        out << s->data->getName() <<endl;
        out << s->data->getLevel() <<endl;
        out << s->data->getMajor() <<endl;
        out << s->data->getGPA() <<endl;
        out << s->data->getAdvisor() <<endl;


        outputStudent(s->right,out);



}

void Database::outputFaculty(TreeNode<Faculty> *f, ofstream &out){

    if(f = NULL)
      return;

      outputFaculty(f->left,out);


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



      outputFaculty(f->right,out);



}
void Database::addStudent(){
//option 7
    //studentRollBackStack->push(masterStudent);
    //facultyRollBackStack->push(masterFaculty);

    string input, name, year, major;
    int id, advID;
    double gpa;


    cout<< "Enter the student's ID "<<endl;
    cin>> input;
    id = stoi(input);

    bool checkID = true;
    while(checkID){

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

    cout<< "Enter the student's major "<<endl;
    cin>>major;

    cout<< "Enter the Student's GPA? "<<endl;
    cin >>gpa;

    bool added = false;

    if(masterFaculty->isEmpty())
      advID = -1;

    if(advID != -1){

      while(added == false){
        cout<< "Enter student's advisor ID "<<endl;
        cin>> advID;

        if(masterFaculty->contain(advID)){
          Faculty *fac = masterFaculty->search(advID);

          fac->addAdvisee(id);
          added = true;
          break;
        }
        else{
          cout<<"This faculty doesn't exist, try again. Advidor ID for this student will be 0"<<endl;
          advID = 0;
          added = true;

        }
      }
    }

    Student *student = new Student(id, name, year, major, gpa, advID);

    masterStudent->add(id, student);

    cout<< "Student added! "<<endl;


}

void Database::addFaculty(){
//option 9
  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);


  string input, name, level, department, answer;
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

  bool added = false;

  cout<< "Does this faculty member have advisees?\n1- Yes\n2- no "<<endl;
  cin>>answerInt;


  if(answerInt == 1 && !masterStudent->isEmpty()){
    cout << "How many student does this faculty member advises? "<<endl;
    cin>>input;

    numAdvisees = stoi(input);

    for(int i = 0; i<numAdvisees; ++i){

      while(added == false){
        cout<< "Please enter a Student ID("<<numAdvisees - i << " remaining): "<<endl;
        cin>>input;

        try{
          adviseeID = stoi(input);

          if(masterStudent->contain(adviseeID)){
            fac->addAdvisee(adviseeID);

            masterStudent->search(adviseeID)->setAdvisor(id);
            added = true;

            break;
          }

          else{
            cout<< "Student does not exist. Faculty will remain without advisees"<<endl;
            added = true;

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

//option 10
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

//option 11
  Student *s = masterStudent->search(stuID);


  if(masterFaculty->contain(facID)){

    Faculty *f = masterFaculty->search(facID);

    s->setAdvisor(facID);
    f->addAdvisee(stuID);
    cout<< "Advisor was changed!"<<endl;

  }
  else{
    cout<< "This faculty doesn't exist, student's advisor was removed intead"<<endl;
      s->setAdvisor(0);
  }


}

void Database::deleteStudent(int stuID){

  //option 8

  //studentRollBackStack->push(masterStudent);
  //facultyRollBackStack->push(masterFaculty);


  if(!masterStudent->contain(stuID))
    cout<< "That was an invalid ID"<<endl;

  else{
    //remove student from advisee LIST

    masterFaculty->search(masterStudent->search(stuID)->getAdvisor())->removeAdvisee(stuID);
    masterStudent->remove(stuID);
    cout<< "Student removed!"<<endl;
  }

}

void Database:: removeAdvisee(int stuID){

//option 12

  Student *s = masterStudent->search(stuID);

  int advID  = s->getAdvisor();
  Faculty *f = masterFaculty->search(advID);

  f->removeAdvisee(stuID);

  cout<< "Advisee was removed!"<<endl;

}


/*void Database::printStudent(){

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

}*/


void Database::findStudent(int id){
  //otion 3

  if(masterStudent->isEmpty()){

    cout<< "There are no students in student tree."<<endl;

  }

  else{
    if(masterStudent->contain(id)==true)
      masterStudent->search(id)->printStudent();

    else{
      cout<< "Student is not in the system"<<endl;
    }

  }

}

void Database::findFaculty(int id){

  //option4

  if(masterFaculty->isEmpty()){

    cout<< "There are no faculty"<<endl;

  }


  else{
    if(masterFaculty->contain(id) == true)

      masterFaculty->search(id)->printFaculty();
    else
      cout<< "Faculty is not in the system"<<endl;
  }

}

void Database::printAllStudents(){
  //option 1
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
//option 5
  if(masterFaculty->isEmpty())
    cout<< "Faculty tree is empty"<<endl;

  if(masterStudent->isEmpty())
    cout<< "Student tree is empty"<<endl;


  if(!masterStudent->isEmpty() && ! masterFaculty->isEmpty()){

    if(masterStudent->contain(stuID)){

          Student *s = masterStudent->search(stuID);

          if(s->getAdvisor()==0){
            cout<< "This student doesn't have an advisor!"<<endl;
          }
          else{
            return findFaculty(s->getAdvisor());
          }


    }
    else
      cout<< "Invalid ID. Try again."<<endl;

  }

}

void Database::printAdvisees(int facID){

// option 6

    if(masterFaculty->contain(facID)){
      Faculty *f = masterFaculty->search(facID);

      cout<< "\nAdvisee list: "<<endl;

      DLinkedList<int> *advisees = f->getAdviseeList();

      ListNode<int> *curr = advisees->front;

      if(f->adviseeList->getSize()==0)
        cout<< "Faculty has zero advisees"<<endl;

      for(int i=0;i< f->adviseeList->getSize(); ++i ){

          int idS = curr->data;


          masterStudent->search(idS)->printStudent();

          curr = curr -> next;

      }

   }
}

/*void Database:: rollBack(){
  //option 13
}*/

void Database::exit(){
//option 14

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


        cout<< "What is the student's id to change their advisor? "<<endl;
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
