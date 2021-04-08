#include <map>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "header/Node.hpp"
#include "header/dijkstra.hpp"

using namespace std;

//split string at delimiter into vector of substrings
vector<string> splitStr(string toSplit, string delim) {
    vector<string> result;

    while (toSplit.find(delim) != string::npos) {
        int pos = toSplit.find(delim);
        result.push_back(toSplit.substr(0, pos));
        toSplit.erase(0, pos + delim.length());
    }
    result.push_back(toSplit);
    return result;
}

//ensure number as a string is an unsigned int
int checkUInt(string x) {
    //check for floating point and negative number
    if (x.find('.') != string::npos || stoi(x) < 0) {
        logError(E1);
        return 1;
    }return 0;
}

//ensure string is a single upper case character
int checkCharUpper(string x) {
    if (x.length() > 1 || !isupper(x[0])) {
        logError(E1);
        return 1;
    }return 0;
}

//creating graph map from edges
int addtoGraph(map<char, Node*>* graph, vector<string> edge) {

    //checking for single upper case node names
    for (int i = 0; i < 2; i++) {
        if (checkCharUpper(edge[i])) { return 1; }
    }
    //checking weights (distances) are unsigned ints
    if (checkUInt(edge[2])) { return 1; }

    //adding nodes to graph if they dont doesnt exist
    for (int i = 0; i < 2; i++) {
        char nodeName = edge[i][0];
        if (graph->find(nodeName) == graph->end()) {
            graph->insert(pair<char, Node*>(nodeName, new Node(nodeName)));
        }
    }
    //adding adjacent nodes and weights to node
    for (int i = 0; i < 2; i++) {
        Node* cur = graph->at(edge[i][0]);
        Node* alt;

        if (i == 0) alt = graph->at(edge[i + 1][0]);
        else alt = graph->at(edge[i - 1][0]);

        if (cur->addAdj(alt, stoi(edge[2]))) return 1;;
    }
    return 0;
}

int main() {
    string graphString, goalString;
    vector<string> edgeStrings, goal, startEnd;
    vector<vector<string>> edges;
    map<char, Node*> graph;
    char start, end;
    int limit;

    getline(cin, graphString);
    getline(cin, goalString);

    //checking for leading or trailing whitespace on inputs
    if (isspace(graphString[0]) || isspace(graphString[graphString.length() - 1]) ||
        isspace(goalString[0]) || isspace(goalString[goalString.length() - 1])) {
        logError(E1);
        return 0;
    }

    //splitting input at spaces
    edgeStrings = splitStr(graphString, " ");

    for (string edgeString : edgeStrings) {
        //ensuring each edge is surrounded by []
        //This will also error if there was white space inside an edge definition
        if (edgeString[0] != '[' || edgeString[edgeString.length() - 1] != ']') {
            logError(E1);
            return 0;
        }

        //removing [] from edge
        edgeString.erase(0, 1);
        edgeString.erase(edgeString.length() - 1);

        //creating graph map from edges
        if (addtoGraph(&graph, splitStr(edgeString, ","))) {
            return 0;
        }
    }

    //ensuring goalstring contains no whitespace
    for (char c : goalString) {
        if (isspace(c)) {
            logError(E1);
            return 1;
        }
    }

    //splitting goal into start and end nodes and limit
    goal = splitStr(goalString, ",");
    startEnd = splitStr(goal[0], "->");

    //verifying correct input
    if (checkUInt(goal[1])) { return 1; }
    for (string str : startEnd) {
        if (checkCharUpper(str)) { return 1; }
    }

    //defining start and end limits
    start = startEnd[0][0];
    end = startEnd[1][0];
    limit = stoi(goal[1]);

    //ensuring the start and end points are defined in the graph
    if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
        logError(E2);
        return 0;
    }

    //dijkstra's shortest path algorithm
    pair<stack<Node*>*, int> shortestPath = dijkstra(&graph, start, end, limit);

    //if result, print results
    stack<Node*>* path = shortestPath.first;
    if (path->size() != 0) {
        cout << endl << "SUCCESS: ";
        while (path->size() != 1) {
            cout << *path->top() << "->";
            path->pop();
        }
        cout << *path->top() << endl << "Cost: " << shortestPath.second;
    }
    cout << "\n\nPress Enter to Continue...";
    cin.ignore();
    delete path;
    return 0;
}
