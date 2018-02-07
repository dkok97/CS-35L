CS 35L
DINKAR KHATTAR
204818138

We first log into the seasnet server.
We then create a directory for srt and
get the files using:

$ wget http://web.cs.ucla.edu/classes/fall17/cs35L/assign/srt.tgz

We then untar this using:

$ tar -xzf srt.tgz

We focus on main.c where we implement multithreading.
At the moment, the program only supports one thread
and if we run it with anything that uses more than
one thread, it outputs an error. I remove this part
of the code and try to implement the function that 
using ’n’ number of threads (nthreads).

The part of the program that can be threaded
is the nested loop in the main function where
we go through each pixel of the image using the
heigh and width.
To be able to use multiple threads, I moved the
part with the loop outside the main function
and into a new function that is connected to each
thread.

I created two loops in the main function, one for
creating the threads using pthread_create and one for
joining the threads using pthread_join.

The way I structured the threading was to divide the image
into multiple parts and let each thread work on a portion.
I used thread IDs for each thread and passed that into
our function. We started the loop at this thread ID and
incremented it by the total number of threads. This way, each
thread works on certain number of pixels, and all threads
together cover all the pixels.

Once I tried running the program, I ran into two problems.

The first problem was with the scene variable.
Since our new function uses the scene variable,
it must be declared as a global variable, instead
of it being in the main function. So I moved the 
declaration of the scene variable outside.

The second problem was with the printing of the pixels.
Since we don’t work on consecutive pixels, the pixels that
print out are not in order. This is confusing to interpret
and is inaccurate. To fix this, I declare a 3D array and store
the values of each pixel into the array once it is worked on
by the function, at the appropriate position. I finally loop
through the array and print all the values in the array at 
the end of the main function.

I finally ran ‘make clean check’ (output in make-log.txt) and
got the following outputs for time:

1 thread:

real	0m41.398s
user	0m41.392s
sys	0m0.000s

2 threads:

real	0m21.799s
user	0m43.219s
sys	0m0.002s

4 threads:

real	0m11.243s
user	0m44.442s
sys	0m0.003s

8 threads:

real	0m5.792s
user	0m44.873s
sys	0m0.002s

We notice that there is improvement in performance
in terms of time taken, with an increase in the number
of threads. The real time decreases since the tasks
are no longer linear and are performed simultaneously.
There is a slight increase in user time, which is a
con of multithreading.


