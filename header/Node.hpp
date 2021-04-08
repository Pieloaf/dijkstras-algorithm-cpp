#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>
#include "errorCodes.hpp"

using namespace std;

class Node {
public:
    Node(char name) :name(name) {}

    char name;
    map<Node*, int> adj;

    int addAdj(Node* n, int weight); //add adjacent nodes and their distance to map

    // overloaded output stream opperator to print node name
    friend ostream& operator<< (ostream& ostr, const Node& n);
};
#endif