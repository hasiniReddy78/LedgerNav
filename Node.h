#ifndef NODE_H
#define NODE_H

#include "Transaction.h"

class Node
{
public:
<<<<<<< HEAD
    Transaction *transaction;
    Node *prev;
    Node *next;

    explicit Node(Transaction *tx);
    ~Node();
};

#endif // NODE_H
=======
    Transaction transaction;
    Node *prev;
    Node *next;

    Node(const Transaction &transaction);
};

#endif
>>>>>>> 435c46a1aee22335a79412aecc6d4a1e06817e74
