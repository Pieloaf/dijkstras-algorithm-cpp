#pragma once

#include "Node.hpp"
#include <vector>
#include <map>
#include <stack>

Node* closestNode(map<Node*, int>* dist, vector<Node*>* unvisited);
pair<stack<Node*>*, int> dijkstra(map<char, Node*>* graph, char start, char end, int limit);