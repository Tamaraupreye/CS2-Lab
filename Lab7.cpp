#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void wait() {
    string c;
    cout << "Press <Return> to continue... ";
    cin.ignore();
    getline(cin, c);
}

struct Transaction {
    int txnNo;
    float LCYAmount, FCYAmount;
    float exchRate, exchAmount;

    void print() {
        cout << "Txn. No.: " << txnNo << endl;
        cout << "LCY Amount: " << LCYAmount << " ";
        cout << "FCY Amount: " << FCYAmount << " ";
        cout << "Exchange Rate: " << exchRate << " ";
        cout << "Amount: " << exchAmount << endl;
    }
};

class CurrExchObj {
    private:
    string LCY, FCY;
    float LFRate, FLRate;
    vector<Transaction> txns;
    public:
    static int txnCount;
    
    CurrExchObj(string LCY, string FCY, float LFRate, float FLRate) {
        this->LCY = LCY;
        this->FCY = FCY;
        this->LFRate = LFRate;
        this->FLRate = FLRate;
    }

    void setLCY(string LCY) {
        this->LCY = LCY;
    }

    string getLCY() {
        return this->LCY;
    }

    void setFCY(string FCY) {
        this->FCY = FCY;
    }

    string getFCY() {
        return this->FCY;
    }

    void setLFRate(float LFRate) {
        this->LFRate = LFRate;
    }

    float getLFRate() {
        return this->LFRate;
    }

    void setFLRate(float FLRate) {
        this->FLRate = FLRate;
    }

    float getFLRate() {
        return this->FLRate;
    }

    void addTxn(float LCYAmount, float FCYAmount) {
        if (LCYAmount == 0 && FCYAmount != 0) {
            Transaction t = {++txnCount, LCYAmount, FCYAmount, FLRate, FLRate * FCYAmount};
            this->txns.push_back(t);
        } else if (FCYAmount == 0 && LCYAmount != 0) {
            Transaction t = {++txnCount, LCYAmount, FCYAmount, LFRate, LFRate * LCYAmount};
            this->txns.push_back(t);
        } else {
            cout << "Invalid transaction, could not save..." << endl;
        };
    }

    void printTxns() {
        cout << "Currency Exchange Transactions....." << endl;
        for (Transaction t: this->txns) {
            t.print();
        }
    }

    ~CurrExchObj() {}
};

int CurrExchObj::txnCount = 100;

int main() {
    vector<CurrExchObj> currExchObjVect;

    string LCY, FCY;
    float LFRate, FLRate, LCYAmount, FCYAmount;
    int i = 0;
    while (true) {
        clearScreen();
        cout << "LCY (enter q to quit): ";
        cin >> LCY;
        if (LCY == "q") break;
        cout << "FCY: ";
        cin >> FCY;
        cout << "LFRate: ";
        cin >> LFRate;
        cout << "FLRate: ";
        cin >> FLRate;
        currExchObjVect.push_back(CurrExchObj(LCY, FCY, LFRate, FLRate));
        cout << endl;

        while (true) {
            cout << "LCYAmount (enter number less than 0 to quit): ";
            cin >> LCYAmount;
            if (LCYAmount < 0) break;
            cout << "FCYAmount: ";
            cin >> FCYAmount;
            currExchObjVect[i].addTxn(LCYAmount, FCYAmount);
            cout << endl;
        }

        i++;
    }

    // CurrExchObj a ("USD", "EUR", 0.9, 1.11);
    // a.addTxn(100, 0);
    // a.addTxn(0, 250);
    // a.addTxn(40, 0);
    // currExchObjVect.push_back(a);

    // CurrExchObj b ("USD", "CAD", 1.31, 0.76);
    // b.addTxn(80, 0);
    // b.addTxn(0, 132);
    // currExchObjVect.push_back(b);

    // CurrExchObj c ("USD", "JPY", 108.5, 0.01);
    // c.addTxn(0, 500);
    // c.addTxn(200, 0);
    // currExchObjVect.push_back(c);

    cout << endl << "Reporting......" << endl << endl;
    for (CurrExchObj x: currExchObjVect) {
        cout << "LCY: " << x.getLCY() << " LCY Rate: " << x.getLFRate() << " ";
        cout << "FCY: " << x.getFCY() << " FCY Rate: " << x.getFLRate() << endl;
        x.printTxns();
        cout << endl;
    }
}