#include<vector>
#include<map>

#include<iostream>
#include<string>
# include <fstream>
# include <sstream>



std::map<std::string,int> station_to_index; //駅に番号をつける
std::vector<std::string>  index_to_station; //上のmapの逆写像

//station.csvを読んで駅に番号を付ける


class Edge{
    int to;
    int line;
    int time;
    int fare;
    Edge(int to,int line,int time,int fare):to(to),line(line),time(time),fare(fare) {}
};


std::vector<std::vector<Edge>> graph;


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
        

        int vertex,next_vertex,line,time,fare;
        std::vector<int*> address={&vertex,&next_vertex,&line,&time,&fare};

        for(int i = 0;i < 5; i++){

            getline(str_buf_stream,str_comma_buf){

                if(i <= 2)*address[i]=st

            }

        }



        


        

    }
    
    return;
}

int main(){

    read_station_csv();

    read_connection_csv();
    return 0; 
    
    

}