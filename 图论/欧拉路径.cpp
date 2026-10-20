#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define up(i, a, b) for (int i = (a); i <= (b); ++i)
#define down(i, a, b) for (int i = (a); i >= (b); --i)
struct node{
    int v,id;
};
void solve(){
    int n,m;
	cin>>n>>m;
	vector<int>ind(n+1,0),head(n+1,0),vis(m+1,0);
    vector<int>ans;
    vector<vector<node>>f(n+1);
    up(i,1,m){
        int u,v;
        cin>>u>>v;
        f[u].push_back({v,i});
        ind[v]++;
        ind[u]--;
    }
    int rt=1;
    up(i,1,n)if(ind[i]==-1)rt=i;
    sort(ind.begin()+1,ind.end());
    bool ok=1;
    if(ind[1]==0)ok=0;
    if(ind[1]==-1&&ind[n]==1){
        ok=0;
        up(i,2,n-1)ok=(ind[i]!=0);
    }
    if(ok){cout<<"No"<<'\n';return ;}
    up(i,1,n)if(f[i].size()){
        sort(f[i].begin(),f[i].end(),[&](node a,node b){
            return a.v<b.v;
        });
    }
    auto dfs=[&](auto &&self,int u)->void{
        for(int &i=head[u];i<(ll)f[u].size();){
            node e=f[u][i++];
            if(!vis[e.id]){
                vis[e.id]=1;
                self(self,e.v);
            }
        }
        ans.push_back(u);
    };
    dfs(dfs,rt);
    reverse(ans.begin(),ans.end());
    for(auto ele:ans)cout<<ele<<" ";
}
//输出字典序最小的欧拉路径