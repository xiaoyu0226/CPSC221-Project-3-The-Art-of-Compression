/**
 *  @file imgtree-private.h
 *  @description student-defined functions for binary tree class storing image data for CPSC 221 PA3
 *  @author CPSC 221
 *
 *  SUBMIT THIS FILE TO PRAIRIELEARN, EVEN IF YOU DO NOT ADD ANYTHING TO IT
 * 
 *  Usage: As this file is included entirely into imgtree.h by the #include statement on line __
 *  you only need to write the function signature,
 *  e.g.
 *  void MyOwnSpecialFunction(int fave_num, ImgTreeNode* nd);
 * 
 *  and add/complete your implementation in imgtree.cpp
 */

 void RenderTree(PNG& img, ImgTreeNode* curr) const;

 void MirrorH(ImgTreeNode* curr);

 void MirrorV(ImgTreeNode* curr);

 unsigned int Count(ImgTreeNode* curr) const;

 void ClearNode(ImgTreeNode* curr);

ImgTreeNode* CopyNode(const ImgTreeNode* curr);

void PruneHelper(ImgTreeNode* curr, double pct, double tol);

unsigned int CountPct(ImgTreeNode* curr, ImgTreeNode* subRoot, double tol);

