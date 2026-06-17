#pragma once



#include <map>
#include <string>
#include <vector>
#include <stack>
#include "Unionfind.hpp"




class Rail{
    public:
    int from_index;
    int to_index;
    int line_index;
    int fare;
    int time;
    
};

struct RailwayNetwork{
    std::map<std::string,int> station_to_index;
    std::vector<std::string> index_to_station;

    std::map<std::string,int> line_to_index;
    std::vector<std::string> index_to_line;

    std::vector<std::vector<Rail>> graph;
    Unionfind uf;

    std::stack<Rail> route_Rail;

    RailwayNetwork();

    void read_connection_csv();

    void station_plan_input(int &start_index,int &goal_index,int &plan);


    void dijkstra(int &start_index,int &goal_index,double fare_ratio,double time_ratio);

    
    void route_output(int &start_index,int &goal_index,int &plan);
};