#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX_V = 52;
const int INF = 1000000000;

// 간선 구조체
struct Edge {
	int to, c, f;
	Edge* dual; // 자신의 역방향 간선을 가리키는 포인터
	Edge() : Edge(-1, 0) {}
	Edge(int to1, int c1) : to(to1), c(c1), f(0), dual(nullptr) {}
	int spare() {
		return c - f;
	}
	void addFlow(int f1) { // 자신과 역방향 간선에 f1만큼의 플로우 값을 갱신
		f += f1;
		dual->f -= f1;
	}
};

inline int CtoI(char c) {
	if (c <= 'Z') return c - 'A';
	return c - 'a' + 26;
}

int main() {
	int N;
	vector<Edge*> adj[MAX_V]; // 존재하는 간선만을 인접 리스트로 저장
	// 간선 정보 입력받음
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		char u, v;
		int w;
		scanf(" %c %c %d", &u, &v, &w);
		u = CtoI(u); v = CtoI(v);
		Edge* e1 = new Edge(v, w), * e2 = new Edge(u, 0);
		e1->dual = e2;
		e2->dual = e1;
		adj[u].push_back(e1);
		adj[v].push_back(e2);
	}

	int total = 0, S = CtoI('A'), E = CtoI('Z');
	while (1) {
		int prev[MAX_V];
		Edge* path[MAX_V] = { 0 }; // 경로상의 간선들을 저장해두어 나중에 참조
		fill(prev, prev + MAX_V, -1);
		queue<int> Q;
		Q.push(S);
		while (!Q.empty() && prev[E] == -1) {
			int curr = Q.front();
			Q.pop();
			for (Edge* e : adj[curr]) {
				int next = e->to;
				if (e->spare() > 0 && prev[next] == -1) {
					Q.push(next);
					prev[next] = curr;
					path[next] = e;
					if (next == E) break;
				}
			}
		}
		if (prev[E] == -1) break;

		int flow = INF;
		for (int i = E; i != S; i = prev[i])
			flow = min(flow, path[i]->spare());
		for (int i = E; i != S; i = prev[i])
			path[i]->addFlow(flow);
		total += flow;
	}
	printf("%d\n", total);
}