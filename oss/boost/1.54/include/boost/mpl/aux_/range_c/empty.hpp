
#ifndef BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: empty.hpp 386076 2013-10-16 12:24:31Z heinzeti $
// $Date: 2013-10-16 14:24:31 +0200 (Mi, 16. Okt 2013) $
// $Revision: 386076 $

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct empty_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : equal_to<
              typename Range::start
            , typename Range::finish
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_EMPTY_HPP_INCLUDED