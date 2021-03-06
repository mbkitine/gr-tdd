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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ferMsgGen_impl.h"
//#include <crc/ccitt.h>
namespace gr {
  namespace tdd {

    ferMsgGen::sptr
    ferMsgGen::make(int frame_size, std::string out_tag_key, std::string len_tag_key)
    {
      return gnuradio::get_initial_sptr
        (new ferMsgGen_impl(frame_size, out_tag_key, len_tag_key));
    }

    /*
     * The private constructor
     */
    ferMsgGen_impl::ferMsgGen_impl(int frame_size, std::string out_tag_key, std::string len_tag_key)
      : gr::tagged_stream_block("ferMsgGen",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)), len_tag_key),
        d_frame_size(frame_size),d_msg_cnt(0),d_out_tag_key(out_tag_key),d_tag_position(0)
    {
       // msg = new msgGen();
        //msg->data   = (unsigned char*)malloc(d_frame_size*sizeof(unsigned char));
    }
    /*
     * Our virtual destructor.
     */
    ferMsgGen_impl::~ferMsgGen_impl()
    {
    }

    unsigned short
    ferMsgGen_impl::crc_ccitt(unsigned char* frame, int frame_len)
    {
        //Calculating CRC
        unsigned int POLY=0x8408; //reflected 0x1021
        unsigned short crc=0xFFFF;
        for(size_t i=0; i<frame_len; i++) {
            crc ^= frame[i];
            for(size_t j=0; j<8; j++) {
                if(crc&0x01) crc = (crc >> 1) ^ POLY;
                else         crc = (crc >> 1);
            }
        }
        crc ^= 0xFFFF;
        return crc;
    }
    int
    ferMsgGen_impl::calculate_output_stream_length(const gr_vector_int &ninput_items)
    {
      int noutput_items = d_frame_size + sizeof(uint64_t) + 2;
      return noutput_items ;
    }

    int
    ferMsgGen_impl::work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      unsigned char *out = (unsigned char *) output_items[0];
      d_msg_cnt +=1;
      //std::cout << "d_msg_cnt : " << d_msg_cnt << std::endl;
      int total_len;
      //msg->msgCnt = d_msg_cnt;
      //memcpy(msg->data,in,d_frame_size);

      //Copyping data to the output circular buffer
      memcpy(out + 0 ,&d_msg_cnt,8);
      memcpy(out + 8 ,in, d_frame_size);
      //calculating CRC
      
      unsigned short crc = crc_ccitt(out,d_frame_size + 8);
      memcpy(out + d_frame_size + 8, &crc, 2);
      total_len = d_frame_size + 8 + 2;
      // Do <+signal processing+>

      //Add output tag
      add_item_tag(0, d_tag_position,pmt::string_to_symbol(d_out_tag_key), pmt::from_long(total_len));
      add_item_tag(0, d_tag_position,pmt::string_to_symbol("msgCnt"), pmt::from_uint64(d_msg_cnt));
      d_tag_position += total_len;


      // Tell runtime system how many output items we produced.
      return total_len;
    }

  } /* namespace tdd */
} /* namespace gr */

