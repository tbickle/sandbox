#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_proc_impl.h"
#include <cstdio>
#include <iostream>
#include <volk/volk.h>
#include <fstream>

namespace gr {
  namespace sandbox {

    		msg_proc::sptr msg_proc::make()
    		{return gnuradio::get_initial_sptr(new msg_proc_impl());}

		// constructor
    		msg_proc_impl::msg_proc_impl() : block("msg_proc",
                 	io_signature::make(0, 0, 0),
                 	io_signature::make(0, 0, 0))
    		{
      			d_in_port = pmt::mp("in");
      			d_out_port = pmt::mp("out");
      			message_port_register_in(d_in_port);
      			message_port_register_out(d_out_port);
        		set_msg_handler(d_in_port, boost::bind(&msg_proc_impl::print_pdu, this ,_1));
    		}

		// destructor
    		msg_proc_impl::~msg_proc_impl() {}

    		void msg_proc_impl::print_pdu(pmt::pmt_t pdu)
    		{
			pmt::pmt_t meta = pmt::car(pdu);
			pmt::pmt_t vector = pmt::cdr(pdu);

			size_t len = pmt::length(vector);
			//printf("length=%i\n",int(len));
			const int hdr = 5;			// add header
			char temp[5] = {'0','0','0','0','0'};	// add header

      			const uint8_t* bytes_in = pmt::u8vector_elements(vector, len);
      			uint8_t* bytes_out = (uint8_t*)volk_malloc(hdr + len*sizeof(uint8_t), volk_get_alignment());

      			//memcpy((void*)bytes_out, (const void*)bytes_in, len);
			//memcpy((void*)(bytes_out + len), &temp, hdr); 

			int pos;
			if(len>hdr) pos=int(len);		// determine position of insertion
			else pos=int(hdr);
			memcpy((void*)bytes_out, &temp, hdr); 
      			memcpy((void*)(bytes_out+pos), (const void*)bytes_in, len);

      			pmt::pmt_t output = pmt::init_u8vector(len+hdr, bytes_out); 		// this copies the values from bytes_out into the u8vector
			pmt::pmt_t msg_pair = pmt::cons(meta, output); 				//construct a pdu (1 metadata pmt + 1 data pmt)
			message_port_pub(d_out_port, msg_pair);
			volk_free(bytes_out);
    		}

  	} /* namespace sandbox */
} /* namespace gr */

