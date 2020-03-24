#pragma once
#include <boost/graph/depth_first_search.hpp>
using boost::default_dfs_visitor;

template<typename OutputIterator>
class BackEdgeRecorder : public default_dfs_visitor {

public: 
	BackEdgeRecorder(OutputIterator it) : m_out(it) {}
	template<typename Graph, typename Edge>
	void back_edge(Edge e, const Graph& g) {
		*m_out++ = e;
	}
private:
	OutputIterator m_out;
};

template<typename OutputIterator>
BackEdgeRecorder<OutputIterator> makeBackEdgeRecorder(OutputIterator out) {
	return BackEdgeRecorder<OutputIterator>(out);
}
