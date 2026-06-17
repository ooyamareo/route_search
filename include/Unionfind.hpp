#pragma once

#include<vector>

struct Unionfind{
  int N;
  std::vector<int> par,size;
  
  Unionfind(int n);

  void resize(int n);

  void size_incriment();
  
  int root(int v);
  
  bool same(int u,int v);
  
  int merge(int u,int v);
  
  
  
};