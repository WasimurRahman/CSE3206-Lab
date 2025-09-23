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

lli spf[100001]; //handle 0, 1 seperately
void SPFsieve(lli n) {
    for(lli p=2; p<=n; p++) {
        if(spf[p]==0) {
            spf[p]=p;
            for(lli i=p*p; i<=n; i+=p) if(spf[i]==0) spf[i]=p;
        }
    }
}
signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t, T=1; //cin>>T;
    SPFsieve(100000);
    for(t=1; t<=T; t++) {
        //prime factorization of n;
        lli n=420;
        vector<pair<lli,lli>>prime_factors;
        while(n>1) {
            lli pr=spf[n];
            if(prime_factors.size()==0 || prime_factors.back().F!=pr) prime_factors.pb({pr,1});
            else prime_factors.back().S++;
            n/=pr;
        }
        for(auto x:prime_factors) cout<<x.F<<" "<<x.S nl;
    }
    return 0;
}
