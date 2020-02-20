#pragma once
#include "./headers/CycleDetectionVisitor.h"
#include "./headers/algorithms/TopoSort.h"

template<typename Graph, typename ColorMap>
bool hasCycle(const Graph& g, ColorMap map) {
	bool hasCycle = false;
	CycleDetectionVisitor<Graph> vis(hasCycle);
	genericDFS(g, vis, map);
	return vis.doesGraphHasCycle();
}
