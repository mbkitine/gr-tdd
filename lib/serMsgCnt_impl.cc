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
#include "serMsgCnt_impl.h"

namespace gr {
  namespace tdd {

    serMsgCnt::sptr
    serMsgCnt::make(std::string sync, std::string cnt, int verbose)
    {
      return gnuradio::get_initial_sptr
        (new serMsgCnt_impl(sync, cnt, verbose));
    }

    /*
     * The private constructor
     */
    serMsgCnt_impl::serMsgCnt_impl(std::string sync, std::string cnt, int verbose)
      : gr::sync_block("serMsgCnt",
              gr::io_signature::make(1, 1, sizeof(unsigned char)),
              gr::io_signature::make(0, 0, 0)),
        d_msgCnt(0),d_synCnt(0),d_verbose(verbose > 0)
    {
        keyMsgCnt  = pmt::mp(cnt);
        keySyncCnt = pmt::mp(sync);
        set_output_multiple(8952);
    }

    /*
     * Our virtual destructor.
     */
    serMsgCnt_impl::~serMsgCnt_impl()
    {
    }

    int
    serMsgCnt_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const unsigned char *in = (const unsigned char *) input_items[0];
      //<+OTYPE+> *out = (<+OTYPE+> *) output_items[0];
      d_tags_cnt.clear();
      this->get_tags_in_window(d_tags_cnt, 0, 0, noutput_items,keyMsgCnt);
      //std::cout << "Size of frame  : " << noutput_items << std::endl;
      //std::cout << "Number of tags : " << d_tags_cnt.size() << std::endl;

      for(d_tags_cnt_itr = d_tags_cnt.begin(); d_tags_cnt_itr != d_tags_cnt.end(); d_tags_cnt_itr++) {
          //Ambiguity resolution
          d_msgCnt = (uint64_t)pmt::to_uint64(d_tags_cnt_itr->value);
          if(d_verbose)
          {
              std::cout << "Message count : " << d_msgCnt << std::endl;
          }

      }



      /*
      d_msgCnt = (int)pmt::to_double(keyMsgCnt.value);
      d_synCnt = (int)pmt::to_double(keySyncCnt.value);

      if(d_verbose)
      {
          std::cout << "Message count : " << d_msgCnt << std::endl;
          std::cout << "Sync value    : " << d_synCnt << std::endl;
      }*/

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tdd */
} /* namespace gr */

