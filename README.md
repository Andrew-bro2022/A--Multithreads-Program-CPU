# A---Multithreads-program-CPU
**Summary**A C++ program using threads to improve the performance of CPU


**Technical Highlights:**

**1. The advantages of using multiple threads**

    In this program, I created 4 threads according to the CPU. The speed of the program is boosted by 75%.
    Below the code are the vector, provider, and threads.
	  I put 4 package_task objects into 4 threads as the task function.
    Last, I also put the string which is one-quarter of the total string of the map.
	
	//code separating map data:

		std::vector<std::string> strArr;// str0, str1, str2, str3
	
	//code provider:package_task:

        std::packaged_task<size_t(std::string)> pt1(func);
        std::packaged_task<size_t(std::string)> pt2(func);
        std::packaged_task<size_t(std::string)> pt3(func);
        std::packaged_task<size_t(std::string)> pt4(func);
	
	//code thread:

		std::thread t1(std::move(pt1), strArr[0]);
		std::thread t2(std::move(pt2), strArr[1]);
		std::thread t3(std::move(pt3), strArr[2]);
		std::thread t4(std::move(pt4), strArr[3]);

**2. Futures and packaged_tasks**

	The code of "future" and "package_task" is like below. The future works with providers together. The "share states"
	is like a bridge that connects them. The package_task(provider) stores the task and set the value of the share state.
	Then, the future can be assigned by provider.get_future(). After this, in the "code thread" of the above Question #3,
	I used 4 threads to deal with the search task. At this step, the 4 different values were calculated in 4 different
	share states. Last, I can get the total number by doing "count = f1.get() + f2.get() + f3.get() + f4.get();".
	
	//provider - package_task:
 
        std::packaged_task<size_t(std::string)> pt1(func);
        std::packaged_task<size_t(std::string)> pt2(func);
        std::packaged_task<size_t(std::string)> pt3(func);
        std::packaged_task<size_t(std::string)> pt4(func);

  	//future:
    
        auto f1 = pt1.get_future();
        auto f2 = pt2.get_future();
        auto f3 = pt3.get_future();
        auto f4 = pt4.get_future();
		
	//join
 
	t1.join();
        t2.join();
        t3.join();
        t4.join();

**Output**

![image](https://github.com/user-attachments/assets/43374a05-9e8c-4539-9b13-37d72352a5d5)
