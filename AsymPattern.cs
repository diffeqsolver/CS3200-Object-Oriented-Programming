namespace P5
/* Class Invariant
 *
 *  AsymPattern manages an array of ArithSeq[], allowing storage of both ArithSeq
 *  and DurableSeq objects while ensuring automatic memory management.
 *  Each sequence is accessed via a **unique integer key**, assigned internally to prevent duplication.
 *  The internal array can be resized when needed, maintaining flexibility.
 *  No DeepCopy support
 *
 *  Public Method Functionality:
 *  int[] getKeys() returns a set of internally generated keys to the user to be used in getArithSeqAtKey(int key) 
 *  replicateWithNewKey(int key): Creates a deep copy of the sequence at key, assigns it a new unique key,
 *  and adds it to the collection.
 *  reset(): resets length to its initial value.
 *  a client may want to re-initalize ArithSeqs inside AsymPattern after a reset, but the keys are re-generated internally
 *
 */
{
    public class AsymPattern
    {
        
        protected ArithSeq[] sequences;
        protected int[] keys;
        protected int originalLength;
        // Pre-condition: ap must not be null,
        // length must be greater than 0.
        // Post-condition: Initializes the object with length sequences,
        // assigns a unique key to each stored sequence.
        public AsymPattern(ArithSeq[] seqArray)
        {
            if (seqArray == null || seqArray.Length == 0)
                throw new ArgumentException("Sequence array must not be null or empty");

            this.originalLength = seqArray.Length;
            this.sequences = new ArithSeq[seqArray.Length];
            this.keys = new int[seqArray.Length];

            for (int i = 0; i < seqArray.Length; i++)
            {
                sequences[i] = seqArray[i];
                keys[i] = GenerateUniqueKey(i);
            }
        }
        
        // Pre-condition: None.
        // Post-condition: Returns a new unique key not present in the collection.
        protected int GenerateUniqueKey(int i) { return i + 1; }

        // Pre-condition: None.
        // Post-condition: Returns a shared pointer to an array of unique keys.
        public int[] GetKeys()
        {
            int[] result = new int[keys.Length];
            for (int i = 0; i < keys.Length; i++)
            {
                result[i] = keys[i];
            }
            return result;
        }
        // Pre-condition: key must exist in the collection.
        // Post-condition: Returns an ArithSeq from the key specification
        public ArithSeq getArithSeqAtKey(int key)
        {
            for (int i = 0; i < keys.Length; i++) { 
                if (keys[i] == key) return sequences[i];
            }
            throw new ArgumentException("Key not found");
        }
        // Pre-condition: None.
        // Post-condition: Restores all sequences to their original values,
        // resets length to its initial value. As denoted in the class invariant, a client may want to
        // re-initalize ArithSeqs inside AsymPattern after a reset.
        public virtual void Reset()
        {
            sequences = new ArithSeq[originalLength];
            keys = new int[originalLength];
            for (int i = 0; i < originalLength; i++)
            {
                keys[i] = GenerateUniqueKey(i);
            }
        }
        //Pre-condition: None
        //Post-condition performs ArithSeq's reset() at the given key
        public virtual void ResetAtKey(int key)
        {
            getArithSeqAtKey(key).Reset();
        }
        //Pre-condition: None
        //Post-condition performs ArithSeq's evenlydividedby() at the given key
        public int EvenlyDividedByAtKey(int key, int n)
        {
            return getArithSeqAtKey(key).EvenlyDividedBy(n);
        }
        //Pre-condition: None
        //Post-condition performs ArithSeq's modifyeverypthvalue() at the given key
        public virtual void ModifyEveryPthValueAtKey(int key, int p, int q)
        {
            getArithSeqAtKey(key).ModifyEveryPthValue(p, q);
        }
        
        // Pre-condition: replicateKey must exist in the current collection.
        // Post-condition: Creates a deep copy of the sequence at replicateKey,
        // assigns the copy a new unique key and increases length by 1.
        public void ReplicateWithNewKey(int replicateKey)
        {
            for (int i = 0; i < keys.Length; i++) {
                if (keys[i] == replicateKey) {
                    Array.Resize(ref sequences, sequences.Length + 1);
                    Array.Resize(ref keys, keys.Length + 1);
                    sequences[sequences.Length - 1] = new ArithSeq(sequences[i]);
                    keys[sequences.Length - 1] = GenerateUniqueKey(keys.Length);
                    return;
                }
            }
            throw new ArgumentException("Key not found");
        }
    }
}

/* Implementation Invariant
 *
 *  No memory management needed
 *  Unique keys are assigned on insertion (generateUniqueKey() ensures no duplicates).
 *  Copying is **disabled** to prevent duplicated ownership
 *  replicateWithNewKey() creates a deep copy of the referenced sequence and assigns it a fresh key.
 *  Exception safety is ensured in constructors and key-based lookups.
 *  An Insight:
 *  Refactor AsymPattern.cs to allow different key management mechanisms through subclassing instead of modifications.
 */
