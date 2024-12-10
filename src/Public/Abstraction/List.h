#pragma once
#include "../../Public/EngineMacros.h"
#include "../../Public/DataEngine.h"
#include <functional>
#include <any>

namespace core {

	/**
	* Superclass for all List implementations. This abstraction defines behavior to be supported
	* by almost all implementations of List. It is a generic class, implemented via the
	* DataEngine MACROS. All List implementations support move semantics and cloning. Copy constructors
	* are deliberately disabled to prevent shallow copying. It is recommended to provide an overload
	* for the polymorphic forms of clone in DataEngine itself when subclassing any of the superclasses
	*
	*/
	S_ABSTRACT_ENGINE_CLASS(List, Nature::UNDEFINED, Behavior::NONE, Ordering::UNSUPPORTED)

	/**
	* Adds the given item to the end of the list
	* @param item Item to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	virtual bool add(E item) = 0;

	/**
	* Adds the given item at the given index in the list
	* @param item Item to be added
	* @param index Index at which the item is to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	virtual bool add(E item, int index) = 0;

	/**
	* Adds the given list into the invoking list
	* @param list The list to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	bool addAll(T* list);

	/**
	* Adds all the elements of the given list lying beyond start position into
	* the invoking list
	* @param list The list to be added
	* @param start Starting index
	* @return Returns true if addition is successful, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	bool addAll(T* list, int start);

	/**
	* Adds all the elements of the given list lying between start position and end
	* position into the invoking list
	* @param list The list to be added
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if addition is successful, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	bool addAll(T* list, int start, int end);

	/**
	* Adds all the elements of the given array into the invoking list
	* @param items The array to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	bool addAll(E items[]);

	/**
	* Adds all the items of the given array lying beyond the start position into the invoking list
	* @param items The array to be added
	* @param start Starting index
	* @return Returns true if addition is successful, false otherwise
	*/
	bool addAll(E items[], int start);

	/**
	* Adds all the items of the given array lying between the start position and the end position
	* into the invoking list
	* @param items The array to be added
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if addition is successful, false otherwise
	*/
	virtual bool addAll(E items[], int start, int end) = 0;

	/**
	* Gets the item at the given index
	* @param index Index of the item to be fetched
	* @return Returns the item at the given index, else nullptr
	*/
	virtual E get(int index) = 0;

	/**
	* Gets the first index of the given item in the list
	* @param item The item to be searched
	* @return Returns the first index of the item, else -1
	*/
	virtual int getFirstIndex(E item) = 0;

	/**
	* Gets the last index of the given item in the list
	* @param item The item to be searched
	* @return Returns the last index of the item, else -1
	*/
	virtual int getLastIndex(E item) = 0;

	/**
	* Removes all occurrences of the given item from the list
	* @param item The item to be removed
	* @return Returns true if removal is successful, false otherwise
	*/
	virtual bool remove(E item) = 0;

	/**
	* Removes the item at the given index
	* @param index The index of the item to be removed
	* @return Returns true if removal is successful, false otherwise
	*/
	virtual bool removeAt(int index) = 0;

	/**
	* Sets the item at the given index
	* @param index The index of the item to be set
	* @param item The item to be set
	*/
	virtual void set(int index, E item) = 0;

	/**
	* Checks if the given item is present in the list
	* @param item The item to be checked
	* @return Returns true if the item is present, false otherwise
	*/
	[[nodiscard]]virtual bool contains(E item) = 0;

	/**
	* Checks if all the items of the given list are present in the invoking list
	* @param list The list to be checked
	* @return Returns true if all the items are present, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool containsAll(T* list);

	/**
	* Checks if all the items of the given list lying beyond the start position are
	* present in the invoking list
	* @param list The list to be checked
	* @param start Starting index
	* @return Returns true if all the items are present, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool containsAll(T* list, int start);

	/**
	* Checks if all the items of the given list lying between the start position and the end
	* are present in the invoking list
	* @param list The list to be checked
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if all the items are present, false otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool containsAll(T* list, int start, int end);

	/**
	* Removes all the items from the given list in the invoking list
	* @param list The list to be retained
	* @return Returns the retained list, nullptr otherwise
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* retainAll(T* list);

	/**
	* Creates a sublist of the invoking list lying beyond the start position 
	* @param start Starting index
	* @return Returns the sublist
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* subList(int start);

	/**
	* Creates a sublist of the invoking list lying between the start position
	* and the end position
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns the sublist
	*/
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* subList(int start, int end);

	/**
	* Replaces all the items in the invoking list with the given the modification applied
	* @param operatorFunction The function to be applied
	*/
	void replaceAll(std::function<E(E*)> operatorFunction);

	/**
	* Replaces all the items in the invoking list lying between the start position and the end
	* with the given the modification applied
	* @param operatorFunction The function to be applied
	* @param start Starting index
	* @param end Endpoint index
	*/
	virtual void replaceAll(std::function<E(E*)> operatorFunction, int start, int end) = 0;

	virtual ~List() = default;

	//Removing copy semantics
	List(const List&) = delete;
	List& operator=(const List&) = delete;

	//Adding move semantics
	List(List&&) noexcept = default;
	List& operator=(List&&) noexcept = default;

protected:
	/**
	* @return Returns the total load on the invoking list
	*/
	[[nodiscard]] double load() const;

	/**
	* Internal type-erasure form of containsAll, used to check if all the items of the given list
	* lying between the start position and the end are present in the invoking list
	* @param list The list to be checked
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if all the items are present, false otherwise
	*/
	[[nodiscard]] virtual bool containsAllInternal(std::any* list, int start, int end) = 0;

	/**
	* Internal type-erasure form of addAll, used to add all the elements of the given list lying between
	* the start position and the end position into the invoking list
	* @param list The list to be added
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if addition is successful, false otherwise
	*/
	[[nodiscard]] virtual bool addAllInternal(std::any* list, int start, int end) = 0;

	/**
	* Internal type-erasure form of retainAll, used to retain all the items of the given list in
	* invoking list
	* @param list The list to be retained
	* @return Returns the retained list, nullptr otherwise
	*/
	[[nodiscard]] virtual std::any* retainAll(std::any* list) = 0;

	/**
	* Internal type-erasure form of subList, used to create a sublist of the invoking list
	* lying between the start position and the end position
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns the sublist
	*/
	[[nodiscard]] virtual std::any* subList(int start, int end) = 0;

	E_ENGINE_CLASS
}