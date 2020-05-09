#include <iostream>
#include "BinarySearchTree.h"
#include "GenStack.h"
#include "Faculty.h"
#include "Student.h"
#include "Menu.h"
#include <fstream>
#include <string>

using namespace std;

class Database{
    public:
      Database();
      ~Database();


      BinarySearchTree<Student> *masterStudent;
      BinarySearchTree<Faculty> *masterFaculty;

      //create a stack for sutdent and faculty rollback

      GenStack<BinarySearchTree<Student>*> *studentRollBackStack;
      GenStack<BinarySearchTree<Faculty>*> *facultyRollBackStack;


      //printing functions
      void printAllStudents();
      void printAllFaculty();
      void printStudent();
      void printFaculty();
      void printAdvisor();
      void printAdvisee();

      //adding and deleting functions
      void addStudent();
      void deleteStudent(int stuID);
      void addFaculty();
      void deleteFaculty(int facID, int advTranferID);



      int changeAdvisor(int frontID, int advTranferID);
      void removeAdvisee(int stuID);

      void importFiles();
      void exportFiles();
      


      void rollBack();
      void exit();
      void run();


      void outputStudent(TreeNode<Student> *stu, string fileName);
      void outputFaculty(TreeNode<Faculty> *fac, string fileName);

      void bfsStudents();
      void bfsFaculty();

      void printMasterStudent(TreeNode<Student> *stu);
      void printMasterFaculty(TreeNode<Faculty> *fac);


};
