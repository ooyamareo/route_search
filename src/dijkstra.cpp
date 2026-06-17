#include "RailwayNetwork.hpp"
#include<stack>
#include<queue>

#include"global_val.hpp"

void RailwayNetwork::dijkstra(int &start_index,int &goal_index,
                                          double fare_ratio,double time_ratio){
    

    const int N=index_to_station.size();

    std::vector<double> dist(N,INT_MAX/2);

    struct node{
        int vertex;
        double distance;
        bool operator<(const node &other)const{
            
            return distance<other.distance;
        }

        bool operator>(const node &other)const{
            
            return distance>other.distance;
        }

        node(int v=0,double d=0):vertex(v),distance(d) {}
    };  

    std::priority_queue<node,std::vector<node>,std::greater<node>> pq;
    dist[start_index]=0;
    pq.push(node{start_index,(double)0});

    while(!pq.empty()){
        int from_index=pq.top().vertex;
        pq.pop();
        for(auto rail:graph[from_index]){
            
            double next_distance=fare_ratio*rail.fare+time_ratio*rail.time;
            if(dist[rail.to_index]<=dist[rail.from_index]+next_distance)continue;
            
            dist[rail.to_index]=dist[rail.from_index]+next_distance;
            pq.push({rail.to_index,dist[rail.to_index]});
        }
    }

    //goalまでたどり着けない場合は考えないものとする
    if(dist[goal_index]==INT_MAX/2)abort();

    //経路を復元するstack
    //route_station:経路上の駅のindexのみのstack;
    
    std::stack<int> route_station;route_station.push(goal_index);

    //route_Rail:経路上の辺のstack この関数の返り値
    

    //See "route_Railのstackで最後に空の辺を追加"
    route_Rail.push(Rail{goal_index,-1,-1,-1,-1});


    while(route_station.top()!=start_index){
        for(auto rail:graph[route_station.top()]){

            double pre_distance=fare_ratio*rail.fare+time_ratio*rail.time;
            if(dist[rail.to_index]+pre_distance==dist[route_station.top()]){
                route_station.push(rail.to_index);

                //最短経路はstartからgoalで出力したいが，
                //railはこのままだとfrom_indexとto_indexが逆になっているので，swap

                std::swap(rail.from_index,rail.to_index);

                
                //同じ路線を一つにまとめる
                if(rail.line_index==route_Rail.top().line_index){
                    Rail next_rail=route_Rail.top();
                    route_Rail.pop();
                    rail.to_index=next_rail.to_index;
                    rail.fare+=next_rail.fare;
                    rail.time+=next_rail.time;
                }
                route_Rail.push(rail);
                break;
            }
        }

    }
    
}

