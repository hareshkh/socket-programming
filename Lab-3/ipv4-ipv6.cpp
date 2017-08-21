#include <bits/stdc++.h>
using namespace std;

//IPv4 mapped IPv6. 
//http://www.ipaddressguide.com/ipv4-to-ipv6

int main()
{
	string IPv4,IPv6;
	string base = "0123456789abcdef";
	IPv6 = "0:0:0:0:0:ffff:";
	cin>>IPv4;
	int b[4];
	int n = IPv4.size();
	int pos =0;
	for(int i=0;i<4;i++) b[i]=0;
	for(int i=0;i<n;i++)
	{
		if(IPv4[i]=='.') pos++;
		else b[pos] = b[pos]*10 + (int)(IPv4[i]-'0');
	}
	// for(int i=0;i<4;i++) cout<<b[i]<<" ";
	for(int i=0;i<4;i++)
	{
		if(i==2) IPv6 += ':';
		IPv6 = IPv6 + base[b[i]/16] + base[b[i]%16];
	}
	cout<<IPv6<<'\n';
}