#pragma once
#include <atomic>
#include <memory>
#include <any>
#include "EngineCore.h"

namespace core {

	template<typename E>
	class DataEngine;

	template<typename E, typename Derived>
	concept ValidBase = is_base_of<DataEngine<E>, Derived>::value;

	class Dummy {}; //Dummy needed for sortable.

	/**
	* The top-level virtual class for all DataEngines. It defines behavior that is shared between among
	* all valid implementations of DataEngine. Certain macros are also to be used while creating a new
	* implementation. All DataEngines support move semantics and cloning. Copy constructors are disabled
	* to prevent shallow-copying. This class is implemented by various partial implementations which
	* can be used to create concrete implementations of DataEngine. Using this class as a direct superclass
	* is considered an error and will result in a compilation error
	* @tparam E Type parameter of stored data
	*/
	template <typename E>
	class DataEngine : Iterable<E> {
	protected:
		size_t maxCapacity;
		size_t activeCapacity;

		constexpr static double GOLDEN_RATIO = 1.61803398875;
		constexpr static int DEFAULT_CAPACITY = 16;

		constexpr static double GROWTH_LOAD_FACTOR = 0.75;
		constexpr static double SHRINK_LOAD_FACTOR = 0.25;

		virtual void grow() = 0; //Method to grow the capacity of the data engine
		virtual void shrink() = 0; //Method to shrink the capacity of the data engine
		virtual void compress() = 0; //Method to compress the data engine

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
		[[nodiscard]] bool isMutable() const;
		[[nodiscard]] bool isThreadSafe() const;

		//Size methods
		[[nodiscard]] size_t getActiveSize() const;
		[[nodiscard]] size_t getMaxCapacity() const;

		//Empty check
		[[nodiscard]] bool isEmpty() const;

		/**
		* Virtual polymorphic copy method, required to override the copy constructor behavior
		*/
		virtual std::unique_ptr<DataEngine> clone() const = 0;

		/**
		* Virtual polymorphic move method
		*/
		virtual std::unique_ptr<DataEngine> move() noexcept = 0;

		//Functions that all implementations must guarantee

		/**
		* Creates a thread-safe image of the invoking data-engine by wrapping it in atomic
		*
		* @return Returns a @code std::atomic pointer containing the invoking engine
		*/
		template<typename T> requires ValidBase<E, T>
		std::atomic<T>* getThreadSafeImage() const;

		/**
		* Removes all the items if present
		*
		* @return Returns true if all items are removed, false if already empty
		*/
		virtual bool removeAll() = 0;

		/**
		* Converts the invoking data engine into an array of all the elements
		*
		* @return Returns an array representation
		*/
		virtual E* toArray() const = 0;

		/**
		* Converts the invoking data engine into an array of all the elements in the provided range
		*
		* @param start Starting index
		* @param end Endpoint index
		* @return Returns the array representation
		*/
		virtual E* toArray(int start, int end) const = 0;

		/**
		* Checks if the invoking data engine and the data engine passed are truly equal, i.e. equal length
		* and ordering of elements
		*
		* @tparam T Type argument for data engine
		* @param de Data engine to compare with
		* @return Returns true if equal, false otherwise
		*/
		template<typename T> requires ValidBase<E, T>
		bool operator==(T de) const;

		/**
		* Checks if the invoking data engine and the data engine passed are truly equal in the provided range,
		* i.e. equal ordering of elements
		*
		* @tparam T Type argument for data engine
		* @param de Data Engine to compare with
		* @param start Start index
		* @param end End index
		* @return Returns true if equal, false otherwise
		*/
		template<typename T> requires ValidBase<E, T>
		[[nodiscard]] bool equals(T de, int start, int end) const;

		/**
		* Checks if the invoking data engine and the data engine passed are equivalent, i.e. have the same
		* elements but not necessarily in the same order
		*
		* @tparam T Type argument of for the data engine
		* @param de Data engine to compare with
		* @return Returns true if equivalent, false otherwise
		*/
		template<typename T> requires ValidBase<E, T>
		[[nodiscard]] bool equivalence(T de) const;

		/**
		* Merges the invoking data engine with the data engine passed. It creates a new instance containing
		* all the elements of both data engines
		*
		* @tparam T Type argument for the data engine
		* @param de Data engine to merge with
		* @return Returns the merged data engine
		*/
		template<typename T> requires ValidBase<E, T>
		T merge(T de) const;

		/**
		* Merge the invoking data engine with the data engine passed, starting from the provided index
		* It creates a new instance containing all the elements of both data engines
		*
		* @tparam T Type argument for the data engine
		* @param de Data engine to merge with
		* @param start Starting index
		* @return Returns the merged data engine
		*/
		template<typename T> requires ValidBase<E, T>
		T merge(T de, int start) const;

		/**
		* Merge the invoking data engine with the data engine passed, starting from the provided start index
		* and ending at the provided end index. It creates a new instance containing all the elements of both
		* data engines
		*
		* @tparam T Type argument for the data engine
		* @param de Data engine to merge with
		* @param start Starting index
		* @param end Endpoint index
		* @return Returns the merged data engine
		*/
		template<typename T> requires ValidBase<E, T>
		T merge(T de, int start, int end) const;

		/**
		* Reverses the invoking data engine
		*/
		virtual void reverse() = 0;


	protected:
		//Type-erasure forms of methods that need to be both virtual and template

		/**
		* Internal type-erasure form of getThreadSafeImage, used to create a thread-safe image of the
		* invoking data-engine. This form uses std::any to cast back and forth during polymorphism
		*
		* @return Returns the thread-safe image of the invoking data-engine
		*/
		[[nodiscard]] virtual std::atomic<std::any>* getThreadSafeImage() const = 0;

		/**
		* Internal type-erasure form of operator==, used to compare the invoking data-engine with another
		* for true equality, i.e. equal length and ordering of elements
		*
		* @param de Data engine to compare with
		* @return Returns true if equal, false otherwise
		*/
		virtual bool operator==(std::any de) const = 0;

		/**
		* Internal type-erasure form of equivalence method, used to compare the invoking data-engine with
		* another for equivalence, i.e. same elements but not necessarily in the same order
		* @param de Data engine to compare with
		* @return Returns true if equivalent, false otherwise
		*/
		[[nodiscard]] virtual bool equivalence(std::any de) const = 0;

		/**
		* Internal type-erasure form for merging data engines
		*
		* @param de Data Engine to be merged with
		* @return Returns the merged data engine
		*/
		virtual std::any merge(std::any de) = 0;

		/**
		* Internal type-erasure form for merging data engines
		*
		* @param de Data Engine to be merged with
		* @param start Starting index
		* @return Returns the merged data engine
		*/
		virtual std::any merge(std::any de, int start) = 0;

		/**
		* Internal type-erasure form for merging data engines
		*
		* @param de Data Engine to be merged with
		* @param start Starting index
		* @param end Endpoint index
		* @return Returns the merged data engine
		*/
		virtual std::any merge(std::any de, int start, int end) = 0;
	};
}