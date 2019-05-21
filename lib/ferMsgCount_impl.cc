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
#include "ferMsgCount_impl.h"
#include <stdlib.h>

namespace gr {
  namespace tdd {

    ferMsgCount::sptr
    ferMsgCount::make(int verbose,int framesync, int crc)
    {
      return gnuradio::get_initial_sptr
        (new ferMsgCount_impl(verbose,framesync,crc));
    }

    /*
     * The private constructor
     */
    ferMsgCount_impl::ferMsgCount_impl(int verbose, int framesync,int crc)
      : gr::sync_block("ferMsgCount",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0)),
        d_verbose(verbose >=1), d_framesync(framesync >=1 ),d_count(0),d_sent(0),d_crc(crc >=1)
    {
        //Registering message ports
        message_port_register_in(pmt::mp("in"));
        message_port_register_out(pmt::mp("out"));
        set_msg_handler(
                        pmt::mp("in"),
                        boost::bind(&ferMsgCount_impl::count, this, _1)
                        );
        switch (verbose)
        {
        case 1:
            d_phrase = "Frames received : ";
            break;
        case 2:
            d_phrase = "Frames sent : ";
            break;
        default:
            d_phrase = "Unknown";
        }
    }

    bool
    ferMsgCount_impl::crc_ccitt(unsigned char* frame, int frame_len)
    {

        unsigned short crc = frame[frame_len-1] << 8
                           | frame[frame_len-2];

        unsigned int POLY=0x8408; //reflected 0x1021
        unsigned short calc_crc=0xFFFF;
        for(size_t i=0; i<frame_len - 2; i++) {
            calc_crc ^= frame[i];
            for(size_t j=0; j<8; j++) {
                if(calc_crc&0x01) calc_crc = (calc_crc >> 1) ^ POLY;
                else         calc_crc = (calc_crc >> 1);
            }
        }
        calc_crc ^= 0xFFFF;

        return (calc_crc == crc);
    }

    /*
     * Our virtual destructor.
     */
    ferMsgCount_impl::~ferMsgCount_impl()
    {
        std::cout << "Total number of frames Received : " << d_count << std::endl;
    }

    void
    ferMsgCount_impl::count(pmt::pmt_t pmt_msg)
    {

        //Extracting message from pmt
        pmt::pmt_t msg = pmt::cdr(pmt_msg);
        size_t offset(0);
        unsigned char *msg_char = (unsigned char*)malloc(pmt::length(msg));
        std::vector<unsigned char> tc;
        memcpy(msg_char,pmt::uniform_vector_elements(msg, offset),pmt::length(msg));
        //tc.insert(tc.end(), msg_char, msg_char + pmt::length(msg));
        
        
        //Number of frames sent
        if(d_framesync)
        {
            memcpy(&d_sent,msg_char, 8);
            //std::cout << "Frame sync set" << std::endl;
        }else{
            d_sent++;
            //std::cout << "Frame sync NOT set" << std::endl;
        }



        //Number of frames received
        if(d_crc){
            if (crc_ccitt(msg_char,pmt::length(msg)))
            {
                d_count ++;

            }
        }else {d_count++;}

        std::cout.precision(4);
        if (d_verbose)
        {
            std::cout << " Frames sent  : "
                      << d_sent
                      << " Frames received  : "
                      << d_count
                      << " Frames lost  : "
                      << d_sent - d_count
                      << " FER  =  "
                      << std::scientific
                      << float((float(d_sent) - float(d_count))/float(d_sent))
                      << std::endl;
        }
        tc.insert(tc.end(), msg_char + 8, msg_char + pmt::length(msg) - 2);
        //Sending payload
        pmt::pmt_t pdu(pmt::cons(pmt::PMT_NIL,pmt::make_blob(tc.data(),tc.size())));
        message_port_pub(pmt::mp("out"), pdu);
        tc.clear();
        free(msg_char);
        return;
    }

    int
    ferMsgCount_impl::work(int noutput_items,
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

