# A-C-program---Multithreads-CPU
**Summary**A C++ program using threads to improve the performance CPU


**Technical Highlights:**

1. 	In this program, I created 4 threads according to the CPU. The speed of the program is boosted by 75%.
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
