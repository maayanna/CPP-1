/**
 * @file my_set.h
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

#ifndef EX1_MY_SET_H
#define EX1_MY_SET_H

// ------------------------------ includes ------------------------------

#include "big_integer.h"
#include <string>

/**
 * a class that implements a set of big_integers
 */
class my_set
{
    /**
     * A node of a set with a next and a big_integers as members
     */
    class Node
    {

    public:

        /**
         * Node constructor
         * @param big_int - big_integer
         */
        Node(big_integer big_int);

        /**
         * Get data
         * @return big_integer
         */
        big_integer getData();

        /**
         * Get next node
         * @return - node
         */
        Node* getNext();

        /**
         * Set the next node
         * @param next - node
         */
        void setNext(Node* next);

    private:

        /* Members */
        big_integer _data;
        Node* _next;

    };

public:

    /**
     * Get Head of the set
     * @return Node - the head
     */
    Node* getHead() const;

    /**
     * set the head of the set
     * @param head - node
     */
    void setHead(my_set::Node* head);

    /**
     * Default constructor
     */
    my_set();

    /**
     * Copy constructor
     * @param set - another my_set
     */
    my_set(const my_set& set);

    /**
     * Destructor
     */
    ~my_set();

    /**
     * Check if the big_int is already in the set
     * @param big_int - the big_integer to check
     * @return true iff the big_int already in the set
     */
    bool is_in_set(const big_integer& big_int) const;

    /**
    * Add the big_int to the set if not already in the set
    * @param big_int - big_integer to add
    * @return true iff the big_int was succesfully add
    */
    bool add(big_integer big_int);

    /**
    * Removing a big_int if in the set
    * @param big_int - big_integer to remove
    * @return true iff the big_int was succesfully removed
    */
    bool remove(big_integer big_int);

    /**
    * Returning the sum of all big_integers in the set
    * @return big_integer - sum of all of them
    */
    big_integer sum_set();

    /**
     * Returning a set with all the nodes in a but not in b
     * @param a - set a
     * @param b - set b
     * @return a/b
     */
    friend my_set operator-(const my_set& a, const my_set& b);

    /**
     * Returning a set with all the nodes in a and in b
     * @param a  - set A
     * @param b - set B
     * @return  AUB
     */
    friend my_set operator|(const my_set& a, const my_set& b);

    /**
     * returning a set with all the nodes in a and also in b
     * @param a - set A
     * @param b - set B
     * @return A∩B
     */
    friend my_set operator&(const my_set &a, const my_set &b);

    /**
     * Printing operator
     * @param os
     * @param set
     * @return ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const my_set& set);

    /**
     * Operator =
     * @param set - the new set
     * @return set& with all the informations of the new set
     */
    my_set& operator=(const my_set& set);

private:

    /* Member */
    Node* _head; // the head of the set

};

#endif //EX1_MY_SET_H