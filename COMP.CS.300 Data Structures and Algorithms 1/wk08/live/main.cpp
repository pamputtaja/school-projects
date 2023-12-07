#include <unordered_set>
#include <deque>

int NO_KEY = -1;

struct Node {
    int key=NO_KEY;
    Node* parent = nullptr;
    std::unordered_set<Node*> children = {};
};

Node* NO_NODE = nullptr;



std::unordered_set<std::deque<int>> get_paths_to_root(Node* node){
    std::unordered_set<std::deque<int>> paths;
    // first checks if node is one below root
    if( node->parent->parent == NO_NODE) {
        paths.insert({node->key, node->parent->key});
        return paths;
    }
}

int main() {

    return 0;
}
