#pragma once
#include "DataEngine.h"

namespace core {
	/**
	* Indicates the intrinsic nature of a data engine
	*/
	enum class Nature { MUTABLE, IMMUTABLE, THREAD_MUTABLE, UNDEFINED };

	/**
	* Indicates the intrinsic behavior of a data engine
	*/
	enum class Behavior { FIXED_LENGTH, DYNAMIC, NONE };

	/**
	* Indicates the intrinsic ordering of the data engine
	*/
	enum class Ordering { SORTED, UNSORTED, UNSUPPORTED };

	/**
	* Indicates the implementation style of the subclass.
	* An IMPLEMENTATION must satisfy certain conditions while being defined
	* An ABSTRACTION_E must be defined in such a manner that it has no intrinsic capabilities except for the fact
	* that it indicates what behavior must be achieved by the concrete IMPLEMENTATIONS
	*/

	enum class Implementation { ABSTRACTION_E, IMPLEMENTATION_E };

	/**
	* Parameter guards for MACRO Parameters
	*/
	static constexpr bool Valid(Implementation implementation,
		Nature nature, Behavior behavior, Ordering order) {
		return (implementation == Implementation::ABSTRACTION_E && nature == Nature::UNDEFINED &&
			behavior == Behavior::NONE && order == Ordering::UNSUPPORTED) ||
			(implementation == Implementation::IMPLEMENTATION_E &&
				nature != Nature::UNDEFINED && behavior != Behavior::NONE);
	}

	template<Implementation implementation, Nature nature, Behavior behavior, Ordering order>
	concept ValidConfig = (implementation == Implementation::ABSTRACTION_E && nature == Nature::UNDEFINED &&
		behavior == Behavior::NONE && order == Ordering::UNSUPPORTED) ||
		(implementation == Implementation::IMPLEMENTATION_E &&
			nature != Nature::UNDEFINED && behavior != Behavior::NONE);

#ifndef ENGINE_CONSTANTS
#define ENGINE_CONSTANTS(implementation, nature, behavior, ordering) \
		static constexpr Implementation engineImplementation = implementation; \
		static constexpr Nature engineNature = nature; \
		static constexpr Behavior engineBehavior = behavior;\
		static constexpr Ordering engineOrder = ordering; \

#endif

#ifndef S_ABSTRACT_ENGINE_CLASS
#define S_ABSTRACT_ENGINE_CLASS(name, nature, behavior, ordering) \
		template<typename E>\
		class name : public DataEngine<E>,\
				conditional_t<nature == Nature::THREAD_MUTABLE, Sortable<E>, Dummy> { \
			static_assert(Valid(Implementation::ABSTRACTION_E, nature, behavior, ordering), \
				"Invalid configuration for abstraction class");\
			public: \
			ENGINE_CONSTANTS(Implementation::ABSTRACTION_E, nature, behavior, ordering)

#endif

#ifndef S_IMPLEMENTAION_CLASS
#define S_IMPLEMENTATION_CLASS(name, Abstraction, nature, behavior, ordering) \
		template<typename E>\
		class name : public Abstraction,\
		conditional_t<(nature == Nature::THREAD_MUTABLE), Sortable<E>, Dummy> { \
			static_assert(Valid(Implementation::IMPLEMENTATION_E, nature, behavior, ordering), \
					"Invalid configuration for implementation class");\
		public: \
			ENGINE_CONSTANTS(Implementation::IMPLEMENTATION_E, nature, behavior, ordering)

#endif

#ifndef E_ENGINE_CLASS
#define E_ENGINE_CLASS \
		};
#endif
	}