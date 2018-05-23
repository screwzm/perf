%title: High Performance Programming
%author: Zhiming, WANG, 2018/05/24, ShanCe Technologies.
%date: 2018-05-24

-> _SUMMARY_ <-

This sharing consists of following chapters.

*Chapter 1* - Introducing main rules on high performance programming
*Chapter 2* - Introducing main technicals on high performance programming
*Chapter 3* - Some C++ case and example
*Chapter 4* - Some System programming case and exmple
*Chapter 5* - Discussion

---
-> _Chapter 1_ <-

# 1.1 Misunderstanding on optimization

> "Premature optimization is the root of all evil." - by *Somebody*
This is the main known wisdom accpted by the public about optimization, and indicates that optimization should be avoided until the very late stage of development.


But I prefer

<br>
> "Familiarize yourself with the best practices and the pitfalls of optimization will help deliver high quality code in the first place." - by *Zhiming, WANG*

<br>
>> "It's ok to take performance into consideration in the first place, even in design stage of your project. What is not ok is spending too much time on deciding which method has better performance and don't actually coding any line." -  From *<<Optimized C++>>*


# 1.2 RULES

<br>
*Rule #1* - It's OK to optimize as early as in design stage.

<br>
*Rule #2* - Always design measure method before any *MAJOR* optimization.
Some trivial optimization may be justfied easily, such as copy elision. Major/systematic optimization must be measured by data, i.e. latency and throughput. Examples in this sharing will be measured by *Google benchmark*.

<br>
*Rule #3* - Obey the "1/9 rule". 
That's 90% of the calculation are handled by 10% of the code. This means that 90% of our code base is not performance critical. Optimization those 90% code has little performance benfit. DO NOT try to optimize all the code.

<br>
*Rule #4* - Optimize with priority in mind: algorithm, IO, data access, lib ...

---

-> _Chapter 2_ <-

#2.1 Main technicals

<br>
*#1 Know the best algorithm for common use case*
And use the best algorithms in your project.

<br>
*#2 Avoid unnecessary overhead*
Know background operations behind API call, and Pay only what we have to.

<br>
*#3 Use the proper Data Structure*
Know details of different DS.

<br>
*#4 IO optimize*

<br>
*#5 Make cache your friend*

<br>
*#6 System level optimization*
lockfree, kernel bypass, numa/cpu affinity, irq affinity, lock memory etc.

<br>
*And More ...*



