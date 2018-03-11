#pragma once

#include "World.h"

using namespace std;
const float HEAT_DECAY = 0.001f;

int main(){
	try {
		//initialisation
		sf::RenderWindow  window(sf::VideoMode(1024,1024), "PacMan", sf::Style::Titlebar | sf::Style::Close);
		WorldToScreen transform(sf::Vector2<float>(-1.0f, 15.0f), sf::Vector2<float>(13.0f, -1.0f), sf::Vector2<float>(0.0f, 0.0f), sf::Vector2<float>(1024.0f, 1024.0f));
		sf::Font font;
		if (!font.loadFromFile("arial.ttf")) {
			throw Error("Can't load arial.ttf");
		}

#pragma region Graph

		Graph<EdgeInfo, VerticeInfo> graph;
		vector<Vertice<VerticeInfo>*> vertices;
		
		//Line 0
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 0))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 0))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 0))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 0))));

		//Line 1
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 1))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 1))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 1))));

		//Line 2
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 2))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 2))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 2))));
		
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 2))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 2))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 2))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 2))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 2))));

		//Line 3
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 3))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 3))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 3))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 3))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 3))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 3))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 3))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 3))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 3))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 3))));

		//Line 4
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 4))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 4))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 4))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 4))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 4))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 4))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 4))));

		//Line 5
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 5))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 5))));

		//Line 6
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 6))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 6))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 6))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 6))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 6))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 6))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 6))));

		//Line 7
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 7))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 7))));

		//Line 8
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 8))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 8))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 8))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 8))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 8))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 8))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 8))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 8))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 8))));

		//Line 9
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 9))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 9))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 9))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 9))));

		//Line 10
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 10))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 10))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 10))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 10))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 10))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 10))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 10))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 10))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 10))));

		//Line 11
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(0, 11))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 11))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 11))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 11))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 11))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 11))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 11))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(12, 11))));

		//Line 12
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(1, 12))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 12))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 12))));
		
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(11, 12))));

		//Line 13
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(2, 13))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 13))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(4, 13))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(6, 13))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(8, 13))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 13))));
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(10, 13))));

		//Line 14
		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(3, 14))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(5, 14))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(7, 14))));

		vertices.push_back(graph.createVertice(Informations(sf::Vector2<int>(9, 14))));
		
		vector<Edge<EdgeInfo, VerticeInfo>*> edges;
		
		EdgeInfo e(0, 1, 1.0f);

		//1 East West
		edges.push_back(graph.createEdge(e, vertices[0], vertices[1]));
		edges.push_back(graph.createEdge(e, vertices[1], vertices[2]));
		edges.push_back(graph.createEdge(e, vertices[2], vertices[3]));

		edges.push_back(graph.createEdge(e, vertices[4], vertices[5]));
		edges.push_back(graph.createEdge(e, vertices[5], vertices[6]));

		edges.push_back(graph.createEdge(e, vertices[7], vertices[8]));
		edges.push_back(graph.createEdge(e, vertices[8], vertices[9]));
		edges.push_back(graph.createEdge(e, vertices[9], vertices[10]));

		edges.push_back(graph.createEdge(e, vertices[12], vertices[13]));
		edges.push_back(graph.createEdge(e, vertices[13], vertices[14]));
		edges.push_back(graph.createEdge(e, vertices[14], vertices[15]));
		edges.push_back(graph.createEdge(e, vertices[15], vertices[16]));

		edges.push_back(graph.createEdge(e, vertices[17], vertices[18]));
		edges.push_back(graph.createEdge(e, vertices[18], vertices[19]));
		edges.push_back(graph.createEdge(e, vertices[19], vertices[20]));
		edges.push_back(graph.createEdge(e, vertices[20], vertices[21]));

		edges.push_back(graph.createEdge(e, vertices[31], vertices[32]));
		edges.push_back(graph.createEdge(e, vertices[32], vertices[33]));

		edges.push_back(graph.createEdge(e, vertices[38], vertices[39]));
		edges.push_back(graph.createEdge(e, vertices[39], vertices[40]));

		edges.push_back(graph.createEdge(e, vertices[43], vertices[44]));
		edges.push_back(graph.createEdge(e, vertices[44], vertices[45]));
		
		edges.push_back(graph.createEdge(e, vertices[48], vertices[49]));
		edges.push_back(graph.createEdge(e, vertices[49], vertices[50]));
		edges.push_back(graph.createEdge(e, vertices[50], vertices[51]));

		edges.push_back(graph.createEdge(e, vertices[55], vertices[56]));
		edges.push_back(graph.createEdge(e, vertices[56], vertices[57]));
		edges.push_back(graph.createEdge(e, vertices[57], vertices[58]));

		edges.push_back(graph.createEdge(e, vertices[60], vertices[61]));
		edges.push_back(graph.createEdge(e, vertices[61], vertices[62]));
		edges.push_back(graph.createEdge(e, vertices[62], vertices[63]));
		edges.push_back(graph.createEdge(e, vertices[63], vertices[64]));

		edges.push_back(graph.createEdge(e, vertices[66], vertices[67]));
		edges.push_back(graph.createEdge(e, vertices[67], vertices[68]));
		edges.push_back(graph.createEdge(e, vertices[68], vertices[69]));
		edges.push_back(graph.createEdge(e, vertices[69], vertices[70]));

		edges.push_back(graph.createEdge(e, vertices[74], vertices[75]));
		edges.push_back(graph.createEdge(e, vertices[75], vertices[76]));
		edges.push_back(graph.createEdge(e, vertices[76], vertices[77]));
		edges.push_back(graph.createEdge(e, vertices[77], vertices[78]));

		edges.push_back(graph.createEdge(e, vertices[82], vertices[83]));
		edges.push_back(graph.createEdge(e, vertices[83], vertices[84]));

		edges.push_back(graph.createEdge(e, vertices[88], vertices[89]));
		edges.push_back(graph.createEdge(e, vertices[89], vertices[90]));

		edges.push_back(graph.createEdge(e, vertices[96], vertices[97]));
		edges.push_back(graph.createEdge(e, vertices[97], vertices[98]));

		edges.push_back(graph.createEdge(e, vertices[102], vertices[103]));
		edges.push_back(graph.createEdge(e, vertices[103], vertices[104]));

		edges.push_back(graph.createEdge(e, vertices[117], vertices[118]));
		edges.push_back(graph.createEdge(e, vertices[118], vertices[119]));
		edges.push_back(graph.createEdge(e, vertices[119], vertices[120]));
		edges.push_back(graph.createEdge(e, vertices[120], vertices[121]));
		edges.push_back(graph.createEdge(e, vertices[121], vertices[122]));
		edges.push_back(graph.createEdge(e, vertices[122], vertices[123]));


		// 2  North - East  South - West
		e.direction = 2;
		
		edges.push_back(graph.createEdge(e, vertices[0], vertices[12]));
		edges.push_back(graph.createEdge(e, vertices[25], vertices[34]));
		edges.push_back(graph.createEdge(e, vertices[28], vertices[38]));
		edges.push_back(graph.createEdge(e, vertices[33], vertices[42]));
		edges.push_back(graph.createEdge(e, vertices[34], vertices[43]));
		edges.push_back(graph.createEdge(e, vertices[42], vertices[51]));
		edges.push_back(graph.createEdge(e, vertices[44], vertices[54]));
		edges.push_back(graph.createEdge(e, vertices[45], vertices[55]));
		edges.push_back(graph.createEdge(e, vertices[52], vertices[62]));
		edges.push_back(graph.createEdge(e, vertices[54], vertices[64]));
		edges.push_back(graph.createEdge(e, vertices[60], vertices[71]));
		edges.push_back(graph.createEdge(e, vertices[62], vertices[73]));
		edges.push_back(graph.createEdge(e, vertices[65], vertices[78]));
		edges.push_back(graph.createEdge(e, vertices[68], vertices[81]));
		edges.push_back(graph.createEdge(e, vertices[70], vertices[82]));
		edges.push_back(graph.createEdge(e, vertices[71], vertices[83]));
		edges.push_back(graph.createEdge(e, vertices[81], vertices[91]));
		edges.push_back(graph.createEdge(e, vertices[82], vertices[93]));
		edges.push_back(graph.createEdge(e, vertices[88], vertices[100]));
		edges.push_back(graph.createEdge(e, vertices[90], vertices[101]));
		edges.push_back(graph.createEdge(e, vertices[91], vertices[102]));
		edges.push_back(graph.createEdge(e, vertices[93], vertices[104]));
		edges.push_back(graph.createEdge(e, vertices[100], vertices[109]));
		edges.push_back(graph.createEdge(e, vertices[101], vertices[110]));
		edges.push_back(graph.createEdge(e, vertices[108], vertices[116]));
		edges.push_back(graph.createEdge(e, vertices[109], vertices[117]));
		edges.push_back(graph.createEdge(e, vertices[110], vertices[119]));
		edges.push_back(graph.createEdge(e, vertices[116], vertices[125]));
		edges.push_back(graph.createEdge(e, vertices[125], vertices[132]));
		edges.push_back(graph.createEdge(e, vertices[127], vertices[133]));
		edges.push_back(graph.createEdge(e, vertices[128], vertices[134]));
		edges.push_back(graph.createEdge(e, vertices[129], vertices[135]));
		
		// 3 North South
		e.direction = 3;

		edges.push_back(graph.createEdge(e, vertices[0], vertices[11]));
		edges.push_back(graph.createEdge(e, vertices[3], vertices[14]));
		edges.push_back(graph.createEdge(e, vertices[4], vertices[16]));
		edges.push_back(graph.createEdge(e, vertices[6], vertices[17]));
		edges.push_back(graph.createEdge(e, vertices[7], vertices[19]));
		edges.push_back(graph.createEdge(e, vertices[10], vertices[22]));

		edges.push_back(graph.createEdge(e, vertices[11], vertices[23]));
		edges.push_back(graph.createEdge(e, vertices[12], vertices[24]));
		edges.push_back(graph.createEdge(e, vertices[14], vertices[25]));
		edges.push_back(graph.createEdge(e, vertices[16], vertices[26]));
		edges.push_back(graph.createEdge(e, vertices[17], vertices[27]));
		edges.push_back(graph.createEdge(e, vertices[19], vertices[28]));
		edges.push_back(graph.createEdge(e, vertices[21], vertices[29]));
		edges.push_back(graph.createEdge(e, vertices[22], vertices[30]));

		edges.push_back(graph.createEdge(e, vertices[23], vertices[31]));
		edges.push_back(graph.createEdge(e, vertices[24], vertices[32]));
		edges.push_back(graph.createEdge(e, vertices[26], vertices[35]));
		edges.push_back(graph.createEdge(e, vertices[27], vertices[36]));
		edges.push_back(graph.createEdge(e, vertices[29], vertices[39]));
		edges.push_back(graph.createEdge(e, vertices[30], vertices[40]));

		edges.push_back(graph.createEdge(e, vertices[32], vertices[41]));
		edges.push_back(graph.createEdge(e, vertices[35], vertices[43]));
		edges.push_back(graph.createEdge(e, vertices[36], vertices[45]));
		edges.push_back(graph.createEdge(e, vertices[39], vertices[47]));

		edges.push_back(graph.createEdge(e, vertices[41], vertices[48]));
		edges.push_back(graph.createEdge(e, vertices[44], vertices[53]));
		edges.push_back(graph.createEdge(e, vertices[47], vertices[58]));
		
		edges.push_back(graph.createEdge(e, vertices[48], vertices[59]));
		edges.push_back(graph.createEdge(e, vertices[51], vertices[60]));
		edges.push_back(graph.createEdge(e, vertices[53], vertices[62]));
		edges.push_back(graph.createEdge(e, vertices[55], vertices[64]));
		edges.push_back(graph.createEdge(e, vertices[58], vertices[65]));

		edges.push_back(graph.createEdge(e, vertices[60], vertices[70]));
		edges.push_back(graph.createEdge(e, vertices[62], vertices[72]));
		edges.push_back(graph.createEdge(e, vertices[64], vertices[74]));

		edges.push_back(graph.createEdge(e, vertices[66], vertices[79]));
		edges.push_back(graph.createEdge(e, vertices[68], vertices[80]));
		edges.push_back(graph.createEdge(e, vertices[72], vertices[83]));
		edges.push_back(graph.createEdge(e, vertices[76], vertices[86]));
		edges.push_back(graph.createEdge(e, vertices[78], vertices[87]));

		edges.push_back(graph.createEdge(e, vertices[79], vertices[88]));
		edges.push_back(graph.createEdge(e, vertices[80], vertices[90]));
		edges.push_back(graph.createEdge(e, vertices[82], vertices[92]));
		edges.push_back(graph.createEdge(e, vertices[84], vertices[94]));
		edges.push_back(graph.createEdge(e, vertices[86], vertices[96]));
		edges.push_back(graph.createEdge(e, vertices[87], vertices[98]));

		edges.push_back(graph.createEdge(e, vertices[88], vertices[99]));
		edges.push_back(graph.createEdge(e, vertices[92], vertices[102]));
		edges.push_back(graph.createEdge(e, vertices[94], vertices[104]));
		edges.push_back(graph.createEdge(e, vertices[98], vertices[107]));

		edges.push_back(graph.createEdge(e, vertices[99], vertices[108]));
		edges.push_back(graph.createEdge(e, vertices[102], vertices[111]));
		edges.push_back(graph.createEdge(e, vertices[104], vertices[112]));
		edges.push_back(graph.createEdge(e, vertices[107], vertices[115]));

		edges.push_back(graph.createEdge(e, vertices[111], vertices[119]));
		edges.push_back(graph.createEdge(e, vertices[112], vertices[121]));

		edges.push_back(graph.createEdge(e, vertices[117], vertices[126]));
		edges.push_back(graph.createEdge(e, vertices[123], vertices[130]));

		edges.push_back(graph.createEdge(e, vertices[126], vertices[132]));
		edges.push_back(graph.createEdge(e, vertices[130], vertices[135]));
		
		// 4 North - West South - East
		e.direction = 4;

		edges.push_back(graph.createEdge(e, vertices[10], vertices[21]));
		edges.push_back(graph.createEdge(e, vertices[25], vertices[33]));
		edges.push_back(graph.createEdge(e, vertices[28], vertices[37]));
		edges.push_back(graph.createEdge(e, vertices[37], vertices[45]));
		edges.push_back(graph.createEdge(e, vertices[38], vertices[46]));
		edges.push_back(graph.createEdge(e, vertices[43], vertices[51]));
		edges.push_back(graph.createEdge(e, vertices[44], vertices[52]));
		edges.push_back(graph.createEdge(e, vertices[46], vertices[55]));
		edges.push_back(graph.createEdge(e, vertices[52], vertices[60]));
		edges.push_back(graph.createEdge(e, vertices[54], vertices[62]));
		edges.push_back(graph.createEdge(e, vertices[59], vertices[66]));
		edges.push_back(graph.createEdge(e, vertices[62], vertices[71]));
		edges.push_back(graph.createEdge(e, vertices[64], vertices[73]));
		edges.push_back(graph.createEdge(e, vertices[73], vertices[83]));
		edges.push_back(graph.createEdge(e, vertices[74], vertices[84]));
		edges.push_back(graph.createEdge(e, vertices[76], vertices[85]));
		edges.push_back(graph.createEdge(e, vertices[84], vertices[93]));
		edges.push_back(graph.createEdge(e, vertices[85], vertices[95]));
		edges.push_back(graph.createEdge(e, vertices[93], vertices[102]));
		edges.push_back(graph.createEdge(e, vertices[95], vertices[104]));
		edges.push_back(graph.createEdge(e, vertices[96], vertices[105]));
		edges.push_back(graph.createEdge(e, vertices[98], vertices[106]));
		edges.push_back(graph.createEdge(e, vertices[105], vertices[113]));
		edges.push_back(graph.createEdge(e, vertices[106], vertices[114]));
		edges.push_back(graph.createEdge(e, vertices[113], vertices[121]));
		edges.push_back(graph.createEdge(e, vertices[114], vertices[123]));
		edges.push_back(graph.createEdge(e, vertices[115], vertices[124]));
		edges.push_back(graph.createEdge(e, vertices[124], vertices[131]));
		edges.push_back(graph.createEdge(e, vertices[127], vertices[132]));
		edges.push_back(graph.createEdge(e, vertices[128], vertices[133]));
		edges.push_back(graph.createEdge(e, vertices[129], vertices[134]));
		edges.push_back(graph.createEdge(e, vertices[131], vertices[135]));





		
		sf::Texture graphTexture;
		if (!graphTexture.loadFromFile("sprites\\tileset.png")) {
			throw Error("can't load tileset.png");
		}		
		
		sf::Sprite graphSprite;
		graphSprite.setTexture(graphTexture);
		graphSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		//Vertice
		Animation verticeNoPacgom(0.5f);
		verticeNoPacgom.addFrame(sf::IntRect(0, 0, 32, 32));
		
		//Edge
		Animation edgeHorizontalNoPacgom(0.5f);
		edgeHorizontalNoPacgom.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation edgeHorizontalWithPacgom(0.5f);
		edgeHorizontalWithPacgom.addFrame(sf::IntRect(32, 32, 32, 32));
		edgeHorizontalWithPacgom.addFrame(sf::IntRect(32, 64, 32, 32));

		Animation edgeTopRightNoPacgom(0.5f);
		edgeTopRightNoPacgom.addFrame(sf::IntRect(64, 0, 32, 32));

		Animation edgeTopRightWithPacgom(0.5f);
		edgeTopRightWithPacgom.addFrame(sf::IntRect(64, 32, 32, 32));
		edgeTopRightWithPacgom.addFrame(sf::IntRect(64, 64, 32, 32));

		Animation edgeVerticalNoPacgom(0.5f);
		edgeVerticalNoPacgom.addFrame(sf::IntRect(96, 0, 32, 32));

		Animation edgeVerticalWithPacgom(0.5f);
		edgeVerticalWithPacgom.addFrame(sf::IntRect(96, 32, 32, 32));
		edgeVerticalWithPacgom.addFrame(sf::IntRect(96, 64, 32, 32));

		Animation edgeTopLeftNoPacgom(0.5f);
		edgeTopLeftNoPacgom.addFrame(sf::IntRect(128, 0, 32, 32));

		Animation edgeTopLeftWithPacgom(0.5f);
		edgeTopLeftWithPacgom.addFrame(sf::IntRect(128, 32, 32, 32));
		edgeTopLeftWithPacgom.addFrame(sf::IntRect(128, 64, 32, 32));
		
		Animator graphAnimator(&graphSprite);
		graphAnimator.addAnimation("VerticeNoPacgom", &verticeNoPacgom);
		
		graphAnimator.addAnimation("EdgeHorizontalNoPacgom", &edgeHorizontalNoPacgom);
		graphAnimator.addAnimation("EdgeTopRightNoPacgom", &edgeTopRightNoPacgom);
		graphAnimator.addAnimation("EdgeVerticalNoPacgom", &edgeVerticalNoPacgom);
		graphAnimator.addAnimation("EdgeTopLeftNoPacgom", &edgeTopLeftNoPacgom);

		graphAnimator.addAnimation("EdgeHorizontalPacgom", &edgeHorizontalWithPacgom);
		graphAnimator.addAnimation("EdgeTopRightPacgom", &edgeTopRightWithPacgom);
		graphAnimator.addAnimation("EdgeVerticalPacgom", &edgeVerticalWithPacgom);
		graphAnimator.addAnimation("EdgeTopLeftPacgom", &edgeTopLeftWithPacgom);		

		DrawGraph<EdgeInfo, VerticeInfo> drawGraph(&window, &graphAnimator, &graphTexture, transform);
		
#pragma endregion
		
#pragma region pacman
		sf::Texture texturePackman;
		if (!texturePackman.loadFromFile("sprites\\Packman.png")) {
			throw Error("Can't load Packman.png");
		}

		sf::Sprite pacmanSprite;
		pacmanSprite.setTexture(texturePackman);
		pacmanSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));

		Animation pacmanWalkLeft(0.166666667f);
		pacmanWalkLeft.addFrame(sf::IntRect(0, 0, 32, 32));
		pacmanWalkLeft.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation pacmanWalkRight(0.166666667f);
		pacmanWalkRight.addFrame(sf::IntRect(64, 0, 32, 32));
		pacmanWalkRight.addFrame(sf::IntRect(96, 0, 32, 32));

		Animation pacmanWalkUp(0.166666667f);
		pacmanWalkUp.addFrame(sf::IntRect(128, 0, 32, 32));
		pacmanWalkUp.addFrame(sf::IntRect(160, 0, 32, 32));

		Animation pacmanWalkDown(0.166666667f);
		pacmanWalkDown.addFrame(sf::IntRect(192, 0, 32, 32));
		pacmanWalkDown.addFrame(sf::IntRect(224, 0, 32, 32));

		Animation pacmanWalkUpLeft(0.166666667f);
		pacmanWalkUpLeft.addFrame(sf::IntRect(0, 32, 32, 32));
		pacmanWalkUpLeft.addFrame(sf::IntRect(32, 32, 32, 32));

		Animation pacmanWalkUpRight(0.166666667f);
		pacmanWalkUpRight.addFrame(sf::IntRect(64, 32, 32, 32));
		pacmanWalkUpRight.addFrame(sf::IntRect(96, 32, 32, 32));

		Animation pacmanWalkDownRight(0.166666667f);
		pacmanWalkDownRight.addFrame(sf::IntRect(128, 32, 32, 32));
		pacmanWalkDownRight.addFrame(sf::IntRect(160, 32, 32, 32));

		Animation pacmanWalkDownLeft(0.166666667f);
		pacmanWalkDownLeft.addFrame(sf::IntRect(192, 32, 32, 32));
		pacmanWalkDownLeft.addFrame(sf::IntRect(224, 32, 32, 32));

		Animation pacmanStandStill(0.45f);
		pacmanStandStill.addFrame(sf::IntRect(0, 0, 32, 32));
		pacmanStandStill.addFrame(sf::IntRect(64, 0, 32, 32));

		Animation pacmanExplode(0.1f, false);
		pacmanExplode.addFrame(sf::IntRect(0, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(32, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(64, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(96, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(128, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(160, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(192, 64, 32, 32));
		pacmanExplode.addFrame(sf::IntRect(224, 64, 32, 32));

		Animator pacManAnimator(&pacmanSprite);

		pacManAnimator.addAnimation("walkLeft", &pacmanWalkLeft);
		pacManAnimator.addAnimation("walkRight", &pacmanWalkRight);
		pacManAnimator.addAnimation("walkUp", &pacmanWalkUp);
		pacManAnimator.addAnimation("walkDown", &pacmanWalkDown);
		pacManAnimator.addAnimation("walkDownLeft", &pacmanWalkDownLeft);
		pacManAnimator.addAnimation("walkDownRight", &pacmanWalkDownRight);
		pacManAnimator.addAnimation("walkUpLeft", &pacmanWalkUpLeft);
		pacManAnimator.addAnimation("walkUpRight", &pacmanWalkUpRight);
		pacManAnimator.addAnimation("standStill", &pacmanStandStill);
		pacManAnimator.addAnimation("explode", &pacmanExplode);

		pacManAnimator.setCurentAnimation("standStill");

		PacmanInfo pacmanInfo;

		GCharacter<VerticeInfo, EdgeInfo, PacmanInfo> pacmanGChar(pacmanInfo, &graph, vertices[44]);
		vertices[44]->value.info.pacmanIsHere = true;

		DrawCharacter<VerticeInfo, EdgeInfo, PacmanInfo>  drawCharPacman(&window, &pacmanSprite, &pacManAnimator, transform, &font);

		PacmanBehavior<VerticeInfo, EdgeInfo, PacmanInfo> pacmanBehavior;

		Actor<
			GCharacter<VerticeInfo, EdgeInfo, PacmanInfo>,
			PacmanBehavior<VerticeInfo, EdgeInfo, PacmanInfo>,
			DrawCharacter<VerticeInfo, EdgeInfo, PacmanInfo>
		> pacman(&pacmanGChar, &pacmanBehavior, &drawCharPacman);

#pragma endregion

#pragma region fantom1
		sf::Texture fantomTexture;

		if (!fantomTexture.loadFromFile("sprites\\fantom.png")) {
			throw Error("Can't load fantom.png");
		}

		sf::Sprite fantomSprite;
		fantomSprite.setTexture(fantomTexture);

		Animation fantomWalkLeft(0.166666667f);
		fantomWalkLeft.addFrame(sf::IntRect(0, 0, 32, 32));
		fantomWalkLeft.addFrame(sf::IntRect(32, 0, 32, 32));

		Animation fantomWalkRight(0.166666667f);
		fantomWalkRight.addFrame(sf::IntRect(64, 0, 32, 32));
		fantomWalkRight.addFrame(sf::IntRect(96, 0, 32, 32));

		Animation fantomWalkUp(0.166666667f);
		fantomWalkUp.addFrame(sf::IntRect(128, 0, 32, 32));
		fantomWalkUp.addFrame(sf::IntRect(160, 0, 32, 32));

		Animation fantomWalkDown(0.166666667f);
		fantomWalkDown.addFrame(sf::IntRect(192, 0, 32, 32));
		fantomWalkDown.addFrame(sf::IntRect(224, 0, 32, 32));

		Animation fantomWalkUpLeft(0.166666667f);
		fantomWalkUpLeft.addFrame(sf::IntRect(0, 32, 32, 32));
		fantomWalkUpLeft.addFrame(sf::IntRect(32, 32, 32, 32));

		Animation fantomWalkUpRight(0.166666667f);
		fantomWalkUpRight.addFrame(sf::IntRect(64, 32, 32, 32));
		fantomWalkUpRight.addFrame(sf::IntRect(96, 32, 32, 32));

		Animation fantomWalkDownRight(0.166666667f);
		fantomWalkDownRight.addFrame(sf::IntRect(128, 32, 32, 32));
		fantomWalkDownRight.addFrame(sf::IntRect(160, 32, 32, 32));

		Animation fantomWalkDownLeft(0.166666667f);
		fantomWalkDownLeft.addFrame(sf::IntRect(192, 32, 32, 32));
		fantomWalkDownLeft.addFrame(sf::IntRect(224, 32, 32, 32));

		Animation fantomStandStill(0.45f);
		fantomStandStill.addFrame(sf::IntRect(0, 0, 32, 32));
		fantomStandStill.addFrame(sf::IntRect(64, 0, 32, 32));

		Animator fantomAnimator(&fantomSprite);
		fantomAnimator.addAnimation("walkLeft", &fantomWalkLeft);
		fantomAnimator.addAnimation("walkRight", &fantomWalkRight);
		fantomAnimator.addAnimation("walkUp", &fantomWalkUp);
		fantomAnimator.addAnimation("walkDown", &fantomWalkDown);
		fantomAnimator.addAnimation("walkDownLeft", &fantomWalkDownLeft);
		fantomAnimator.addAnimation("walkDownRight", &fantomWalkDownRight);
		fantomAnimator.addAnimation("walkUpLeft", &fantomWalkUpLeft);
		fantomAnimator.addAnimation("walkUpRight", &fantomWalkUpRight);
		fantomAnimator.addAnimation("standStill", &fantomStandStill);

		fantomAnimator.setCurentAnimation("standStill");


		FantomInfo fantomInfo;

		GCharacter<VerticeInfo, EdgeInfo, FantomInfo> fantomGchar(fantomInfo, &graph, vertices[0]);
		
		DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>  drawCharFantom(&window, &fantomSprite, &fantomAnimator, transform, &font);

		FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo> fantomBehavior(FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::random);

		Actor<
			GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
			FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
			DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
		> fantom(&fantomGchar, &fantomBehavior, &drawCharFantom);

#pragma endregion

#pragma region fantom2

		sf::Sprite fantom2Sprite;
		fantom2Sprite.setTexture(fantomTexture);

		Animation fantom2WalkLeft(0.333333334f);
		fantom2WalkLeft.addFrame(sf::IntRect(0, 64, 32, 32));
		fantom2WalkLeft.addFrame(sf::IntRect(32, 64, 32, 32));

		Animation fantom2WalkRight(0.333333334f);
		fantom2WalkRight.addFrame(sf::IntRect(64, 64, 32, 32));
		fantom2WalkRight.addFrame(sf::IntRect(96, 64, 32, 32));

		Animation fantom2WalkUp(0.333333334f);
		fantom2WalkUp.addFrame(sf::IntRect(128, 64, 32, 32));
		fantom2WalkUp.addFrame(sf::IntRect(160, 64, 32, 32));

		Animation fantom2WalkDown(0.333333334f);
		fantom2WalkDown.addFrame(sf::IntRect(192, 64, 32, 32));
		fantom2WalkDown.addFrame(sf::IntRect(224, 64, 32, 32));

		Animation fantom2WalkUpLeft(0.333333334f);
		fantom2WalkUpLeft.addFrame(sf::IntRect(0, 96, 32, 32));
		fantom2WalkUpLeft.addFrame(sf::IntRect(32, 96, 32, 32));

		Animation fantom2WalkUpRight(0.333333334f);
		fantom2WalkUpRight.addFrame(sf::IntRect(64, 96, 32, 32));
		fantom2WalkUpRight.addFrame(sf::IntRect(96, 96, 32, 32));

		Animation fantom2WalkDownRight(0.333333334f);
		fantom2WalkDownRight.addFrame(sf::IntRect(128, 96, 32, 32));
		fantom2WalkDownRight.addFrame(sf::IntRect(160, 96, 32, 32));

		Animation fantom2WalkDownLeft(0.333333334f);
		fantom2WalkDownLeft.addFrame(sf::IntRect(192, 96, 32, 32));
		fantom2WalkDownLeft.addFrame(sf::IntRect(224, 96, 32, 32));

		Animation fantom2StandStill(0.45f);
		fantom2StandStill.addFrame(sf::IntRect(0, 64, 32, 32));
		fantom2StandStill.addFrame(sf::IntRect(64, 64, 32, 32));

		Animator fantom2Animator(&fantom2Sprite);
		fantom2Animator.addAnimation("walkLeft", &fantom2WalkLeft);
		fantom2Animator.addAnimation("walkRight", &fantom2WalkRight);
		fantom2Animator.addAnimation("walkUp", &fantom2WalkUp);
		fantom2Animator.addAnimation("walkDown", &fantom2WalkDown);
		fantom2Animator.addAnimation("walkDownLeft", &fantom2WalkDownLeft);
		fantom2Animator.addAnimation("walkDownRight", &fantom2WalkDownRight);
		fantom2Animator.addAnimation("walkUpLeft", &fantom2WalkUpLeft);
		fantom2Animator.addAnimation("walkUpRight", &fantom2WalkUpRight);
		fantom2Animator.addAnimation("standStill", &fantom2StandStill);

		fantom2Animator.setCurentAnimation("standStill");
		
		GCharacter<VerticeInfo, EdgeInfo, FantomInfo> fantom2Gchar(fantomInfo, &graph, vertices[128]);
		
		DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>  drawCharFantom2(&window, &fantom2Sprite, &fantom2Animator, transform, &font);

		FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo> fantom2Behavior(FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>::random);

		Actor<
			GCharacter<VerticeInfo, EdgeInfo, FantomInfo>,
			FantomBehavior<VerticeInfo, EdgeInfo, FantomInfo>,
			DrawCharacter<VerticeInfo, EdgeInfo, FantomInfo>
		> fantom2(&fantom2Gchar, &fantom2Behavior, &drawCharFantom2);

#pragma endregion

		World world(&window, &graph, &drawGraph, &pacman, &font, transform);
		world.addFantom(&fantom);
		world.addFantom(&fantom2);

		world.init();
		//main loop
		GameClock*clock = GameClock::getInstance();
		
		while (window.isOpen()) {
			world.update();
		}
	}
	catch (Error e) {
		cout << e << endl;
		system("pause");
		return -1;
	}

	return 0;
}
