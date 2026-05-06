namespace P5;
/* Class Invariant
 *
 * TrackedSeq extends AsymPattern by tracking modifications via an array of Gob objects.
 * Each Gob in the array is notified when a sequence modification occurs (by key).
 * total keeps track of how many total modifications (including ResetAtKey) have occurred.
 * 
 * Public Methods:
 * TrackedSeq(ArithSeq[] seqArray): Creates a new TrackedSeq with no Gob objects initially.
 * void replaceLastGob(Gob gob): Replaces the last Gob in the array with a new Gob.
 * int inactiveGobs(): Counts how many Gobs are currently inactive.
 * void AddGob(Gob newGob): Appends a new Gob to the internal array.
 * override void Reset(): Clears the underlying AsymPattern plus resets Gobs to empty and total to 0.
 * override void ResetAtKey(int key): Resets one sequence at a key, increments total, notifies all Gobs.
 * override void ModifyEveryPthValueAtKey(int key, int p, int q): Modifies the sequence at key, increments total, notifies Gobs.
 * 
 */

public class TrackedSeq : AsymPattern
{
    private Gob[] gobs;
    private int total;
    public int GetTotalModifications() { return total; }
    
    //Pre-condition: seqArray must not be null and must contain at least one valid ArithSeq.
    //Post-condition: Initializes a TrackedSeq object with the given ArithSeq array.
    //The Gob array is initialized empty, and total modifications count is set to zero.
    public TrackedSeq(ArithSeq[] seqArray) : base(seqArray)
    {
        gobs = new Gob[0];
    }
    //Pre-condition: gobs.Length > 0 (At least one Gob must exist in the array).
    //Post-condition: The last Gob in the gobs array is replaced with the new Gob.
    public void replaceLastGob(Gob gob)
    {
        if (gobs.Length <= 0) throw new ArgumentException("TrackedSeq must have at least one Gob before replacing");
        gobs[gobs.Length - 1] = gob;
    }
    //Pre-condition: None.
    //Post-condition: Returns the number of Gob objects in the gobs array that are inactive (isActive == false).
    public int inactiveGobs()
    {
        int count = 0;
        for (int i = 0; i < gobs.Length; i++) {
            if (!gobs[i].isActive) count++;
        }
        return count;
    }
    //Pre-condition: newGob must not be null.
    //Post-condition: The gobs array is resized to accommodate one additional Gob.
    //The newly passed Gob is placed at the last index of the gobs array.
    public void AddGob(Gob newGob)
    {
        Array.Resize(ref gobs, gobs.Length + 1);
        gobs[gobs.Length - 1] = newGob;
    }
    //Pre-condition: None.
    //Post-condition: Calls base.Reset(), resetting all sequences in AsymPattern.
    //Clears the gobs array (gobs = new Gob[0]) and resets total modification count to 0.
    public override void Reset()
    {
        base.Reset();
        gobs = new Gob[0];
        total = 0;
    }
    //Pre-condition: key must exist in the AsymPattern sequences.
    //Post-condition: Calls base.ResetAtKey(key), resetting the sequence at the given key.
    //Increments the total modification count by 1.
    //Calls Modified(key) on each Gob object in the gobs array to notify them of the modification.
    public override void ResetAtKey(int key)
    {
        base.ResetAtKey(key);
        total++;
        for (int j = 0; j < gobs.Length; j++) gobs[j].Modified(key);
    }
    //Pre-condition: key must exist in the AsymPattern sequences.
    //p must be a valid step (0 < p < sequence length), and q can be any integer.
    //Post-condition: Modifies every p-th value in the sequence at 'key' by 'q' using ModifyEveryPthValue().
    //Increments the total modification count by 1.
    //Calls Modified(key) on each Gob object in the gobs array to notify them of the modification.
    public override void ModifyEveryPthValueAtKey(int key, int p, int q)
    {
        getArithSeqAtKey(key).ModifyEveryPthValue(p, q);
        total++;
        for (int j = 0; j < gobs.Length; j++) gobs[j].Modified(key);
    }

}
 /*
     * Implementation Invariant
     *  
     *  - The gobs array is never null but may be empty, ensuring TrackedSeq can always operate without a Gob.
     *  - The total variable always remains non-negative and increases only when a modification is performed.
     *  - When a modification occurs (ResetAtKey, ModifyEveryPthValueAtKey), all Gobs in the array must be notified via Modified(key).
     *  - The array of Gobs dynamically grows when AddGob() is called.
     *  - replaceLastGob() assumes there is at least one Gob in the array before replacing.
     *  - Reset() ensures that both sequence modifications and Gob tracking are cleared at the same time.
     *  - Each method must maintain consistency between sequence modifications and Gob notifications.
     *  - ResetAtKey() and ModifyEveryPthValueAtKey() notify all Gobs before terminating to prevent missed updates.
     *  - If a Gob becomes permanently active or inactive due to modification tracking, that state must be preserved.
     *  - If a Gob object is replaced using replaceLastGob(), it will no longer be notified of future changes.
     *  An Insight:
     *  Use dependency injection for TrackedSeq.cs to avoid modifying the class when adding new tracking behavior?
     */