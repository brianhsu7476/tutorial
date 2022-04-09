#include <bits/stdc++.h>
#define int long long
#define kN 200005
using namespace std;

int a[kN], n;
struct seg{
	int l, r, m, sum, mx, lz; seg *cl, *cr; bool lzt;
	seg(int _l, int _r):l(_l), r(_r), m(l+r>>1), lz(0), lzt(0){
		if(r-l>1)cl=new seg(l, m), cr=new seg(m, r), pull();
		else sum=mx=a[l];
	}
	void change(int plz, bool plzt){
		if(plzt)sum=plz*(r-l), mx=lz=plz, lzt=1;
		else lzt=lz?lzt:0, sum+=plz*(r-l), mx+=plz, lz+=plz;
	}
	void pull(){sum=cl->sum+cr->sum, mx=max(cl->mx, cr->mx);}
	void push(){if(r-l>1&&lz)cl->change(lz, lzt), cr->change(lz, lzt); lz=0;}
	bool to(int a, int b, int v){
		if(a<=l&&r<=b)change(v, 1);
		else push(), a<m&&cl->to(a, b, v), m<b&&cr->to(a, b, v), pull();
	}
	bool add(int a, int b, int v){
		if(a<=l&&r<=b)change(v, 0);
		else push(), a<m&&cl->add(a, b, v), m<b&&cr->add(a, b, v), pull();
	}
	int qsum(int a, int b){
		if(a<=l&&r<=b)return sum;
		int ans=0;
		push(), a<m&&(ans+=cl->qsum(a, b)), m<b&&(ans+=cr->qsum(a, b));
		return ans;
	}
	int qmx(int a, int b){
		if(a<=l&&r<=b)return mx;
		int ans=-1;
		push(), a<m&&(ans=max(ans, cl->qmx(a, b))), m<b&&(ans=max(ans, cr->qmx(a, b)));
		return ans;
	}
};

signed main(){
	int q; scanf("%lld%lld", &n, &q);
	for(int i=0; i<n; ++i)scanf("%lld", a+i);
	seg s(0, n);
	while(q--){
		int t, l, r; scanf("%lld%lld%lld", &t, &l, &r);
		switch(t){
			case 3: int v; scanf("%lld", &v), s.to(l-1, r, v); break;
			case 2: scanf("%lld", &v), s.add(l-1, r, v); break;
			case 0: printf("%lld\n", s.qsum(l-1, r)); break;
			case 1: printf("%lld\n", s.qmx(l-1, r)); break;
		}
	}
}
