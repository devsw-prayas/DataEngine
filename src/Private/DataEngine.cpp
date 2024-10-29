#include "../Public/DataEngine.h"

namespace core {
	template <typename E>
	size_t DataEngine<E>::getActiveSize() {
		return activeCapacity;
	}

	template <typename E>
	size_t DataEngine<E>::getMaxCapacity() {
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
}