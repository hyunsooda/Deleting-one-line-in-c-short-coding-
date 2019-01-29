# Deleting-one-line-in-c-short-coding-
Deleting one line in c(short coding)


There are two ways to implement deleting one line.
There are two goto statement which is implemented two ways each other.

we don't need to discuss about EXIT2(first way) and time complexity is dependent on size of file. 

Let me explain about second way(EXIT1), second way will be good in terms of time complexity but it has a critical problem on length of line

Assume there is a test.txt
<pre><code>
asd
123
qwe
456
johndoe
good
man
</code></pre>

if we delete johndoe, the result is 
<pre><code>
asd
123
qwe
456
good
oe
mand
</code></pre>
this is not expected one. why this happen? because length of johndoe is 7 and alternative line(good) is 5.
if solve this problem and can proceed with this way, we can reduce amount of processing time but it is also dependent on position of target line.

Maybe, I think that database venders have implemented inserting and deleting the data with second way or awesome another way to reduce amount of processing.

