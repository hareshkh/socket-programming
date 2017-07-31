/*input
45000073000040004011b861c0a80001c0a800c7
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define pb push_back

string IP;

int hex_val(int pt)
{
	char c;
	int ans = 0;
	for(int i = 0; i<4; i++)
	{
		ans = ans*16;
		c = IP[pt+i];
		if(c>='0' && c<='9')
			ans += c - '0';
		else
			ans += c - 'a' + 10;
	}
	return ans;
}

void rev_hex(int val)
{
	int temp;
	vector<char> v;
	while(val>0)
	{
		temp = val%16;

		if(temp>9)
			v.pb((char)('a' + temp - 10));
		else
			v.pb('0'+temp);
		val = val/16;
	}
	for(int i = v.size()-1; i>=0; i--)
		cout << v[i];
	if(v.size()==0)
		cout << "0";
	cout << "\n";
	return;
}

int main()
{
	
	cin >> IP;
	int len = IP.size();
	int cnt = 0, val, temp = 0;
	int pt;
	for(int i = 0; i<len; i+=4)
	{
		cnt++;
		if(cnt==6)
		{
			val = hex_val(i);
			continue;
		}
		temp += hex_val(i);
	}
	while(temp>=(1<<16))
		temp = (temp%(1<<16)) + (temp>>16);
	temp = (1<<16) - 1 - temp;
	rev_hex(temp);

	return 0;
}