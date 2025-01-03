# Sorting-Algorithm-Performance-Comparison
Write a C code to implement the heapsort, as explained in our lectures.  


1)	Implement the heapsort algorithm using the declarations below: (70 points)
a.	Your implementation must be consistent with the below declarations. (Minor or major error otherwise!)
b.	Your implementations must be consistent with the pseudocode introduced in the corresponding lectures (see lecture slides). 
![image](https://github.com/user-attachments/assets/85627c50-9f2b-4f02-8d29-9b78f944f80c)
2)	Evaluate the Heapsort Algorithm (30 points)
a.	Use arrays of a large size, where array_size ranges from 27 … 222
i.	Create a heap named 'h' and two arrays named 'f' and 'g'. Please use these exact names.
ii.	Start indexing at 1. Leave out the first array index (it will remain unused).
iii.	Fill all three arrays with random numbers as demonstrated below.
    int tmp;
    for(unsigned int i=1; i < array_size; i++){ 
//deliberately leaving out the first array element
        tmp = rand()%INT16_MAX;
        f[i] = (unsigned long) tmp; 
        g[i] = (unsigned long) tmp;
        h->arr[i] = (unsigned long) tmp;
    }   

iv.	Ensure that all three arrays are equal (i.e., same size and content).
b.	Measure the time it takes to perform the following sorting operations:
i.	Sort the elements of 'h' using the heap_sort() algorithm.
ii.	Sort the elements of 'g' using the insertion_sort() algorithm.
iii.	Sort the elements of 'f' using the merge_sort() algorithm.
iv.	Use the methods provided by <time.h> (i.e., clock(), difftime(), and the constant CLOCKS_PER_SEC) to measure the time, as demonstrated in previous labs and lectures when discussing merge_sort.
v.	Write the necessary C code to store the results in a comma-separated file.

c.	Use Excel to generate a scatter plot, where each algorithm's measured running time 't' (in milliseconds) is plotted against log2(array_size).
![image](https://github.com/user-attachments/assets/84299cde-3ca1-45ea-b1f2-62b481c6795c)

