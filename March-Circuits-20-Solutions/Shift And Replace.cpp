#include<bits/stdc++.h>
using namespace std;
 
const int MAXN = 110000;
int elem[MAXN];
int cost[MAXN];
 
class Cost {
public:
	Cost(int c, int i): cost(c), index(i) {}
	int cost, index;
	bool operator<(const Cost& another) const {
		return cost > another.cost;
	}
};
 
int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		// cost[i] = number of right cyclic shifts needed to bring position i to the beginning
		cost[i] = i + N;
	}
	for (int i = 0; i < N; i++) {
		cin >> elem[i];
		if (elem[i] >= 1 && elem[i] <= N) {
			// if an element is in [1, N] range it will help exactly any one array starting from position x in reducing cost by one,
			// x -> (i + 1 - elem[i] + N) % N
			cost[(i + 1 - elem[i] + N) % N]--;
		}
	}
	priority_queue<Cost> q;
	for (int i = 0; i < N; i++) {
		// put costs and starting positions in the queue that keeps least cost at the top
		q.emplace(cost[i], i);
	}
	int Q;
	cin >> Q;
	while (Q--) {
		int loc, newValue;
		cin >> loc >> newValue;
		loc--;
		if (elem[loc] != newValue) {
			if (elem[loc] >= 1 && elem[loc] <= N) {
				int pos = (loc - elem[loc] + N + 1) % N;
				cost[pos]++;
				q.emplace(cost[pos], pos);
			}
			if (newValue >= 1 && newValue <= N) {
				int pos = (loc - newValue + N + 1) % N;
				cost[pos]--;
				q.emplace(cost[pos], pos);
			}
			elem[loc] = newValue;
		}
		while (true) {
			Cost top = q.top();
			if (cost[top.index] != top.cost) {
				// need to pop the outdated values
				q.pop();
				continue;
			}
			cout << top.cost << endl;
			break;
		}
	}
}