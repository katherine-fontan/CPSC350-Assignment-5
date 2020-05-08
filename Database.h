#include <iostream>
#include "BinarySearchTree.h"
#include "GenStack.h"
#include "Faculty.h"
#include "Student.h"
#include <fstream>

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
      void pritnStudent();
      void printFaculty();
      void printAdvisor();
      void printAdvisee();

      //adding and deleting functions
      void addStudent();
      int deleteStudent();
      void addFaculty();
      int deleteFaculty();



      int changeAdvisor();
      int removeAdvisee();

      void importFiles();
      void exportFiles();

      void printMenu();
      void rollBack();
      void exit();

      void outputStudent(TreeNode<Student> *stu, string fileName);
      void outputFaculty(TreeNode<Faculty> *fac, string fileName);

      void bfsStudents();
      void bfsFaculty();



};
