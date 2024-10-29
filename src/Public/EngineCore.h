#pragma once
#include<type_traits>

namespace core {
	/**
	* Custom conditional types implementation
	* @tparam flag Selector switch for types
	* @tparam Type_A Type Argument for type when flag is true
	* @tparam Type_B Type Argument for type when flag is false
	*/
	template<bool flag, typename Type_A, typename Type_B>
	struct conditional {
		using type = Type_A;
	};

	//Specialization for false
	template<typename Type_A, typename Type_B>
	struct conditional<false, Type_A, Type_B> {
		using type = Type_B;
	};

	//Alias
	template<bool Condition, typename Type_A, typename Type_B>
	using conditional_t = typename conditional<Condition, Type_A, Type_B>::type;

	/**
	* Custom "type enable if"
	* @tparam Condition Flag variable
	* @tparam Type The type to be used
	*/
	template<bool Condition, typename Type = void>
	struct enable_if {
		using type = void;
	};

	//Specialization
	template<typename Type>
	struct enable_if<true, Type> {
		using type = Type;
	};

	//Alias
	template<bool Condition, typename Type = void>
	using enable_t_if = typename enable_if<Condition, Type>::type;

	/**
	* Custom "is base of" implementation
	* @tparam Base The base class
	* @tparam Derived The derived class
	*/
	template<typename Base, typename Derived, typename = void>
	struct is_base_of {
		static constexpr bool value = false;
	};

	/*^
	* Specialization when it is true
	*/
	template<typename Base, typename Derived>
	struct is_base_of<Base, Derived, std::void_t<decltype(static_cast<Base*>(std::declval<Derived*>()))>> {
		static constexpr bool value = true;
	};

	/**
	* General template for a functional interface
	*/
#ifndef FUNTCIONAL_INTERFACE
#define FUNCTIONAL_INTERFACE(name, functionName, flag) \
		template<typename... Types> \
		class name { \
		public: \
			virtual ~name() = default; \
			\
			name(const name&) = delete; \
			name& operator=(const name&) = delete; \
			name(const name&&) noexcept = delete; \
			name& operator=(const name&&) noexcept = delete; \
			\
			virtual enable_t_if<flag, void> functionName(Types... args) = 0;\
			virtual enable_t_if<flag, void> functionName() = 0;\
		protected: \
			name() = default; \
		};\

#endif

	/**
	* General template for an interface
	*/
#ifndef S_INTERFACE
#define S_INTERFACE(name)\
		template<typename E>\
		class name{ \
		protected: \
			name() = default;\
		public: \
			virtual ~name() = default; \
			\
			name(const name&) = delete; \
			name& operator=(const name&) = delete; \
			name(const name&&) noexcept = delete; \
			name& operator=(const name&&) noexcept = delete; \
			\

#endif

#ifndef E_INTERFACE
#define E_INTERFACE \
		};\

#endif

	/**
	* Special Data Engine implementations are required to implement Sortable's sort method
	* The MACRO for the engine will automatically extend it
	*/
	FUNCTIONAL_INTERFACE(Sortable, sort, false)//Defines the sortable interface

		/**
		* All concrete implementations of DataEngine are required to have an Iterator. The Iterator
		* interface defines the basic layout of an Iterator
		*/
		S_INTERFACE(Iterator)

		E_INTERFACE

		/**
		* The Iterable interface defines the methods that create an Iterator in both directions. All
		* DataEngine classes have access to it and are required to override it
		*/
		S_INTERFACE(Iterable)
		/**
		* @return Returns an Iterator at the beginning of the engine
		*/
		virtual Iterator<E> begin() = 0;

	/**
	* @return Returns an Iterator at the end of the engine
	*/
	virtual Iterator<E> end() = 0;
	E_INTERFACE
}
