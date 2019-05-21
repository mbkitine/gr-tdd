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
#include "nullMsgSink_impl.h"

namespace gr {
  namespace tdd {

    nullMsgSink::sptr
    nullMsgSink::make(int meta)
    {
      return gnuradio::get_initial_sptr
        (new nullMsgSink_impl(meta));
    }

    /*
     * The private constructor
     */
    nullMsgSink_impl::nullMsgSink_impl(int meta)
      : gr::sync_block("nullMsgSink",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        message_port_register_in(pmt::mp("in"));
        set_msg_handler(
                                pmt::mp("in"),
                                boost::bind(&nullMsgSink_impl::count, this, _1)
                                );
    }

    void
    nullMsgSink_impl::count(pmt::pmt_t pmt_msg)
    {
        //Do nothing
    }

    /*
     * Our virtual destructor.
     */
    nullMsgSink_impl::~nullMsgSink_impl()
    {
    }

    int
    nullMsgSink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      //const <+ITYPE+> *in = (const <+ITYPE+> *) input_items[0];
      //<+OTYPE+> *out = (<+OTYPE+> *) output_items[0];

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace tdd */
} /* namespace gr */

