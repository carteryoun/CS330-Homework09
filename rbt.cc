#include "rbt.h"

// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST::tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}

// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
//3RD REV
/*
  RBTNode* lChild = (RBTNode*) y->get_left();
  RBTNode* rChild = (RBTNode*) y->get_right();
  RBTNode* parent = (RBTNode*) y->get_parent();

  y->add_left(rChild);
  
  if(rChild) {
    rChild->add_parent(y);
  }
  lChild->add_parent(parent);

  if(parent == sentinel) {
    root = lChild;
  } else if (parent->get_right() == y) {
      parent->add_right(lChild);
  } else {
      parent->add_left(lChild);
  }
  lChild->add_right(y);
  y->add_parent(lChild);
*/
//2ND REV
/*
  RBTNode* lChild = (RBTNode*) y->get_left();
  y->add_left(lChild->get_right());
  
  if(lChild->get_right() != sentinel) {
    lChild->get_right()->add_parent(y);
  }
  lChild->add_parent(y->get_parent());
  
  if(lChild->get_parent() == sentinel) {
    root = lChild;
  }
  
  else if (lChild->get_parent()->get_right() == y) {
    lChild->get_parent()->add_right(lChild);
  }
  else {
    lChild->get_parent()->add_left(lChild);
  }
  y->add_parent(lChild);
  lChild->add_right(y);
*/
//1ST REV
  //RBTNode* rChild = (RBTNode*) y->get_right();
  RBTNode* lChild = (RBTNode*) y->get_left();
  RBTNode* grChild = (RBTNode*) lChild->get_right();
  RBTNode* parent = (RBTNode*) y->get_parent();
  // y->add_left(grChild);
  y->add_left(grChild);

  if(grChild != sentinel) {
    grChild->add_parent(y);
  }
  lChild->add_parent(parent);

  if(parent == sentinel) {
    root = lChild;
    // root = lChild;
  }
  else if(parent->get_right() == y) {
    parent->add_right(lChild);
  }
  else {
    parent->add_left(lChild);
  }
  y->add_parent(lChild);
  lChild->add_right(y);
}

// Left rotate
void RBT::left_rotate(RBTNode* x)
{
//3RD REV
/*
  RBTNode* lChild = (RBTNode*) x->get_left();
  RBTNode* rChild = (RBTNode*) x->get_right();
  RBTNode* parent = (RBTNode*) x->get_parent();

  x->add_right(lChild);

  if(lChild) {
    lChild->add_parent(x);
  }
  lChild->add_parent(parent);

  if(parent == sentinel) {
    root = rChild;
  } else if (parent->get_left() == x) {
      parent->add_left(rChild);
  } else {
      parent->add_right(rChild);
  }
  rChild->add_left(x);
  x->add_parent(rChild);
*/
//2ND REV
/*
  RBTNode* rChild = (RBTNode*) x->get_right();
  x->add_right(rChild->get_left());

  if(rChild->get_left() != sentinel) {
    rChild->get_left()->add_parent(x);
  }
  rChild->add_parent(x->get_parent());

  if(rChild->get_parent() == sentinel) {
    root = rChild;
  }
  
  else if (rChild->get_parent()->get_left() == x) {
    rChild->get_parent()->add_left(rChild);
  }
  else {
    rChild->get_parent()->add_right(rChild);
  }
  x->add_parent(rChild);
  rChild->add_left(x);
*/
//1ST REV
  RBTNode* rChild = (RBTNode*) x->get_right();
  //RBTNode* lChild = (RBTNode*) x->get_left();
  RBTNode* grChild = (RBTNode*) rChild->get_left();
  RBTNode* parent = (RBTNode*) x->get_parent();
  // x->add_right(grChild);
  x->add_right(grChild);

  if(grChild != sentinel) {
    grChild->add_parent(x);
  }
  rChild->add_parent(parent);

  if(parent == sentinel) {
    root = rChild;
    // root = rChild;
  }
  else if(parent->get_left() == x) {
    parent->add_left(rChild);
  }
  else {
    parent->add_right(rChild);
  }
  x->add_parent(rChild);
  rChild->add_left(x);
}

void RBT::rb_insert_fixup(RBTNode* in)
{
  if (in == root) {
    ((RBTNode*) root)->add_color(BLACK);
    return;
  }

  RBTNode* p = (RBTNode*) in->get_parent();
 
  // Root node must be black from P2 (Case 0: Z is the root)
  while (p && (p->get_color() == RED)) {
    p = (RBTNode*) in->get_parent();
    RBTNode* gp = (RBTNode*) p->get_parent();

    if(gp) {
      if(gp->get_left() == p) {
        // Case 1: Z's uncle is red
	RBTNode* uncle = (RBTNode*) gp->get_right(); // Uncle
        if (uncle && (uncle->get_color() == RED)) {
          p->add_color(BLACK);
          uncle->add_color(BLACK);
	  gp->add_color(RED);
	  in = (RBTNode*) in->get_parent()->get_parent();
	  //Psuedocode lines 1-8
        } else {
	       	if ((RBTNode*) p->get_right() == in) {
	    //Case 2: Z's uncle is black and Z is a right child
	      		in = (RBTNode*) in->get_parent();
	      		//p = (RBTNode*) in->get_parent();
	      		//gp = (RBTNode*) p->get_parent();
	      		left_rotate(in);
			p = (RBTNode*) in->get_parent();
        	}
	        //Case 3: Z's uncle is black and Z is a left child
	      	  p->add_color(BLACK);
	      	  gp->add_color(RED);
	      	  right_rotate(gp);
} 
    } else {
	//Case 1: Z's uncle is red
        RBTNode* uncle = (RBTNode*) gp->get_left(); // Uncle
        if (uncle && uncle->get_color() == RED) {
          p->add_color(BLACK);
	  uncle->add_color(BLACK);
	  gp->add_color(RED);
	  in = (RBTNode*) in->get_parent()->get_parent();
	} else { 
		if ((RBTNode*) p->get_left() == in) {
	    //Case 2: Z's uncle is black and Z is a left child
	      		in = p;
	      		//p = (RBTNode*) in->get_parent();
	      		//gp = (RBTNode*) p->get_parent();
	      		right_rotate(in);
			p = (RBTNode*) in->get_parent();
        	}
	        //Case 3: Z's uncle is black and Z is a right child
	          p->add_color(BLACK);
	          gp->add_color(RED);
	          left_rotate(gp);
    }
  }  
} 
p = (RBTNode*) in->get_parent();
//gp = (RBTNode*) p->get_parent();
}
((RBTNode*) root)->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{
  insert_node(in, sentinel);
  in->add_left(sentinel);
  in->add_right(sentinel);
  in->add_color(RED);
  rb_insert_fixup(in);
}

void RBT::rb_delete_fixup(RBTNode* in)
{
  ((RBTNode*) root);
  while (in != sentinel && in != root && in->get_color() == BLACK) {
    RBTNode* p = (RBTNode*) in->get_parent();
  
    if(p->get_left() == in) {
      RBTNode* sibling = (RBTNode*) p->get_right();	    
      RBTNode* rNephew = (RBTNode*) sibling->get_right();
      RBTNode* lNephew = (RBTNode*) sibling->get_left();

    	if(sibling->get_color() == RED) {
      	  sibling->add_color(BLACK);
      	  p->add_color(RED);
      	  left_rotate(p);
      	  sibling = (RBTNode*) p->get_right(); // end of CASE r.1: if uncle is red -> left rotate p -> color shift
    	}  
        if((lNephew->get_color() == BLACK) && (rNephew->get_color() == BLACK)) {
      	  sibling->add_color(RED);
      	  in = (RBTNode*) in->get_parent(); // end of CASE r.2: if uncle and children of uncle is black -> move in up -> change uncle to red
          //p = (RBTNode*) in->get_parent();
	  //sibling = (RBTNode*) p->get_right();
	  //lNephew = (RBTNode*) sibling->get_left();
	  //rNephew = (RBTNode*) sibling->get_right();
    	}
    	else {
	  if(rNephew->get_color() == BLACK) {
            lNephew->add_color(BLACK);
      	    sibling->add_color(RED);
      	    right_rotate(sibling);
      	    sibling = (RBTNode*) p->get_right();
	   //end of CASE r.3: uncle is black, right child of uncle is black, left is red
	   // right rotate uncle -> switch colors of uncle and left child
    	}
      	      sibling->add_color(p->get_color());
      	      p->add_color(BLACK);
      	      rNephew->add_color(BLACK);
       	      left_rotate(p);
      	      in = (RBTNode*) root; 
	      //end of CASE r.4: uncle is black, right child is red, left is black -> left rotate p ->
	      // switch colors of parent, uncle, and left child
}
}
    else {
      RBTNode* sibling = (RBTNode*) p->get_left();
      RBTNode* rNephew = (RBTNode*) sibling->get_right();
      RBTNode* lNephew = (RBTNode*) sibling->get_left();

    	// INVERSE FOR IF P->GET_RIGHT() == IN !!!!
        if(sibling->get_color() == RED) {
      	  sibling->add_color(BLACK);
      	  p->add_color(RED);
      	  right_rotate(p);
      	  sibling = (RBTNode*) p->get_left(); 
	  // end of CASE l.1: if uncle is red -> right rotate p -> color shift
        }
        if(lNephew->get_color() == BLACK && rNephew->get_color() == BLACK) {
      	  sibling->add_color(RED);
      	  in = (RBTNode*) in->get_parent(); // end of CASE l.2: if uncle and children of uncle is black -> move in up -> change uncle to red
    	}
        else {
	  if(lNephew->get_color() == BLACK) {
      	    rNephew->add_color(BLACK);
      	    sibling->add_color(RED);
      	    left_rotate(sibling);
      	    sibling = (RBTNode*) p->get_left();
	  //end of CASE l.3: uncle is black, left child of uncle is black, right is red
                              // left rotate uncle -> switch colors of uncle and right child
        }
      	      sibling->add_color(p->get_color());
      	      p->add_color(BLACK);
	      lNephew->add_color(BLACK);
      	      right_rotate(p);
      	      in = (RBTNode*) root; 
	    //end of CASE l.4: uncle is black, left child is red, right is black -> right rotate p ->
            // switch colors of parent, uncle, and right child
    }
}
in->add_color(BLACK);
//delete sentinel;
}
}

void RBT::rb_delete_node(RBTNode* out)
{
   // temporary pointers
    RBTNode* y = sentinel;
    RBTNode* x = sentinel;

    // first determine if out has at most one child
    if((out->get_left() == sentinel) || (out->get_right() == sentinel)) {
        // 0 or 1 child - out will be spliced
        y = out;
    } else {
        // 2 children - out's successor will be sliced out
        y = (RBTNode*) BST::get_succ(out, sentinel);
        // cout << y->get_key() << endl;
    }

    Node_color y_original_color = y->get_color();

    // set x to a non-null child of y, or null if it has no children
    // Recall that y is either out (if it has 0 or 1 child),
    // or succ (if it has 2 children)
    // Since succ can only have 1 child, y should only have one child
    if(y->get_left() != sentinel) {
        x = (RBTNode*) y->get_left();
    } else {
        x = (RBTNode*) y->get_right();
    }

    // Splice out node y with its child
    // check for null, otherwise the code will segfault
    if(x != sentinel) {
        x->add_parent(y->get_parent());
    }

    if(y->get_parent() == sentinel) {
        root = x;
    } else if(y == y->get_parent()->get_left()) {
        y->get_parent()->add_left(x);
    } else {
        y->get_parent()->add_right(x);
    }

    // Finally, replace out with y
    if(y != out) {
        // first copy out's parent and children to y
        y->add_parent(out->get_parent());
        if(y->get_parent() == sentinel) {
            root = y;
        } else {
            // update the parent's child to y
            if(out == out->get_parent()->get_left()) {
                y->get_parent()->add_left(y);
            } else {
                y->get_parent()->add_right(y);
            }
        }
        y->add_left(out->get_left());
        y->add_right(out->get_right());

        // update the children's parents to y
        if(y->get_left() != sentinel) {
            y->get_left()->add_parent(y);
        }
        if(y->get_right() != sentinel) {
            y->get_right()->add_parent(y);
        }
	y->add_color(out->get_color());
	}	
    if(y_original_color == BLACK) {
	rb_delete_fixup(x);
    }
    // out is no longer needed - free it
    delete out;
}

// ---------------------------------------

