#include<vector>
#include<map>

#include<iostream>
#include<string>
# include <fstream>
# include <sstream>



std::map<std::string,int> station_to_index; //駅に番号をつける
std::vector<std::string>  index_to_station; //上のmapの逆写像

std::map<std::string,int> line_to_index; //路線に番号をつける
std::vector<std::string>  index_to_line; //上のmapの逆写像


//station.csvを読んで駅に番号を付ける


class Edge{
    
    int to_index;
    int line_index;
    int time;
    int fare;
    public:


    Edge(int to_index,int line_index,int time,int fare):to_index(to_index),line_index(line_index),time(time),fare(fare) {}
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
        
        graph[current_station_index].push_back(Edge{next_station_index,line_index,time,fare});

        graph[next_station_index].push_back(Edge{current_station_index,line_index,time,fare});
       



        


        

    }
    
    return;
}


void dijkstra(){

}




int main(){

    
    //read_station_csv();

    read_connection_csv();

    while(true){

        std::string cmd;
        std::cout <<"from>";
        if (!getline(std::cin, cmd)) {
            break; // EOF
        }

        if (cmd == "exit") {
            break;
        }

    }
    return 0; 
    
    

}