#include "AStarTools.h"

Vertice<VerticeInfo>* AStarTools::target = NULL;

float AStarTools::squaredDistance(const Vertice<VerticeInfo>* v1, const Vertice<VerticeInfo>* v2){
	int deltaX = v2->value.info.pos.x - v1->value.info.pos.x;
	int deltaY = v2->value.info.pos.y - v1->value.info.pos.y;
	
	return deltaX*deltaX + deltaY*deltaY;
}

Edge<EdgeInfo, VerticeInfo>* AStarTools::
	createEdge(Vertice<VerticeInfo> *v1, Vertice<VerticeInfo>* v2, 
		Graph<EdgeInfo, VerticeInfo>& graph, const EdgeInfo &eInfo){
	return graph.createEdge(eInfo, v1, v2);
}

void AStarTools::freeAllVertices(Graph<EdgeInfo, VerticeInfo> &graph){
	PElement<Vertice<VerticeInfo>> *l;
	
	for (l = graph.lVertices; l; l = l->next){
		state(l->value) = AStarInfo::FREE;
		father(l->value) = NULL;
	}
}

float AStarTools::computeHeuristic(const Vertice<VerticeInfo>* v){
	return AStarTools::squaredDistance(v, AStarTools::target);
}

PElement<pair<Vertice<VerticeInfo>*, float>>* AStarTools::neighborsList(const Vertice<VerticeInfo>* v, const Graph<EdgeInfo, VerticeInfo>& graph){
	PElement< pair < Vertice<VerticeInfo> *, Edge<EdgeInfo, VerticeInfo> * > > * ladj, *lA;
	ladj = graph.adjacent(v);

	PElement< pair<Vertice<VerticeInfo>*, float> > * lVC;

	for (lA = ladj, lVC = NULL; lA; lA = lA->next)
		lVC = new PElement< pair<Vertice<VerticeInfo>*, float> >(new pair<Vertice<VerticeInfo>*, float>(lA->value->first, lA->value->second->value.distance), lVC);

	PElement< pair< Vertice<VerticeInfo> *, Edge<EdgeInfo, VerticeInfo> * > >::erasePointer(ladj);
	return lVC;
}

Vertice<VerticeInfo>* AStarTools::father(const Vertice<VerticeInfo>* v){
	return (Vertice<VerticeInfo>*)v->value.aStarInfo.father;
}

Vertice<VerticeInfo>*& AStarTools::father(Vertice<VerticeInfo>* v) {
	return (Vertice<VerticeInfo>*&)v->value.aStarInfo.father;
}

int & AStarTools::state(Vertice<VerticeInfo>* v){
	return v->value.aStarInfo.state;
}

float & AStarTools::cost(Vertice<VerticeInfo>* v){
	return v->value.aStarInfo.cost;
}

float & AStarTools::heuristic(Vertice<VerticeInfo>* v){
	return v->value.aStarInfo.heuristic;
}

float AStarTools::globalCost(const Vertice<VerticeInfo>* v) {
	return v->value.aStarInfo.globalCost;
}

float & AStarTools::globalCost(Vertice<VerticeInfo>* v){
	return v->value.aStarInfo.globalCost;
}

bool AStarTools::isFinal(const Vertice<VerticeInfo>* v){
	return v->value.info.pacmanIsHere;
}

void freeAllVertices(Graph<EdgeInfo, VerticeInfo>& graph){
	return AStarTools::freeAllVertices(graph);
}

PElement<pair<Vertice<VerticeInfo>*, float>>* neighborsList(const Vertice<VerticeInfo>* v, const Graph<EdgeInfo, VerticeInfo>& graph){
	return AStarTools::neighborsList(v, graph);
}

Vertice<VerticeInfo>* father(const Vertice<VerticeInfo>* v){
	return AStarTools::father(v);
}

Vertice<VerticeInfo> * & father(Vertice<VerticeInfo> * v) {
	return AStarTools::father(v);
}

int & state(Vertice<VerticeInfo>* v){
	return AStarTools::state(v);
}

float &cost(Vertice<VerticeInfo>* v){
	return AStarTools::cost(v);
}

float & heuristic(Vertice<VerticeInfo>* v){
	return AStarTools::heuristic(v);
}

float globalCost(const Vertice<VerticeInfo>* v){
	return AStarTools::globalCost(v);
}

float &globalCost(Vertice<VerticeInfo> *v) {
	return AStarTools::globalCost(v);
}

bool isFinal(const Vertice<VerticeInfo>* v){
	return AStarTools::isFinal(v);
}

int pathLenght(const Vertice<VerticeInfo>* head){
	if (!head)
		return 0;
	else
		return 1 + pathLenght(father(head));
}

const Vertice<VerticeInfo>* lastElement(const Vertice<VerticeInfo>* head){
	if (!head) return NULL;
	else
		if (father(head) == NULL)
			return head;
		else
			return lastElement(father(head));
}
