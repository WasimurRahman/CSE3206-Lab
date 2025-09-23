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

//Segment Tree
//arrsize n, treesize 4*n; node (tree) 0 based, low-high (arr: 0 to n-1) 0 based.
int invalid=-1; //changeable.        //**Set int=long long, if needed.**//
int operation(int v1, int v2) {
    return max(v1,v2); //changable
}
void build(int node, int low, int high, int arr[], int tree[]) {
    if(low==high) tree[node]=arr[low];
    else{
        int m=low+(high-low)/2;
        build(node*2+1, low, m, arr, tree);
        build(node*2+2, m+1, high, arr, tree);
        tree[node]=operation(tree[node*2+1],tree[node*2+2]);
    }
}
void update(int node, int low, int high, int i, int newval, int arr[], int tree[]) {
    if(low==high && low==i) {
        tree[node]=newval;
        arr[low]=newval; //changing in the main array.
    }
    else if(low<=i && i<=high) {
        int m=low+(high-low)/2;
        update(node*2+1, low, m, i, newval, arr, tree);
        update(node*2+2, m+1, high, i, newval, arr, tree);
        tree[node]=operation(tree[node*2+1],tree[node*2+2]);
    }
}
int query(int node, int low, int high, int i, int j, int tree[]) {
    if(j<low || high<i) return invalid;
    if(i<=low && high<=j) return tree[node];
    int m=low+(high-low)/2;
    int p1=query(node*2+1, low, m, i, j, tree), p2=query(node*2+2, m+1, high, i, j, tree);
    return operation(p1,p2);
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, T=1; cin>>T;
    for(t=1; t<=T; t++) {
        int n, q;
        cin>>n>>q;
        int a[n], tree[4*n]; input(a);
        build(0,0,n-1,a,tree);
        while(q--) {
            int type;
            cin>>type;
            if(type==1) {
                int id, val;
                cin>>id>>val;
                update(0,0,n-1,id,val,a,tree); //0-based indexing;
            }
            else{
                int l, r;
                cin>>l>>r;
                cout<<query(0,0,n-1,l,r,tree) nl;
            }
        }
    }
    return 0;
}
