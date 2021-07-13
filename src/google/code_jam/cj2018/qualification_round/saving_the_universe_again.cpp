#include <bits/stdc++.h>

using namespace std;

long long count_damage(const string &s) {
    long long res = 0;
    long long p = 1;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'C') {
            p = min(p + p, inf);
        } else {
            res = min(res + p, inf);
        }
    }
    return res;
}

void solve(int test) {
    long long D;
    string P;
    cin >> D >> P;

    int len = P.size();
    int swaps = 0;
    
    while (true) {
        long long current = count_damage(P);
        if (current <= D) {
            break;
        }

        int index = -1;
        for (int i = len - 2; i >= 0; i--) {
            if (P[i] == 'C' && P[i + 1] == 'S') {
                index = i;
                break;
            }
        }
        if (index == -1) {
            break;
        }

        swap(P[index], P[index + 1]);
        swaps++;
    }

    if (count_damage(P) <= D) {
        printf("Case #%d: %d\n", test, swaps);
    } else {
        printf("Case #%d: IMPOSSIBLE\n", test);
    }
}

int main(int argc, char* argv[]) {
    
	int tests;
	cin >> tests;
	for (int i = 1; i <= tests; ++i) {
		solve(i);
	}
	return 0;
}