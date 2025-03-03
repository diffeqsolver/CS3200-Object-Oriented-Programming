#ifndef ARITHSEQ_H
#define ARITHSEQ_H
#include <memory>

class ArithSeq {
public:

    ArithSeq(int firstTerm, int commonDiff, int length, int maxOperations);

    ArithSeq &operator=(ArithSeq &&other) noexcept;

    ArithSeq &operator=(const ArithSeq &other) noexcept;

    ArithSeq(ArithSeq &&other) noexcept;

    ArithSeq(const ArithSeq &other) noexcept;


    void generateSequence();

    virtual int getLength();


    virtual void reset();

    int getKthVal(int k);

    int evenlyDividedBy(int n);

    virtual void modifyEveryPthValue(int p, int q);


    bool operator==(const ArithSeq &other) const;

    bool operator!=(const ArithSeq &other) const;

    ArithSeq &operator++();

    ArithSeq operator++(int);

    ArithSeq &operator--();

    ArithSeq operator--(int);

    int operator[](int index);

    ArithSeq &operator+(ArithSeq &other);

protected:
    std::shared_ptr<int[]> sequence;
    int operationCount;
    int maxOperations;
    int commonDiff;
    int firstTerm;
    int length;

private:
    bool checkOperationLimit();

    void copy(const ArithSeq &other) noexcept;
};

#endif //ARITHSEQ_H
