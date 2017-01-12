#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <string>
#include "HuffNode.h"
using namespace std;


// need a comparyson foncteur to implement heaptype
struct comptype{
    bool operator()(tuple<int,float> p1 , tuple<int,float> p2){
        return (get<1>(p1) >  get<1>(p2));
    };
};

// my heap type
typedef priority_queue< tuple<int,float>,vector<tuple<int,float>>, comptype > heaptype;

class HuffTree{
public:

    // constructors
    HuffTree( const vector<tuple<int,float>>& );
    HuffTree( const vector<float>&);

    // methods
    void construct( const vector<tuple<int,float>>& ); // construct the huffman tree
    HuffNode* addFather(HuffNode*, HuffNode*);
   
    // getters
    queue<bool> getEncode(const  int &);
    queue<bool> getEncode( HuffNode*  );
    string getEncodeString(HuffNode*);
    vector<queue<bool>> getEncodeTable();
    vector<string> getEncodeStringTable();

private:
    // attributes
    vector<HuffNode> node_vect_; // nodes of the tree
    HuffNode* rootptr_;          // pointer to the root of the tree
    heaptype weight_list_;       // priority list, used to build the tree
    size_t nbr_symbol_;          // number of symbol considered
};

#endif
