#include "../../Public/Abstraction/List.h"

namespace core
{
	template<typename E>
	bool List<E>::addAll(E items[]) {
		return addAll(items, 0);
	}

	template<typename E>
	bool List<E>::addAll(E items[], int start) {
		return addAll(items, start, sizeof(items) / sizeof(E));
	}

	template<typename E>
	[[nodiscard]] double List<E>::load() const {
		return this->maxCapacity * 1.0 / this->activeCapacity;
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	bool List<E>::addAll(T* list) {
		return addAll(list, 0 , list->getActiveSize());
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	bool List<E>::addAll(T* list, int start) {
		return addAll(list, start, list->getActiveSize());
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	bool List<E>::addAll(T* list, int start, int end) {
		if (list == nullptr) {
			return false;
		}
		if (start < 0 || end < 0 || start >= list->getActiveSize() || end > list->getActiveSize()) {
			return false;
		}
		if (start >= end) {
			return false;
		}
		return this->addAllInternal(list, start, end);
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool List<E>::containsAll(T* list) {
		return containsAll(list, 0, list->getActiveSize());
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool List<E>::containsAll(T* list, int start) {
		return containsAll(list, start, list->getActiveSize());
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] bool List<E>::containsAll(T* list, int start, int end) {
		if (list == nullptr) {
			return false;
		}
		if (start < 0 || end < 0 || start >= list->getActiveSize() || end > list->getActiveSize()) {
			return false;
		}
		if (start >= end) {
			return false;
		}
		return containsAllInternal(list, start, end);
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* List<E>::retainAll(T* list) {
		if (list == nullptr) {
			return nullptr;
		}
		return retainAll(list, 0, list->getActiveSize());
	}

	template<typename E>
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* List<E>::subList(int start) {
		return subList(start, this->activeCapacity);
	}

	template<typename E >
	template<typename T> requires ValidBase<T, List<E>>
	[[nodiscard]] T* List<E>::subList(int start, int end) {
		if (start < 0 || end < 0 || start >= this->activeCapacity || end > this->activeCapacity) {
			return nullptr;
		}
		if (start >= end) {
			return nullptr;
		}
		return std::any_cast<T*>(subList(start, end));
	}

	template<typename E>
	void List<E>::replaceAll(std::function<E(E*)> operatorFunction) {
		replaceAll(operatorFunction, 0, this->activeCapacity);
	}
}