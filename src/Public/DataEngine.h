#pragma once
#include <atomic>
#include <memory>
#include "EngineCore.h"

namespace core {
	/**
	* The top-level virtual class for all DataEngines. It defines behavior that is shared between among
	* all valid implementations of DataEngine. Certain macros are also to be used while creating a new
	* implementation. All DataEngines support move semantics and cloning. Copy constructors are disabled
	* to prevent shallow-copying. This class is implemented by various partial implementations which
	* further lead to
	* @tparam E
	*/
	template <typename E>
	class DataEngine : Iterator<E> {
	protected:
		size_t maxCapacity;
		size_t activeCapacity;

		virtual ~DataEngine() = default;
		DataEngine() = default;

		//Adding move semantics
		DataEngine(DataEngine&&) noexcept = default;
		DataEngine& operator=(DataEngine&&) noexcept = default;

	public:
		//Removing copy semantics
		DataEngine(const DataEngine&) = delete;
		DataEngine& operator=(const DataEngine&) = delete;

		//Nature methods
		bool isMutable() const;
		bool isThreadSafe() const;

		//Size methods
		virtual size_t getActiveSize();
		virtual size_t getMaxCapacity();

		//Empty check
		bool isEmpty() const;

		/**
		* Virtual polymorphic copy method, required to override the copy constructor behavior
		*/
		virtual std::unique_ptr<DataEngine<E>> clone() const = 0;

		/**
		* Virtual polymorphic move method
		*/
		virtual std::unique_ptr<DataEngine<E>> move() noexcept = 0;

		//Functions that all implementations must guarantee

		/**
		* Creates a thread-safe image of the invoking data-engine by wrapping it in atomic
		*
		* @return Returns a @code std::atomic pointer containing the invoking engine
		*/
		virtual std::atomic<DataEngine<E>>* getThreadSafeImage() = 0;

		/**
		* Removes all the items if present
		*
		* @return Returns true if all items are removed, false if already empty
		*/
		virtual bool removeAll() = 0;

		/**
		* Checks if the invoking data engine and the engine passed are equal.
		* Here equality is considered as both having the same ordering of elements and identical
		* sizes, including maximum capacity
		*
		* @param engine The engine to be compared with
		* @return Returns true if both are equal, false otherwise
		*/
		virtual bool equals(DataEngine<E>* engine) = 0;

		/**
		* Converts the invoking data engine into an array of all the elements
		*
		* @return Returns an array representation
		*/
		virtual E* toArray() = 0;

		/**
		* Converts the invoking data engine into an array of all the elements in the provided range
		*
		* @param start Starting index
		* @param end Endpoint index
		* @return Returns the array representation
		*/
		virtual E* toArray(int start, int end) = 0;

		/**
		* Checks if two Data Engines are equivalent, i.e., both contain the same elements,
		* irrespective of length and repetition
		*
		* @param engine The engine to be compared with
		* @return Returns true if both are equivalent, false otherwise
		*/
		virtual bool equivalence(DataEngine<E>* engine) = 0;
	};
}