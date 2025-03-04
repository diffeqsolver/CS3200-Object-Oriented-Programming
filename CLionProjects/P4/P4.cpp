#include <iostream>
#include <memory>
#include "ArithSeq.h"
#include "AsymPattern.h"
#include "DurableSeq.h"

//equality == and !=
bool testAllEquality();
bool testAPEquality();
bool testASEquality();
bool testDSEquality();

//pre and post increment ++
bool testAllPrePostIncrement();
bool testAPIncrement();
bool testASIncrement();
bool testDSIncrement();

//pre and post decrement --
bool testAllPrePostDecrement();
bool testAPDecrement();
bool testASDecrement();
bool testDSDecrement();

//addition operator +
bool testASAdd();

//tests for efficient, deep copying
bool testAllCopy();
bool testASCopy();
bool testDSCopy();

bool testAllEquality() {
    bool passed = true;
    if (!testAPEquality()) {
        std::cerr << "AsymPattern equailty failed" << std::endl;
        passed = false;
    }
    if (!testASEquality()) {
        std::cerr << "ArithSeq equailty failed" << std::endl;
        passed = false;
    }
    if (!testDSEquality()) {
        std::cerr << "DurableSeq equailty failed" << std::endl;
        passed = false;
    }
    return passed;
}
bool testAPEquality() {
    bool passed = true;
    try {
        int length = 2;
        //ap with ArithSeq and DurableSeq
        std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap1 = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(
            new std::shared_ptr<ArithSeq>[length]);
        ap1[0] = std::make_shared<ArithSeq>(10, 1, 4, 10);
        ap1[1] = std::make_shared<DurableSeq>(2, 2, 3, 10, "file1.txt");
        AsymPattern pattern1(ap1, length);

        //AP with same data but different filePath for a DurableSeq, should not matter
        std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap2 = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(
            new std::shared_ptr<ArithSeq>[length]);
        ap2[0] = std::make_shared<ArithSeq>(10, 1, 4, 10);
        ap2[1] = std::make_shared<DurableSeq>(2, 2, 3, 10, "file2.txt");
        AsymPattern pattern2(ap2, length);

        //should be true, all data members are the same except filePath
        if (!(pattern1 == pattern2)) {
            std::cout << "Failure of AP == operator" << std::endl;
        }
        //self equality check, should return true
        if (!(pattern1 == pattern1)) {
            std::cerr << "Failure of AP == self equality check" << std::endl;
            passed = false;
        }

        //AP with different data from pattern1 and pattern2
        std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap3 = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(
            new std::shared_ptr<ArithSeq>[length]);
        ap3[0] = std::make_shared<ArithSeq>(111, 1, 2, 15);
        ap3[1] = std::make_shared<DurableSeq>(1, 2, 3, 10, "file3.txt");
        AsymPattern pattern3(ap3, length);
        if (!(pattern1 != pattern3)) {
            std::cerr << "Failure of AP != operator" << std::endl;
            passed = false;
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "EXCEPTION in testAsymPatternEquality(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testASEquality() {
    bool passed = true;

    try {
        //create two identical ArithSeq objects
        ArithSeq seqA(10, 2, 5, 10);
        ArithSeq seqB(10, 2, 5, 10);

        if (!(seqA == seqB)) {
            std::cerr << "Failure of AS == operator" << std::endl;
            passed = false;
        }
        if (seqA != seqB) {
            std::cerr << "Failure of AS != operator" << std::endl;
            passed = false;
        }

        //different ArithSeq
        ArithSeq seqC(10, 3, 5, 10);

        if (seqA == seqC) {
            std::cerr << "Failure of AS == operator" << std::endl;
            passed = false;
        }
        if (!(seqA != seqC)) {
            std::cerr << "Failure of AS == operator" << std::endl;
            passed = false;
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testArithSeqEquality(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testDSEquality() {
    bool passed = true;

    try {
        //create two identical DurableSeq objects, filePath does not matter in equality test as per class invariant
        DurableSeq seqA(10, 2, 5, 10, "seqA.txt");
        DurableSeq seqB(10, 2, 5, 10, "seqB.txt");

        if (!(seqA == seqB)) {
            std::cerr << "Failure of DS == operator" << std::endl;
            passed = false;
        }
        if (seqA != seqB) {
            std::cerr << "Failure of DS != operator" << std::endl;
            passed = false;
        }

        //different DurableSeq
        DurableSeq seqC(15, 3, 2, 11, "seqC.txt");

        if (seqA == seqC) {
            std::cerr << "Failure of DS == operator" << std::endl;
            passed = false;
        }
        if (!(seqA != seqC)) {
            std::cerr << "Failure of DS == operator" << std::endl;
            passed = false;
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testDurableSeqEquality(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}

bool testAllPrePostIncrement() {
    bool passed = true;
    if (!testAPIncrement()) {
        std::cerr << "AsymPattern increment failed" << std::endl;
        passed = false;
    }
    if (!testASIncrement()) {
        std::cerr << "ArithSeq increment failed" << std::endl;
        passed = false;
    }
    if (!testDSIncrement()) {
        std::cerr << "DurableSeq increment failed" << std::endl;
        passed = false;
    }
    return passed;
}
bool testAPIncrement() {
    bool passed = true;
    try {
        int length = 2;
        std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap1 = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(
            new std::shared_ptr<ArithSeq>[length]);
        ap1[0] = std::make_shared<ArithSeq>(10, 1, 4, 10);
        ap1[1] = std::make_shared<DurableSeq>(2, 2, 3, 10,"seqB.txt");
        AsymPattern pattern1(ap1, length);

        //get keys
        std::shared_ptr<int[]> keys = pattern1.getKeys();
        int key0 = keys[0];
        int key1 = keys[1];

        ++pattern1;
        pattern1++;

        //first value in ap[0] should now be 12 after two increments
        if (pattern1[key0]->getKthVal(1) != 12) {
            std::cerr << "Failure of ++ operator" << std::endl;
            passed = false;
        }

        //pre increment
        for (int i = 0; i < 3; i++) {
            ++pattern1;

            //first value should be 13 + i because of pre-increment
            if (pattern1[key0]->getKthVal(1) != (12 + i + 1)) {
                std::cerr << "Failure of pre-increment operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        pattern1.reset();

        //post increment
        for (int i = 0; i < 3; i++) {
            int beforeIncrement = pattern1[key1]->getKthVal(1);
            //should update values AFTER evaluation
            pattern1++;
            int afterIncrement = pattern1[key1]->getKthVal(1);

            if (afterIncrement != beforeIncrement + 1) {
                std::cerr << "Failure of post-increment in iteration " << i
                        << ": Expected " << (beforeIncrement + 1)
                        << ", but got " << afterIncrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testAsymPatternIncrement(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testASIncrement() {
    bool passed = true;
    try {
        //create two ArithSeq objects
        ArithSeq seqA(10, 2, 5, 10);
        ArithSeq seqB(15, 5, 5, 12);
        ++seqA;
        seqA++;
        if (seqA[0] != 12) {
            std::cerr << "Failure of ++ operator" << std::endl;
        }
        //pre increment
        for (int i = 0; i < 3; i++) {
            ++seqB;
            //first value should be 15 + i because of pre-increment
            if (seqB[0] != (15 + i + 1)) {
                std::cerr << "Failure of pre-increment operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        seqA.reset();

        //post increment
        for (int i = 0; i < 3; i++) {
            int beforeIncrement = seqA[0];
            //should update values AFTER evaluation
            seqA++;
            int afterIncrement = seqA[0];

            if (afterIncrement != beforeIncrement + 1) {
                std::cerr << "Failure of post-increment in iteration " << i
                        << ": Expected " << (beforeIncrement + 1)
                        << ", but got " << afterIncrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testArithSeqIncrement()" << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testDSIncrement() {
    bool passed = true;
    try {
        //create two ArithSeq objects
        DurableSeq seqA(10, 2, 5, 10, "seqA.txt");
        DurableSeq seqB(15, 5, 5, 12, "seqB.txt");
        ++seqA;
        seqA++;
        if (seqA[0] != 12) {
            std::cerr << "Failure of ++ operator" << std::endl;
        }
        //pre increment
        for (int i = 0; i < 3; i++) {
            ++seqB;
            //first value should be 15 + i because of pre-increment
            if (seqB[0] != (15 + i + 1)) {
                std::cerr << "Failure of pre-increment operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        seqA.reset();

        //post increment
        for (int i = 0; i < 3; i++) {
            int beforeIncrement = seqA[0];
            //should update values AFTER evaluation
            seqA++;
            int afterIncrement = seqA[0];

            if (afterIncrement != beforeIncrement + 1) {
                std::cerr << "Failure of post-increment in iteration " << i
                        << ": Expected " << (beforeIncrement + 1)
                        << ", but got " << afterIncrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testArithSeqIncrement()" << e.what() << std::endl;
        passed = false;
    }
    return passed;
}

bool testAllPrePostDecrement() {
    bool passed = true;
    if (!testAPDecrement()) {
        std::cerr << "AsymPattern decrement failed" << std::endl;
        passed = false;
    }
    if (!testASDecrement()) {
        std::cerr << "ArithSeq decrement failed" << std::endl;
        passed = false;
    }
    if (!testDSDecrement()) {
        std::cerr << "DurableSeq decrement failed" << std::endl;
        passed = false;
    }
    return passed;
}
bool testAPDecrement() {
    bool passed = true;
    try {
        int length = 2;
        std::shared_ptr<std::shared_ptr<ArithSeq>[]> ap1 = std::shared_ptr<std::shared_ptr<ArithSeq>[]>(
            new std::shared_ptr<ArithSeq>[length]);
        ap1[0] = std::make_shared<ArithSeq>(10, 1, 4, 10);
        ap1[1] = std::make_shared<DurableSeq>(2, 2, 3, 10, "file1.txt");
        AsymPattern pattern1(ap1, length);

        //get keys
        std::shared_ptr<int[]> keys = pattern1.getKeys();
        int key0 = keys[0];
        int key1 = keys[1];

        --pattern1;
        pattern1--;
        //first value in ap[0] should now be 8 after two decrements
        if (pattern1[key0]->getKthVal(1) != 8) {
            std::cerr << "Failure of AP -- operator" << std::endl;
            passed = false;
        }

        //pre decrement
        for (int i = 0; i < 3; i++) {
            --pattern1;

            //first value should be 7 - i because of pre-decrement
            if (pattern1[key0]->getKthVal(1) != (8 - i - 1)) {
                std::cerr << "Failure of pre-decrement operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        pattern1.reset();

        //post decrement
        for (int i = 0; i < 3; i++) {
            int beforeDecrement = pattern1[key1]->getKthVal(1);
            //should update values AFTER evaluation
            pattern1--;
            int afterDecrement = pattern1[key1]->getKthVal(1);

            if (afterDecrement != beforeDecrement - 1) {
                std::cerr << "Failure of post-decrement in iteration " << i
                        << ": Expected " << (beforeDecrement - 1)
                        << ", but got " << afterDecrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testAsymPatternDecrement(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testASDecrement() {
    bool passed = true;
    try {
        //create two ArithSeq objects
        ArithSeq seqA(10, 2, 5, 10);
        ArithSeq seqB(15, 5, 5, 12);
        --seqA;
        seqA--;
        if (seqA[4] != 16) {
            std::cerr << "Failure of AS -- operator" << std::endl;
        }
        //pre decrement
        for (int i = 0; i < 3; i++) {
            --seqB;
            //first value should be 15 - i because of pre-decrement
            if (seqB[0] != (15 - i - 1)) {
                std::cerr << "Failure of pre-decrement operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        seqA.reset();

        //post decrement
        for (int i = 0; i < 3; i++) {
            int beforeDecrement = seqA[0];
            //should update values AFTER evaluation
            seqA--;
            int afterDecrement = seqA[0];

            if (afterDecrement != beforeDecrement - 1) {
                std::cerr << "Failure of post-decrement in iteration " << i
                        << ": Expected " << (beforeDecrement - 1)
                        << ", but got " << afterDecrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testArithSeqDecrement()" << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testDSDecrement() {
    bool passed = true;
    try {
        //create two identical DurableSeq objects with different file names
        DurableSeq seqA(10, 2, 5, 10, "seqA.txt");
        DurableSeq seqB(15, 5, 5, 12, "seqB.txt");
        --seqA;
        seqA--;
        if (seqA[4] != 16) {
            std::cout << seqA[4] << std::endl;
            std::cerr << "Failure of DS -- operator" << std::endl;
        }
        //pre decrement
        for (int i = 0; i < 3; i++) {
            --seqB;
            //first value should be 15 - i because of pre-decrement
            if (seqB[0] != (15 - i - 1)) {
                std::cerr << "Failure of pre-decrement operator on iteration " << i << std::endl;
                passed = false;
            }
        }

        seqA.reset();

        //post decrement
        for (int i = 0; i < 3; i++) {
            int beforeDecrement = seqA[0];
            //should update values AFTER evaluation
            seqA--;
            int afterDecrement = seqA[0];

            if (afterDecrement != beforeDecrement - 1) {
                std::cerr << "Failure of post-decrement in iteration " << i
                        << ": Expected " << (beforeDecrement - 1)
                        << ", but got " << afterDecrement << std::endl;
                passed = false;
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testDurableSeqDecrement()" << e.what() << std::endl;
        passed = false;
    }
    return passed;
}

bool testASAdd() {
    bool passed = true;
    try {
        ArithSeq seqA(10, 2, 5, 10);
        ArithSeq seqB(5, 3, 5, 10);
        seqA + seqB;
        if (seqA[0] != 15) {
            std::cerr << "Failure of addition operator" << std::endl;
            passed = false;
        }
        if (seqA[4] != 35) {
            std::cerr << "Failure of addition operator" << std::endl;
            passed = false;
        }
        if (seqB[0] != 5) {
            std::cerr << "Error in addition operator, added sequence modified" << std::endl;
            passed = false;
        }
    }
    catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testASAdd()" << e.what() << std::endl;
        passed = false;
    }
    return passed;
}

bool testAllCopy() {
    bool passed = true;
    if (!testASCopy()) {
        std::cerr << "ArithSeq copy failed" << std::endl;
        passed = false;
    }
    if (!testDSCopy()) {
        std::cerr << "DurableSeq copy failed" << std::endl;
        passed = false;
    }
    return passed;
}
bool testASCopy() {
    bool passed = true;
    try {
        ArithSeq seqA(10, 2, 5, 10);
        //tests copy constructor and assignment operator
        ArithSeq seqB(seqA);
        ArithSeq seqC = seqA;
        if (!(seqA == seqB) || !(seqA == seqC)) {
            std::cerr << "Failure in ArithSeq deep copy: copied objects do not match original" << std::endl;
            passed = false;
        }
        //ensure copied versions do not change after modiyfing original
        seqA.modifyEveryPthValue(1, 5);
        if (seqB[0] == seqA[0] || seqC[0] == seqA[0]) {
            std::cerr << "Failure in ArithSeq deep copy: copies are not independent" << std::endl;
            passed = false;
        }
    }
    catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testASDeepCopy(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}
bool testDSCopy() {
    bool passed = true;
    try {
        DurableSeq seqA(10, 2, 5, 10, "seqA.txt");
        DurableSeq seqB(seqA);
        DurableSeq seqC = seqA;

        if (!(seqA == seqB) || !(seqA == seqC)) {
            std::cerr << "Failure in DurableSeq deep copy: copied objects do not match original" << std::endl;
            passed = false;
        }

        //ensures only original is modified
        seqA.modifyEveryPthValue(1, 5);
        if (seqB[0] == seqA[0] || seqC[0] == seqA[0]) {
            std::cerr << "Failure in DurableSeq deep copy: copies are not independent" << std::endl;
            passed = false;
        }
        //file paths should be different after a deep copy
        if (seqB.getFilePath() == seqA.getFilePath() || seqC.getFilePath() == seqA.getFilePath()) {
            std::cerr << "Failure in DurableSeq deep copy: file paths should be different" << std::endl;
            passed = false;
        }
    }
    catch (const std::exception &e) {
        std::cerr << "EXCEPTION in testDSDeepCopy(): " << e.what() << std::endl;
        passed = false;
    }
    return passed;
}

int main() {
    if (testAllEquality()) std::cout << "== and != operator overloads passed." << std::endl;
    if (testAllPrePostIncrement()) std::cout << "pre and post increment operator overloads passed." << std::endl;
    if (testAllPrePostDecrement()) std::cout << "pre and post decrement operator overloads passed." << std::endl;
    //index operator overloads are tested throughout all test functions
    if (testASAdd()) std::cout << "addition operator overload passed." << std::endl;
    //outstream << operator for DurableSeq overload is already tested throughout all test functions as
    //the class design of DurableSeq relies on it functioning
    //testAllCopy() does not include AsymPattern because it has suppressed copy
    if (testAllCopy()) std::cout << "deep copy implementation tests passed." << std::endl;
    return -1;
}

