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

		//////////////////////////////////////////////
    		void msg_proc_impl::print_pdu(pmt::pmt_t pdu)
    		{
			pmt::pmt_t meta = pmt::car(pdu);
			pmt::pmt_t vector = pmt::cdr(pdu);

			size_t len = pmt::length(vector);
			size_t offset(0);
			const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(vector, offset);
			int extra = 0;
      			unsigned int crc = 0;
			char temp0[4] = {'0','0','0','0'};
			char temp1[5] = {'1','1','1','1','1'};
			if(len==12) {extra=4; crc=0x30303030;}
			else if(len==13) {extra=5; crc=0x31313131;}
			else {extra=0; crc=0;}

      			const uint8_t* bytes_in = pmt::u8vector_elements(vector, len);
      			uint8_t* bytes_out = (uint8_t*)volk_malloc(extra + len*sizeof(uint8_t), volk_get_alignment());

      			memcpy((void*)bytes_out, (const void*)bytes_in, len);

      			//memcpy((void*)(bytes_out + len), &crc, extra); 			// big-endian/little-endian, this might be wrong
			if(len==12) memcpy((void*)(bytes_out + len), &temp0, extra); 
			else if(len==13) memcpy((void*)(bytes_out + len), &temp1, extra);

			// inject a key/value
			pmt::pmt_t d_k1; pmt::pmt_t d_v1;
			pmt::pmt_t d_k2; pmt::pmt_t d_v2;
			d_k1 = pmt::intern("pdu_id"); d_v1 = pmt::intern("1"); 			// set d_k1 and d_v1
			d_k2 = pmt::intern("last_flg"); d_v2 = pmt::intern("0"); 		// set d_k2 and d_v2
      			meta = pmt::dict_add(meta, d_k1, d_v1);
      			meta = pmt::dict_add(meta, d_k2, d_v2);

      			pmt::pmt_t output = pmt::init_u8vector(len+extra, bytes_out); 		// this copies the values from bytes_out into the u8vector
			pmt::pmt_t msg_pair = pmt::cons(meta, output); 				//construct a pdu (1 metadata pmt + 1 data pmt)
			message_port_pub(d_out_port, msg_pair);
			volk_free(bytes_out);

    		}

    		int msg_proc_impl::num_messages()
    		{return (int)d_messages.size();}

    		pmt::pmt_t msg_proc_impl::get_message(int i)
    		{
   			gr::thread::scoped_lock guard(d_mutex);
      			if((size_t)i >= d_messages.size())
			{
        			throw std::runtime_error("msg_proc: index for message out of bounds.\n");
      			}
      			return d_messages[i];
    		}
  } /* namespace sandbox */
} /* namespace gr */

