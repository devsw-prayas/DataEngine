#pragma once
#include "../../Public/DataEngine.h"
#include "../../Public/EngineCore.h"
#include "../../Public/EngineMacros.h"
#include <functional>

namespace core {
	/**
	* Superclass for all Deque implementations. This abstraction defines behavior to be supported
	* by all implementations of Deque. A deque is defined as a double ended queue, which allows
	* item addition and removal from both the head and the tail. It is a generic class, implemented
	* through the DataEngine MACROS. All Deque implementations support move semantics. Cloning
	* through copy constructors is disabled due to shallow copying. Instead, deep copying is
	* enabled via polymorphic methods provided.
	*/
	S_ABSTRACT_ENGINE_CLASS(Deque, Nature::UNDEFINED, Behavior::NONE, Ordering::UNSUPPORTED)
	/**
	* Adds the item to the head of the deque
	* @param item The item to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	virtual bool addFirst(E item) = 0;

	/**
	* Adds the item to the tail of the deque
	* @param item The item to be added
	* @return Returns true if addition is successful, false otherwise
	*/
	virtual bool addLast(E item) = 0;

	/**
	* Removes the first item from the deque
	* @return Returns the removed item
	*/
	[[nodiscard]] virtual E removeFirst() = 0;

	/**
	* Removes the last item from the deque 
	* @return Returns the removed item
	*/
	[[nodiscard]] virtual E removeLast() = 0;

	/**
	* Gets the first item from the deque
	* @return Returns the first item
	*/
	[[nodiscard]] virtual E peekFirst() = 0;

	/**
	* Gets the last item from the deque
	* @return Returns the last item
	*/
	[[nodiscard]] virtual E peekLast() = 0;

	/**
	* Checks if the invoking deque contains the given item
	* @param item The item to be checked
	* @return Returns true if the item is present, false otherwise
	*/
	[[nodiscard]] virtual bool contains(E item) = 0;

	/**
	* Checks if the invoking deque contains all the items of the given deque
	* @param deque The deque to be checked
	* @return Returns true if all the items are present, false otherwise
	*/
	template <typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool containsAll(T* deque);

	/**
	* Checks if the invoking deque contains all the items of the given deque lying
	* beyond the start position
	* @param deque The deque to be checked
	* @param start Starting index
	* @return Returns true if all the items are present, false otherwise
	*/
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool containsAll(T* deque, int start);

	/**
	* Checks if the invoking deque contains all the items of the given deque lying
	* between the start and the end position
	* @param deque The deque to be checked
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if all the items are present, false otherwise
	*/
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool containsAll(T* deque, int start, int end);

	/**
	* Retains all the items of the invoking deque that are present in the given deque
	* @param deque The deque to be retained
	* @return Returns the retained deque, nullptr otherwise
	*/
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* retainAll(T* deque);

	/**
	* Merges the given deque at the head of the invoking deque
	* @param deque The deque to be merged
	* @return Returns the merged deque, nullptr otherwise
	*/
	template <typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* mergeFirst(T* deque);

	/**
	* Merge the given deque at the tail of the invoking deque
	* @param deque The deque to be merged
	* @return Returns the merged deque, nullptr otherwise
	*/
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* mergeLast(T* deque);

	/**
	* Replace all the items in the invoking deque with the given the modification applied
	* @param operatorFunction The function to be applied
	*/
	void replaceAll(std::function<E* (E*)> operatorFunction);

	/**
	* Replace all the items in the invoking deque lying between start position and end
	* with the given the modification applied
	* @param operatorFunction The function to be applied
	* @param start Starting index
	* @param end Endpoint index
	*/
	virtual void replaceALl(std::function<E* (E*)> operatorFunction, int start, int end) = 0;
protected:

	/**
	* Internal type-erasure form of containsAll, checks if the invoking deque contains all the items present
	* in the given deque lying between the start and the end position
	* @param deque The deque to be checked
	* @param start Starting index
	* @param end Endpoint index
	* @return Returns true if all the items are present, false otherwise
	*/
	[[nodiscard]] virtual bool containsAllInternal(std::any* deque, int start, int end) = 0;

	/**
	* Internal type-erasure form of retainAll, retains all the items of the invoking deque that are present
	* in the given deque
	* @param deque The deque to be retained
	* @return Returns the retained deque, nullptr otherwise
	*/
	[[nodiscard]] virtual std::any* retainAll(std::any* deque) = 0;

	/**
	* Internal type-erasure form of mergeFirst, merges the given deque at the head of the invoking deque
	* @param deque The deque to be merged
	* @return Returns the merged deque, nullptr otherwise
	*/
	[[nodiscard]] virtual std::any* mergeFirst(std::any* deque) = 0;

	/**
	* Internal type-erasure form of mergeLast, merges the given deque at the tail of the invoking deque
	* @param deque The deque to be merged
	* @return Returns the merged deque, nullptr otherwise
	*/
	[[nodiscard]] virtual std::any* mergeLast(std::any* deque) = 0;
	E_ENGINE_CLASS
}