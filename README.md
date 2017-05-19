An online retail system similar to Amazon that can read/write to a database and recommend products based on similar user's reviews using Dijkstra's algorithm. This retail system, coded in C++ and QT, features an efficient search that parses keywords and matches them to search results for O(1) access. Password hashing is used to store user passwords securely. The hashing, sorting, mapping, dijkstra, and product recommendation algorithms were all coded from scratch without the use of libraries. 

To run the program, simply run 
$ make clean
$ qmake
$ make
$ ./RetailSystem database.txt 

(You can use any of the databases provided, or make your own as long as it meets the database criteria.)