#pragma once

#include <iostream>
//#include <exception> 

template<class Element>
class Queue
{
public:
    // Error classes
    class EmptyQueue{};
    
    /** C'tor of Queue class
     *
     *  A new empty Queue.
    */
    Queue();
    
    /** d’tor of Queue class
    */
    ~Queue();
    
    /** Copy C’tor of Queue class
    */
    Queue(const Queue<Element>& other);
    
    /* Assignment operator
    *  removes all current elements and add the queue elements
    * param queue
         the queue we want to change our queue according to
    */
    Queue& operator=(const Queue& queue);
    
    
    // the parameter we wantd to add to the queue(add from the back)
    Queue& pushBack(const Element& data);

    // reference to the first element in the queue (the element can be changed)
    Element& front(); // what happens when queue<const int>?

    //reference to the first element in the queue (the element can not
    const Element& front() const; // if const queue<int>

    // removing the last element in the queue(the one thaw was added last)
    Queue& popFront();

    // the current size of the queue
    int size() const; // inline ??
    
    
    class Iterator;
    // an iterator pointing at the start of the queue
    Iterator begin();
    // an iterator pointing at the end of the queue
    Iterator end();

    
    class ConstIterator;
    // a const iterator pointing at the start of the const queue
    ConstIterator begin() const;
    // a const iterator pointing at the end of the const queue
    ConstIterator end() const;

    
private:
    class Node;
    
    int m_size;
    Node* m_front;
    Node* m_back;
    
    bool empty() const; // inline ??
};

// C'tor of Queue class
template<class Element>
Queue<Element>::Queue() :
    m_size(0),
    m_front(nullptr),
    m_back(nullptr)
{}

// d'tor of Queue class
template<class Element>
Queue<Element>::~Queue()
{
    while (!empty())
    {
        popFront();
    }
}

// copy c'tor of Queue class
template<class Element>
Queue<Element>::Queue(const Queue<Element>& other) :
    m_size(0),
    m_front(nullptr),
    m_back(nullptr)
{
    try
    {
        for (const Element& x : other)
        {
            pushBack(x);
        }
    } catch(...)
    {
        while(!empty())
        {
            popFront();
        }
        throw;
    }
}

// assignment operator of Queue class
template<class Element>
Queue<Element>& Queue<Element>::operator=(const Queue<Element>& other)
{
    // check for self-assignment
    if (this == &other)
    {
        return *this;
    }
    // creates a temp queue
    Queue<Element> tempQueue;
    
    for(const Element& otherElement : other)
    {
        tempQueue.pushBack(otherElement);
    }
    // after this try catch we have no bad::alloc
    // connect the linked list of the tempQueue to the this queue
    // and then delete this queue linked list
    while (!empty())
    {
        popFront();
    }
    // this queue is empty, time to connect
    m_front = tempQueue.m_front;
    tempQueue.m_front = nullptr; // this is the most important
    m_back = tempQueue.m_back;
    tempQueue.m_back = nullptr; // this is NOT important we did it just to be sure
    m_size = other.m_size;
    // tempQueue is diconnected from the linked list, meaning
    // if a d'tor for the tempQueue is called it will not delete
    // the nodes we created
    return *this;
}

template<class Element>
Queue<Element>& Queue<Element>::pushBack(const Element& data)
{
    // creates a node and intialize its data to the given data and the next node to null
    try
    {
        Node* newNode = new Node(data);
        // Node<Element>* newNode = new Node<Element>; // no need for this we use the c'tor for node
        if (empty()) // the newNode is our head now
        {
            m_front = newNode; // takes the address for the head node
        }
        else
        {
            m_back->m_nextNode = newNode;
        }
        m_back = newNode;
        m_size++;
        return *this;
    }
    catch(...) // no need for std::bad_aloc ??
    {
        throw;
    }
}

// should return a refrence so we would be able to chagne it seamlessly if thats what we want
// if not queue<const int>
template<class Element>
Element& Queue<Element>::front()
{
    if(empty())
    {
        throw EmptyQueue{};
    }
    return m_front->m_data;
}

template<class Element>
const Element& Queue<Element>::front() const
{
    if(empty())
    {
        throw EmptyQueue{};
    }
    return m_front->m_data;
}

template<class Element>
Queue<Element>& Queue<Element>::popFront()
{
    if(empty())
    {
        throw EmptyQueue();
    }
    Node* headToDelete = m_front;
    m_front = m_front->m_nextNode;
    delete headToDelete;
    // in case the last element was the first and we delete it we need to "empty" the list
    if (m_front == nullptr)
    {
        m_back = nullptr;
    }
    m_size--;
    return *this;
}

template<class Element>
int Queue<Element>::size() const
{
    return m_size;
}

template<class Element>
bool Queue<Element>::empty() const
{
    return (m_front == nullptr);
}

// aux_functions for the module Queue
template<class Element ,class Function>
Queue<Element> filter(const Queue<Element>& source, Function filterFunction)
{
    Queue<Element> newQueue;
    for(const Element& sourceElement : source)
    {
        if(filterFunction(sourceElement) == true)
        {
            newQueue.pushBack(sourceElement);
        }
    }
    return newQueue;
}

template<class Element, class Function>
void transform(Queue<Element>& queue, Function transformFunction)
{
    for(Element& queueElement : queue)
    {
        transformFunction(queueElement);
    }
}

//---------------------- implementing Node class ----------------------//

template<class Element>
class Queue<Element>::Node
{
    /*
     * C'tor of Node class
     *default constructor
     */
    Node(const Element& data); // this should be like this no???  no refrence ? 

    /*
     * d’tor of Node class
     *
     *
    */
    ~Node() = default; // assumes data have a valid d'tor
    
    // copy c'tor
    Node(const Node& other);
    
    Node& operator=(const Node& other);
    
    Element m_data;
    Node* m_nextNode;

    friend class Queue; // we want Queue to have acsses to the (private) data
};

template<class Element>
Queue<Element>::Node::Node(const Element& data) :
    m_data(data),
    m_nextNode(nullptr)
{}

template<class Element>
Queue<Element>::Node::Node(const Node& other) :
    m_data(other.m_data),
    m_nextNode(nullptr)
{}

template<class Element>
typename Queue<Element>::Node& Queue<Element>::Node::operator=(const Node& other)
{
    // check for self-assignment
    if (this == &other)
    {
        return *this;
    }
    m_data = other.m_data;
    m_nextNode = nullptr;
    return *this;
}
//---------------------- implementing Iterator class ------------------//

/** Iterator
 * the c'tor of an iterator must be private

 * every iterator overload the following three operators:
 * operator*: This overloads the dereference operator (*).
 *               It is used to access the value of the element that the
 *               iterator is currently pointing to.
 * operator++: This overloads the pre-increment operator (++).
 *               It is used to move the iterator to the next element in
 *               the container.
 * operator!=: This overloads the not-equal-to operator (!=).
 *               It is used to compare two iterators and check if they are
 *               pointing to different elements.
*/
template<class Element>
class Queue<Element>::Iterator
{
public:

    // error classes
    class InvalidOperation{};

    // operators
    Element& operator*() const;

    Iterator& operator++();

    bool operator!=(const Iterator& other) const;

    // copy c'tor
    Iterator(const Iterator&) = default;
    // assignment operator
    Iterator& operator=(const Iterator&) = default;
    // d'tor
    ~Iterator() = default;
    
private:

    const Queue* m_queue; // why do we need const here?
    int m_index;
    Node* m_currentNode;

    friend class Queue; // this allows Queue to use the Iterator's c'tor
    // i dont think Node should or even want to acsses the privates of Iterator
    
    // c'tor
    Iterator(const Queue* currentQueue, int index);
};

template<class Element>
Queue<Element>::Iterator::Iterator(const Queue<Element>* currentQueue, int index) :
    m_queue(currentQueue),
    m_index(index),
    m_currentNode(nullptr)
{
    // no need to throw an Error because the c'tor is private
    if (index < m_queue->m_size)
    {
        m_currentNode = m_queue->m_front; // starts at head (if it exists)
        for (int i = 0; i < index; i++)
        {
            m_currentNode = m_currentNode->m_nextNode;
        }
    }
}

template<class Element>
Element& Queue<Element>::Iterator::operator*() const
{
    if (m_index >= m_queue->m_size)
    {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

template<class Element>
typename Queue<Element>::Iterator& Queue<Element>::Iterator::operator++()
{
    if (m_index >= m_queue->m_size)
    {
        throw InvalidOperation();
    }
    ++m_index;
    m_currentNode = m_currentNode->m_nextNode;
    return *this;
}

template<class Element>
bool Queue<Element>::Iterator::operator!=(const Iterator& other) const
{
    return (m_index != other.m_index);
}

template<class Element>
typename Queue<Element>::Iterator Queue<Element>::begin()
{
    return Iterator(this, 0);
}

template<class Element>
typename Queue<Element>::Iterator Queue<Element>::end()
{
    return Iterator(this, m_size);
}

//----------------- implementing ConstIterator class ------------------//
template<class Element>
class Queue<Element>::ConstIterator
{
public:
    // error classes
    class InvalidOperation{};

    // operators
    const Element& operator*() const; // the later const is because * doesnt change the Iterator itself

    ConstIterator& operator++();

    bool operator!=(const ConstIterator& other) const;
    
    // copy c'tor
    ConstIterator(const ConstIterator&) = default;
    // assignment operator
    ConstIterator& operator=(const ConstIterator&) = default;
    // d'tor
    ~ConstIterator() = default;

private:

    const Queue* m_queue; // wants a const Queue
    int m_index;
    Node* m_currentNode;
    
    friend class Queue;

    // c'tor
    ConstIterator(const Queue* currentQueue, int index);
};

// c'tor
template<class Element>
Queue<Element>::ConstIterator::ConstIterator(const Queue<Element>* currentQueue, int index) :
    m_queue(currentQueue),
    m_index(index),
    m_currentNode(nullptr)
{
    if (index < m_queue->m_size)
    {
        m_currentNode = m_queue->m_front; // starts at head (if it exists)
        for (int i = 0; i < index; i++)
        {
            m_currentNode = m_currentNode->m_nextNode;
        }
    }
}

template<class Element>
const Element& Queue<Element>::ConstIterator::operator*() const // the later const is because * doesnt change the Iterator itself
{
    if (m_index >= m_queue->m_size)
    {
        throw InvalidOperation();
    }
    return m_currentNode->m_data;
}

template<class Element>
typename Queue<Element>::ConstIterator& Queue<Element>::ConstIterator::operator++()
{
    if (m_index >= m_queue->m_size)
    {
        throw InvalidOperation();
    }
    ++m_index;
    m_currentNode = m_currentNode->m_nextNode;
    return *this;
}

template<class Element>
bool Queue<Element>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return (m_index != other.m_index);
}

template<class Element>
typename Queue<Element>::ConstIterator Queue<Element>::begin() const
{
    return ConstIterator(this, 0);
}

template<class Element>
typename Queue<Element>::ConstIterator Queue<Element>::end() const
{
    return ConstIterator(this, m_size);
}
