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







//dijkstra()で得た経路を出力する関数
void RailwayNetwork::route_output(int &start_index,int &goal_index,int &plan){
    
    
    std::cout <<"\n";
    
    
    
    //最低運賃経路の場合はfareで,最短経路の場合はtimeで探索するようにする
    
    
    int total_fare=0,total_time=0;

    
    
    //経路を文字列responseで出力する
    std::string response=index_to_station[start_index]+"\n";
    
    
    /*
    "route_Railのstackで最後に空の辺を追加"
    以下のwhile文では連続した部分の路線(continous_line_index)を保存し，
    それがroute_Rail.top().line_indexと異なるときに，responseに路線，運賃，時間を追加する
    最後の空の辺を追加しなければ，経路の最後の路線が復元されないため，空の辺を追加した．
    */

    while(route_Rail.top().line_index!=-1){
        
        Rail rail=route_Rail.top();
        route_Rail.pop();
        


        //路線名
        response+="|\n|--"+index_to_line[rail.line_index]+"(";
        rail.line_index=rail.line_index;

        //運賃
        response+=std::to_string(rail.fare)+"円"+",";
        total_fare+=rail.fare;
        rail.fare=0;
        
        //時間
        response+=std::to_string(rail.time)+"分)\n|\n";
        total_time+=rail.time;
        rail.time=0;

        //経由駅名
        response+=  index_to_station[rail.to_index]+"\n";
            //std::cout <<rail.to_index<<index_to_station[rail.to_index]<<"\n";
            

        
        rail.fare+=rail.fare;
        rail.time+=rail.time;
        
    

    }
    

    std::cout <<"\n";
    


    if(plan == 0)printf("最低運賃経路(%d円,%d分)\n",total_fare,total_time);
    if(plan == 1)printf("最短経路(%d円,%d分)\n",    total_fare,total_time);

    std::cout <<response<<"\n";

    
        
}



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