#include "Node.h"

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
}