#pragma once

#include <Windows.h>
#include <unordered_map>

#include "IMemorySource.hpp"

class ProcessMemory
{
	//
	//
	// Variables
	//
	//

	/**
	 * \brief The id of the process.
	 */
	DWORD process_id;

	/**
	 * \brief The current memory source.
	 */
	IMemorySource * memory_source = nullptr;

	/**
	 * \brief The list of memory sources.
	 */
	std::unordered_map<const char *, IMemorySource *> memory_sources;

public:

	/**
	 * \brief The current memory source name.
	 */
	static char * current_memory_source;

	//
	//
	// Constructors/Destructors
	//
	//

	/**
	 * \brief Stores the parameters.
	 * \param process_id the id of the process
	 */
	explicit ProcessMemory(DWORD process_id);

	/**
	 * \brief Deletes the memory source.
	 */
	~ProcessMemory();


	//
	//
	// Important functions
	//
	//

	/**
	  * \brief Reads memory from the process. (e.g. float)
	 * \tparam T the read value data type
	 * \param start_address the memory start address
	 * \return the memory buffer
	 */
	template <typename T>
	auto ReadMemory(const DWORD_PTR start_address) -> T
	{
		return reinterpret_cast<T>(this->memory_source->ReadMemory(start_address, sizeof(T)));
	}

	/**
	 * \brief Reads memory from the process. (e.g. float[])
	 * \tparam T the read value data type
	 * \param start_address the memory start address
	 * \param size the size of the memory buffer
	 * \return the memory buffer
	 */
	template <typename T>
	auto ReadMemory(const DWORD_PTR start_address, const SIZE_T size) -> T
	{
		return reinterpret_cast<T>(this->memory_source->ReadMemory(start_address, size));
	}

	/**
	 * \brief Reads memory from the process. (e.g. float or float[])
	 * \param start_address the memory start address
	 * \param size the buffer size
	 * \return the memory buffer
	 */
	auto ReadMemory(DWORD_PTR start_address, SIZE_T size) const -> PVOID;


	//
	//
	// Checks
	//
	//

	/**
	 * \brief Checks whether the memory is valid.
	 * \return true if successful
	 */
	auto IsValid() const -> BOOL;


	//
	//
	// Getters
	//
	//

	/**
	 * \brief Returns the base address.
	 * \return the base address of the process
	 */
	auto GetBaseAddress() const -> DWORD_PTR;

	/**
	 * \brief 
	 * \return 
	 */
	static auto GetMemorySources() -> std::vector<const char*>;


	//
	//
	// Setters
	//
	//

	/**
	 * \brief Sets the new memory source name. 
	 * \param memory_source_name the name of the memory source
	 * \return true if successful
	 */
	static auto SetMemorySource(char * memory_source_name) -> VOID;
};
