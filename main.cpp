#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<array>

#include<iostream>
#include<string>
# include <fstream>
# include <sstream>

constexpr int INT_MAX=2147483647;

std::map<std::string,int> station_to_index; //駅に番号をつける
std::vector<std::string>  index_to_station; //上のmapの逆写像

std::map<std::string,int> line_to_index; //路線に番号をつける
std::vector<std::string>  index_to_line; //上のmapの逆写像

template<class T>inline void swap(T a,T b){
    T c=a;
    a=b;
    b=c;
    return ;

}
//station.csvを読んで駅に番号を付ける


class Edge{
    public:
    int from_index;
    int to_index;
    int line_index;
    int time;
    int fare;
    


    Edge(int from_index,int to_index,int line_index,int time,int fare):
    from_index(from_index),
    to_index(to_index),
    line_index(line_index),
    time(time),
    fare(fare) 
    {}
};



std::vector<std::vector<Edge>> graph;

/*
void read_station_csv(){
    std::string str_buf;
    std::ifstream ifs_station("~/route/station.csv");

    if(!ifs_station){
        std::cout <<"csvファイルが開けません\n";
        exit(0);
    }

    getline(ifs_station,str_buf);
    if(str_buf!="name"){
        std::cout <<"ファイル名，またはファイルの中身が誤っています\n";
        exit(0);
    }

    int index=0;


    while(getline(ifs_station,str_buf)){


        station_to_index[str_buf]=index;

        index_to_station.push_back(str_buf);

        index++;

        
    }
    
    graph.resize(index);

    return;


}

//*/

void read_connection_csv(){
    std::string str_buf;
    std::ifstream ifs_station("/home/yourname/connection.csv");

    if(!ifs_station){
        std::cout <<"csvファイルが開けません\n";
        exit(1);
    }

    getline(ifs_station,str_buf);
    if(str_buf!="from,to,line,time,fare"){
        std::cout <<"ファイル名，またはファイルの中身が誤っています\n";
        exit(1);
    }

    int index=0;


    while(getline(ifs_station,str_buf)){

        std::string str_comma_buf;
        std::istringstream str_buf_stream(str_buf);

        //str_bufをコンマ区切りで読む
        

        int current_station_index,next_station_index,line_index,time,fare;


        std::vector<int*> address={&current_station_index,&next_station_index,&line_index,&time,&fare};
        for(int i = 0; i < 5 ; i++){
            getline(str_buf_stream,str_comma_buf,',');


            // iの値で分岐
            if (i <= 1){
                
                
                //初めて見る駅なら番号を付ける
                if(!station_to_index.count(str_comma_buf)){
                    station_to_index[str_comma_buf]=index_to_station.size();
                    index_to_station.push_back(str_comma_buf);
                }

                //出発駅と到着駅のインデックスを保存
                *address[i]=station_to_index[str_comma_buf];
            }
            else if( i == 2){
                
                //初めて見る路線なら番号を付ける
                if(!line_to_index.count(str_comma_buf)){
                    line_to_index[str_comma_buf]=index_to_line.size();
                    index_to_line.push_back(str_comma_buf);
                }
                //路線のインデックスを保存
                *address[i]=line_to_index[str_comma_buf];

            }
            else{

                //運賃，または経由時間を保存
                *address[i]=std::stoi(str_comma_buf);

            }
        }
        graph.resize(index_to_station.size());
        
        graph[current_station_index].push_back(Edge{current_station_index,
                                                    next_station_index,
                                                    line_index,
                                                    time,
                                                    fare                });

        graph[next_station_index   ].push_back(Edge{next_station_index,
                                                    current_station_index,
                                                    line_index,
                                                    time,
                                                    fare});
       



        


        

    }
    
    return;
}


//最短経路（または最安値の経路）をダイクストラ法で求めて，stack<Edge>で経路復元 
//memberはfareとtimeのどちらかを入れることを想定
std::stack<Edge> dijkstra(int start_index,int goal_index,int Edge::* member){

    const int N=index_to_station.size();

    std::vector<int> dist(N,INT_MAX/2);

    std::priority_queue<int,std::vector<int>,std::greater<int>> pq;
    dist[start_index]=0;
    pq.push(start_index);

    while(!pq.empty()){
        int from_index=pq.top();
        pq.pop();
        for(auto edge:graph[from_index]){

            if(dist[edge.to_index]<=dist[edge.from_index]+edge.*member)continue;
            
            dist[edge.to_index]=dist[edge.from_index]+edge.*member;
            pq.push(edge.to_index);
        }
    }

    //goalまでたどり着けない場合は考えないものとする
    if(dist[goal_index]==INT_MAX/2)abort();

    //経路を復元するstack
    //route_station:経路上の駅のindexのみのstack;
    
    std::stack<int> route_station;route_station.push(goal_index);

    //route_Edge:経路上の辺のstack この関数の返り値
    std::stack<Edge> route_Edge;

    while(route_station.top()!=start_index){
        for(auto edge:graph[route_station.top()]){
            if(dist[edge.to_index]+edge.*member==dist[route_station.top()]){
                route_station.push(edge.to_index);
                //最短経路はstartからgoalで出力したいが，edgeはこのままだとfrom_indexとto_indexが逆になっている
                swap(edge.from_index,edge.to_index);
                route_Edge.push(edge);
                break;
            }
        }

    }
    return route_Edge;

}




int main(){

    
    //read_station_csv();

    read_connection_csv();

    while(true){


        int start_index,goal_index;
        for(int i = 0; i < 2 ;i++){
            std::string cmd;

            switch(i){
                case 0: std::cout <<"from>";
                        break;
                case 1: std::cout <<"to>";
                        break;
                
            }
            
            
            if (!getline(std::cin,cmd) || cmd=="exit")return 0; 
            
            if (station_to_index.count(cmd)==false) abort();
            

            switch(i){
                case 0: start_index=station_to_index[cmd];
                        break;
                case 1: goal_index  =station_to_index[cmd];
                        break;
            }
        }
        

        std::array member_array={&Edge::time,&Edge::fare};
        for(int i = 0; i < 2; i++){
            if(i == 0)std::cout <<"最短経路\n";
            if(i == 1)std::cout <<"最低運賃経路\n";
            
            auto member=member_array[i];

            std::stack<Edge> route_Edge=dijkstra(start_index,goal_index,member);
            while(!route_Edge.empty()){
                Edge edge=route_Edge.top();
                route_Edge.pop();
                std::cout <<index_to_station[edge.from_index] <<std::endl;

                std::cout <<"| "<<index_to_line[edge.line_index] <<"\n";
                std::cout <<"| "<<edge.*member <<"\n";


            }

            std::cout <<index_to_station[goal_index]<<std::endl;
            
        }
        
        return 0; 


    }

    
    
    

}