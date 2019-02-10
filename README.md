# Deleting-one-line-in-c-short-coding-
Deleting one line in c(short coding)

# Before applying deletion marker
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

# After applying deletion marker
My major is computer science but I totally forgot disk's mechanism...
Before thinking woenderful solution for this problem, I have read some database article and there was deletion marker!!
I have studied database(both RDBMS and Nosql) but... anyway, I have solved deleting oneline using deletion marker and implemented by C lang.

### there are two things we have to consider.
<ul>
  <li>1. When perform clean marked space ?  </li>
  <li>2. Other operations are wating during operation of cleaning ? </li>
</ul>

About answer of first stuff, I let process clean marked space when deletion marker is 5
About answer of second stuff, Yes. this question is relavant with first question. if perform clean when deletin marker is very bigger, wating time will be long but in case of lower, wating time will be short. 
Also this is simliar to Mark Sweep Algorithm(Garbage Collector)


