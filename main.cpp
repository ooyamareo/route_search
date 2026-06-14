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

template<class T>inline void swap(T &a,T &b){
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
    int fare;
    int time;
    


    Edge(int from_index,int to_index,int line_index,int fare,int time):
    from_index(from_index),
    to_index(to_index),
    line_index(line_index),
    fare(fare),
    time(time) 
    {}
};



std::vector<std::vector<Edge>> graph;



void read_connection_csv(){
    std::string str_buf;
    std::ifstream ifs_station("/home/delta2197/route/connection.csv");

    if(!ifs_station){
        std::cout <<"csvファイルが開けません\n";
        exit(1);
    }

    getline(ifs_station,str_buf);
    if(str_buf!="from,to,line,fare,time"){
        std::cout <<"ファイル名，またはファイルの中身が誤っています\n";
        exit(1);
    }

    int index=0;


    while(getline(ifs_station,str_buf)){

        std::string str_comma_buf;
        std::istringstream str_buf_stream(str_buf);

        //str_bufをコンマ区切りで読む
        

        int current_station_index,next_station_index,line_index,fare,time;


        std::vector<int*> address={&current_station_index,&next_station_index,&line_index,&fare,&time};
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
                }std::string response;
                //路線のインデックスを保存
                *address[i]=line_to_index[str_comma_buf];

            }
            else{
                //std::cout <<str_comma_buf<<' ';
                //運賃，または経由時間を保存
                *address[i]=std::stoi(str_comma_buf);

            }
        }
        graph.resize(index_to_station.size());
        
        graph[current_station_index].push_back(Edge{current_station_index,
                                                    next_station_index,
                                                    line_index,
                                                    fare,
                                                    time                });

        graph[next_station_index   ].push_back(Edge{next_station_index,
                                                    current_station_index,
                                                    line_index,
                                                    fare,
                                                    time});
       



        


        

    }
    
    return;
}


//最短経路（または最安値の経路）をダイクストラ法で求めて，stack<Edge>で経路復元 
//memberはtimeとfareのどちらかを入れることを想定
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

    //See "route_Edgeのstackで最後に空の辺を追加"
    route_Edge.push(Edge{goal_index,-1,-1,-1,-1});


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


using std::cout;

int main(){

    
    

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
            
            if (station_to_index.count(cmd)==false) {
                std::cout <<cmd<<"\n";
                return 0;
            }

            switch(i){
                case 0: start_index=station_to_index[cmd];
                        break;
                case 1: goal_index  =station_to_index[cmd];
                        break;
            }
        }
        std::cout <<"\n";
        
        
        std::array member_array={&Edge::fare,&Edge::time};

        
        for(int i = 0; i < 2; i++){
            int total_fare=0,total_time=0;
            std::string response;
            
            auto member=member_array[i];
            
            
            std::stack<Edge> route_Edge=dijkstra(start_index,goal_index,member);

            
            int continous_line_index=route_Edge.top().line_index;
            int continous_sum_fare=0,continous_sum_time=0;
            
            response+=index_to_station[start_index]+"\n";
          
            
            /*
            "route_Edgeのstackで最後に空の辺を追加"
            以下のwhile文では連続した部分の路線(continous_line_index)を保存し，それがroute_Edge.top()と異なるとき
            responseに路線，運賃，時間を追加する構図
            最後の空の辺を追加しなければ，経路の最後の路線が復元されないため，空の辺を追加した．
            */

            while(!route_Edge.empty()){
                
                Edge edge=route_Edge.top();
                route_Edge.pop();
                
                if(continous_line_index != edge.line_index){
                    
                    
                    


                    //路線名
                    response+="|\n|--"+index_to_line[continous_line_index]+"(";
                    continous_line_index=edge.line_index;

                    //運賃
                    response+=std::to_string(continous_sum_fare)+"円"+",";
                    total_fare+=continous_sum_fare;
                    continous_sum_fare=0;
                    
                    //時間
                    response+=std::to_string(continous_sum_time)+"分)\n|\n";
                    total_time+=continous_sum_time;
                    continous_sum_time=0;

                    //経由駅名
                    response+=  index_to_station[edge.from_index]+"\n";
                   
                    

                }
                continous_sum_fare+=edge.fare;
                continous_sum_time+=edge.time;
                
            

            }
            

            cout <<"\n";
            


            if(i == 0)printf("最低運賃経路(%d円,%d分)\n",total_fare,total_time);
            if(i == 1)printf("最短経路(%d円,%d分)\n",    total_fare,total_time);

            std::cout <<response<<"\n";

        }
        
        


    }

    
    
    

}