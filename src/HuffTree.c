#include "HuffTree.h"




HuffTree::HuffTree( const vector<tuple<int,float>>& pairvect ){
   /* only symbol [0:n] please
      TODO: add assert lines to check it. 
   */
     construct(pairvect); 
}


HuffTree::HuffTree( const  vector<float>& vect){
  /* building from a vector of float, we assume implicitely that
     the underlying symbols are [0:vect.size()-1]
  */
    int size = vect.size();
    vector<tuple<int,float>> pairvect;
    pairvect.reserve(size);
    for(int i = 0; i < size; i++){
        pairvect.push_back(tuple<int,float>(i,vect[i]));
    }
    construct(pairvect);
}


void HuffTree::construct( const vector<tuple<int,float>>& pairvec ){
  /*  build the tree by bottom up (begin with leafs, and add fathers recursively)
      @pairvec : vector of symbol (int)/ probability of occurence (float)
  */ 
    nbr_symbol_ = pairvec.size(); 
    int size_vec = 2*nbr_symbol_-1;  // nbr_of_symbol_ is the number of leafs in the tree
    node_vect_.reserve(size_vec);    
    node_vect_.resize(pairvec.size());
    int idx;                         // variable which will contains idx to process
    
    // build the leafs nodes ( leafs linked to symbols )
    for(size_t i=0; i < pairvec.size(); i++){
      idx = get<0>(pairvec[i]);
      node_vect_[idx] = HuffNode( get<1>(pairvec[i]),idx);
    }
    // heap to extract lowest key elements
    // initialise it with all the leafs
    weight_list_ = heaptype(comptype(),vector<tuple<int,float>>(pairvec));

    // while loop to build father and create edges recursively

    HuffNode*  ptr_r = 0;
    HuffNode*  ptr_l = 0;

   
    while((!weight_list_.empty())
    ){  
        ptr_l = & node_vect_[get<0>(weight_list_.top())]; // ptr to the first lowest key node
        weight_list_.pop();                               // take the first lowest key/value
      if(!weight_list_.empty()){                          // if the remaining is not empty
            ptr_r =  & node_vect_[get<0>(weight_list_.top())]; // ptr to the second lowest key node
            weight_list_.pop();                           // take the second lowest key/value
            addFather(ptr_l, ptr_r);                      // build the father and return its pointer
        }// else this mean that ptr_l is our root.
        
    } 

}

queue<bool> HuffTree::getEncode( HuffNode * ptr_leaf){
  /* get a queue of bool encoding the leaf
     @ptr_leaf : ptr on the considered node (morally a leaf, but could also work of other nodes)
  */

    HuffNode* ptr = ptr_leaf;
    queue<bool> result;
    bool res_temp; 
    // while there is a father, continue to add a bool
    do{ res_temp = ptr->getIsLeft();
        ptr = ptr->getPfather();
        if(ptr != 0){result.push(res_temp);};
    }while(ptr!=0);
    return result;
}

string HuffTree::getEncodeString( HuffNode *  ptr_leaf){
  /* Wrapper of getEncode to process to get a string as an output
  */

    // here is an occasion tho show that I can use lambda functions :)
    // creating a foncteur with struct could have also been possible...

    auto converter = [](bool b){if(b){return char('1');}else{return char('0');}};
    queue<bool> int_res; // intermediary result
    int_res = getEncode(ptr_leaf);
    size_t size = int_res.size();
    
    char * result = new char[size]; 
    for(int i = size - 1 ; i>=0 ; i-- ){
        result[i]=char(converter(int_res.front()));
        int_res.pop();
    }
    string result_f(result,size);
    delete result;
    return result_f;
}

queue<bool> HuffTree::getEncode(const int & idx_leaf){
  /* wraper of getEncode to use an int as argument
  */

    return getEncode( & node_vect_[idx_leaf] );
}


vector<queue<bool>> HuffTree::getEncodeTable(){
  /* build and return  a table containing the encoding
     queue bool associated to each symbol
  */   
    vector<queue<bool>> result;
    result.resize(nbr_symbol_);
    for(size_t i=0;i < nbr_symbol_; i++){
        result[i] = getEncode(&node_vect_[i]);
    }
    return result;
}


vector<string> HuffTree::getEncodeStringTable(){
  /* build and return  a table containing the encoding
     string associated to each symbol
  */   
    vector<string> result;
    result.resize(nbr_symbol_);
   
    for(size_t i=0;i < nbr_symbol_; i++){
        result[i] = getEncodeString(&node_vect_[i]);
    }
    return result;
}


HuffNode* HuffTree::addFather( HuffNode* lptr, HuffNode* rptr){
  /* add the father in the tree
     return the father
  */
    int size = node_vect_.size();
    float sum_prob= lptr->getProb() + rptr->getProb();
    node_vect_.push_back(HuffNode(lptr,rptr,sum_prob,size)); // add father 
    weight_list_.push(tuple<int,float>(size,sum_prob)); // add weight in priority queue
    HuffNode* pfather =  & node_vect_[size]; // pointer on the father

    // then updates the child nodes                               
    lptr->setPfather(pfather);
    rptr->setPfather(pfather);
    lptr->setIsLeft(1);
    rptr->setIsLeft(0);
    return pfather;
}



