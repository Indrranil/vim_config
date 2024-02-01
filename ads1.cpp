#include<iostream>
#include<stack>

using namespace std;

class treenode{
    int data;
    treenode* left;
    treenode* right;
    friend class tree;
};

class Stack{
    int top;
    treenode* data[30];
    public:
        Stack();
        void push(treenode* temp);
        treenode* pop();
        int isEmpty();
        friend class tree;
};
//:: used to access stack from class stack
Stack::Stack(){  // constructor 
    top = -1;
}
// below it indicates that PUSH is a member function of class stack
void Stack::push(treenode* temp){
    if (top < 29){
        top++;
        data[top] = temp;
    }
}

treenode* Stack::pop(){
    treenode* temp = data[top];
    top--;
    return temp;
}

int Stack::isEmpty(){
    if (top == -1){
        return 1;
    }
    return 0;
}

// (treenode* temp) indicates that the temp is a pointer to an obj of type treemnode
class tree{
    treenode* root;
    Stack* st;
    public:
        tree();
        void create_nr();// non-recursive starts(iterative)
        void create_r(); // for creating root node
        void create_r(treenode* temp);// creating non-root nodes
        void inorder_r(); // initiating inorder traversal
        void inorder_r(treenode* temp); // allows traversal of a subtree 
        void preorder_r();
        void preorder_r(treenode* temp);
        void postorder_r();
        void postorder_r(treenode* temp);
        void inorder_nr();
        void preorder_nr();
        void postorder_nr();
};

tree::tree(){
    root = NULL;
    st = new Stack();
}

void tree::create_r(){
    root = new treenode();
    int data;
    cout << "Enter data of root node: ";
    cin >> data;
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    create_r(root);
}

void tree::create_r(treenode* temp){
    int ch;
    cout << "Enter node to left? (1/0): ";
    cin >> ch;
    if (ch == 1){
        treenode* curr = new treenode();
        curr->right = NULL;
        curr->left = NULL;
        int d;
        cout << "Enter value of node: ";
        cin >> d;
        curr->data = d;
        temp->left = curr;
        create_r(curr);
    }
    ch = 0;
    cout << "Enter node to right? (1/0): ";
    cin >> ch;
    if (ch == 1){
        treenode* curr = new treenode();
        curr->right = NULL;
        curr->left = NULL;
        int d;
        cout << "Enter value of node: ";
        cin >> d;
        curr->data = d;
        temp->right = curr;
        create_r(curr);
    }
}

void tree::create_nr(){
    if (root == NULL){
        root = new treenode();
        int data;
        cout << "Enter data of root node: ";
        cin >> data;
        root->data = data;
        root->left = NULL;
        root->right = NULL;
    }
    char choice = 'y';
    do {
        treenode* temp = root;
        int flag = 0;
        treenode* curr = new treenode();
        int data;
        cout << "Enter data of node: ";
        cin >> data;
        curr->data = data;
        curr->left = NULL;
        curr->right = NULL;
        while(flag == 0){
            char c;
            cout << "Enter node to left or right? (l/r): ";
            cin >> c;
            if (c == 'l'){
                if (temp->left == NULL){
                    temp->left = curr;
                    flag = 1;
                }
                temp = temp->left;
            }else{
                if (temp->right == NULL){
                    temp->right = curr;
                    flag = 1;
                }
                temp = temp->right;
            }
        }
        cout << "Add more nodes? (y/n): ";
        cin >> choice;
    } while(choice == 'y');
}

void tree::inorder_r(){
    inorder_r(root);
}

void tree::inorder_r(treenode* temp){
    if (temp != NULL){
        inorder_r(temp->left);
        cout << temp->data << " ";
        inorder_r(temp->right);
    }
}

void tree::preorder_r(){
    preorder_r(root);
}

void tree::preorder_r(treenode* temp){
    if (temp != NULL){
        cout << temp->data << " ";
        preorder_r(temp->left);
        preorder_r(temp->right);
    }
}

void tree::postorder_r(){
    postorder_r(root);
}

void tree::postorder_r(treenode* temp){
    if (temp != NULL){
        postorder_r(temp->left);
        postorder_r(temp->right);
        cout << temp->data << " ";
    }
}

void tree::inorder_nr(){
    treenode* temp = root;
    while(1){
        while(temp != NULL){
            st->push(temp);
            temp = temp->left;
        }
        if (st->isEmpty() == 1){
            break;
        }
        temp = st->pop();
        cout << temp->data <<" ";
        temp = temp->right;
    }
}

void tree::preorder_nr(){
    treenode* temp = root;
    while(1){
        while(temp != NULL){
            cout << temp->data <<" ";
            st->push(temp);
            temp = temp->left;
        }
        if (st->isEmpty() == 1){
            break;
        }
        temp = st->pop();
        temp = temp->right;
    }
}

void tree::postorder_nr(){
    treenode* temp = root;
    while(1){
        while(temp != NULL){
            st->push(temp);
            temp = temp->left;
        }
        if (st->data[st->top]->right == NULL){
            temp = st->pop();
            cout << temp->data;
        }
        while(st->isEmpty() == 0 && st->data[st->top] == temp){
            temp = st->pop();
            cout << temp->data;
        }
        if (st->isEmpty() == 1){
            break;
        }
        st->data[st->top]->right = temp;
    }
}

int main(){
    tree bt;
    // bt.create_nr();
    // cout << "\n";
    // cout << "\nInorder traversal: \n"; 
    // bt.inorder_r();
    // cout << "\nPreorder traversal: \n"; 
    // bt.preorder_r();
    // cout << "\nPostorder traversal: \n"; 
    // bt.postorder_r();
    int n;
    cout << "Create tree using reccursion or not?(1/0): ";
    cin >> n;
    switch (n)
    {
    case 1:
        bt.create_r();
        break;
    case 0:
        bt.create_nr();
        break;
    default:
        cout << "Error in input";
        return 0;
        break;
    }

    cout << "Which traversal to use?\n";
    cout << "1 - PreOrder\n";
    cout << "2 - InOrder\n";
    cout << "3 - PostOrder\n";
    cout << "Enter your choice: ";
    cin >> n;
    int x;
    cout << "Use Recurrsion or not? (1/0): ";
    cin >> x;
    switch (n)
    {
    case 1:
        if (x == 1){
            bt.preorder_r();
        }
        else{
            bt.preorder_nr();
        }
        break;
    case 2:
        if (x == 1){
            bt.inorder_r();
        }
        else{
            bt.inorder_nr();
        }
        break;
    case 3:
        if (x == 1){
            bt.postorder_r();
        }
        else{
            bt.postorder_nr();
        }
        break;
    default:
        break;
    }

    return 0;
}