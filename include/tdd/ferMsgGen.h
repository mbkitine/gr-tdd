/* -*- c++ -*- */
/* 
 * Copyright 2019 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_TDD_FERMSGGEN_H
#define INCLUDED_TDD_FERMSGGEN_H

#include <tdd/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
  namespace tdd {

    /*!
     * \brief <+description of block+>
     * \ingroup tdd
     *
     */
    class TDD_API ferMsgGen : virtual public gr::tagged_stream_block
    {
     public:
      typedef boost::shared_ptr<ferMsgGen> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of tdd::ferMsgGen.
       *
       * To avoid accidental use of raw pointers, tdd::ferMsgGen's
       * constructor is in a private implementation
       * class. tdd::ferMsgGen::make is the public interface for
       * creating new instances.
       */
      static sptr make(int frame_size, std::string out_tag_key, std::string len_tag_key);
    };

  } // namespace tdd
} // namespace gr

#endif /* INCLUDED_TDD_FERMSGGEN_H */

