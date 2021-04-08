#include "../header/Node.hpp"

int Node::addAdj(Node* n, int weight){

    //ensuring adjacent node has not previously been defined
    if (adj.find(n) != adj.end()) {
        logError(E2);
        return 1;
    }
    adj.insert(pair<Node*, int>(n, weight));
    return 0;
}

ostream& operator<< (ostream& ostr, const Node& n) {
    ostr << n.name;
    return ostr;
}