#pragma once
#include "DataEngine.h"
#include "EngineCore.h"

namespace core {
	/**
	* Indicates the intrinsic nature of a data engine
	*/
	enum Nature { MUTABLE, IMMUTABLE, THREAD_MUTABLE, UNDEFINED };

	/**
	* Indicates the intrinsic behavior of a data engine
	*/
	enum Behavior { FIXED_LENGTH, DYNAMIC, NONE };

	/**
	* Indicates the intrinsic ordering of the data engine
	*/
	enum Ordering { SORTED, UNSORTED, UNSUPPORTED };

	/**
	* Indicates the implementation style of the subclass.
	* An IMPLEMENTATION must satisfy certain conditions while being defined
	* An ABSTRACTION_E must be defined in such a manner that it has no intrinsic capabilities except for the fact
	* that it indicates what behavior must be achieved by the concrete IMPLEMENTATIONS
	*/
	enum Implementation { ABSTRACTION_E, IMPLEMENTATION_E };

	/**
	* Parameter guards for MACRO Parameters
	*/
	template<Implementation implementation, Nature nature, Behavior behavior, Ordering order>
	concept ValidConfiguration =
		(implementation == ABSTRACTION_E && nature == UNDEFINED && behavior == NONE && order == UNSUPPORTED) ||
		(implementation == IMPLEMENTATION_E && nature != UNDEFINED && behavior != NONE);

	template<typename Base, typename E>
	concept ValidBase = is_base_of < DataEngine<E>, Base >::value;

	class Dummy {};

#ifndef ENGINE_CONSTANTS
#define ENGINE_CONSTANTS(implementation, nature, behavior, ordering) \
		static constexpr Implementation engineImplementation = implementation; \
		static constexpr Nature engineNature = nature; \
		static constexpr Behavior engineBehavior = behavior;\
		static constexpr Ordering engineOrder = ordering; \

#endif

#ifndef S_ABSTRACT_ENGINE_CLASS
#define S_ABSTRACT_ENGINE_CLASS(name, nature, behavior, ordering) \
		template<typename E> \
		requires ValidConfiguration<ABSTRACTION_E, nature, behavior, ordering> \
		class name : public DataEngine<E>,\
				conditional_t<nature == THREAD_MUTABLE, Sortable<void>, Dummy> { \
			public: \
			ENGINE_CONSTANTS(ABSTRACTION_E, nature, behavior, ordering)

#endif

#ifndef S_IMPLEMENTAION_CLASS
#define S_IMPLEMENTATION_CLASS(name, Abstraction, nature, behavior, ordering) \
		template<typename E> \
		requires ValidConfiguration<IMPLEMENTATION_E, nature, behavior, ordering> && ValidBase<Abstraction, E>\
		class name : public Abstraction,\
				conditional_t<(nature == THREAD_MUTABLE), Sortable<void>, Dummy> { \
		public: \
			ENGINE_CONSTANTS(IMPLEMENTATION_E, nature, behavior, ordering)

#endif

#ifndef E_ENGINE_CLASS
#define E_ENGINE_CLASS \
		};
#endif
	}