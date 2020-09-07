#include "tree.hpp"
#include "exeptions.hpp"

#define DUMMY_ROOT -1

int main() {

  try {
    Tree tree;



    tree.add_operator_node(1, DUMMY_ROOT, Add);

    tree.add_operator_node(2, 1, Add);
    tree.add_operator_node(3, 1, Multiply);
    tree.add_operand_node(5, 3, 2);
    tree.add_operand_node(6, 3, 10);
    tree.add_operand_node(7, 2, 11);
    tree.add_operand_node(8, 2, 15);

    

    cout << tree.evaluate_tree() << endl;
  } catch(std::exception* ex) {
    cout << ex->what() << endl;
  }
}

/*
     +
    / \
   *   5
  / \
 2   3

*/
