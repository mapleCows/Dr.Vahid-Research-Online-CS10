# Dr.Vahid-Research-Online-CS10

# Lab 1

## Student information
* Full name: Luis Sanchez
* E-mail: lsanc044@ucr.edu	
* UCR NetID: lsanc044
* Student ID: 862046663

## Answers


(Q1) copied 33554432 bytes from 'AREAWATER.csv' to 'AREAWATER-COPY.csv' in 20440932900 nano seconds.

20.4 seconds.

(Q2) 56.997644 seconds

(Q3) 56.997644 - 20.4  = 36.597644 second diffrence
	Since we are using the hadoop FileSystem API we can expect much faster speeds than our local disk drive since a diffrent file system is being used. 
On the normal windows copy and paste command from the cmd we are using the much slower windows file system to copy the data over. 
When using the hadoop FileSystem API we are using the Hadoop file system servers to copy the data over and those are much faster than our local windows file system.


(Q4) copied 134217728 bytes from 'test.txt' to 'test2.txt' in 488995700 nano seconds.
20/04/08 14:15:27 ERROR hdfs.DFSClient: Failed to close file: /user/Luis/test2.txt with inode: 16390



(Q5)
Copy a file from local file system to HDFS

	copied 134217728 bytes from 'file:///C:\Users\Luis\lab2_lsanc044\test.txt' to 'test4.txt' in 406449200 seconds.

Copy a file from HDFS to local file system.

       copied 134217728 bytes from 'test.txt' to 'file:///C:\Users\Luis\lab2_lsanc044\test5.txt' in 65784600 seconds.
    
Copy a file from HDFS to HDFS.

	copied 134217728 bytes from 'test.txt' to 'test12.txt' in 389159400 seconds.


| TEST| time (s)          |
| ------------- |:-------------:|
| Local Jar large file  | 20.4 |
| Windows File copy paste      | 56.99      |
| local to HDFS | 0.488 |
| HDFS to local | 0.065      |
| HDFS to HDFS | 0.389     |
