#pragma once

#include "Vertice.h"
#include "VerticeInfo.h"
#include "EdgeInfo.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

class AStarTools{

public:
	static float squaredDistance(const Vertice<VerticeInfo> * v1, const Vertice<VerticeInfo> * v2);
	static Edge<EdgeInfo, VerticeInfo> * createEdge(Vertice<VerticeInfo> *v1, Vertice<VerticeInfo> *v2, Graph<EdgeInfo, VerticeInfo> &graph, const EdgeInfo &eInfo);
	static void freeAllVertices(Graph<EdgeInfo, VerticeInfo> &graph);
	static float computeHeuristic(const Vertice<VerticeInfo> *v);
	static PElement< pair<Vertice<VerticeInfo>*, float> > * neighborsList(const Vertice<VerticeInfo> *v, const Graph<EdgeInfo, VerticeInfo> &graph);

	static Vertice<VerticeInfo> *father(const Vertice<VerticeInfo> * v);
	static Vertice<VerticeInfo> *&father(Vertice<VerticeInfo> * v);
	static int & state(Vertice<VerticeInfo> * v);
	static float & cost(Vertice<VerticeInfo> * v);
	static float & heuristic(Vertice<VerticeInfo> * v);
	static float globalCost(const Vertice<VerticeInfo> * v);
	static float & globalCost(Vertice<VerticeInfo> * v);

	static bool isFinal(const Vertice<VerticeInfo> * v);

	static Vertice<VerticeInfo> * target;
};

void freeAllVertices(Graph<EdgeInfo, VerticeInfo> & graph);
PElement< pair<Vertice<VerticeInfo>*, float> > * neighborsList(const Vertice<VerticeInfo> * v, const Graph<EdgeInfo, VerticeInfo> & graph);
Vertice<VerticeInfo> *  father(const Vertice<VerticeInfo> * v);
Vertice<VerticeInfo> * & father(Vertice<VerticeInfo> * v);
int & state(Vertice<VerticeInfo> * v);
float & cost(Vertice<VerticeInfo> * v);
float & heuristic(Vertice<VerticeInfo> * v);
float globalCost(const Vertice<VerticeInfo> * v);
float & globalCost(Vertice<VerticeInfo> * v);
bool isFinal(const Vertice<VerticeInfo> * v);

int pathLenght(const Vertice<VerticeInfo>* head);
const Vertice<VerticeInfo> * lastElement(const Vertice<VerticeInfo>* head);
Vertice<VerticeInfo> * penultimateElement(Vertice<VerticeInfo>* head);
