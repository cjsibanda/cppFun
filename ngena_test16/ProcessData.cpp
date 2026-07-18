// Exercise - Multi-Threading, Thread Class

#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
#include <thread>
#include "ProcessData.h"

namespace seneca
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2.
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++)
		{
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2.
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++)
		{
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data != nullptr && num_threads>0 && averages && variances && p_indices;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples.
	ProcessData::ProcessData(const std::string& filename, int n_threads) {
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream file(filename, std::ios::in | std::ios::binary);
		if (!file)
		{
			throw std::string("Cannot open file: " + filename);
		}

		//-->Read total_items (first 4 bytes)
		file.read(reinterpret_cast<char*>(&total_items), sizeof(total_items));

		//Allocate the memory for dynamic data block
		data = new int[total_items];

		//Read the dataset values into data array
		file.read(reinterpret_cast<char*>(data), total_items * sizeof(int));

		file.close();


		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}

	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Implement operator(). For the computation of average and variance run the
	//   functions `computeAvgFactor` and `computeVarFactor` in multiple threads.
	// The function divides the data into a number of parts, where the number of parts is
	//   equal to the number of threads. Use multi-threading to compute average-factor for
	//   each part of the data by calling the function `computeAvgFactor`. Add the obtained
	//   average-factors to compute total average. Use the resulting total average as the
	//   average value argument for the function computeVarFactor, to compute variance-factors
	//   for each part of the data. Use multi-threading to compute variance-factor for each
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument `target_file`.
	// Also, read the workshop instruction.

    //--> Implementing operator() using std::thread and std::bind
	int ProcessData::operator()(const std::string& target_file, double& avg, double& var){
		///////////////////////////////////////////////////////
		//-> part 1: Compute averages with Mulit-Threading 
		///////////////////////////////////////////////////////
		std::vector<std::thread> avgThreads;

		for (int i = 0; i < num_threads; ++i) {
			//--> figure out current partision bounds
			int start_idx = p_indices[i];
			int size = p_indices[i + 1] - start_idx;

			//Bind computeAvgFactor 3rd parameter (divisor) to total_items
			// pass placeholder values for parameters 
			auto boundAvgFunc = std::bind(computeAvgFactor,
			 std::placeholders::_1,
			 std::placeholders::_2,
		     total_items,
	         std::placeholders::_3);

			 //Spawn the thread passing bound calculation
			 avgThreads.push_back(std::thread(boundAvgFunc, &data[start_idx], size, std::ref(averages[i])));
		}

		//--> Synchronize htread executions
		for (auto& th : avgThreads){
			th.join();
		}

		//Accumulate individual factor averages to get global average
		avg = 0.0;
		for (int i = 0; i < num_threads; ++i) 
		{
			avg += averages[i];
		}

		/////////////////////////////////////////////////////
		// Part 2 : Computing Variances with Multi-Threading
        //////////////////////////////////////////////////////
		std::vector<std::thread> varThreads;

		for (int i = 0; i < num_threads; ++i) 
		{
			int start_idx = p_indices[i];
			int size = p_indices[i + 1] - start_idx;

			//Bind divisor (total_items) and computed average (avg) to computeVarFactor
			auto boundVarfunc = std::bind(computeVarFactor,
			std::placeholders::_1, std::placeholders::_2, total_items, avg, std::placeholders::_3);

			//spawn variance computation thread
			varThreads.push_back(std::thread(boundVarfunc, &data[start_idx], size, std::ref(variances[i])));

		}

		//Synchronize threads
		for (auto& th : varThreads)
		{
			th.join();
		}

		//Accumulate individual variance factors to get total variance
		var = 0.0;
		for (int i = 0; i < num_threads; ++i) 
		{
			var += variances[i];
		}

		////////////////////////////////////////////////////////
		// Part 3: Save results to target file in binary format
		/////////////////////////////////////////////////////////
		std::ofstream file(target_file, std::ios::out | std::ios::binary);
		if (!file) 
		{
			throw std::string("Cannot open the target file for writing: " + target_file);
		}

		//Write first 4 bytes representing item count
		file.write(reinterpret_cast<const char*>(&total_items), sizeof(total_items));

		//Write dataset array contents sequentially
		file.write(reinterpret_cast<const char*>(data), total_items * sizeof(int));

		file.close();

		return total_items;
	}


}