#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "utrello_interface.hpp"
#include <stdexcept>
#include <string>



TEST_CASE("‫‪‬TEST of {Adding users and other class}"){

  UTrelloInterface interface;
  cout << interface.addUser("Amin") << endl;
  cout << interface.addUser("Behzad") << endl;
  cout << interface.addUser("Alireza") << endl;
  cout << interface.addUser("Seyed") << endl;
  cout << interface.addList("Game") << endl;
  cout << interface.addList("study") << endl;
  cout << interface.addList("out side things") << endl;
  cout << interface.addList("time with myself") << endl;
  cout << interface.addTask("Game", "Dota2", 10, 1, "Dota is soo fucking life") << endl;
  cout << interface.addTask("Game", "stronghold3", 4, 5, "those good old days") << endl;
  cout << interface.addTask("study", "AP project", 11, 2, "this is soo killing me man") << endl;
  cout << interface.addTask("study", "Ta thing", 3, 3, "assign the HW") << endl;
  cout << interface.addTask("time with myself", "music", 1, 4, "this is what i really wanna") << endl;
  cout << interface.assignTask("Dota2", "Amin") << endl;
  cout << interface.assignTask("AP project", "Alireza") << endl;
  cout << interface.assignTask("stronghold3", "Behzad") << endl;
  cout << interface.assignTask("Ta thing", "Amin") << endl;
  cout << interface.completeTask("Dota2") << endl;
  cout << interface.completeTask("Ta thing") << endl;
  cout << interface.assignTask("music", "Seyed") << endl;




  SECTION("The declaration"){
    CHECK(interface.printUserWorkload("Amin") == 13);
    CHECK(interface.printUserWorkload("Seyed") == 1);
    CHECK(interface.printUserWorkload("Behzad") == 4);
    CHECK(interface.printUserWorkload("Alireza") == 11);
    CHECK(interface.addUser("Amin") == "User‬‬ ‫‪already‬‬ ‫‪exists");
  }

  cout << interface.moveTask("music", "Game") << endl;
  cout << interface.moveTask("stronghold3", "study") << endl;

  SECTION("The print time remaining"){
    CHECK(interface.printTotalEstimatedTime() == 29);
    CHECK(interface.printTotalRemainingTime() == 16);
  }

  cout << interface.deleteTask("music") << endl;
  cout << interface.deleteTask("AP project") << endl;

  SECTION("The result for deleting the tasks"){
    CHECK(interface.printUserWorkload("Amin") == 13);
    CHECK(interface.printUserWorkload("Seyed") == 0);
    CHECK(interface.printUserWorkload("Behzad") == 4);
    CHECK(interface.printUserWorkload("Alireza") == 11);
  }


  cout << interface.editTask("Dota2", 29, 1, "still the best") << endl;
  cout << interface.editTask("stronghold3", 12, 3, "no idea") << endl;
  cout << interface.editTask("music", 10, 5, "makes me happy really happy") << endl;

  SECTION("The result for deleting the tasks"){
    CHECK(interface.printUserWorkload("Amin") == 32);
    CHECK(interface.printUserWorkload("Seyed") == 0);
    CHECK(interface.printUserWorkload("Behzad") == 12);
    CHECK(interface.printUserWorkload("Alireza") == 11);
  }


}






