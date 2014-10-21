#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_hdr_fill_impl.h"
#include <cstdio>
#include <iostream>
#include <volk/volk.h>
#include <fstream>

namespace gr {
  namespace sandbox {

    		msg_hdr_fill::sptr msg_hdr_fill::make()
    		{return gnuradio::get_initial_sptr(new msg_hdr_fill_impl());}

		// constructor
    		msg_hdr_fill_impl::msg_hdr_fill_impl() : block("msg_hdr_fill",
                 	io_signature::make(0, 0, 0),
                 	io_signature::make(0, 0, 0))
    		{
      			d_in_port = pmt::mp("in");
      			d_out_port = pmt::mp("out");
      			message_port_register_in(d_in_port);
      			message_port_register_out(d_out_port);
        		set_msg_handler(d_in_port, boost::bind(&msg_hdr_fill_impl::print_pdu, this ,_1));
    		}

		// destructor
    		msg_hdr_fill_impl::~msg_hdr_fill_impl() {}

    		void msg_hdr_fill_impl::print_pdu(pmt::pmt_t pdu)
    		{
			pmt::pmt_t meta = pmt::car(pdu);
			pmt::pmt_t vector = pmt::cdr(pdu);

			size_t len = pmt::length(vector);
			//printf("length=%i\n",int(len));

			size_t hdr_len = 1;
			uint8_t hdr[1] = {'1'};
			printf("len=%i\n",int(len));

			size_t fill_max = 3;	// cannot fill beyond 6 bytes
			size_t fill_len = size_t(int(fill_max)-int(len));
			if(int(fill_len)<0) fill_len=0;
			uint8_t fill[6] = {'0','1','0','1','0','1'};
			
      			const uint8_t* bytes_in = pmt::u8vector_elements(vector, len);
      			uint8_t* bytes_out = (uint8_t*)volk_malloc((hdr_len+len+fill_len)*sizeof(uint8_t), volk_get_alignment());



			memcpy((void*)bytes_out, &hdr, hdr_len); 
      			memcpy((void*)(bytes_out+hdr_len), (const void*)bytes_in, len);
      			memcpy((void*)(bytes_out+hdr_len+len), &fill, fill_len);


      			pmt::pmt_t output = pmt::init_u8vector(hdr_len+len+fill_len, bytes_out);	// this copies the values from bytes_out into the u8vector
			pmt::pmt_t msg_pair = pmt::cons(meta, output); 					// construct a pdu (1 metadata pmt + 1 data pmt)
			message_port_pub(d_out_port, msg_pair);
			volk_free(bytes_out);
    		}
  	}
}

//memcpy((void*)bytes_out, (const void*)bytes_in, len);
//memcpy((void*)(bytes_out + len), &hdr, hdr_len); 

/*
// pull a key value
//pmt::pmt_t d_k = pmt::intern("packet_len");
pmt::pmt_t d_k = pmt::intern("pdu_id");
//pmt::pmt_t d_k = pmt::intern("pdu_len");
pmt::pmt_t d_v = pmt::dict_ref(meta,d_k,pmt::PMT_NIL);

printf("is_dict=%i\n",int(pmt::is_dict(meta)));			// is meta a dictionary?
printf("dict_has_key=%i\n",int(dict_has_key(meta,d_k)));	// does the dict. have key d_k?
printf("pdu_id="); int(pmt::print(d_v); printf("\n");		// print to stdout
*/

