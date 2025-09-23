#include <bits/stdc++.h>
using namespace std;
#define lli long long
#define nl <<"\n"
#define PI acos(-1.0)
#define pb push_back
#define vec2d(name,n,m,val) vector<vector<lli>>(name)((n),vector<lli>((m),(val)))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mem(a,b) memset(a,b,sizeof(a))
#define UNIQUE(a) (a).erase(unique(all(a)),(a).end())
#define l_b lower_bound
#define u_b upper_bound
#define F first
#define S second
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define Yes cout<<"Yes\n"
#define No cout<<"No\n"
#define ok cout<<"ok" nl
#define Case(t) cout<<"Case "<<t<<":\n"
#define setpre(n) fixed<<setprecision(n)
#define input(x) for(auto &i:x) cin>>i
#define print(x) for(auto &i:x) cout<<i<<" "; cout nl

void bfs(lli src, vector<lli>v_childs[], bool vis[], lli lvl[]) {
    vis[src]=1, lvl[src]=0;
    queue<lli>q;
    q.push(src);
    while(q.size()) {
        for(auto child:v_childs[q.front()]) {
            if(vis[child]==0) {
                q.push(child);
                vis[child]=1;
                lvl[child]=lvl[q.front()]+1;
            }
        }
        q.pop();
    }
}
signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, T=1; cin>>T;
    for(t=1; t<=T; t++) {
        lli n, m;
        cin>>n>>m;
        vector<lli>vc[n+1];
        for(lli i=0; i<m; i++) {
            lli u, v;
            cin>>u>>v;
            vc[u].pb(v);
            vc[v].pb(u);
        }
        bool vis[n+1]={0};
        lli lvl[n+1];
        bfs(1,vc,vis,lvl);
        for(lli i=1; i<=n; i++) cout<<i<<" "<<lvl[i] nl;
    }
    return 0;
}
