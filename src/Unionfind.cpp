#include<vector>

#include "Unionfind.hpp"

Unionfind::Unionfind(int n):N(n){
    par.resize(N);
    for(int i=0;i<N;i++)par[i]=i;
    size.resize(N,1);
}

void Unionfind::resize(int n){
    N=n;
    par.resize(N);
    for(int i=0;i<N;i++)par[i]=i;
    size.resize(N,1);
    return;
}

void Unionfind::size_incriment(){
    N++;
    par.push_back(par.size());
    size.push_back(1);
    return;
}

int Unionfind::root(int v){
    if(par[v]==v)return v;
    else return par[v]=root(par[v]);
}

bool Unionfind::same(int u,int v){
    int root_u=root(u);
    int root_v=root(v);
    return root_u==root_v;
}

int Unionfind::merge(int u,int v){

    int root_u=root(u);
    int root_v=root(v);

    if(root_u==root_v)return root_u;

    if(size[root_u]<size[root_v]){
        std::swap(u,v);
        std::swap(root_u,root_v);
    }

    par[root_v]=root_u;
    size[root_u]+=size[root_v];
    return root_u;
}
