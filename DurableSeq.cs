﻿namespace P5;
using System;
using System.IO;
/* Class Invariant
 *
 * DurableSeq extends ArithSeq, adding file persistence functionality.
 * Every DurableSeq instance is associated with a file (filePath), where its state is stored.
 * File operations (saveToFile() and loadFromFile()) ensure persistence across instances.
 *
 * Public Method Functionality & Client Expectations:
 * modifyEveryPthValue(int p, int q): same functionality as base but with file saving
 * reset(): Restores sequence from file if available; otherwise, regenerates it.
 * getLength(): Returns sequence length.
 * getFilePath(): Returns the current file path.
 * 
 */
public class DurableSeq : ArithSeq
{
    private string filePath;
    
    // Pre-condition: firstTerm, commonDiff, length, and maxOperations must be valid integers,
    // filePath must be a valid string representing a writable file.
    // Post-condition: Initializes a DurableSeq instance and writes sequence to file
    public DurableSeq(int firstTerm, int commonDiff, int length, int maxOperations, string filePath)
        : base(firstTerm, commonDiff, length, maxOperations)
    {
        if (string.IsNullOrWhiteSpace(filePath))
            throw new ArgumentException("File path must not be null or empty");

        this.filePath = filePath;
        
        if (!File.Exists(filePath))
        {
            SaveToFile();
        }
    }

    //Pre-condition: None
    //Post-condition: innitalizes a new DurableSeq with an extended filePath, then saves.
    public DurableSeq(DurableSeq other) : base(other)
    {
        this.filePath = other.filePath + "_copy";
        SaveToFile();
    }
    // Pre-condition: None.
    // Post-condition: Overwrites the file with the current sequence
    public void SaveToFile()
    {
        try
        {
            using (StreamWriter writer = new StreamWriter(filePath, false))
            {
                for (int i = 0; i < GetLength(); i++)
                {
                    writer.WriteLine(sequence[i]);
                }
            }
        }
        catch (IOException ex)
        {
            throw new Exception("Error writing to file: " + ex.Message);
        }
    }

    // Pre-condition: The file must exist and be readable.
    // Post-condition: Loads sequence data from the file into memory.
    public void LoadFromFile()
    {
        try
        {
            if (!File.Exists(filePath))
                throw new FileNotFoundException("File not found: " + filePath);

            string[] lines = File.ReadAllLines(filePath);

            if (lines.Length != GetLength())
                throw new ArgumentException("File data does not match sequence length");

            for (int i = 0; i < lines.Length; i++)
            {
                if (int.TryParse(lines[i], out int value))
                {
                    sequence[i] = value; 
                }
                else
                {
                    throw new ArgumentException("Invalid file format");
                }
            }
        }
        catch (IOException ex)
        {
            throw new Exception("Error reading from file: " + ex.Message);
        }
    }


    // Pre-condition: p must be a valid step (0 < p < length),
    // operation count must be within limits.
    // Post-condition: Modifies every p-th value in the sequence by q
    public override void ModifyEveryPthValue(int p, int q)
    {
        base.ModifyEveryPthValue(p, q);
        SaveToFile();
    }
    // Pre-condition: None.
    // Post-condition: If a valid file exists, reloads the sequence from the file,
    // reads all lines and updates file internally
    public override void Reset()
    {
        base.Reset();
    
        if (File.Exists(filePath))
        {
            string[] lines = File.ReadAllLines(filePath);
            for (int i = 0; i < lines.Length; i++)
            {
                if (int.TryParse(lines[i], out int value))
                {
                    sequence[i] = value;
                }
            }
        }
    }
    //Pre-condition: None
    //Pre-condition: returns representation of sequence
    public override string ToString()
    {
        return string.Join("\n", sequence);
    }
    // Pre-condition: None.
    // Post-condition: writes the current sequence to file.
    ~DurableSeq()
    {
        SaveToFile();
    }
}
/* Implementation Invariant
 *
 * Copy constructor and assignment create a **new file path** (_copy suffix) to maintain unique persistence.
 * File reading (loadFromFile()) restores the sequence only when needed.
 * reset() restores the original sequence from the file, ensuring consistency.
 * Exception safety is enforced in all file operations to prevent corrupted states.
 *
 */