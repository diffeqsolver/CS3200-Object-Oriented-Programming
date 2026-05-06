namespace P5;
/* Class Invariant
 *
 * The Gob class implements the ITracker interface.
 * It tracks two distinct integer keys (key1, key2) with separate limits (key1Limit, key2Limit).
 * Internally, it counts how many times each key has been passed to Modified(...).
 * Based on these counts, Gob can become permanently off (inactive) or permanently on (active).
 * Once Gob is permanently on or off, it will not toggle again.
 *
 * Public Methods:
 * - Gob(int key1, int key2, int key1Limit, int key2Limit): Constructs a Gob ensuring distinct keys and positive limits.
 * - void Modified(int key): Increments the count for the appropriate key and may change Gob's on/off state permanently.
 */
public class Gob : ITracker
{
    private int key1;
    private int key2;
    private int key1Limit;
    private int key2Limit;
    private int key1Count;
    private int key2Count;
    private bool active;
    private bool permanent;
    public bool isActive => active;
    public int getKey1Count => key1Count;
    public int getKey2Count => key2Count;

    //Pre-condition:key1 != key2, key1Limit > 0, key2Limit > 0 (implied valid positive limits)
    //Post-condition: A new Gob is created with zero counts, active = true, and permanent = false.
    public Gob(int key1, int key2, int key1Limit, int key2Limit)
    {
        if (key1 == key2) throw new ArgumentException("Keys must be distinct");
        this.key1 = key1;
        this.key2 = key2;
        this.key1Limit = key1Limit;
        this.key2Limit = key2Limit;
        this.key1Count = 0;
        this.key2Count = 0;
        this.active = true;
        this.permanent = false;
    }
    //Pre-condition: None
    //Post-condition: If the passed key matches key1, key1Count increments.
    //If key1Count >= key1Limit and not permanent, Gob becomes permanently off (active = false).
    //If the passed key matches key2, key2Count increments.
    //If key2Count >= key2Limit and not permanent, Gob becomes permanently on (active = true).
    //If Gob is already permanent, it stays in its current active/off state.
    public virtual void Modified(int key)
    {
        if (key == key2)
        {
            key2Count++;
            if (!permanent && key2Count >= key2Limit)
            {
                //permanently on
                permanent = true;
                active = true;
            }
        }
        if (key == key1)
        {
            key1Count++;
            if (!permanent && key1Count >= key1Limit)
            {
                //permanently off
                permanent = true; active = false;
            }
        }
        
    }
}
/*
 * Implementation Invariant
 *  - key1 and key2 must remain distinct throughout the object's lifetime.
 *  - key1Limit and key2Limit must be > 0 (or some positive threshold).
 *  - key1Count, key2Count >= 0. Once 'permanent' is set, active should no longer toggle.
 *  - Modified(int key) made virtual for extension
 */