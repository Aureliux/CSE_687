CSE_687 - Object-Oriented Design<br>
Project 1
=
Omar Vargas (Github ID: Aureliux), Huiying Wu (Github ID: jowu58)
-


Requirements to Run:
C++17 - Needed to include the "filesystem" library used by the FileManager class.
In Visual Studio, go to Project > Properties > Configuration Properties > C/C++ > Language > C++ Language Standard > ISO C++17 Standard.
Google Testing - Need Visual Studio installation of "Desktop development with C++", which contains the capability.


Summary:
This is a MapReduce program that takes in a set of text files from an input folder designated by the user and returns a text file that contains every word contained in the input files and how many times each word is repeated. Each class has a corresponding header to declare its methods and include files. The program will prompt the user to enter 3 paths. The first is the input files path, the second is the intermediate output files, and the last is the output files path.

Program Contains the Following Classes:

Main - Prompts the user to designate input folder, temporary folder, and output folder. Then, it sends those folder paths to the Workflow class.

Workflow Class - Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.

FileManager Class: Used to open files, read files, create files, and delete files in the folders designated by the user.

Mapper Class: Receives a string from Workflow, splits every word, and appends a "1" to each word. A buffer of preset size is used to periodically write to the mapped file in the temporary directory.

Sorter Class: Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.

Reducer Class: Deletes repeated words and append a "1" to the original word to count how many times it was repeated. Then, returns a final reduced string.

Results:
The final output text file will be a reduced file containing one word per line in alphabetical order followed by a "1" for each time that specific word was repeated.
A separate success file is also created in the output directory to mark the completion of the Map-Reduce program.
