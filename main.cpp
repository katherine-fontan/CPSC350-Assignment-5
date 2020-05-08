#include <iostream>

//#include "BinarySearchTree.h"
#include "Database.h"
//#include "Menu.h"

using namespace std;

int main(int argc, char **argv){

  Database d1;
  //Menu menu;

  d1.importFiles();

  //menu.welcome();

  //p1.run();

  d1.exportFiles();


  return 0;
}
