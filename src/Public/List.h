#pragma once
#include "EngineMacros.h"
#include "DataEngine.h"

namespace core {
	S_ABSTRACT_ENGINE_CLASS(List, Nature::UNDEFINED, Behavior::NONE, Ordering::UNSUPPORTED)

	virtual bool add(E item) = 0;
	virtual bool addAll(List<E>* list) = 0;
	virtual bool addAll(List<E>* list, int start) = 0;

	bool addAll(E items[]);
	bool addAll(E items[], int start);
	virtual bool addAll(E items[], int start, int end) = 0;

	virtual ~List() = default;

	//Removing copy semantics
	List(const List&) = delete;
	List& operator=(const List&) = delete;

	//Adding move semantics
	List(List&&) noexcept = default;
	List& operator=(List&&) noexcept = default;

protected:
	[[nodiscard]] double load() const;

	E_ENGINE_CLASS
}