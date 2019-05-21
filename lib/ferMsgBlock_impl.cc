/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
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
#include "ferMsgBlock_impl.h"
#include <stdlib.h>

namespace gr {
  namespace tdd {

    ferMsgBlock::sptr
    ferMsgBlock::make(float numSamples)
    {
      return gnuradio::get_initial_sptr
        (new ferMsgBlock_impl(numSamples));
    }

    /*
     * The private constructor
     */
    ferMsgBlock_impl::ferMsgBlock_impl(float numSamples)
      : gr::sync_block("ferMsgBlock",
              gr::io_signature::make(1, 1, sizeof(uint8_t)),
              gr::io_signature::make(1, 1, sizeof(uint8_t))),
        d_numSamples(numSamples),d_index(0.0)
    {

    }

    /*
     * Our virtual destructor.
     */
    ferMsgBlock_impl::~ferMsgBlock_impl()
    {
        std::cout << "Number of samples : " << d_index << std::endl;
    }

    int
    ferMsgBlock_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      const uint8_t *in = (const uint8_t *) input_items[0];
      uint8_t *out = (uint8_t *) output_items[0];

      for(int i = 0; i < noutput_items; i++)
      {
          d_index += 1.0;
          out[i] = in[i];
          /*if (d_index < d_numSamples)
          {
              out[i] = in[i];
          }
          else{
              std::cout << "d_index : " << d_index << std::endl;
              std::cout << "d_numS  : " << d_numSamples << std::endl;
              //std::cout << "Number of frames processed : " << d_numSamples << std::endl;
              //abort();
          }*/
      }

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tdd */
} /* namespace gr */

