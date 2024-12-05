#include "../Public/DataEngine.h"

namespace core {
	template <typename E>
	size_t DataEngine<E>::getActiveSize() const {
		return activeCapacity;
	}

	template <typename E>
	size_t DataEngine<E>::getMaxCapacity() const {
		return maxCapacity;
	}

	template <typename E>
	bool DataEngine<E>::isEmpty() const {
		return activeCapacity > 0;
	}

	template <typename E>
	bool DataEngine<E>::isMutable() const {
		return false; //TODO
	}

	template <typename E>
	bool DataEngine<E>::isThreadSafe() const {
		return false; //TODO
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	std::atomic<T>* DataEngine<E>::getThreadSafeImage() const {
		return std::any_cast<std::atomic<T>*>(getThreadSafeImage());
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	bool DataEngine<E>::operator==(T de) const {
		return std::any_cast<T>(operator==(de));
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	bool DataEngine<E>::equals(T de, int start, int end) const {
		return std::any_cast<T>(equals(de, start, end));
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	bool DataEngine<E>::equivalence(T de) const {
		return std::any_cast<T>(equivalence(de));
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	T DataEngine<E>::merge(T de) const {
		return std::any_cast<T>(merge(std::any(de)));
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	T DataEngine<E>::merge(T de, int start) const {
		return std::any_cast<T>(merge(std::any(de), start));
	}

	template<typename E>
	template<typename T> requires ValidBase<E, T>
	T DataEngine<E>::merge(T de, int start, int end) const {
		return std::any_cast<T>(merge(std::any(de), start, end));
	}
}