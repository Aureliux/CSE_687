# CSE_687 - Object Oriented Design
# Team Members: Omar Vargas, Huiying Wu

This is a MapReduce word count program.

Program contain:

WorkFlow Class: tie together all components.

File Manager Class: use to open the file, read the file, create the file, and write to temp or output file.

Map Class: will accept a string from the workflow, break it into words and append a 1 to each word.

Sort Class: accept a vector and sort the vector in alphabetical order and then send it to reduce class.

Reduce Class: deleted duplicate words and append 1 to the original word whenever there is a duplicate occurs.



The final output will be in alphabetical order with words that occur in the text files with many numbers of 1 as it occurs in the text.
