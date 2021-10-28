/**
 * @file my_set.cpp
 * @author  Maayann Affriat <maayann.affriat@mail.huji.ac.il>
 * @version 1.0
 * @date 3 sep 2018
 *
 * @brief
 *
 * @section LICENSE
 * This program is not a free software.
 *
 * @section DESCRIPTION
 */

// ------------------------------ includes ------------------------------

#include <algorithm>
#include <iostream>
#include "my_set.h"

/**
 * Node construtor
 * @param big_int - big_integer
 */
my_set::Node::Node(big_integer big_int)
{
    _data = big_int;
    _next = nullptr;
}

/**
 * Get the data
 * @return big_integer - data
 */
big_integer my_set::Node::getData()
{
    return _data;
}

/**
 * Get the next node
 * @return Node
 */
my_set::Node* my_set::Node::getNext()
{
    return _next;
}

/**
 * Set the next node
 * @param next
 */
void my_set::Node::setNext(Node* next)
{
    _next = next;
}

/**
 * Get the head of the set
 * @return Node - head
 */
my_set::Node* my_set::getHead() const
{
    return _head;
}

/**
 * Set the head of the set
 * @param head - Node
 */
void my_set::setHead(Node* head)
{
    _head = head;
}

/**
 * Default constructor
 */
my_set::my_set()
{
    _head = nullptr;
}

/**
 * copy constructor
 * @param Set - another set
 */
my_set::my_set(const my_set& Set)
{
    setHead(nullptr);
    Node* myNode = Set.getHead();

    while(myNode != nullptr) //copying all the set
    {
        add(myNode->getData());
        myNode = myNode->getNext();
    }
}

/**
 * Check if the big_int is already in the set
 * @param big_int - the big_integer to check
 * @return true iff the big_int already in the set
 */
bool my_set::is_in_set(const big_integer& big_int) const
{
    Node* myNode = getHead();

    if (myNode == nullptr)
    {
        return false; //Empty set
    }

    while(myNode != nullptr) //Otherwise
    {
        if (myNode->getData() == big_int)
        {
            return true;
        }
        myNode = myNode->getNext();
    }
    return false;
}

/**
 * Add the big_int to the set if not already in the set
 * @param big_int - big_integer to add
 * @return true iff the big_int was succesfully add
 */
bool my_set::add(big_integer big_int)
{
    Node* newOne = new Node(big_int);

    if (is_in_set(big_int))
    {
        delete(newOne); //freeing the memory
        return false;
    }

    Node* myNode = getHead();
    Node* previous = nullptr;

    if (myNode == nullptr)
    {
        setHead(newOne);
        return true;
    }

    while (myNode != nullptr)
    {
        if(myNode->getData() < big_int) //Adding directy in ascending order
        {
            previous = myNode;
            myNode = myNode->getNext();
        }
        else
        {
            break;
        }
    }
    if (previous == nullptr)
    {
        setHead(newOne);
    }
    else
    {
        previous->setNext(newOne);
    }
    newOne->setNext(myNode);
    return true;

}

/**
 * Removing a big_int if in the set
 * @param big_int - big_integer to remove
 * @return true iff the big_int was succesfully removed
 */
bool my_set::remove(big_integer big_int)
{
    if (!is_in_set(big_int))
    {
        return false; //Not in the set
    }

    Node* previous = nullptr;
    Node* myNode = getHead();

    while(myNode != nullptr)
    {
        if(myNode->getData() == big_int)
        {
            Node* temp = myNode->getNext();
            if (previous == nullptr)
            {
                setHead(temp);
            }
            else
            {
                previous->setNext(temp);
            }
            delete(myNode); //deleting the node
            return true;
        }
        previous = myNode; //Need to rely the nodes
        myNode = myNode->getNext();
    }
    return true;
}

/**
 * Returning the sum of all big_integers in the set
 * @return big_integer - sum of all of them
 */
big_integer my_set::sum_set()
{
    big_integer toReturn = big_integer();
    Node* myNode = getHead();

    while(myNode != nullptr)
    {
        toReturn += myNode->getData();
        myNode = myNode->getNext();
    }
    return toReturn;
}

/**
 * Returning a set with all the nodes in a but not in b
 * @param a - set a
 * @param b - set b
 * @return a/b
 */
my_set operator-(const my_set& a, const my_set& b)
{
    my_set toReturn = my_set(a);
    my_set::Node* temp = a.getHead();
    big_integer big1;

    while(temp != nullptr)
    {
        big1 = temp->getData();
        if (b.is_in_set(big1)) //A without B
        {
            toReturn.remove(big1);
        }
        temp = temp->getNext();
    }
    return toReturn;
}

/**
 * Returning a set with all the nodes in a and in b
 * @param a  - set A
 * @param b - set B
 * @return  AUB
 */
my_set operator|(const my_set& a, const my_set& b)
{
    my_set toReturn = my_set(a);
    my_set::Node *myNode = b.getHead();
    big_integer big1;

    while (myNode != nullptr)
    {
        big1 = myNode->getData();
        if (!a.is_in_set(big1))
        {
            if (toReturn.getHead() == nullptr) //Head of the set
            {
                toReturn.add(big1);
            }
            else
            {
                toReturn.add(big1);
            }
        }
        myNode = myNode->getNext();
    }
    return toReturn;
}

/**
 * returning a set with all the nodes in a and also in b
 * @param a - set A
 * @param b - set B
 * @return A∩B
 */
my_set operator&(const my_set& a, const my_set& b)
{
    my_set toReturn = my_set(a);
    my_set::Node* temp = a.getHead();
    big_integer big1;

    while(temp != nullptr)
    {
        big1 = temp->getData();
        if (!b.is_in_set(big1)) //Need to be in a and in b
        {
            toReturn.remove(big1);
        }
        temp = temp->getNext();
    }
    return toReturn;
}

/**
 * Printing operator
 * @param os
 * @param set
 * @return ostream&
 */
std::ostream& operator<<(std::ostream& os, const my_set& set)
{
    // In order to print them in an ascending order I decided to add them
    // directly checking the big_integers between them.
    // Like that, we just need to run on every node to print them in an
    // order, who takes only o(n)
    string toReturn;
    my_set::Node* myNode = set.getHead();
    int sign;
    string data;

    if(myNode == nullptr)
    {
        toReturn = "\n";
        return os << toReturn;
    }

    while(myNode != nullptr)
    {
        sign = myNode->getData().getSign();
        data = myNode->getData().getData();
        reverse(data.begin(), data.end());
        if (sign == NEG)
        {
            toReturn += "-";
        }
        toReturn += data;
        toReturn += "\n";
        myNode = myNode->getNext();
    }

    return os << toReturn;
}

/**
 * Operator =
 * @param set - the new set
 * @return set& with all the informations of the new set
 */
my_set& my_set::operator=(const my_set& set)
{
    if ( this == &set)
    {
        return *this;
    }

    Node* next;
    Node* myNode = getHead();

    while(myNode != nullptr) //deleting all the old informations
    {
        next = myNode->getNext();
        delete(myNode);
        myNode = next;
    }

    setHead(nullptr);
    myNode = set.getHead();

    while(myNode != nullptr) // Using the new set
    {
        add(myNode->getData());
        myNode = myNode->getNext();
    }
    return *this;
}

/**
 * Destructor
 */
my_set::~my_set()
{
    my_set::Node* myNode = getHead();
    my_set::Node* temp;

    while(myNode != nullptr)
    {
        temp = myNode->getNext();
        delete(myNode);
        myNode = temp;
    }
}