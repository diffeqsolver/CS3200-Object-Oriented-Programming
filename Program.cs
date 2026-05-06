namespace P5
{
    class P5
    {
        static void Main(string[] args)
        {
            ArithSeq[] sequences = new ArithSeq[3];
            sequences[0] = new ArithSeq(10, 5, 5, 10); // firstTerm = 10, commonDiff = 5, length = 5, maxOperations = 10.
            sequences[1] = new ArithSeq(0, 3, 5, 10);
            sequences[2] = new ArithSeq(-10, 2, 5, 10);

            AsymPattern ap = new AsymPattern(sequences);
            TrackedSeq ts = new TrackedSeq(sequences);
            
            //Heterogenous collection (HC)
            AsymPattern[] HC = new AsymPattern[2];
            HC[0] = ap;
            HC[1] = ts;
            
            int[] keys = ts.GetKeys();
            int key1 = keys[0];
            int key2 = keys[1];
            int key3 = keys[2];

            Gob gob1 = new Gob(key1, key2, 2, 5); // key1Limit = 2, key2Limit = 5.
            ts.AddGob(gob1);
            
            Console.WriteLine("Initial State:");
            DisplayTrackedSeq(ts);

            RunTrackedSeqTests(ts, ap, gob1, key1, key2, key3);
            
            TestErrorHandling();
        }

        private static void TestErrorHandling()
        {
            Console.WriteLine("\nError Handling Tests ---");
            try
            {
                Console.WriteLine("\nAttempting to create TrackedSeqs with a null sequence");
                TrackedSeq tsError = new TrackedSeq(null);
            }
            catch (Exception e)
            {
                Console.WriteLine($"Caught expected error: {e.Message}");
            }
            try
            {
                Console.WriteLine("\nAttempting to replace a Gob when none exist");
                TrackedSeq tsEmptyGobs = new TrackedSeq(new ArithSeq[] { new ArithSeq(1, 1, 1, 1) });
                tsEmptyGobs.replaceLastGob(new Gob(1, 2, 1, 2));
            }
            catch (Exception e)
            {
                Console.WriteLine($"Caught expected error: {e.Message}");
            }
        }

        static void RunTrackedSeqTests(TrackedSeq ts, AsymPattern ap, Gob gob1, int key1, int key2, int key3)
        {
            //Modify and check tracked key counts
            ts.ModifyEveryPthValueAtKey(key1, 2, 3);
            Console.WriteLine($"Key1 modifications tracked: {gob1.getKey1Count}");

            ts.ModifyEveryPthValueAtKey(key2, 1, 2);
            Console.WriteLine($"Key2 modifications tracked: {gob1.getKey2Count}");

            //Replace last Gob
            Gob gob2 = new Gob(key2, key3, 3, 4);
            ts.replaceLastGob(gob2);

            //Add more Gobs
            Gob gob4 = new Gob(key1, key3, 3, 6);
            Gob gob5 = new Gob(key2, key3, 1, 2);
            ts.AddGob(gob4);
            ts.AddGob(gob5);

            Console.WriteLine($"Total Inactive Gobs after adding more: {ts.inactiveGobs()}");

            //Replicate and check updated keys, also tests substitutability
            Gob gob3 = new Gob(key3, key1, 1, 3);
            ts.ReplicateWithNewKey(key3);
            Console.WriteLine("\nVerifying Replicated Key...");
            int[] updatedKeys = ts.GetKeys();
            Console.WriteLine($"Updated Keys: {string.Join(", ", updatedKeys)}");

            //Test Gob mode changes
            Console.WriteLine("\nForcing Gob to become permanently inactive");
            ts.ResetAtKey(key1);
            ts.ResetAtKey(key1);
            Console.WriteLine($"Gob1 active state: {gob1.isActive} Expected: false");

            Console.WriteLine("\nForcing Gob to become permanently active");
            for (int i = 0; i < 5; i++) ts.ResetAtKey(key2);
            Console.WriteLine($"Gob1 active state: {gob1.isActive} Expected: true");

            //Reset all and check results
            ts.Reset();
            DisplayTrackedSeq(ts);
            
            //Test that AsymPattern does not relate to Gobs
            Console.WriteLine("\nResetAtKey should call AsymPattern ResetAtKey and not affect state of gob");
            for (int i = 0; i < 5; i++) ap.ResetAtKey(key2);
            Console.WriteLine($"Gob1 active state: {gob1.isActive} Expected: true");
            
        }

        static void DisplayTrackedSeq(TrackedSeq ts)
        {
            Console.WriteLine($"Total modifications tracked: {ts.GetTotalModifications()}");
            Console.WriteLine($"Inactive Gobs: {ts.inactiveGobs()}");
        }
    }
}
