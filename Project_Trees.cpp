#include <iostream>
#include <vector>

using namespace std;

class BinaryTree{
    private:
    struct Node{
        string key;
        Node *left;
        Node *right;
        vector<Node*> children;
    };
    Node *root;
    Node *temp;

    void addLeafPrivate(string key,Node *ptr);
    Node *createLeafPrivate(string key);
    void printPreOrderPrivate(Node *ptr);
    void printInOrderPrivate(Node *ptr);
    void printPostOrderPrivate(Node *ptr);
    Node* returnNodePrivate(string key,Node *ptr);
    string findSmallestPrivate(Node *ptr);
    void removeNodePrivate(string key,Node *parent);
    void removeRootMatch();
    void removeMatch(Node *parent,Node *match,bool left);
    int countAllNodesPrivate(Node *ptr);
    int countChildrenPrivate(Node *ptr);
    void freeTreePrivate(Node *ptr);
    void addNodePrivate( string key, vector<Node*>children, Node *ptr);

    public:
    BinaryTree();

    void addLeaf(string key);
    Node *createLeaf(string key);
    void printPreOrder();
    void printInOrder();
    void printPostOrder();
    Node* returnNode(string key);
    string returnRootKey();
    void printChildren(string key);
    int countChildren();
    int countAllNodes();
    string findSmallest();
    void removeNode(string key);
    void freeTree();
    void addNode(string key, vector<Node*>children);
};

int main(){   

    string familyMembers[9] = {"John","Jane","Bob","Mary","Sally","Sue","Sam","Tom","Dick"};        
    BinaryTree familyTree;

    //add family members to the tree
    for(int i = 0; i < 9; i++){     
        familyTree.addLeaf(familyMembers[i]);
    }
    cout<<"Who is the father of Bob?"<<endl;
    cout<<familyTree.returnRootKey()<<endl;

    cout<<"Who are all the sons of John?"<<endl;
    familyTree.printPreOrder();
    cout<<endl;

    cout<<"Who are all the brothers of Bob?"<<endl;
    familyTree.printInOrder();
    cout<<endl;

    cout<<endl;
    familyTree.printChildren("John");
    familyTree.printChildren("Bob");
    cout<<endl;
    
    return 0;
}

BinaryTree::BinaryTree(){
    root = NULL;
}

BinaryTree:: Node* BinaryTree::createLeafPrivate(string key){       //creates a leaf node
    Node *ptr = new Node;       
    ptr->key = key;
    ptr->left = NULL;
    ptr->right = NULL;

    return ptr;
}

BinaryTree::Node *BinaryTree::createLeaf(string key){
    return createLeafPrivate(key);      //returns a pointer to the new node  
}
void BinaryTree::addNode(string key, vector<Node*>children){
    addNodePrivate(key,children,root);
}
void BinaryTree::addNodePrivate(string key, vector<Node*>children, Node *ptr){
    createLeafPrivate(key);
}

void BinaryTree::addLeaf(string key){
    addLeafPrivate(key,root);
}

void BinaryTree::addLeafPrivate(string key,Node *ptr){
    if(root == NULL){
        root = createLeaf(key);
        temp = root;
    }
    else if(key < ptr->key){
        if(ptr->left != NULL){
            addLeafPrivate(key,ptr->left);
        }
        else{
            ptr->left = createLeaf(key);
        }
    }
    else if(key > ptr->key){
        if(ptr->right != NULL){
            addLeafPrivate(key,ptr->right);
        }
        else{
            ptr->right = createLeaf(key);
        }
    }
    else{
        cout<<"The key "<<key<<"  is already added to the tree. "<< endl;
    }
}

void  BinaryTree::printPreOrder(){
    printPreOrderPrivate(root);
}

void BinaryTree::printPreOrderPrivate(Node *ptr){
    if(root != NULL){
        if(ptr->left != NULL){
            ptr = ptr->left;
            cout<< ptr -> key <<endl;
        }
        if (ptr->right != NULL){
            ptr = ptr->right;
            cout<< ptr -> key <<", ";
        }
    }
    else{
        cout<<"The tree is empty."<<endl;
    }
}

void BinaryTree::printInOrder(){
    printInOrderPrivate(root);
}
void BinaryTree::printInOrderPrivate(Node *ptr){
    if(root != NULL){
        if(ptr->left != NULL){
            ptr = ptr->left;
        }
        if(ptr->right != NULL){
            ptr = ptr->right;
            cout<< ptr -> key <<", ";
        }
    }
    else{
        cout<<"The tree is empty."<<endl;
    }
}

void BinaryTree::printPostOrder(){
    printPostOrderPrivate(root);
}
void BinaryTree::printPostOrderPrivate(Node *ptr){
    if(root != NULL){
        if(ptr->left != NULL){
            printPostOrderPrivate(ptr->left);
        }
        if(ptr->right != NULL){
            printPostOrderPrivate(ptr->right);
        }
         cout<< ptr -> key <<", ";
    }
    else{
        cout<<"The tree is empty."<<endl;
    }
}

BinaryTree:: Node *BinaryTree::returnNode(string key){
    return returnNodePrivate(key,root);
}

BinaryTree:: Node *BinaryTree::returnNodePrivate(string key,Node *ptr){
    if(ptr != NULL){
        if(ptr -> key == key){
            return ptr;
        }else{
            if(ptr->left) {
                return returnNodePrivate(key,ptr->left);
            }
            else{
                return returnNodePrivate(key,ptr->right);
            }
        }
    }
        else{
            return NULL;
        }
}

string BinaryTree::returnRootKey(){
    if(root != NULL){
        return root->key;
    }
    else{
        return NULL;
    }
}

void BinaryTree::printChildren(string key){
    Node *ptr = returnNode(key);
    if(ptr != NULL){
        cout<<"Parent Node"<<ptr->left->key<<endl;

        if(ptr->left == NULL){      //if the node has no left child
            cout<<"No children"<<endl;
        }
        else{
            cout<<"Left Child: "<<ptr->left->key<<endl;
            
        }
        if(ptr->right == NULL){ //if the node has a right child
            cout<<"No right sibling"<<endl;
        }
    
    else{
        cout<<"The right sibling: "<<ptr->right->key <<endl;
    }
}else{
    cout<<"The node "<<key<<" is not in the tree."<<endl;
}
}

int BinaryTree::countChildren(){
    return countChildrenPrivate(root);
}
int BinaryTree::countChildrenPrivate(Node *ptr){
    int childCount=0;
    if(ptr != NULL){
        if(ptr->left != NULL){
            childCount+= countChildrenPrivate(ptr->left);
        }
        if(ptr->right != NULL){
            childCount+= countChildrenPrivate(ptr->right);
        }
    }
    return childCount;
}

int BinaryTree::countAllNodes(){
    return countAllNodesPrivate(root);
}

int BinaryTree::countAllNodesPrivate(Node *ptr){
    int nodeCount = 0;
    if(ptr != NULL){
        nodeCount+= countAllNodesPrivate(ptr->left) + countAllNodesPrivate(ptr->right) + 1;
    }
    return nodeCount;
} 

string BinaryTree::findSmallest(){
    return findSmallestPrivate(root);
}
void BinaryTree::freeTree(){
    freeTreePrivate(root);
}
void BinaryTree::freeTreePrivate(Node *ptr){
    if(ptr != NULL){
        freeTreePrivate(ptr->left);
        freeTreePrivate(ptr->right);
        delete ptr;
    }
}

string BinaryTree::findSmallestPrivate(Node *ptr){
    if(root == NULL){
        cout<<"The tree is empty."<<endl;
        return NULL;
    }else{
        if(ptr->left != NULL){
            return findSmallestPrivate(ptr->left);
        }
        else{
            return ptr->key;
        }
    }
}
   
void BinaryTree::removeNode(string key){
    removeNodePrivate(key,root);
}

void BinaryTree::removeNodePrivate(string key,Node *parent){
    if(root != NULL){
        if(root->key == key){        //if the root is the node to be removed
            removeRootMatch();
            }else{
                if(key < parent-> key && parent->left != NULL){
                    parent->left -> key == key ? 
                    removeMatch(parent,parent->left,true):removeNodePrivate(key,parent->left);
                }
                else if(key > parent-> key && parent->right != NULL){
                    parent->right-> key == key ?
                    removeMatch(parent,parent->right,false):removeNodePrivate(key,parent->right);
                }
                else{
                    cout<<"The key "<<key<<" is not in the tree."<<endl;
                }
            }
    }
    else{
        cout<<"The tree is empty."<<endl;
    }
}

void BinaryTree::removeRootMatch()
{
    if(root!=NULL){
        Node *delptr = root;
        string rootKey = root->key;
        string smallestInRightSubtree;
        if(root->left == NULL && root->right == NULL)
        {
            root = NULL;
            delete delptr;
        }
        else if(root->left == NULL && root -> right != NULL){
            root = root->right;
            delptr->right = NULL;
            delete delptr;
            cout<<"The root node "<<rootKey<<" was deleted."<<endl<<"The new root node is "<<root->key<<endl;
        }
        else if (root->left != NULL && root->right == NULL){
            root = root->left;
            delptr->left = NULL;
            delete delptr;
            cout<<"The root node "<<rootKey<<" was deleted."<<endl<<"The new root node is "<<root->key<<endl;
        }
        else{
            smallestInRightSubtree = findSmallestPrivate(root->right);
            removeNodePrivate(smallestInRightSubtree,root);
            root->key = smallestInRightSubtree;
            cout<<"The root node "<<rootKey<<" was deleted."<<endl<<"The new root node is "<<root->key<<endl;
        }
    }else{
        cout<<"Cannot remove, the tree is empty."<<endl;
    }
}

void BinaryTree::removeMatch(Node *parent,Node *match,bool left){
    if(root != NULL){
        Node *delptr;
        string matchKey = match->key;
        string smallestInRightSubtree;
        if(match->left == NULL && match->right == NULL){
            delptr = match;
            if(left){
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
            delete delptr;
            cout<<"The node "<<matchKey<<" was deleted."<<endl;
        }
        else if(match->left == NULL && match->right != NULL){
            delptr = match;
            if(left){
                parent->left = match->right;
            }else{
                parent->right = match->right;
            }
            match->right = NULL;
            delete delptr;
            cout<<"The node "<<matchKey<<" was deleted."<<endl;
        }
        else if(match->left != NULL && match->right == NULL){
            delptr = match;
            if(left){
                parent->left = match->left;
            }else{
                parent->right = match->left;
            }
            match->left = NULL;
            delete delptr;
            cout<<"The node "<<matchKey<<" was deleted."<<endl;
        }
        else{
            smallestInRightSubtree = findSmallestPrivate(match->right);
            removeNodePrivate(smallestInRightSubtree,match);
            match->key = smallestInRightSubtree;
            cout<<"The node "<<matchKey<<" was deleted."<<endl;
        }
    }
}