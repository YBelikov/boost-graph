#pragma once

class DefaultVisitor {
public:
	template<typename V, typename G>
	void discoverVertex(V, const G&){}

	template<typename E, typename G>
	void discoverEdge(E, const G&){ }

	template<typename E, typename G>
	void backEdge(E, const G&) {}

	template<typename E, typename G>
	void forwardOrCrossEdge(E, const G&) {}

	template<typename V, typename G>
	void finishVertex(V, const G&) {}

};