#include "../header/dijkstra.hpp"

Node* closestNode(map<Node*, int>* dist, vector<Node*>* unvisited) {

    //initialising closest node to the first in list of unvisted nodes
    pair<Node*, int> min = *dist->find(unvisited->at(0));

    //comapring current closest node with each unvisited nodes and updating as needed
    for (vector<Node*>::iterator itr = unvisited->begin();
        itr != unvisited->end(); itr++)
    {
        if (min.second > dist->find(*itr)->second) {
            min = *dist->find(*itr);
        }
    }
    return min.first;
}

//Dijkstra's shortest path algorithm
pair<stack<Node*>*,int> dijkstra(map<char, Node*>* graph, char start, char end, int limit) {
    vector<Node*> unvisited;
    map<Node*, int> nodeDist;
    map<Node*, Node*> prevNode;
    stack<Node*>* path = new stack<Node*>;
    pair<stack<Node*>*, int> result (path, 0);
    Node* current;

    //getting Node objects for the start and end (specified in the input)
    Node* source = graph->at(start);
    Node* target = graph->at(end);

    //occupy the vector of unvisted nodes with all nodes in graph
    for (map<char, Node*>::iterator itr = graph->begin();
        itr != graph->end(); itr++) {

        //set inital distance to infinity i.e. very large number
        //used max short because using max int would overflow on addition
        nodeDist.insert(pair<Node*, int>(itr->second, numeric_limits<short>::max()));
        unvisited.push_back(itr->second);
    }
    //setting distance from source to source = 0
    nodeDist.at(source) = 0;

    //do until all nodes have been visited
    while (unvisited.size() != 0) {
        //setting the current node as closest, unvisted, node to the source
        current = closestNode(&nodeDist, &unvisited);

        //remove current node from unvisted
        unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

        //for all nodes adjacent to current that have not yet been visited
        for (map<Node*, int>::iterator itr = current->adj.begin(); itr != current->adj.end(); itr++)
        {
            if (find(unvisited.begin(), unvisited.end(), itr->first) != unvisited.end()) {
                //if alternative route through the current node is shorter
                //update the previous node 
                int altRoute = nodeDist.at(current) + itr->second;
                if (altRoute < nodeDist.at(itr->first)) {
                    nodeDist.at(itr->first) = altRoute;
                    if (prevNode.find(itr->first) == prevNode.end()) {
                        prevNode.insert(pair<Node*, Node*>(itr->first, current));
                    }
                    else prevNode.at(itr->first) = current;
                }
            }
        }
    } //TODO: keep track of multiple shortest paths
    for (pair<Node*, int> p : nodeDist) {
        if (p.second == numeric_limits<short>::max()) {
            logError(E2);
            return result;
        }
    }
    //if no path under the limit could be found produce error
    //else add each node to a stack
    if (nodeDist.find(target)->second > limit){   
        logError(E3);
    }
    else {
        current = target;
        result.second = nodeDist.at(target);
        while (current != source) {
            path->push(current);
            current = prevNode.at(current);
        }
        path->push(current);
        result.first = path;
    }
    return result;
}