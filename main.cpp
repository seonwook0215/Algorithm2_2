#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

int n, m, dfn;

vector<int> Edge[10000];
vector <int> Type[10000];
int Dfn[10000];
int L[10000];
int Cut[10000];

void dfs(int x, int p) {
	int i, s;
	Dfn[x] = ++dfn;
	s = Edge[x].size();
	for (i = 0; i < s; i++) {
		if (Edge[x][i] == p)
			Type[x][i] = 1;
		else if (Dfn[Edge[x][i]] == 0) {
			Type[x][i] = 2;
			dfs(Edge[x][i], x);
		}
		else
			Type[x][i] = 3;
	}
}

int dfs2(int x, int p)
{
	int i, s, rv,cc;
	L[x] = Dfn[x];
	s = Edge[x].size();
	for (i = 0; i < s; i++) {
		if (Type[x][i] == 1)
			;
		else if (Type[x][i] == 2) {
			rv = dfs2(Edge[x][i],x);
			L[x] = min(L[x], rv);
		}
		else
			L[x] = min(L[x], Dfn[Edge[x][i]]);
	}
	if (p == 0) {
		cc = 0;
		for (i = 0; i < s; i++)
			if (Type[x][i] == 2)
				cc++;
		if (cc > 1)
			Cut[x] = 1;
	}
	else {
		for (i = 0; i < s; i++) {
			if (Type[x][i] == 2) {
				if (L[Edge[x][i]] >= Dfn[x])
					Cut[x] = 1;
			}
		}
	}
	return L[x];
}

int main()
{
	int i, x, y;
	scanf("%d %d", &n, &m);
	for (i = 0; i < m; i++) {
		scanf("%d %d", &x, &y);
		Edge[x].push_back(y);
		Type[x].push_back(0);
		Edge[y].push_back(x);
		Type[y].push_back(0);
	}
	dfn = 0;
	dfs(1, 0);
	for (i = 1; i <= n; i++)
		if (Dfn[i] == 0)
			break;
	if (i <= n) {
		printf("Disconnected Graph!\n");
		exit(1);
	}
	dfs2(1,0);
	printf("Cut Vertices:");
	for (i = 1; i <= n; i++)
		if (Cut[i] == 1)
			printf(" %d", i);
	printf("\n");
	return 0;
}