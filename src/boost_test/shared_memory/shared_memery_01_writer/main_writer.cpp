#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <cstdio>
#include "doc_anonymous_condition_shared_data.hpp"
#include <boost/interprocess/windows_shared_memory.hpp>
using namespace boost::interprocess;

int main ()
{
#ifdef USE_WINDOW
	//Erase previous shared memory and schedule erasure on exit
	struct shm_remove
	{
		shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
	} remover;

	//Create a shared memory object.
	
	try{
		windows_shared_memory shm
			(create_only               //only create
			,"MySharedMemory"           //name
			,read_write ,
			sizeof(trace_queue) + trace_queue::getBufferSize()//read-write mode
			);

		//Map the whole shared memory in this process
		mapped_region region
			(shm                       //What to map
			,read_write //Map it as read-write
			);

		//Get the address of the mapped region
		void * addr       = region.get_address();

		//Construct the shared structure in memory
		trace_queue * data = new (addr) trace_queue;

		const int NumMsg = trace_queue::LineSize;

		boost::posix_time::ptime time_now, time_now1;
		boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

		char* pBufferTemp = new char[trace_queue::RowSize];

		time_now = boost::posix_time::microsec_clock::universal_time();
		for(int i = 0; i < NumMsg; ++i){
			scoped_lock<interprocess_mutex> lock(data->mutex);
			if(data->message_in){
				data->cond_full.wait(lock);
			}
			if(i == (NumMsg-1))
				std::sprintf(data->items, "%s", "last message");
			else
				std::sprintf(data->items, "%s_%d", "my_trace", i);

			//memset(data->m_pItems[i], i + 1, trace_queue::RowSize);
			data->m_nDataIndex = i;
			memcpy(data->m_pItems[data->m_nDataIndex], pBufferTemp, trace_queue::RowSize);
			//Notify to the other process that there is a message
			data->cond_empty.notify_one();

			//Mark message buffer as full
			data->message_in = true;
		}
		time_now1 = boost::posix_time::microsec_clock::universal_time();
		time_elapse = time_now1 - time_now;

		int nTick = time_elapse.total_milliseconds();
		std::cout << "MemSpeed:"
			<< nTick / (double(trace_queue::getBufferSize()) / _MB)
			<< " ms/MB \n"; 
	}
	catch(interprocess_exception &ex){
		std::cout << ex.what() << std::endl;
		return 1;
	}
	std::system("pause");
	return 0;
#else
	//Erase previous shared memory and schedule erasure on exit
	struct shm_remove
	{
		shm_remove() 
		{ 
			shared_memory_object::remove("MySharedMemory"); 
			shared_memory_object::remove("MySharedMemory1");
		}
		~shm_remove()
		{ 
			shared_memory_object::remove("MySharedMemory"); 
			shared_memory_object::remove("MySharedMemory1");
		}
	} remover;

	//Create a shared memory object.
	shared_memory_object shm
		(create_only               //only create
		,"MySharedMemory"           //name
		,read_write                //read-write mode
		);

	shared_memory_object shm_my_data
		(create_only               //only create
		,"MySharedMemory1"           //name
		,read_write                //read-write mode
		);
	try{
		//Set size
		shm.truncate(sizeof(trace_queue));
		//Map the whole shared memory in this process
		mapped_region region
			(shm                       //What to map
			,read_write //Map it as read-write
			);

		//Get the address of the mapped region
		void * addr       = region.get_address();
		//Construct the shared structure in memory
		trace_queue * data = new (addr) trace_queue;

		shm_my_data.truncate(trace_queue::getBufferSize());
		mapped_region region_my_data
			(shm_my_data                       //What to map
			,read_write //Map it as read-write
			);
		void * addr_data       = region_my_data.get_address();
// 		for (int i = 0; i < trace_queue::LineSize; ++i)
// 		{
// 			data->m_itemsaddr[i] = (unsigned char*)addr1 + i * trace_queue::RowSize;
// 		}

		const int NumMsg = trace_queue::LineSize;

		boost::posix_time::ptime time_now, time_now1;
		boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;

		char* pBufferTemp = new char[trace_queue::RowSize];
		memset(pBufferTemp, 0, trace_queue::RowSize);
		std::cout << "Ready Write...!" << std::endl;

		bool bfirst = true;
		
		for(int i = 0; i < NumMsg; ++i){
			scoped_lock<interprocess_mutex> lock(data->mutex);
			if(data->message_in){
				data->cond_full.wait(lock);
			}
			if(i == (NumMsg-1))
			{
				std::sprintf(data->items, "%s", "last message");
			}
			else
			{
				//std::sprintf(data->items, "%s_%d", "my_trace", i);
				std::sprintf(pBufferTemp, "%s_%d", "mydata with index of ", i);
			}

			//memset(data->m_pItems[i], i + 1, trace_queue::RowSize);
			if (bfirst)
			{
				time_now = boost::posix_time::microsec_clock::universal_time();
				bfirst = false;
			}

			data->m_nDataIndex = i;
			//memset((char*)addr_data + i * trace_queue::RowSize, 0, trace_queue::RowSize);
			memcpy((char*)addr_data + i * trace_queue::RowSize, pBufferTemp, trace_queue::RowSize);
			//Notify to the other process that there is a message
			data->cond_empty.notify_one();
			data->message_in = true;
		}
		time_now1 = boost::posix_time::microsec_clock::universal_time();
		time_elapse = time_now1 - time_now;
		std::cout << "Write Finish!";
		int nTick = time_elapse.total_milliseconds();
		std::cout << "MemSpeed:"
			<< nTick / (double(trace_queue::getBufferSize()) / _MB)
			<< " ms/MB \n"; 
	}
	catch(interprocess_exception &ex){
		std::cout << ex.what() << std::endl;
		return 1;
	}
	std::system("pause");
	return 0;
#endif
}