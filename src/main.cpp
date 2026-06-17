#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<array>

#include<iostream>
#include<string>
#include <fstream>
#include <sstream>
#include<algorithm>




#include "global_val.hpp"
#include "Unionfind.hpp"

#include "RailwayNetwork.hpp"
















//最短経路（または最安値の経路）をダイクストラ法で求めて，stack<Rail>で経路復元 
//memberはtimeとfareのどちらかを入れることを想定









using std::cout;

int main(){
    RailwayNetwork network;

    network.read_connection_csv();


    //出発地と到着地を入力
    while(true){

        int start_index,goal_index;

        bool start_is_connected_to_goal=true;
        int plan=-1;

        network.station_plan_input(start_index,goal_index,plan);

        
        
        int fare_ratio,time_ratio;
        if(start_is_connected_to_goal == true){
            switch (plan)
            {
            case 0: //最短経路
                fare_ratio=1,time_ratio=0;
                break;
            
            case 1:
                fare_ratio=0,time_ratio=1;
            }
        }
        network.dijkstra(start_index,goal_index,fare_ratio,time_ratio);

        network.route_output(start_index,goal_index,plan);
    }

    
    
    

}