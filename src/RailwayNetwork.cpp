#include<string> 
#include<fstream>
#include<iostream>
#include<sstream>

using std::cout;
#include "RailwayNetwork.hpp"

RailwayNetwork::RailwayNetwork():uf(0){}

//connection.csvの読み取り


void RailwayNetwork::read_connection_csv(){


    std::string str_buf;
    std::ifstream ifs_station("data/connection.csv");

    if(!ifs_station){
        std::cout <<"csvファイルが開けません\n";
        exit(1);
    }

    ifs_station>>str_buf;
    //getline(ifs_station,str_buf);
    if(str_buf!="from,to,line,fare,time"){
        std::cout <<"ファイル名，またはファイルの中身が誤っています\n";
        exit(1);
    }

    
    
    
    std::string pre_str_buf=str_buf;
    while(true){
    
    //while(getline(ifs_station,str_buf)){
        ifs_station>>str_buf;if(str_buf==pre_str_buf)break;
        pre_str_buf=str_buf;
        //cout <<str_buf<<"\n";
        std::string str_comma_buf;
        std::istringstream str_buf_stream(str_buf);
        
        //str_bufをコンマ区切りで読む
        

        int current_station_index,next_station_index,line_index,fare,time;


        std::vector<int*> address={&current_station_index,&next_station_index,&line_index,&fare,&time};
        for(int i = 0; i < 5 ; i++){
            getline(str_buf_stream,str_comma_buf,',');
            //std::cout <<str_comma_buf<<' ';
            
            
            // iの値で分岐
            if (i <= 1){
                
                
                //初めて見る駅なら番号を付ける
                if(!station_to_index.count(str_comma_buf)){
                    station_to_index[str_comma_buf]=index_to_station.size();
                    index_to_station.push_back(str_comma_buf);

                    uf.size_incriment();
                    
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
               
                //運賃，または経由時間を保存
                *address[i]=std::stoi(str_comma_buf);

            }
        }
        
        
        graph.resize(index_to_station.size());
        graph[current_station_index].push_back(Rail{current_station_index,
                                                    next_station_index,
                                                    line_index,
                                                    fare,
                                                    time                });

        graph[next_station_index].push_back(Rail{next_station_index,
                                                    current_station_index,
                                                    line_index,
                                                    fare,
                                                    time});
       
        uf.merge(current_station_index,next_station_index);



        


        

    }
    
    
    return;
}


void RailwayNetwork::station_plan_input(int &start_index,int &goal_index,int &plan){
    
    //出発，到着駅名を入力した後，最短経路，最安賃金経路，最小乗り換え経路から選ぶ

    //出発，到着駅名を入力

    while(true){
        bool start_is_connected_to_goal=true;
        for(int i = 0; i < 2 ;i++){
            std::string cmd;

            while(true){
                switch(i){
                    case 0: std::cout <<"from>";
                            break;
                    case 1: std::cout <<"to>";
                            break;
                    
                    
                }
                
                
                if (!getline(std::cin,cmd) || cmd=="exit")exit(0); 
                
                //二つの駅の少なくともが存在しないなら中止して次の入力を待つ
                if (station_to_index.count(cmd)==false) {
                    std::cout <<cmd<<"は存在しない駅名です"<<"\n";

                    continue;
                }

                switch(i){
                    case 0: start_index=station_to_index[cmd];
                            break;
                    case 1: goal_index  =station_to_index[cmd];
                            break;
                }
                break;
            }
            
        }
            //二つの駅が経路でつながっていないなら中止して次の入力を待つ
        if(uf.same(start_index,goal_index)==false){


            std::cout<<index_to_station[start_index]<<"から";
            std::cout<<index_to_station[ goal_index]<<"にたどり着くことはできません"<<"\n";
            start_is_connected_to_goal=false;
        }

        if(start_is_connected_to_goal==false)continue;
        //最短経路，最安賃金経路，最小乗り換え経路から選ぶ
        //入力ミスがあったらやり直しをする
        std::string cmd;
        while(true){
            std::cout <<"最安運賃経路...0/最短経路...1>";
            if (!getline(std::cin,cmd) || cmd=="exit")exit(0);
            char c=cmd.at(0);

            if(cmd.size()>=2 || c<'0' || '2'<=c){
                std::cout <<"\n0,1のふたつからいずれか一つを入力してください\n";
                continue;
                
            }
            
            break;

        }

        plan=cmd.at(0)-'0';
        
        
            
        return;

    }
    
    
    

    


    
    
        

}
