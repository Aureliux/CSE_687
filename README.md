# CSE_687 - Object-Oriented Design<br>

## Omar Vargas (Github ID: Aureliux), Huiying Wu (Github ID: jowu58)

* ### Project 4

#### Requirements to Run:

Run project 4 solution console to activate stub process, then run controller solution console to begin process.

C++17 - Needed to include the "filesystem" library used by the FileManager class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `Language` > `C++ Language Standard` > `ISO C++17 Standard`.<br>

boost/tokenizer.hpp - Needed to add "boost" library to use Tokenizer class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `General` > `Additional Include Directories` > add path to boost file.<br>

Google Testing - Need Visual Studio installation of "Desktop development with C++", which contains the capability.<br>

#### Summary:
This is a MapReduce program that takes in a set of text files from an input folder designated by the user and returns a text file that contains every word contained in the input files and how many times each word is repeated. Each class has a corresponding header to declare its methods and include files. The Mapper and Reducer are included as Dynamic Link Libraries (DLLs) to the client executable file.

The program will prompt the user to enter 3 paths. The first is the `input files path`, the second is the `temporary output path`, and the last is the `output files path`. The program will then calculate the number of R buckets based on how many files are on the input folder. This R value will be used to determine how many mapper and reducer threads need to be called. All the mapper threads are executed before the reducer threads are called to sort and reduce the files. At the end, a success file is created and the temporary files are deleted.

#### Program Contains the Following Classes:
Main - Prompts the user to designate input folder, temporary folder, and output folder. The program will call Workflow to calculate the number of R buckets based on how many files are on the input folder. Finally, the R value is used to execute mapper threads until completion followed by reducer threads.

Workflow Class - Calls the FileManager class to handle file operations and the Mapper DLL, Sorter class, and Reducer DLL to handle the modification algorithms.

FileManager Class: Used to open files, read files, create files, and delete files in the folders designated by the user.

Sorter Class: Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.

#### Program Contains the Following DLLs:

Mapper DLL: Receives a string from Workflow, splits every word, and appends a "1" to each word. A buffer of preset size is used to periodically write to the mapped file in the temporary directory.

Reducer DLL: Deletes repeated words and append a "1" to the original word to count how many times it was repeated. Then, returns a final reduced string.<br>

#### Results: 
The final output text file will be a reduced file containing one word per line in alphabetical order followed by a "1" for each time that a specific word is repeated. A separate success file is also created in the output directory to mark the completion of the Map-Reduce program.

_______________
* ### Project 3

#### Requirements to Run:
C++17 - Needed to include the "filesystem" library used by the FileManager class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `Language` > `C++ Language Standard` > `ISO C++17 Standard`.<br>

boost/tokenizer.hpp - Needed to add "boost" library to use Tokenizer class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `General` > `Additional Include Directories` > add path to boost file.<br>

Google Testing - Need Visual Studio installation of "Desktop development with C++", which contains the capability.<br>

#### Summary:
This is a MapReduce program that takes in a set of text files from an input folder designated by the user and returns a text file that contains every word contained in the input files and how many times each word is repeated. Each class has a corresponding header to declare its methods and include files. The Mapper and Reducer are included as Dynamic Link Libraries (DLLs) to the client executable file.

The program will prompt the user to enter 3 paths. The first is the `input files path`, the second is the `temporary output path`, and the last is the `output files path`. The program will then calculate the number of R buckets based on how many files are on the input folder. This R value will be used to determine how many mapper and reducer threads need to be called. All the mapper threads are executed before the reducer threads are called to sort and reduce the files. At the end, a success file is created and the temporary files are deleted.

#### Program Contains the Following Classes:
Main - Prompts the user to designate input folder, temporary folder, and output folder. The program will call Workflow to calculate the number of R buckets based on how many files are on the input folder. Finally, the R value is used to execute mapper threads until completion followed by reducer threads.

Workflow Class - Calls the FileManager class to handle file operations and the Mapper DLL, Sorter class, and Reducer DLL to handle the modification algorithms.

FileManager Class: Used to open files, read files, create files, and delete files in the folders designated by the user.

Sorter Class: Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.

#### Program Contains the Following DLLs:

Mapper DLL: Receives a string from Workflow, splits every word, and appends a "1" to each word. A buffer of preset size is used to periodically write to the mapped file in the temporary directory.

Reducer DLL: Deletes repeated words and append a "1" to the original word to count how many times it was repeated. Then, returns a final reduced string.<br>

#### Results: 
The final output text file will be a reduced file containing one word per line in alphabetical order followed by a "1" for each time that a specific word is repeated. A separate success file is also created in the output directory to mark the completion of the Map-Reduce program.


_______________
* ### Project 2

#### Requirements to Run:
C++17 - Needed to include the "filesystem" library used by the FileManager class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `Language` > `C++ Language Standard` > `ISO C++17 Standard`.<br>

boost/tokenizer.hpp - Needed to add "boost" library to use Tokenizer class. 
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `General` > `Additional Include Directories` > add path to boost file.<br>

Google Testing - Need Visual Studio installation of "Desktop development with C++", which contains the capability.<br>

#### Summary:
This is a MapReduce program that takes in a set of text files from an input folder designated by the user and returns a text file that contains every word contained in the input files and how many times each word is repeated. Each class has a corresponding header to declare its methods and include files, Map and Reduce is connect as DLL to the client executable file for mapping word and reducing word.

The program will prompt the user to enter 3 paths. The first is the `input files path`, the second is the `intermediate output path`, and the last is the `output files path`.

#### Program Contains the Following Classes:
Main - Prompts the user to designate input folder, temporary folder, and output folder. Then, it sends those folder paths to the Workflow class.

Workflow Class - Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.

FileManager Class: Used to open files, read files, create files, and delete files in the folders designated by the user.

Sorter Class: Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.

#### Program Contains the Following DLLs:

Map DLL: Receives a string from Workflow, splits every word, and appends a "1" to each word. A buffer of preset size is used to periodically write to the mapped file in the temporary directory.

Reduce DLL: Deletes repeated words and append a "1" to the original word to count how many times it was repeated. Then, returns a final reduced string.<br>

#### Results: 
The final output text file will be a reduced file containing one word per line in alphabetical order followed by a "1" for each time that specific word was repeated. A separate success file is also created in the output directory to mark the completion of the Map-Reduce program.


_______________
* ### Project 1

#### Requirements to Run:
C++17 - Needed to include the "filesystem" library used by the FileManager class.
>In Visual Studio, go to `Project` > `Properties` > `Configuration Properties` > `C/C++` > `Language` > `C++ Language Standard` > `ISO C++17 Standard`.<br>

Google Testing - Need Visual Studio installation of "Desktop development with C++", which contains the capability.

#### Summary:
This is a MapReduce program that takes in a set of text files from an input folder designated by the user and returns a text file that contains every word contained in the input files and how many times each word is repeated. Each class has a corresponding header to declare its methods and include files. <br>
The program will prompt the user to enter 3 paths. The first is the `input files path`, the second is the `intermediate output path`, and the last is the `output files path`.


#### Program Contains the Following Classes:
Main - Prompts the user to designate input folder, temporary folder, and output folder. Then, it sends those folder paths to the Workflow class.<br><br>
Workflow Class - Calls the FileManager class to handle file operations and the Mapper, Sorter, and Reducer classes to handle the modification algorithms.<br><br>
FileManager Class: Used to open files, read files, create files, and delete files in the folders designated by the user.<br><br>
Mapper Class: Receives a string from Workflow, splits every word, and appends a "1" to each word. A buffer of preset size is used to periodically write to the mapped file in the temporary directory.<br><br>
Sorter Class: Reads a string vector from the mapped file, sorts the vector in alphabetical order, and creates a sorted file in the temporary directory.<br><br>
Reducer Class: Deletes repeated words and append a "1" to the original word to count how many times it was repeated. Then, returns a final reduced string.
<br>

#### Results:
The final output text file will be a reduced file containing one word per line in alphabetical order followed by a "1" for each time that specific word was repeated.
A separate success file is also created in the output directory to mark the completion of the Map-Reduce program.
