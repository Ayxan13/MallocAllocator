/*
 * Written by Ayxan Haqverdili
 * March 7 2020
 *
 *
 * Simple allocator that uses malloc as it's memory source
 *
 */

#ifndef MALLOC_ALLOCATOR_H
#define MALLOC_ALLOCATOR_H
#pragma once // Won't hurt https://stackoverflow.com/a/1144110/10147399

#include <cstdlib>   // malloc/free
#include <stdexcept> // bad_alloc

template<class T>
struct MallocAllocator
{
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        MallocAllocator() noexcept = default;
        template<class U>
        MallocAllocator(const MallocAllocator<U>&) noexcept
        {}

        T* allocate(size_type const s, void const* = nullptr) const
        {
                if (s == 0)
                        return nullptr;

                T* temp = static_cast<T*>(std::malloc(s * sizeof(T)));

                if (!temp)
                        throw std::bad_alloc();

                return temp;
        }
        void deallocate(T* p, size_type) const noexcept { std::free(p); }

        template<class U>
        bool operator==(MallocAllocator<U> const&) noexcept
        {
                return true;
        }

        template<class U>
        bool operator!=(MallocAllocator<U> const&) noexcept
        {
                return false;
        }

        using propagate_on_container_move_assignment = std::true_type;
};

#endif // !MALLOC_ALLOCATOR_H
