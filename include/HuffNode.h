#ifndef HUFFNODE_H
#define HUFFNODE_H


class HuffNode{
public:

    // constructors
    HuffNode(  HuffNode* lson, HuffNode* rson, float prob,int idx):prightson_(rson),pleftson_(lson),pfather_(0),prob_(prob),idx_(idx),is_left_(1){;};
    HuffNode(float prob, int idx):prightson_(0),pleftson_(0),pfather_(0),prob_(prob), idx_(idx),is_left_(0){;};
    HuffNode(){};

    // getters
    float getProb(){return prob_;};
    int getIdx(){return idx_;};
    HuffNode* getPrightson(){return prightson_; };
    HuffNode* getPleftson(){return pleftson_; };
    HuffNode* getPfather(){return pfather_; };
    bool getIsLeft(){return is_left_;};

    // setters
    void setPfather(HuffNode* ptr){pfather_ = ptr;};
    void setIsLeft(int i){is_left_ = i;};

private:
    
    // attributes
    HuffNode* prightson_ ; // pointer to the right son (if any)
    HuffNode* pleftson_ ;  // pointer to the left son (if any)
    HuffNode* pfather_ ;   // pointer to the father (if any)
    float prob_;
    int idx_;              // idx of the node in vector
    bool is_left_;         // is the node at left side ?
};
#endif
