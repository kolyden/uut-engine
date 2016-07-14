#pragma once
#include <cassert>
#include <cstddef>
#include <memory>

namespace uut
{
	template<class T>
	class SharedPtr
	{
	public:
		typedef std::shared_ptr<T> StdShared;

		constexpr SharedPtr() noexcept {}
		constexpr SharedPtr(nullptr_t) noexcept {}
		SharedPtr(T* ptr) : _data(ptr) {}
		SharedPtr(const StdShared& ptr) : _data(ptr) {}
		SharedPtr(StdShared&& ptr) : _data(ptr) {}

		template<typename U, class = typename std::enable_if<std::is_convertible<U*, T*>::value, void>::type>
		SharedPtr(const SharedPtr<U>& ptr) : _data(ptr.GetShared()) {}

		T* operator -> () const { return _data.get(); }
		operator T* () const { return _data.get(); }

// 		template<class U, class = typename std::enable_if<std::is_convertible<T, U>::value, void>::type>
// 		operator SharedPtr<U>() const { return std::static_pointer_cast<U>(_data); }

		T* Get() const { return _data.get(); }

		template<typename... Args>
		static SharedPtr<T> Make(Args&&... args)
		{
			return std::make_shared<T>(std::forward<Args>(args)...);
		}

		StdShared& GetShared() { return _data; }
		const StdShared& GetShared() const { return _data; }

	protected:
		StdShared _data;
	};

	//////////////////////////////////////////////////////////
	template<class T>
	class WeakPtr
	{
	public:
		typedef std::weak_ptr<T> StdShared;

		constexpr WeakPtr() noexcept {}
		constexpr WeakPtr(nullptr_t) noexcept {}
		WeakPtr(const SharedPtr<T>& ptr) : _data(ptr.GetShared()) {}
		WeakPtr(const std::shared_ptr<T>& ptr) : _data(ptr) {}

		SharedPtr<T> Lock() const { return _data.lock(); }

		bool Expired() const { return _data.expired(); }

	protected:
		StdShared _data;
	};

	//////////////////////////////////////////////////////////
// 	template<class T>
// 	class UniquePtr
// 	{
// 	public:
// 		typedef std::unique_ptr<T> StdShared;
// 
// 		UniquePtr() {}
// 		UniquePtr(nullptr_t) {}
// 		UniquePtr(T* ptr) : _data(ptr) {}
// 		UniquePtr(StdShared&& ptr) : _data(std::move(ptr)) {}
// 		UniquePtr(UniquePtr&& ptr) : _data(std::move(ptr._z)) {}
// 	protected:
// 		StdShared _data;
// 	};

	//////////////////////////////////////////////////////////
	/// Perform a static cast from one shared pointer type to another.
	template <class T, class U> SharedPtr<T> StaticCast(const SharedPtr<U>& ptr)
	{
		return std::static_pointer_cast<T>(ptr.GetShared());
	}

	/// Perform a dynamic cast from one weak pointer type to another.
	template <class T, class U> SharedPtr<T> DynamicCast(const SharedPtr<U>& ptr)
	{
		return std::dynamic_pointer_cast<T>(ptr.GetShared());
	}

// 	/// Perform a static cast from one weak pointer type to another.
// 	template <class T, class U> WeakPtr<T> StaticCast(const WeakPtr<U>& ptr)
// 	{
// 		return std::static_pointer_cast<T, U>(ptr.Lock().GetShared());
// 	}
// 
// 	/// Perform a dynamic cast from one weak pointer type to another.
// 	template <class T, class U> WeakPtr<T> DynamicCast(const WeakPtr<U>& ptr)
// 	{
// 		return std::dynamic_pointer_cast<T, U>(ptr.Lock().GetShared());
// 	}

	template<class T> using SPtr = SharedPtr<T>;
	template<class T> using WPtr = WeakPtr<T>;

	template<class T, typename... Args>
	static SharedPtr<T> MakeShared(Args... args)
	{
		return std::make_shared<T>(args...);
	}
}