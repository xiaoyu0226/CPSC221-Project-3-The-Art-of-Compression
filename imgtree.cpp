/**
 *  @file imgtree.cpp
 *  @description implementation of a binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN
 */

#include "imgtree.h"
#include <queue>
// not necessary to include imgtree-private.h since it is already included in imgtree.h

    /**
     *  Default constructor creates an empty tree
     */
ImgTree::ImgTree() {
  // complete your implementation below
  root = NULL;
}

/**
 *  Parameterized constructor creates a tree from an input image.
 *  Every leaf in the tree corresponds to a single pixel in the PNG.
 *  Every non-leaf node corresponds to a rectangle of pixels defined
 *  by upper, left, lower, and right image coordinates. A node will
 *  also store the average color over its defined rectangle. Note that
 *  this average MUST be freshly computed from the individual pixels in
 *  the image and NOT by computing a weighted average from the colors
 *  of its direct children, as this would lead to an accumulation of
 *  rounding errors due to the integer nature of RGB color channels.
 *
 *  A non-leaf node's children correspond to a partition of the node's
 *  rectangle into two smaller rectangles, either by a horizontal line
 *  creating an upper rectangle and a lower rectangle, or a vertical line
 *  creating a left rectangle and a right rectangle.
 *
 *  The split is determined as follows:
 *  1. If the current node's rectangle width is the same or larger than its height,
 *     then a vertical line will divide the rectangle into left and right rectangles.
 *     If the current node's rectangle width is smaller than its height,
 *     then a horizontal line will divide the rectangle into upper and lower rectangles.
 *  2. The coordinate of the dividing line is chosen such that combined sum squared
 *     deviations from the mean color in the left/upper and right/lower rectangles is minimal
 *     among all other potential dividing lines of the same orientation.
 *     e.g. for a region (0,0) to (3,2), the candidates are the vertical lines dividing the region into:
 *     - (0,0) to (0,2) and (1,0) to (3,2)
 *     - (0,0) to (1,2) and (2,0) to (3,2)
 *     - (0,0) to (2,2) and (3,2) to (3,2)
 *     The line which produces the minimal combined sum squared scores on the left
 *     and right will be used for the split.
 *  3. In the unlikely event that multiple candidates produce the same score, the one which
 *     most evenly splits the rectangular area will be chosen.
 *  4. In the even more unlikely even that two candidates produce the same score and produce
 *     the same minimal area difference, the one with the smaller coordinate will be chosen.
 */
ImgTree::ImgTree(const PNG& img) {
  // complete your implementation below
  Stats s(img);

  root = BuildNode(s, 0, 0, img.height() - 1, img.width() - 1);
  imgwidth = img.width();
  imgheight = img.height();

}

/**
 *  Copy constructor creates a new tree that is structurally the same as the input tree and
 *  contains the same image data.
 *  @param other - the ImgTree to be copied
 */
ImgTree::ImgTree(const ImgTree& other) {
  // This implementation has already been completed for you
  Copy(other);
}

/**
 *  Overloaded assignment operator allows statements such as mytree_a = some_other_tree;
 *  Releases any existing memory and reconstructs this tree as a copy of other.
 *  @param rhs - the right hand side of the assignment statement
 */
ImgTree& ImgTree::operator=(const ImgTree& rhs) {
  // This implementation has already been completed for you
  if (this != &rhs) { // this and rhs are physically different trees in memory
    Clear(); // release any existing heap memory for this tree
    Copy(rhs);  // rebuild this tree as a copy of rhs
  }
  return *this;
}

/**
 *  Destructor releases any heap memory associated with this tree.
 */
ImgTree::~ImgTree() {
  // This implementation has already been completed for you
  Clear();



}

/**
 *  Releases all heap memory associated with this tree, restoring it to an "empty tree" state.
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::Clear() {
  // complete your implementation below
  ClearNode(root);
  
}

/**
 *  Copies the supplied parameter tree into this tree. Does not free any memory.
 *  Called by the copy constructor and operator=.
 *  Will be useful to define a recursive helper function for this.
 *  HINT: the helper should allocate a new node, and return a pointer to the allocated node.
 *        See the documention for BuildNode - this should work similarly.
 */
void ImgTree::Copy(const ImgTree& other) {
  // complete your implementation below
  imgwidth = other.imgwidth;
  imgheight = other.imgheight;
  this->root = CopyNode(other.root);


}

/**
 *  Recursive helper function for initial construction of the tree. Constructs a single
 *  node according to supplied Stats and the requirements specified by the constructor
 *  documentation, and returns a pointer to the completed node.
 *  @param s - populated Stats object for computing this node's attributes
 *  @param upr - y-coordinate of the upper edge of the node's rectangular region
 *  @param lft - x-coordinate of the left side of the node's rectangular region
 *  @param lwr - y-coordinate of the lower edge of the node's rectangular region
 *  @param rt - x-coordinate of the right side of the node's rectangular region
 *  @return - pointer to a (completed) newly-allocated node for the specified parameters.
 */
ImgTreeNode* ImgTree::BuildNode(Stats& s, unsigned int upr, unsigned int lft, unsigned int lwr, unsigned int rt) {
  // complete your implementation below
  ImgTreeNode* node;
  ImgTreeNode* lu;
  ImgTreeNode* rl;

  if (upr == lwr && lft == rt) {
    node = new ImgTreeNode(upr, lft, lwr, rt, s.GetAvg(upr, lft, lwr, rt));
    return node;
  }

  unsigned width = rt - lft + 1;
  unsigned height = lwr - upr + 1;

  if (width >= height) {
    double minsqd = 0.0;
    double minadiff = 0.0;
    unsigned coord = 0;
    for (unsigned i = lft; i < rt; i++) {
      double sqd = s.GetSumSqDev(upr, lft, lwr, i) + s.GetSumSqDev(upr, i + 1, lwr, rt);
      double adiff = ((i - lft + 1) - (rt - i)) * ((i - lft + 1) - (rt - i));
      if (i == lft) {
        minsqd = sqd;
        minadiff = adiff;
        coord = lft;
      } else {
        if (sqd < minsqd) {
          minsqd = sqd;
          minadiff = adiff;
          coord = i;
        } else if (sqd == minsqd) {
          if (adiff < minadiff) {
            minsqd = sqd;
            minadiff = adiff;
            coord = i;
          }
        }
      }
    }
    lu = BuildNode(s, upr, lft, lwr, coord);
    rl = BuildNode(s, upr, coord + 1, lwr, rt);
    node = new ImgTreeNode(upr, lft, lwr, rt, s.GetAvg(upr, lft, lwr, rt));
    node->A = lu;
    node->B = rl;
  } else {
    double minsqd = 0.0;
    double minadiff = 0.0;
    unsigned coord = 0;
    for (unsigned i = upr; i < lwr; i++) {
      double sqd = s.GetSumSqDev(upr, lft, i, rt) + s.GetSumSqDev(i + 1, lft, lwr, rt);
      double adiff = ((i - upr + 1) - (lwr - i)) * ((i - upr + 1) - (lwr - i));
      if (i == upr) {
        minsqd = sqd;
        minadiff = adiff;
        coord = upr;
      } else {
        if (sqd < minsqd) {
          minsqd = sqd;
          minadiff = adiff;
          coord = i;
        } else if (sqd == minsqd) {
          if (adiff < minadiff) {
            minsqd = sqd;
            minadiff = adiff;
            coord = i;
          }
        }
      }
    }
    lu = BuildNode(s, upr, lft, coord, rt);
    rl = BuildNode(s, coord + 1, lft, lwr, rt);
    node = new ImgTreeNode(upr, lft, lwr, rt, s.GetAvg(upr, lft, lwr, rt));
    node->A = lu;
    node->B = rl;
  }
  return node; // REPLACE THIS STUB
}

/**
 *  Produces a PNG of appropriate dimensions and paints every leaf node's rectangle
 *  into the appropriate area of the PNG.
 *  May be called on pruned trees.
 *  @return fully-colored PNG, painted from the tree's leaf node data
 */
 
PNG ImgTree::Render() const {
  // complete your implementation below
  PNG img(imgwidth, imgheight);

  RenderTree(img, root);
  return img; // REPLACE THIS STUB
}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped horizontally when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipHorizontal() {
  // complete your implementation below
  MirrorH(root);

}

/**
 *  Rearranges a tree's internal pointers and node content so that its image data
 *  appears flipped vertically when rendered.
 *  Beware that the tree may or may not have been pruned!
 *  Will be useful to define a recursive helper function for this.
 */
void ImgTree::FlipVertical() {
  // complete your implementation below
  MirrorV(root);

}

/**
 *  Trims subtrees as high as possible in the tree.
 *  A subtree is pruned (all decendants deallocated and child links set to null)
 *  if at least pct (out of 100) of its leaves are within tol of the average
 *  color in the subtree's root.
 *  Assume that this will only be called on trees which have not previously been pruned.
 *  Will be useful to define AT LEAST one recursive helper function for this.
 *  @pre pct is a valid value between 0 and 100
 *  @param pct percentage (out of 100) of leaf node descendants must be within the tolerance threshold
 *             of color difference in order to be pruned
 *  @param tol threshold color difference to qualify for pruning
 */
void ImgTree::Prune(double pct, double tol) {
  // complete your implementation below
  PruneHelper(root, pct, tol);
}

/**
 *  Counts the number of leaf nodes in the tree.
 *  Will be useful to define a recursive helper function for this.
 */
unsigned int ImgTree::CountLeaves() const {
  // complete your implementation below
  return Count(root); // REPLACE THIS STUB
}

/**
 *  ADD YOUR PRIVATE FUNCTION IMPLEMENTATIONS BELOW
 */
 // helper function
void ImgTree::RenderTree(PNG& img, ImgTreeNode* curr) const {
  if (curr == NULL) {
    return;
  }

  if (curr->A == NULL && curr->B == NULL) {
    for (unsigned i = curr->left; i <= curr->right; i++) {
      for (unsigned j = curr->upper; j <= curr->lower; j++) {
          RGBAPixel* pixel = img.getPixel(i, j);
          pixel->r = curr->avg.r;
          pixel->g = curr->avg.g;
          pixel->b = curr->avg.b;
          pixel->a = curr->avg.a;
      }
    }
  } 

  RenderTree(img, curr->A);
  RenderTree(img, curr->B);
 }

 void ImgTree::MirrorH(ImgTreeNode* curr) {
    if (curr == NULL) {
      return;
    }

    MirrorH(curr->A);
    MirrorH(curr->B);

    unsigned diff = curr->right - curr->left;

    if (curr->A == NULL && curr->B == NULL) {
      curr->right = imgwidth - 1 - curr->left;
      curr->left = curr->right - diff;
    }

 }

  void ImgTree::MirrorV(ImgTreeNode* curr) {
    if (curr == NULL) {
      return;
    }

    MirrorV(curr->A);
    MirrorV(curr->B);

    unsigned diff = curr->lower - curr->upper;

    if (curr->A == NULL && curr->B == NULL) {
      curr->lower = imgheight - 1 - curr->upper;
      curr->upper = curr->lower - diff;
    }
 } 

 unsigned int ImgTree::Count(ImgTreeNode* curr) const {
  if (curr == NULL) {
    return 0;
  }

  if (curr->A == NULL && curr->B == NULL) {
    return 1;
  }

  return Count(curr->A) + Count(curr->B);
 }

 void ImgTree::ClearNode(ImgTreeNode* curr) {
  if (curr == NULL) {
    return;
  }
  ClearNode(curr->A);
  ClearNode(curr->B);

  delete curr;
  curr = NULL;
 }

 ImgTreeNode* ImgTree::CopyNode(const ImgTreeNode* curr) {
  if (curr == NULL) {
    return NULL;
  }

  ImgTreeNode* node = new ImgTreeNode(curr->upper, curr->left, curr->lower, curr->right, curr->avg);
  node->A = CopyNode(curr->A);
  node->B = CopyNode(curr->B);

  return node;
 }

 unsigned int ImgTree::CountPct(ImgTreeNode* curr, ImgTreeNode* subRoot, double tol) {
  if (curr == NULL) {
    return 0;
  }
  
  if (curr->A == NULL && curr->B == NULL) {
    if (subRoot->avg.dist(curr->avg) <= tol) {
      return 1;
    }
  }

  return CountPct(curr->A, subRoot, tol) + CountPct(curr->B, subRoot, tol);
 }


 void ImgTree::PruneHelper(ImgTreeNode* curr, double pct, double tol) {
  if (curr == NULL) {
    return;
  }

  double leaves = (double) Count(curr);
  double pctLeaves = (double) CountPct(curr, curr, tol);

  if ((pctLeaves / leaves) * 100.0 >= pct) {
    ClearNode(curr->A);
    ClearNode(curr->B);
    curr->A = NULL;
    curr->B = NULL;
  }

  PruneHelper(curr->A, pct, tol);
  PruneHelper(curr->B, pct, tol);
 } 