#ifndef BENE_SINGLETON
#define BENE_SINGLETON
// Copyright (C) 2015 Joe Ruether jrruethe@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>

#ifdef BENE_BOOST_SINGLETON

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/once.hpp>
#include <boost/thread/tss.hpp>

namespace bene_detail {
template <typename T, template <typename U> class P>
class SingletonImpl;

template <typename T, template <typename U> class pointer_type>
class SingletonBase {
protected:
    static T& reference(boost::once_flag& flag)
    {
        boost::call_once(&SingletonBase::create, flag);
        return *pointer;
    }

    static void create(void)
    {
        pointer.reset(new T());
    }

    static boost::scoped_ptr<T> pointer;
};

template <typename T, template <typename U> class P>
boost::scoped_ptr<T> SingletonBase<T, P>::pointer;

template <typename T>
class SingletonImpl<T, boost::scoped_ptr>
    : public SingletonBase<T, boost::scoped_ptr> {
public:
    static T& instance(void)
    {
        return SingletonImpl::reference(*once_flag_ptr);
    }

protected:
    static boost::scoped_ptr<boost::once_flag> once_flag_ptr;
};

template <typename T>
boost::scoped_ptr<boost::once_flag>
    SingletonImpl<T, boost::scoped_ptr>::once_flag_ptr(new boost::once_flag());

template <typename T>
class SingletonImpl<T, boost::thread_specific_ptr>
    : public SingletonBase<T, boost::thread_specific_ptr> {
public:
    static T& instance(void)
    {
        if (!once_flag_ptr.get()) {
            once_flag_ptr.reset(new boost::once_flag());
        }

        return SingletonImpl::reference(*once_flag_ptr);
    }

protected:
    static boost::thread_specific_ptr<boost::once_flag> once_flag_ptr;
};

template <typename T>
boost::thread_specific_ptr<boost::once_flag>
    SingletonImpl<T, boost::thread_specific_ptr>::once_flag_ptr;
}

namespace bene {
template <typename T>
class Singleton : public bene_detail::SingletonImpl<T, boost::scoped_ptr> {
};

template <typename T>
class ThreadSingleton : public bene_detail::SingletonImpl<T, boost::thread_specific_ptr> {
};
}

#else

namespace bene {
template <typename T>
class Singleton {
public:
    static T& instance(void)
    {
        static T singleton;
        return singleton;
    }

private:
    Singleton(void);
};
}
#endif // BENE_SINGLETON_BOOST

#endif //BENE_SINGLETON