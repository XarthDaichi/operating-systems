#include <iostream>
#include <vector>
#include <stack>
#define vvi vector<vector<int>>

bool there_is_cycle(vvi graph) {
		stack<int> stk;
		bool visited[graph.size()];
		stk.push(0);
		while(!stk.empty()) {
			int tope = stk.top();
			stk.pop();
			if (visited[tope]) return 1;
			visited[tope] = 1;
			for (int v = 0; v < graph[tope]; v++) stk.push(graph[tope][v]);
		}
		return 0;
}

int main() {
	return 0;
}
