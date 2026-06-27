#pragma once



#include <map>
#include<unordered_map>
#include <string>
#include <vector>
#include <stack>
#include "Unionfind.hpp"




struct Rail{
    int from_index;
    int to_index;
    int line_index;
    int fare;
    int time;
    
};

struct RailwayNetwork{
    std::unordered_map<std::string,int> station_to_index;
    std::vector<std::string> index_to_station;

    std::unordered_map<std::string,int> line_to_index;
    std::vector<std::string> index_to_line;

    std::vector<std::vector<Rail>> graph;
    Unionfind uf;


    RailwayNetwork();

    void read_connection_csv();

    void station_plan_input(int &start_index,int &goal_index,int &plan);


    std::stack<Rail> dijkstra(const int start_index,const int goal_index,int fare_ratio,int time_ratio);

    
    void route_output(const int start_index,const int goal_index,int &plan,std::stack<Rail> &route_Rail);
};