#ifndef NODE_H
#define NODE_H

#include "Transaction.h"

class Node
{
public:
    Transaction transaction;
    Node *prev;
    Node *next;

    Node(const Transaction &transaction);
};

#endif