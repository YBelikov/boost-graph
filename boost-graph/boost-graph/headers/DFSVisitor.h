#pragma once
#include <boost/graph/graph_traits.hpp>
#include "DefaultVisitor.h"

template <typename OutputIterator>

class DFSVisitor : public DefaultVisitor {
public:
	DFSVisitor(OutputIterator& order) : topoOrder{ order } {}

	template<typename Graph> 
	void finishVertex(typename boost::graph_traits<Graph>::vertex_descriptor u, const Graph&) {
		*--topoOrder = u;
	}
private:
	OutputIterator& topoOrder;
};