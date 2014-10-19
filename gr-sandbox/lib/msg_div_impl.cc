#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_div_impl.h"
#include <cstdio>
#include <iostream>
#include <volk/volk.h>
#include <fstream>

namespace gr {
	namespace sandbox {

    		msg_div::sptr msg_div::make()
    		{return gnuradio::get_initial_sptr(new msg_div_impl());}

		// constructor
    		msg_div_impl::msg_div_impl() : block("msg_div",
                 	io_signature::make(0, 0, 0),
                 	io_signature::make(0, 0, 0))
    		{
      			d_in_port = pmt::mp("in");
      			d_out_port = pmt::mp("out");
      			message_port_register_in(d_in_port);
      			message_port_register_out(d_out_port);
        		set_msg_handler(d_in_port, boost::bind(&msg_div_impl::print_pdu, this ,_1));
    		}

		// destructor
    		msg_div_impl::~msg_div_impl() {}

    		void msg_div_impl::print_pdu(pmt::pmt_t pdu)
    		{
			pmt::pmt_t meta = pmt::car(pdu);
			pmt::pmt_t vector = pmt::cdr(pdu);

			/////// size determination //////
			size_t len = pmt::length(vector);
			size_t offset(0);
			int reg_len = 3; 	// <--- USER DEFINED (size of division)
			int last_len = int(len) % reg_len;
			//printf("last len=%i\n",last_len);
			offset = size_t(reg_len);
			int nchunks;
			if(last_len==0) nchunks=int(len)/reg_len;
			else nchunks=int(len)/reg_len+last_len/last_len;
			//printf("# of chuncks=%i\n",nchunks);
			/////////////////////////////////

      			const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(vector, offset);
			size_t a = size_t(reg_len);
			size_t b = size_t(last_len);
			const uint8_t* bytes_in;
			uint8_t* bytes_out;
			pmt::pmt_t output;
			pmt::pmt_t tvec;
			pmt::pmt_t d_k1; pmt::pmt_t d_v1;
			pmt::pmt_t d_k2; pmt::pmt_t d_v2;
			bool last = 0;

			// break up incoming vector
			for(size_t ii=0; ii<nchunks; ii++) 
			{
				// not last chunk
				if(int(ii)<(nchunks-1)) { 	// not last chunk
					tvec = pmt::init_u8vector(a,&d[ii*a]);
					bytes_in = pmt::u8vector_elements(tvec, a);
					bytes_out = (uint8_t*)volk_malloc(0 + a*sizeof(uint8_t), volk_get_alignment());
					memcpy((void*)bytes_out, (const void*)bytes_in, a);
					output = pmt::init_u8vector(a+0, bytes_out); 			// this copies the values from bytes_out into the u8vector
					last = 0;
				}
				// last chunk
				else if(last_len==0) {
					tvec = pmt::init_u8vector(a,&d[ii*a]);
					bytes_in = pmt::u8vector_elements(tvec, a);
					bytes_out = (uint8_t*)volk_malloc(0 + a*sizeof(uint8_t), volk_get_alignment());
					memcpy((void*)bytes_out, (const void*)bytes_in, a);
					output = pmt::init_u8vector(a+0, bytes_out); 			// this copies the values from bytes_out into the u8vector
					last = 1;
				}
				else
				{
					tvec = pmt::init_u8vector(b,&d[ii*a]);
					bytes_in = pmt::u8vector_elements(tvec, b);
					bytes_out = (uint8_t*)volk_malloc(0 + b*sizeof(uint8_t), volk_get_alignment());
					memcpy((void*)bytes_out, (const void*)bytes_in, b);
					output = pmt::init_u8vector(b+0, bytes_out); 			// this copies the values from bytes_out into the u8vector
					last = 1;
				}

				////////// inject a key/value ////////
				d_k1 = pmt::intern("pdu_id"); d_v1=pmt::from_double(double(ii));	// set d_k1 and d_v1
				d_k2 = pmt::intern("last_flg"); d_v2=pmt::from_bool(last); 		// set d_k2 and d_v2
				meta = pmt::dict_add(meta, d_k1, d_v1);
				meta = pmt::dict_add(meta, d_k2, d_v2);
				//////////////////////////////////////

				// construct pdu
				pmt::pmt_t msg_pair = pmt::cons(meta, output);
				message_port_pub(d_out_port, msg_pair);
				volk_free(bytes_out);
			}
    		}

  	} /* namespace sandbox */
} /* namespace gr */

