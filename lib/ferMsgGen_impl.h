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

#ifndef INCLUDED_TDD_FERMSGGEN_IMPL_H
#define INCLUDED_TDD_FERMSGGEN_IMPL_H

#include <tdd/ferMsgGen.h>
#include <cstdlib>

namespace gr {
  namespace tdd {
    /*typedef struct
    {
       uint64_t msgCnt;
       unsigned char* data;
    } msgGen;*/

    class ferMsgGen_impl : public ferMsgGen
    {
     private:
      int d_frame_size;
      uint64_t d_msg_cnt;
      std::string d_out_tag_key;
      uint64_t d_tag_position;
      pmt::pmt_t d_me;
      
      //msgGen *msg;
     protected:
      int calculate_output_stream_length(const gr_vector_int &ninput_items);

     public:
      ferMsgGen_impl(int frame_size, std::string out_tag_key, std::string len_tag_key);
      ~ferMsgGen_impl();
      unsigned short crc_ccitt(unsigned char* frame, int frame_len);

      // Where all the action really happens
      int work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace tdd
} // namespace gr

#endif /* INCLUDED_TDD_FERMSGGEN_IMPL_H */

