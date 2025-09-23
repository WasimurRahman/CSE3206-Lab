//Tested

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

lli n, q, bucket, result=0, TM, LOG; //bucket=sqrt(2*n)+1;
lli a[200001], ans[200001], st[200001], en[200001], depth[200001], freq[200001], TtoN[400005], anc[200001][21];
bool checked[200001];
vector<lli>g[200001];
vector<pair<pair<lli,lli>,lli>>que; //{{u,v},id}
//1-based graph; lli LOG=log2(n)+1; vector<vector<lli>>anc(n+1, vector<lli>(LOG+1,-1));
void dfss(lli nd, lli par) {
    anc[nd][0]=par, TtoN[TM]=nd, st[nd]=TM++;
    depth[nd]=(par==-1?0:depth[par]+1);
    for(lli c:g[nd]) if(c!=par) dfss(c,nd);
    TtoN[TM]=nd, en[nd]=TM++;
}
void preprocess() {
    dfss(1,-1); //assuming 1 as root;
    for(lli j=1; j<LOG; j++) for(lli i=1; i<=n; i++) if(anc[i][j-1]!=-1) anc[i][j]=anc[anc[i][j-1]][j-1];
}
lli LCA(lli x, lli y) {
    if(depth[x]<depth[y]) swap(x,y);
    for(lli i=LOG; i>=0; i--) if(((depth[x]-depth[y])&(1LL<<i))) x=anc[x][i];
    if(x==y) return x;
    for(lli i=LOG; i>=0; i--) if(anc[x][i]!=anc[y][i]) x=anc[x][i], y=anc[y][i];
    return anc[x][0];
}
bool comp(pair<pair<lli,lli>,lli>&a, pair<pair<lli,lli>,lli>&b) {
    lli block_a=a.F.F/bucket, block_b=b.F.F/bucket;
    if(block_a!=block_b) return block_a<block_b;
    return (block_a&1)?(a.F.S>b.F.S):(a.F.S<b.F.S);
}
void add(lli node) {
    if(freq[a[node]]++==0) result++;
}
void rem(lli node) {
    if(--freq[a[node]]==0) result--;
}
void operation(lli node) {
    if(!checked[node]) add(node);
    else rem(node);
    checked[node]^=1;
}
void runMOs() {
    sort(all(que),comp); //q={{L-1,R-1},id}; if given L,R is 1-based.
    lli l=0, r=-1;
    result=0;
    for(auto q:que) {
        while(l>q.F.F) operation(TtoN[--l]);
        while(r<q.F.S) operation(TtoN[++r]);
        while(l<q.F.F) operation(TtoN[l++]);
        while(r>q.F.S) operation(TtoN[r--]);
        //extra modification
        lli u=TtoN[l], v=TtoN[r], lc=LCA(u,v);
        if(lc!=u && lc!= v) operation(lc); //take care of the lca separately
        ans[q.S]=result;
        if(lc!=u && lc!=v) operation(lc);
    }
}
map<lli,lli>mp;
void compress() {
    vector<lli>tmp_vc;
    for(lli i=0; i<n; i++) tmp_vc.pb(a[i]);
    sort(all(tmp_vc));
    UNIQUE(tmp_vc);
    for(lli i=0; i<(lli)tmp_vc.size(); i++) mp[tmp_vc[i]]=i;
    for(lli i=0; i<n; i++) a[i]=mp[a[i]];
}
void CLEAR() {
    for(lli i=0; i<=n; i++) {
        g[i].clear();
        checked[i]=0, freq[i]=0;
        for(lli j=0; j<=LOG; j++) anc[i][j]=-1;
    }
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, T=1; //cin>>T;
    for(t=1; t<=T; t++) {
        cin>>n>>q;
        for(lli i=0; i<n; i++) cin>>a[i]; //compress if necessary.
        compress();
        CLEAR();
        for(lli i=0; i<n-1; i++) {
            lli x, y;
            cin>>x>>y;
            g[x].pb(y);
            g[y].pb(x);
        }
        TM=0, LOG=log2(n)+1;
        preprocess();
        for(lli i=0; i<q; i++) {
            lli u, v;
            cin>>u>>v;
            if(st[u]>st[v]) swap(u,v);
            lli lc=LCA(u,v);
            if(lc==u) que.pb({{st[u],st[v]},i});
            else que.pb({{en[u],st[v]},i});
        }
        sort(all(que),comp);
        runMOs();
        for(lli i=0; i<q; i++) cout<<ans[i] nl;
    }
    return 0;
}

// https://www.spoj.com/problems/COT2/
