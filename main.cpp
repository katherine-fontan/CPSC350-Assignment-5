#include <iostream>
#include "Database.h"



using namespace std;

int main(int argc, char **argv){

  Database d1;
  Menu menu;

  d1.importFiles();

  menu.welcome();

  d1.run();




  return 0;
}
