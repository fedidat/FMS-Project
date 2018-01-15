*********VERY IMPORTANT!!!**********
I implemented the random number generating algorithm without repeats, as we discussed in class on 23/05/11.
The folder "Level 2" contains the project including the algorithm's implementation. But sometimes (without making changes, it may be hard to believe), it RETURNS BAD ALLOCATION.
That is why I included the folder "Level 2 Iterative" that uses the {0,1,...,499} series key implementation, which should give better results to MODHFunc.

FOR YOUR INFORMATION:
A lot of changes were made from Level 1 to Level 2, aside from the mandatory functions: 
- Better and faster implementations with the knwoledge of the overall behavior and ultimate goals of each function.
- Much more comments: almost line by line in both PhysicalFile.cpp and HashFile.cpp.
- Fine testing material in MainProgram.cpp.

HOW TO USE:
You will mainly want to test functions 20, 21 and 22, which present the behavior of the hash functions with 500 identical records.
Aside from that, you can easily read and write any record in any file. Do not forget to [create AND] open the file beforehand!

MISC:
"Level 2"
Copyright Pinhas Fedidat (ID 7665692), Aviram Michaeli (ID 302210224), 2011.
For Dr. Moshe Goldstein, Project in File Management Systems, Jerusalem College of Technology.
The software is provided "as is", without any warranty. 
You are free to make any changes, as long as you keep this disclaimer in its present form.