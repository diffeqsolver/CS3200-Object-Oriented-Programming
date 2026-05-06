namespace P5;
/* Invariant
 *
 * ITracker is an interface with a single method:
 *   - void Modified(int key)
 * This represents an object that can be "notified" of some key-based event or modification.
 * There are no additional constraints or stored data within ITracker itself.
 *
 */
public interface ITracker
{ 
    public void Modified(int key);
}