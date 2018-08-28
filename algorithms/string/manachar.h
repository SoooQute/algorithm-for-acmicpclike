#pragma once
#include "stdafx.h"
using namespace std;
class Manachar {
public:
	string str;
	vector<int> p;
	int mx, id;
	//type=0 任意 type=1 奇数 type=2 偶数
	pair<int, int> run(string s, int type) {
		int n = s.length();
		pair<int, int> range(-1, -1);
		int ans = 0;
		str = "$#";
		for (int i = 0; i < n; i++) {
			str += s[i];
			str += '#';
		}
		n = str.length();
		str += "@";
		id = mx = 0;
		p.resize(n << 1);
		for (int i = 1; i < n; i++) {
			if (i < mx) p[i] = min(p[2 * id - i], mx - i);
			else p[i] = 1;
			while (str[i - p[i]] == str[i + p[i]]) p[i]++;
			if (mx < i + p[i]) {
				id = i;
				mx = i + p[i];
			}
			if (type == 1 && i % 2 == 1) continue;
			if (type == 2 && i % 2 == 0) continue;
			if (p[i] - 1 > ans) {
				ans = p[i] - 1;
				int l = i - p[i] + 1, r = i + p[i] - 1;
				if (l % 2 == 1) l++;
				if (r % 2 == 1) r--;
				l = (l - 2) / 2, r = (r - 2) / 2;
				range.first = l, range.second = r;
			}
		}
		return range;
	}
};