#pragma once
using namespace std;

template <typename T> class ListNode
{
  public: 
    // bunch of types 
    typedef T value_type;
    typedef T& reference_type;
    typedef T const& const_reference_type;
    typedef T* pointer_type;
    typedef T const* const_pointer_type;
    value_type data;
    
    ListNode<value_type>* next;
    /*ListNode()
    {
      this->data = value_type();
      this->next = NULL;
    };*/
    ListNode<value_type>()
    {
      this->data = value_type();
      this->next = NULL;
    };
    /*ListNode(value_type data)
    {
      this->data = data;
    };*/
    ListNode<value_type>(value_type obj) //generalized template constructor
    {
      this->data = value_type(obj);
      this->next = NULL;
      //cout << "ListNode T constructor" << endl;
    };
};

//template function to print data of any template ListNode.
//Note that this is just a template function, meaning it calls the overloading function from the specific class, so it has to be defined in each class that we wish to print
//from here
// template<class T> inline std::ostream& operator<<(std::ostream& output, const ListNode<T>& ListNode)
// {
//   output << ListNode.data;
//   return output;
// }

// template<class T> bool operator==(ListNode<T>&Node1, ListNode<T>&Node2) //template function for == operator
// {
//   return Node1.data == Node2.data;
// };

// template<class T> bool operator<(ListNode<T>&Node1, ListNode<T>&Node2) //template function for < operator
// {
//   return Node1.data < Node2.data;
// };

// template<class T> bool operator>(ListNode<T>&Node1, ListNode<T>&Node2) //template function for > operator
// {
//   return Node1.data > Node2.data;
// };
//till here
template <typename T> class LinkedList
{
  //TODO: isertfront, insertlast, insert after an iterator

  // private, no need to expose implementation
  typedef ListNode<T> node_type;

  // From now on, T should never appear
  typedef node_type* node_pointer;
  typedef node_type& node_reference;
  public:
    typedef typename node_type::value_type value_type;
    typedef typename node_type::pointer_type pointer_type;
    typedef typename node_type::reference_type reference_type;
    typedef typename node_type::const_reference_type const_reference_type;

    int size;
    node_pointer root;   // special variable which stores address of the head node.
    node_pointer last;   // special variable which stores address of the last node.
    node_pointer ploc;   //to be used by Search(value) method to store address of logical predecessor of value in a list.
    node_pointer loc;   //to be used by Search(value) method to store address of the node containing the searched value in a list. If it is not found it contains NULL.
    // LinkedList();   //constructor
    // //Linked List functions
    // bool isEmpty();   //tells if list is empty
    // void push(int value);   //inserts node at the end of list
    // void printList(ListNode<T> *headNode);   //prints the maintained linked list
    // void search(int value);   //searches the linked list for a node data
    // void destroyList();   //destroys the whole list and all of its nodes
    // void printReverse(ListNode<T> *headNode); //prints list in reverse
    // void reverseList(ListNode<T> *headNode); //reverses a listr

// Diff types of iterator
   /* struct Iterator 
{
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = int;
    using pointer           = int*;  // or also value_type*
    using reference         = int&;  // or also value_type&
};*/
    class iterator;
    friend class iterator;

    LinkedList() //linked list constructor to create an empty list
    {
      this->root=NULL;   //initializing pointers to NULL
      this->last = NULL;
      this->ploc=NULL;
      this->loc=NULL;
      this->size = 0;
      //this->itr = root;
      //cout << "Linked list constructor" << endl; 
    }
    iterator begin()
    {
      return iterator(root);
    }
    iterator end()
    {
      return iterator(NULL);
    }
    bool isEmpty()   //check if list is empty
    {
      return root==NULL;
    }
    
    //i changed the whole code yesterday
    //change ListNode<class> to class throughout the code etc
    //like linked list of <Event> instead of <ListNode<Event>>
    class iterator
    {
      public:
        friend class LinkedList;
        node_pointer currentNode; //points to a node in a linked list

        iterator(node_pointer node) //parametrized constructor
        {
          this->currentNode = node;
        }
        iterator() //default constructor
        {
          this->currentNode = NULL;
        }
        // reference_type operator*() const { return &currentNode; }
        pointer_type operator->() { return currentNode; }

        // // Prefix increment
        // iterator& operator++() { 
        //   m_ptr++; 
        //   return *this; 
        // }  

        // // Postfix increment
        // iterator operator++(ListNode<T>) { 
        //   iterator tmp = *this; 
        //   ++(*this); 
        //   return tmp; 
        // }

        // friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        // friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
        // Overload for the comparison operator !=
        bool operator!=(const iterator& itr) const {
          return currentNode != itr.currentNode;
        } 

        bool operator==(const iterator& itr) const {
          return currentNode == itr.currentNode;
        }

        bool operator<(const iterator& itr) const {
          return currentNode < itr.currentNode;
        }
        
        bool operator>(const iterator& itr) const {
          return currentNode > itr.currentNode;
        }

        // Overload for the dereference operator *
        reference_type operator*() const {
          return currentNode->data;
        }

        /*// Overload for the postincrement operator ++
        iterator operator++(int) {
          iterator temp = *this;
          currentNode = currentNode->next;
          return temp;
        }*/
        // Overload for the postincrement operator ++
        iterator operator++( int ) {
          currentNode = currentNode->next;
          return iterator(currentNode);
        }
        // Overload for the preincrement operator -- in case of doubly linked link
        // iterator operator--(int) {
        //   currentNode = currentNode->prev;
        //   return iterator(currentNode);
        // }
    };    

    iterator begin() const {
      return iterator(root);
    }
    
    iterator end() const {
      return (iterator(last)->next);
    }
    
    iterator insert(iterator position, const T& value) {
      node_pointer newNode = new ListNode<T>(value, position.nodePtr->next);
      if (position.nodePtr == root) 
        last = newNode;
      position.nodePtr->next = newNode;
      return position;
    }

    iterator erase(iterator position) {
      node_pointer toDelete = position.nodePtr->next;
      position.nodePtr->next = position.nodePtr->next->next;
      if (toDelete == last) 
        last = position.nodePtr;
      delete toDelete;
      return position;
    }
    // void insert(node_type inputNode)   //inserts a new node at the end of list
    // {
    //   node_pointer newnode = new node_type; 
    //   newnode->data = inputNode.data;  
    //   if( !isEmpty() )  //if list isn't empty, insert it after last
    //     last->next = newnode;
    //   else   //if list is empty, set newnode to be the root node
    //     root = newnode;

    //   last = newnode;//set newnode to be the last node
    //   last->next = NULL;

    //   size++;
    // }  

    void insert(value_type nodeValue)   //inserts a new node at the end of list
    {
      searchData(nodeValue);
      if(!loc)
      {
        node_pointer newnode = new node_type; 
        newnode->data = nodeValue;  
        if( !isEmpty() )  //if list isn't empty, insert it after last
          last->next = newnode;
        else   //if list is empty, set newnode to be the root node
          root = newnode;

        last = newnode;//set newnode to be the last node
        last->next = NULL;

        size++;
      }
    }  
    void printList(node_pointer headNode)   //prints the entire linked list
    {
      if ( !isEmpty() )   //empty check
      {
        node_pointer iterator = headNode;   //iterator node
        cout << "\e[48;2;77;0;77mStart:\x1b[0m " << root->data << " | \e[48;2;77;0;77mEnd:\x1b[0m " << last->data << endl;
        cout << "\e[48;2;77;0;77mList content:\x1b[0m ";
        while ( iterator != NULL )   //loop until node points to NULL
        {
          cout << iterator->data;   //print node data
          if( iterator->next != NULL )
            cout << " --> "; //pretti-fy linked list output
          else
            cout << " --> /";
          iterator = iterator->next;   //advance to next node
        }
        cout << endl;
      }
      else
        cout << "\x1b[31mError: List is empty.\x1b[37m" << endl;
    }

    void printList()
    {
      printList(this->root);
    }
    //ListNode<T>
    bool search(node_type inputNode)   //search value in list
    {
      loc = root; ploc = NULL;   //initialize loc and ploc

      if( isEmpty() )   //ends function if list is empty, since we don't need to search
        return false;

      while( loc != NULL && !(loc->data == inputNode.data) ) //if value not found, advance to next node
      {
        ploc = loc;
        loc = loc->next;
      }
      //assigns NULL to loc if value is not present in the list
      //and if its logical position is in the list except not after tail node
      if( loc != NULL && !(loc->data == inputNode.data)) {
        loc = NULL;
      }

      if(loc!=NULL && loc->data == inputNode.data)
        return true; //value found
      else
        return false; //value not found
    }

    // Direct value <T> is searched
    bool searchData(value_type inputValue)   //search value in list
    {
      loc = root; ploc = NULL;   //initialize loc and ploc

      if( isEmpty() )   //ends function if list is empty, since we don't need to search
        return false;

      while( loc != NULL && !(loc->data == inputValue) ) //if value not found, advance to next node
      {
        ploc = loc;
        loc = loc->next;
      }
      //assigns NULL to loc if value is not present in the list
      //and if its logical position is in the list except not after tail node
      if( loc != NULL && !(loc->data == inputValue)) {
        loc = NULL;
      }

      if(loc!=NULL && loc->data == inputValue)
        return true; //value found
      else
        return false; //value not found
    }

    void destroyList()   //destroys each node of the list
    {
      node_pointer iterator = root; //iterator pointer points to the first node
      while( iterator != NULL )  //iterating until we reach last node
      {
        root = root->next;  //advancing root node
        delete iterator; //deleting iterator
        iterator = root; //iterator now points to new root
      }
      cout << "\e[0;32mList destroyed.\x1b[0;37m" << endl;
    }

    void printReverse(node_pointer headNode) //prints a linked list in reverse recursively given its starting node
    {
      if( isEmpty() ) //empty check
      {
        cout << "\x1b[0;31mError: List is empty.\x1b[0;37m" << endl;
        return;
      }
      else if(headNode == NULL ) //base case of recursive function
      {
        cout << "\e[48;2;77;0;77mReverse list content:\x1b[0m ";
        return;
      }
      printReverse(headNode->next); //recursively calls the function
      cout << headNode->data << " "; //output node data

      if( headNode != root ) //pretti-fy linked list output
        cout << "--> ";
      else
        cout << "--> /" << endl;
    }

    void reverseList( node_pointer headNode, node_pointer prevNode )
    {
      if(headNode == NULL ) { //base case of recursive function
        root = prevNode; //updae the starting node when we reach last node
        return;
      }
      if( headNode->next == NULL ) { //second base case of recursive function
      //at each function call
        //cout << "\e[0;32mList succesfully reversed.\x1b[0;37m" << endl;
        headNode->next = prevNode; //node now points to it predecessor if it was the last node in the list
        root = headNode; //let the list now begin from this headNode 
      }
      else if( headNode->next != NULL ) { ///recursive calls
      //calls the reverseList function revursively until we reach the last node
      //sets the root pointer to point to the last node
        reverseList(headNode->next, headNode); //recursive calls
        headNode->next = prevNode;// update next field of each node star
      }
      last = prevNode;
      last->next = NULL;
    }
};