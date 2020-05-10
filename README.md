# CPSC350-Assignment-5
Building a Database


Relational Operator Overloading :
https://www.geeksforgeeks.org/types-of-operator-overloading-in-c/
https://en.cppreference.com/w/cpp/language/operator_comparison


Maya Mistry helped me with some errors I couldn't figure out, and gave me insight on somethings I was confused on since my usual partner dropped the class :(

I used files from past assignments, and code from class to complete this assignment.

There is a file on student and faculty table so you can visualize but it should work with another textFile with the same name and format.
Student file format is:
    --
    id
    name
    level
    gpa
    major
    advisor id
    --


Faculty file format is:
    --
    id
    name
    level
    department
    # advisees (n)
    n lines of advisee ids
    --


Delete student was giving a segmentation fault if I selected to add a student (7), added it and then chose to delete(8), but I think I fixed it. another thing that I didn't think was working was 11- changing student advisor but i also think it was fixed and should work now.


I couldn't figure out serialization and deserialization, and Rene told us it was ok to read and write to a file.
