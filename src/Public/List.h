#pragma once
#include "../Public/EngineMacros.h"

namespace core {
	S_ABSTRACT_ENGINE_CLASS(List, UNDEFINED, NONE, UNSUPPORTED)
		virtual bool add(E item) = 0;
		virtual bool addAll(List<E>* list) = 0;
		virtual bool addAll(List<E>* list, int start) = 0;

	E_ENGINE_CLASS
}