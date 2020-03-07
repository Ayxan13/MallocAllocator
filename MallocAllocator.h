/*
 * Written by Ayxan Haqverdili
 * March 7 2020
 *
 *
 * Simple allocator that uses malloc as it's memory source
 * 
 */

#pragma once // Won't hurt
#ifndef MALLOC_ALLOCATOR_H
#define MALLOC_ALLOCATOR_H

#include <cstdlib>   // malloc/free
#include <stdexcept> // bad_alloc

template<class T>
struct MallocAllocator
{
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type = T;

        MallocAllocator() noexcept = default;
        MallocAllocator(const MallocAllocator&) noexcept = default;
        template<class U>
        MallocAllocator(const MallocAllocator<U>&) noexcept
        {}
        ~MallocAllocator() noexcept = default;

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
};

#endif // !MALLOC_ALLOCATOR_H
