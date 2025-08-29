#include <iostream>
class Transaction {
public:
    Transaction() {const std::string& logInfo};
    void LogTransaction(const std::string& logInfo) const;
    Transaction::Transaction(const std::string& logInfo) {
    LogTransaction(logInfo); 
    }
};

class subTrans : public Transaction{
public:
    LogTransaction(logInfo);  
};

int main() {
    subTrans t;  // prints: Printing from SubTrans
    t.LogTransaction();
}