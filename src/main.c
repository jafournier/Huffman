/* This file is only here to generate a test executable
   and test that everything works fine in the C++ part
*/


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include "HuffTree.h"
using namespace std;

// first some helper functions

void printpair(tuple<int,int> t){
    cout << get<0>(t) << "," << get<1>(t)<< "\n";
}

void printblist(queue<bool> q){
while(!q.empty()){
        cout << int(q.front());
        q.pop();
    }
cout << "\n";
}



int main(void)
    tuple<int, char> t( 1, '1' );
    int vec[7][2] = {{0,1},{1, 8}, {2, 5}, {3, 10},{4,12},{5,3},{6,0}};
    cout << vec[1][1]<< "\n";
    vector<tuple<int,float>> pairvec;
    pairvec.resize(7);
    get<0>(pairvec[0]) = 30;
    int i =0;
    for(  vector<tuple<int,float>>::iterator it = pairvec.begin();
          it != pairvec.end(); it++ , i++ ){
       get<0>(*it)= vec[i][0];
       get<1>(*it)= float(vec[i][1]);
       cout <<"\n"<<"v"<< get<1>(*it) << "i "<< i <<"\n";
    } 
    HuffTree tree(pairvec);

    // test if comparison works
    cout << "== check comparison fonctor ==\n";
    comptype comp;
    cout << " comparaison " << comp(pairvec[0],pairvec[1])<< "\n";
    
    heaptype pq(comp,pairvec);
    // check if my heaptype works (if pop order is correct)
    cout << "== check heap functionning ==\n";
    while(!pq.empty()){
         printpair( pq.top() );
         pq.pop();
    }
    cout << "== result of HuffTree == \n";
    vector<string> table = tree.getEncodeStringTable();
    vector<queue<bool>> tableq = tree.getEncodeTable();
    cout <<"test string " << char('1') << "\n";
    for( size_t i = 0; i < table.size(); i++ ){
        cout << " symbol : "<< i << " code: "<< string( table[i])<< " size " <<\
        table[i].size() << "\n";
    }
    return 0;
}
	
