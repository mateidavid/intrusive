/**
 *   Copyright 2011 Travis Gockel
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  Modified by Matei David; Feb 2014:
 *  - changed return types to prevent failure if sizeof(char)==sizeof(long)
 */

#ifndef __HAS_MEMBER_HPP
#define __HAS_MEMBER_HPP

#include <type_traits>


namespace boost {
namespace intrusive {
namespace detail {
    
template <typename T, typename NameGetter>
struct has_member_impl
{
    struct false_t { char _v[1]; };
    struct true_t { char _v[2]; };
    template <typename C> static true_t f(typename NameGetter::template get<C>*);
    template <typename C> static false_t f(...);
    static const bool value = (sizeof(f<T>(0)) == sizeof(true_t));
};

template <typename T, typename NameGetter>
struct has_member
  : std::integral_constant< bool, has_member_impl< T, NameGetter >::value >
{};

}
}
}

#endif
