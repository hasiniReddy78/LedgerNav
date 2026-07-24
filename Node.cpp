#include "Node.h"

Node::Node(const Transaction &transaction)
{
    this->transaction = transaction;
    prev = nullptr;
    next = nullptr;
}