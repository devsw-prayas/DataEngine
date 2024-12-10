#include "../../Public/Abstraction/Deque.h"

namespace core
{
	template <typename E>
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool Deque<E>::containsAll(T* deque) {
		return containsAll(deque, 0, deque->getActiveSize());
	}

	template <typename E>
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool Deque<E>::containsAll(T* deque, int start) {
		return containsAll(deque, start, deque->getActiveSize());
	}

	template <typename E>
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] bool Deque<E>::containsAll(T* deque, int start, int end) {
		if (deque == nullptr) {
			return false;
		}
		if (start < 0 || end < 0 || start >= deque->getActiveSize() || end > deque->getActiveSize()) {
			return false;
		}
		if (start >= end) {
			return false;
		}
		return containsAllInternal(deque, start, end);
	}

	template<typename E>
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* Deque<E>::retainAll(T* deque) {
		if (deque == nullptr) {
			return nullptr;
		}
		return std::any_cast<T*>(retainAll(deque));
	}

	template <typename E>
	template <typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* Deque<E>::mergeFirst(T* deque) {
		if (deque == nullptr) {
			return nullptr;
		}
		return std::any_cast<T*>(mergeFirst(deque));
	}

	template<typename E>
	template<typename T> requires ValidBase<T, Deque<E>>
	[[nodiscard]] T* Deque<E>::mergeLast(T* deque) {
		if (deque == nullptr) {
			return nullptr;
		}
		return std::any_cast<T*>(mergeLast(deque));
	}

	template <typename E>
	void Deque<E>::replaceAll(std::function<E* (E*)> operatorFunction) {
		replaceAll(operatorFunction, 0, this->activeCapacity);
	}
}
