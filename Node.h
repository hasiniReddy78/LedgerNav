#ifndef NODE_H
#define NODE_H

#include "Transaction.h"

class Node
{
public:
    Transaction *transaction;
    Node *prev;
    Node *next;

    explicit Node(Transaction *tx);
    ~Node();
};

#endif // NODE_H
