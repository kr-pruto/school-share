
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "GraphAlgorithms.h"

// GraphAlgorithms::kruskalMST 구현(DisjointSet 클래스를 별도로 두지 않고 함수 내부에 통합)
MSTResult GraphAlgorithms::kruskalMST(const Graph& graph) {
	if (graph.isDirected()) {
		throw std::logic_error("MST is normally defined for undirected graphs.");
	}
	std::vector<Edge> edges = graph.edges(true);
	std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
		return a.weight < b.weight;
	});

	const int n = graph.vertexCount();
	std::vector<int> parent(n);
	std::vector<int> rank(n, 0);
	std::iota(parent.begin(), parent.end(), 0);

	MSTResult result;
	for (const Edge& e : edges) {
		// iterative find with simple path compression
		int a = e.from;
		while (parent[a] != a) {
			parent[a] = parent[parent[a]]; // compress one level
			a = parent[a];
		}
		int b = e.to;
		while (parent[b] != b) {
			parent[b] = parent[parent[b]];
			b = parent[b];
		}
		if (a == b)
			continue;

		// union by rank
		if (rank[a] < rank[b])
			std::swap(a, b);
		parent[b] = a;
		if (rank[a] == rank[b])
			++rank[a];

		result.edges.push_back(e);
		result.totalWeight += e.weight;
		if (static_cast<int>(result.edges.size()) == n - 1)
			break;
	}
	result.connected = static_cast<int>(result.edges.size()) == n - 1;
	return result;
}
