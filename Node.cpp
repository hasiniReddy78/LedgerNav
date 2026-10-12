#include "Node.h"

<<<<<<< HEAD
Node::Node(Transaction *tx)
    : transaction(tx), prev(nullptr), next(nullptr)
{
}

Node::~Node()
{
    if (transaction != nullptr)
    {
        delete transaction;
        transaction = nullptr;
    }
=======
Node::Node(const Transaction &transaction)
{
    this->transaction = transaction;
    prev = nullptr;
    next = nullptr;
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
}