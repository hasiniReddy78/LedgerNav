#include "Ledger.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

// Constructor
Ledger::Ledger(int userId)
    : head(nullptr), tail(nullptr), current(nullptr), account(userId)
{
}

// Destructor
Ledger::~Ledger()
{
    clear();
}

// Free all doubly linked list nodes and reset state
void Ledger::clear()
{
    Node *curr = head;
    while (curr != nullptr)
    {
        Node *nextNode = curr->next;
        delete curr; // Node destructor deletes transaction
        curr = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    account.reset();
}

// History State Management: Discard forward history when branching from an undo state
void Ledger::discardForwardHistory()
{
    Node *discardNode = (current == nullptr) ? head : current->next;

    if (current != nullptr)
    {
        current->next = nullptr;
        tail = current;
    }
    else
    {
        head = nullptr;
        tail = nullptr;
    }

    int count = 0;
    while (discardNode != nullptr)
    {
        Node *nextNode = discardNode->next;
        delete discardNode; // Deletes node and underlying Transaction
        discardNode = nextNode;
        count++;
    }

    if (count > 0)
    {
        cout << "\n>>> [History State Management] Discarded " << count
             << " forward transaction(s) following an undo fork.\n";
    }
}

// Add transaction with browser-style history management
void Ledger::addTransaction(Transaction *transaction)
{
    if (transaction == nullptr)
    {
        throw InvalidTransactionException("Cannot add a null transaction to the ledger.");
    }

    // Discard any forward history if we are currently navigated backwards
    if (current != tail)
    {
        discardForwardHistory();
    }

    Node *newNode = new Node(transaction);

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Set cursor to the newly added tip of history
    current = tail;

    // Apply financial effects to Account state
    transaction->applyToAccount(account);
}

// Can navigate backward (Undo)
bool Ledger::canUndo() const
{
    return current != nullptr;
}

// Can navigate forward (Redo)
bool Ledger::canRedo() const
{
    return (current == nullptr && head != nullptr) ||
           (current != nullptr && current->next != nullptr);
}

// Browser-Style Undo: roll back current transaction and move cursor backwards
Transaction *Ledger::undo()
{
    if (!canUndo())
    {
        throw HistoryNavigationException("Cannot Undo: Already at the earliest recorded state (Genesis).");
    }

    Transaction *rolledBackTx = current->transaction;
    rolledBackTx->rollbackFromAccount(account);

    current = current->prev;
    return rolledBackTx;
}

// Browser-Style Redo: move cursor forwards and re-apply transaction
Transaction *Ledger::redo()
{
    if (!canRedo())
    {
        throw HistoryNavigationException("Cannot Redo: Already at the latest transaction state.");
    }

    Node *target = (current == nullptr) ? head : current->next;
    current = target;
    current->transaction->applyToAccount(account);

    return current->transaction;
}

// Recalculate account state strictly up to current cursor
void Ledger::recalculateAccountState()
{
    account.reset();
    Node *curr = head;
    while (curr != nullptr)
    {
        curr->transaction->applyToAccount(account);
        if (curr == current)
        {
            break;
        }
        curr = curr->next;
    }
}

// Visual history timeline renderer
void Ledger::displayHistoryTimeline() const
{
    cout << "\n=================== TRANSACTION HISTORY TIMELINE ===================\n";
    if (head == nullptr)
    {
        cout << "[Empty Ledger] No transaction history recorded.\n";
        cout << "====================================================================\n";
        return;
    }

    cout << (current == nullptr ? "[*CURSOR: GENESIS (0 TX applied)]" : "[Genesis: 0 TX]") << "\n";
    cout << "       |\n";

    Node *curr = head;
    int index = 1;
    bool isForward = (current == nullptr);

    while (curr != nullptr)
    {
        cout << "       v\n";
        cout << "  #" << index << " [ID: " << curr->transaction->getId()
             << " | " << curr->transaction->getType()
             << " | Rs. " << fixed << setprecision(2) << curr->transaction->getAmount()
             << " | " << curr->transaction->getCategory()
             << " | " << curr->transaction->getDate() << "]";

        if (curr == current)
        {
            cout << " <== [CURRENT ACTIVE CURSOR]";
            isForward = true;
        }
        else if (isForward)
        {
            cout << " [FORWARD / REDOABLE]";
        }
        else
        {
            cout << " [APPLIED]";
        }
        cout << "\n";

        curr = curr->next;
        index++;
    }

    cout << "====================================================================\n";
    cout << "Navigation Status: "
         << (canUndo() ? "[<- Undo Available] " : "[<- Undo Disabled] ")
         << (canRedo() ? "[Redo Available ->]" : "[Redo Disabled ->]") << "\n";
    if (canRedo())
    {
        cout << "Note: Adding a new transaction right now will DISCARD forward history!\n";
    }
    cout << "====================================================================\n";
}

// Interactive Browser-style Navigator console
void Ledger::navigateHistory()
{
    char navChoice;
    do
    {
        cout << "\n+-------------------------------------------------------------+\n";
        cout << "|             TRANSACTION HISTORY NAVIGATOR                   |\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "  Current Status: ";
        if (current == nullptr)
        {
            cout << "GENESIS (Zero transactions applied)\n";
        }
        else
        {
            cout << "Transaction #" << current->transaction->getId()
                 << " (" << current->transaction->getType()
                 << " - Rs. " << current->transaction->getAmount() << ")\n";
        }
        cout << "  Account Balance at this point: Rs. " << account.getBalance() << "\n";
        cout << "  [U]ndo (<- Back)    : " << (canUndo() ? "AVAILABLE" : "DISABLED") << "\n";
        cout << "  [R]edo (-> Forward) : " << (canRedo() ? "AVAILABLE" : "DISABLED") << "\n";
        cout << "  [V]iew Current Transaction Details\n";
        cout << "  [T]imeline Full View\n";
        cout << "  [A]ccount State Breakdown\n";
        cout << "  [Q]uit Navigator\n";
        cout << "+-------------------------------------------------------------+\n";
        cout << "Enter command (U/R/V/T/A/Q): ";
        cin >> navChoice;

        navChoice = toupper(navChoice);

        try
        {
            switch (navChoice)
            {
            case 'U':
            {
                Transaction *tx = undo();
                cout << "\n<<< [UNDONE] Successfully rolled back Transaction #"
                     << tx->getId() << " (" << tx->getType() << " of Rs. " << tx->getAmount() << ").\n";
                break;
            }
            case 'R':
            {
                Transaction *tx = redo();
                cout << "\n>>> [REDONE] Successfully advanced to Transaction #"
                     << tx->getId() << " (" << tx->getType() << " of Rs. " << tx->getAmount() << ").\n";
                break;
            }
            case 'V':
            {
                if (current == nullptr)
                {
                    cout << "\nAt Genesis state. No transaction is currently selected.\n";
                }
                else
                {
                    cout << "\n--- Currently Active Transaction ---\n";
                    current->transaction->display();
                }
                break;
            }
            case 'T':
                displayHistoryTimeline();
                break;
            case 'A':
                account.displayAccountSummary();
                break;
            case 'Q':
                cout << "\nExiting History Navigator.\n";
                break;
            default:
                cout << "\nInvalid navigator option! Please enter U, R, V, T, A, or Q.\n";
            }
        }
        catch (const LedgerException &e)
        {
            cout << "\n[Navigation Alert] " << e.what() << "\n";
        }
    } while (navChoice != 'Q');
}

// Display all transactions with history state indication
void Ledger::displayTransactions() const
{
    if (head == nullptr)
    {
        cout << "No transactions found.\n";
        return;
    }

    Node *curr = head;
    bool isForward = (current == nullptr);

    while (curr != nullptr)
    {
        if (curr == current)
        {
            cout << "\n>>> [CURRENT HISTORY POSITION] <<<\n";
            isForward = true;
        }
        else if (isForward)
        {
            cout << "\n[FORWARD / REDOABLE TRANSACTION]\n";
        }

        curr->transaction->display();
        curr = curr->next;
    }
}

// Financial summary report
void Ledger::displayFinancialSummary() const
{
    account.displayAccountSummary();
}

int Ledger::getHighestTransactionId() const
{
    if (head == nullptr)
        return 1000;

    int highestId = 1000;
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getId() > highestId)
        {
            highestId = curr->transaction->getId();
        }
        curr = curr->next;
    }
    return highestId;
}

Node *Ledger::getHead() const
{
    return head;
}

Node *Ledger::getTail() const
{
    return tail;
}

Node *Ledger::getCurrent() const
{
    return current;
}

const Account &Ledger::getAccount() const
{
    return account;
}

void Ledger::setUserId(int userId)
{
    account = Account(userId);
}

// Update transaction details
bool Ledger::updateTransaction(int id, const string &date, double amount,
                               const string &category, const string &type,
                               const string &description)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getId() == id)
        {
            int uid = curr->transaction->getUserId();
            // Create updated transaction polymorphically using factory
            Transaction *updated = TransactionFactory::createTransaction(
                id, uid, date, amount, category, type, description);

            delete curr->transaction;
            curr->transaction = updated;

            recalculateAccountState();
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Delete transaction by ID
bool Ledger::deleteTransaction(int id)
{
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getId() == id)
        {
            // If current was pointing to this node, move current to prev
            if (current == curr)
            {
                current = curr->prev;
            }

            if (curr->prev != nullptr)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }

            if (curr->next != nullptr)
            {
                curr->next->prev = curr->prev;
            }
            else
            {
                tail = curr->prev;
            }

            delete curr; // cleans up transaction
            recalculateAccountState();
            return true;
        }
        curr = curr->next;
    }
    return false;
}

// Search transactions
void Ledger::searchTransactions(int searchChoice, const string &query) const
{
    Node *curr = head;
    bool found = false;

    while (curr != nullptr)
    {
        bool match = false;
        Transaction *t = curr->transaction;

        if (searchChoice == 1) // ID
        {
            try
            {
                int idQuery = stoi(query);
                if (t->getId() == idQuery)
                    match = true;
            }
            catch (...) {}
        }
        else if (searchChoice == 2) // Category
        {
            if (t->getCategory().find(query) != string::npos)
                match = true;
        }
        else if (searchChoice == 3) // Date
        {
            if (t->getDate() == query)
                match = true;
        }
        else if (searchChoice == 4) // Type
        {
            if (t->getType().find(query) != string::npos)
                match = true;
        }

        if (match)
        {
            t->display();
            found = true;
        }
        curr = curr->next;
    }

    if (!found)
    {
        cout << "No matching transactions found.\n";
    }
}

// Date comparison helper
int Ledger::compareDates(const string &d1, const string &d2)
{
    if (d1.length() != 10 || d2.length() != 10)
        return d1.compare(d2);

    string day1 = d1.substr(0, 2);
    string month1 = d1.substr(3, 2);
    string year1 = d1.substr(6, 4);

    string day2 = d2.substr(0, 2);
    string month2 = d2.substr(3, 2);
    string year2 = d2.substr(6, 4);

    if (year1 != year2)
        return year1.compare(year2);
    if (month1 != month2)
        return month1.compare(month2);
    return day1.compare(day2);
}

// Split DLL helper for Merge Sort
Node *Ledger::split(Node *h)
{
    Node *fast = h;
    Node *slow = h;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *temp = slow->next;
    slow->next = nullptr;
    if (temp != nullptr)
    {
        temp->prev = nullptr;
    }
    return temp;
}

// In-place Merge helper for Merge Sort
Node *Ledger::merge(Node *first, Node *second, int sortChoice)
{
    if (!first)
        return second;
    if (!second)
        return first;

    Node *mergedHead = nullptr;
    Node *mergedTail = nullptr;

    while (first && second)
    {
        bool firstIsSmaller = false;
        if (sortChoice == 1) // Date
        {
            firstIsSmaller = compareDates(first->transaction->getDate(),
                                          second->transaction->getDate()) <= 0;
        }
        else if (sortChoice == 2) // Amount
        {
            firstIsSmaller = first->transaction->getAmount() <= second->transaction->getAmount();
        }
        else if (sortChoice == 3) // Category
        {
            firstIsSmaller = first->transaction->getCategory() <= second->transaction->getCategory();
        }

        Node *chosen = nullptr;
        if (firstIsSmaller)
        {
            chosen = first;
            first = first->next;
        }
        else
        {
            chosen = second;
            second = second->next;
        }

        if (!mergedHead)
        {
            mergedHead = chosen;
            mergedTail = chosen;
            mergedHead->prev = nullptr;
        }
        else
        {
            mergedTail->next = chosen;
            chosen->prev = mergedTail;
            mergedTail = chosen;
        }
    }

    if (first)
    {
        mergedTail->next = first;
        first->prev = mergedTail;
        while (mergedTail->next)
        {
            mergedTail = mergedTail->next;
        }
    }
    else if (second)
    {
        mergedTail->next = second;
        second->prev = mergedTail;
        while (mergedTail->next)
        {
            mergedTail = mergedTail->next;
        }
    }

    return mergedHead;
}

// Recursive Merge Sort
Node *Ledger::mergeSort(Node *h, int sortChoice)
{
    if (!h || !h->next)
        return h;

    Node *second = split(h);

    h = mergeSort(h, sortChoice);
    second = mergeSort(second, sortChoice);

    return merge(h, second, sortChoice);
}

// Public Sort method: sorts in-place, updates head, tail, and cursor
void Ledger::sortTransactions(int sortChoice)
{
    head = mergeSort(head, sortChoice);

    Node *temp = head;
    while (temp && temp->next)
    {
        temp = temp->next;
    }
    tail = temp;
    current = tail; // set cursor to latest after sort
    recalculateAccountState();
}

// Category-wise Expense Report
void Ledger::displayCategoryExpenseReport() const
{
    map<string, double> categoryTotals;
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getType() == "Expense")
        {
            categoryTotals[curr->transaction->getCategory()] += curr->transaction->getAmount();
        }
        curr = curr->next;
    }

    cout << "\n========== Category-wise Expense Report ==========\n";
    if (categoryTotals.empty())
    {
        cout << "No expenses recorded.\n";
    }
    else
    {
        for (const auto &pair : categoryTotals)
        {
            cout << pair.first << " : Rs. " << fixed << setprecision(2) << pair.second << "\n";
        }
    }
    cout << "==================================================\n";
}

// Investment Report
void Ledger::displayInvestmentReport() const
{
    map<string, double> investmentTotals;
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getType() == "Investment")
        {
            investmentTotals[curr->transaction->getCategory()] += curr->transaction->getAmount();
        }
        curr = curr->next;
    }

    cout << "\n========== Investment Report ==========\n";
    if (investmentTotals.empty())
    {
        cout << "No investments recorded.\n";
    }
    else
    {
        for (const auto &pair : investmentTotals)
        {
            cout << pair.first << " : Rs. " << fixed << setprecision(2) << pair.second << "\n";
        }
    }
    cout << "=======================================\n";
}

// Monthly Report
void Ledger::displayMonthlyReport(int month, int year) const
{
    double income = 0.0;
    double expense = 0.0;
    double investment = 0.0;
    int count = 0;

    Node *curr = head;
    while (curr != nullptr)
    {
        string date = curr->transaction->getDate();
        if (date.length() == 10)
        {
            try
            {
                int tMonth = stoi(date.substr(3, 2));
                int tYear = stoi(date.substr(6, 4));

                if (tMonth == month && tYear == year)
                {
                    count++;
                    if (curr->transaction->getType() == "Income")
                    {
                        income += curr->transaction->getAmount();
                    }
                    else if (curr->transaction->getType() == "Expense")
                    {
                        expense += curr->transaction->getAmount();
                    }
                    else if (curr->transaction->getType() == "Investment")
                    {
                        investment += curr->transaction->getAmount();
                    }
                }
            }
            catch (...) {}
        }
        curr = curr->next;
    }

    cout << "\n========== Monthly Report ("
         << (month < 10 ? "0" : "") << month << "-" << year << ") ==========\n";
    cout << "Total Transactions : " << count << "\n";
    cout << "Total Income       : Rs. " << fixed << setprecision(2) << income << "\n";
    cout << "Total Expense      : Rs. " << expense << "\n";
    cout << "Total Investment   : Rs. " << investment << "\n";
    cout << "Net Monthly Balance: Rs. " << (income - expense - investment) << "\n";
    cout << "====================================================\n";
}

// Budget Status Dashboard
void Ledger::displayBudgetStatus(const map<string, double> &budgets) const
{
    cout << "\n========== Budget Status Dashboard ==========\n";
    if (budgets.empty())
    {
        cout << "No budgets set yet. Set a budget to track spending.\n";
        cout << "==============================================\n";
        return;
    }

    map<string, double> spentByCategory;
    Node *curr = head;
    while (curr != nullptr)
    {
        if (curr->transaction->getType() == "Expense")
        {
            spentByCategory[curr->transaction->getCategory()] += curr->transaction->getAmount();
        }
        curr = curr->next;
    }

    for (const auto &pair : budgets)
    {
        string category = pair.first;
        double budgetAmount = pair.second;
        double spent = spentByCategory[category];
        double remaining = budgetAmount - spent;

        cout << "Category:  " << category << "\n";
        cout << "  Budget:    Rs. " << fixed << setprecision(2) << budgetAmount << "\n";
        cout << "  Spent:     Rs. " << spent << "\n";
        cout << "  Remaining: Rs. " << remaining << "\n";
        if (spent > budgetAmount)
        {
            cout << "  WARNING: Budget exceeded by Rs. " << (spent - budgetAmount) << "!\n";
        }
        cout << "----------------------------------------------\n";
    }
    cout << "==============================================\n";
}