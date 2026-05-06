namespace P5;
public class ArithSeq
{
/* Class Invariant
 *
 * ArithSeq represents an arithmetic sequence defined by a first term, common difference, and length.
 * The sequence is generated dynamically using a helper method GenerateSequence() upon construction.
 * The sequence allows controlled modifications, subject to an operation limit (maxOperations).
 * The class ensures index validity checks and operation count enforcement to prevent excessive modifications.
 *
 * Public Method Functionality:
 * GetKthVal(int k): Returns the k-th value in the sequence, respecting the maxOperations limit.
 * EvenlyDividedBy(int n): Counts how many terms in the sequence are divisible by n.
 * ModifyEveryPthValue(int p, int q): Increments every p-th term by q, if operation limits allow.
 * Reset(): Resets the sequence to its original values and resets operationCount to 0.
 *
 */
    private int firstTerm;
    private int commonDiff;
    private int length;
    private int maxOperations;
    private int operationCount;
    protected int[] sequence;
    public int GetLength() => length;
    // Pre-condition: length and maxOperations must be positive.
    // Post-condition: Initializes an arithmetic sequence with the given parameters,
    // allocates memory for sequence and fills it using generateSequence().
    public ArithSeq(int firstTerm, int commonDiff, int length, int maxOperations)
    {
        if (length <= 0 || maxOperations <= 0)
        {
            throw new ArgumentException("length and maxOperations must be positive");
        }

        this.firstTerm = firstTerm;
        this.commonDiff = commonDiff;
        this.length = length;
        this.maxOperations = maxOperations;
        this.operationCount = 0;
        this.sequence = new int[length];

        GenerateSequence();
    }
    // Pre-condition: length and maxOperations must be positive.
    // Post-condition: Initializes an arithmetic sequence with the given parameters,
    // allocates memory for sequence and fills it using generateSequence().
    private void GenerateSequence()
    {
        if (length == 1)
        {
            sequence[0] = firstTerm;
            return;
        }
        for (int i = 0; i < length; i++)
        {
            sequence[i] = firstTerm + (i * commonDiff);
        }
    }
    // Pre-condition: other must be a valid ArithSeq object.
    // Post-condition: Performs deep copy of other’s sequence and data.
    public ArithSeq(ArithSeq other)
    {
        if (other == null) throw new ArgumentException("Parameter must not be null");
        this.firstTerm = other.firstTerm;
        this.commonDiff = other.commonDiff;
        this.length = other.length;
        this.maxOperations = other.maxOperations;
        this.operationCount = other.operationCount;
        this.sequence = (int[])other.sequence.Clone();
    }
    // Pre-condition: k must be a valid index (0 ≤ k < length).
    // Pre-condition: Operation count must be within limits,
    // returns the k-th value in the sequence.
    public virtual int GetKthVal(int k)
    {
        if (!CheckOperationLimit()) throw new ArgumentException("Operation limit exceeded");
        if (k < 0 || k >= length) throw new ArgumentException("k must be a valid index");
        operationCount++;
        return sequence[k];
    }
    // Pre-condition: None.
    // Post-condition: Returns true if operation count has not exceeded maxOperations.
    private bool CheckOperationLimit()
    {
        return operationCount < maxOperations;
    }
    // Pre-condition: n must be non-zero.
    // Pre-condition: Operation count must be within limits,
    // returns the count of terms divisible by n.
    public int EvenlyDividedBy(int n)
    {
        if (!CheckOperationLimit()) throw new ArgumentException("Operation limit exceeded");
        if (n == 0) throw new ArgumentException("n must be non-zero");
        if (length == 1 && sequence[0] % n == 0) return 1;
        int count = 0;
        for (int i = 0; i < length; i++)
        {
            if (sequence[i] % n == 0) count++;
        }
        operationCount++;
        return count;
    }
    // Pre-condition: p must be a valid step (0 < p < length).
    // Pre-condition: Operation count must be within limits,
    // increments every p-th value in the sequence by q.
    public virtual void ModifyEveryPthValue(int p, int q)
    {
        if (!CheckOperationLimit()) throw new ArgumentException("Operation limit exceeded");
        if (p < 0 || p >= length) throw new ArgumentException("p must be a valid index");
        if (length == 1)
        {
            sequence[0] += q;
            return;
        }

        for (int i = 0; i < length; i += p)
        {
            sequence[i] += q;
        }
        operationCount++;
    }
    // Pre-condition: None.
    // Post-condition: Resets sequence to its original state,
    // resets operation count to zero.
    public virtual void Reset()
    {
        operationCount = 0;
        GenerateSequence();
    }
}
/* Implementation Invariant
 *
 * The constructor initializes the sequence and enforces positive, nonzero values for length and maxOperations.
 * Copy constructor performs deep copies, ensuring data integrity across instances.
 * generateSequence() initializes values according to the arithmetic progression formula.
 * modifyEveryPthValue() ensures valid index bounds before modifying elements.
 * getKthVal() and evenlyDividedBy() enforce operation count limits before executing computations.
 * Exception safety is ensured by validating parameters in methods that modify or retrieve sequence elements.
 * An Insight:
 * ArithSeq might not be as closed for modification as P5 likes, I hope this isn't bad but consider
 * modifications to functionality like operation limits, sequence generation, or constraints
 * may require altering the class rather than extending it.
 */