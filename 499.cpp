#include <vector>
#include <iostream>
#include <queue>
#include <string>
using namespace std;


struct node{
    int x,y,d;
    string path;
    node(int x,int y,int d,string path):x(x),y(y),d(d),path(path){}
    bool operator<(const node&to)const{
        return(d==to.d) ? path>to.path : d>to.d; 
    }
};


struct cmp{
	bool operator()(node a, node b){
		return(a.d==b.d) ? a.path>b.path : a.d>b.d;
	}
};


class Solution{
private:
    static constexpr int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
    static constexpr char ds[4]={'r','d','l','u'};
public:
    string findShortestWay(vector<vector<int>>&maze,vector<int>&ball,vector<int>&hole) {

        //priority_queue<node, vector<node>> pq;
        priority_queue<node, vector<node>, cmp> pq;
        int r=maze.size(),c=maze[0].size();
        vector<vector<int>>dis(r,vector<int>(c,1e9));

        auto isHole=[&](int x,int y){return x==hole[0] && y==hole[1];};        
        auto canGoAhead =[&](int x,int y)->bool {return 0<=x && x<r && 0<=y && y<c && !maze[x][y];}; 

        pq.push(node(ball[0],ball[1],0,""));
        dis[ball[0]][ball[1]]=0;

        while(!pq.empty()){
            auto u=pq.top();
            pq.pop();

            if(isHole(u.x,u.y))return u.path;

            for(int i=0;i<4;i++){
                int new_x=u.x, new_y=u.y, new_d=u.d;
                string new_path=u.path+ds[i];

                while(canGoAhead(new_x+dx[i],new_y+dy[i])){
                    new_x+=dx[i],new_y+=dy[i],new_d++;
                    if(isHole(new_x,new_y))break;
                }

                if(new_d>u.d && new_d<=dis[new_x][new_y]){
                    pq.push(node(new_x,new_y,new_d,new_path));
                    dis[new_x][new_y]=new_d;
                }
            }
        }

        return "impossible";
    }
};
