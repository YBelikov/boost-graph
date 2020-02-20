#pragma once
#include "./headers/CycleDetectionVisitor.h"
#include "./headers/algorithms/TopoSort.h"

template<typename Graph>
bool hasCycle(const Graph& g) {
	bool hasCycle = false;
	CycleDetectionVisitor vis(hasCycle);
	genericDFS(g, vis);
}
