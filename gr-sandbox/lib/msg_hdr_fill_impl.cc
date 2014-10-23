#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_hdr_fill_impl.h"
#include <cstdio>
#include <iostream>
#include <volk/volk.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

namespace gr {
  namespace sandbox {

    		msg_hdr_fill::sptr msg_hdr_fill::make(int fill_max)
    		{return gnuradio::get_initial_sptr(new msg_hdr_fill_impl(fill_max));}

		// constructor
    		msg_hdr_fill_impl::msg_hdr_fill_impl(int fill_max) : block("msg_hdr_fill",
                 	io_signature::make(0, 0, 0),
                 	io_signature::make(0, 0, 0))
    		{
			d_fill_max=fill_max;
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

			/////// header ///////
			size_t hdr_len = 5;
			uint8_t hdr[5] = {0xFF,0xFF,0xFC,0x00,0x00};	// the 1st 22-bits i'm arbitrarily filling w/ 1's
			//uint8_t hdr[5] = {0x00,0x00,0x00,0x00,0x00};
			//printf("len=%i\n",int(len));
			if(int(len)>-1 && int(len)<1024) {
				if(int(len)<512) hdr[3]=char(len);
				else {hdr[2]=char(len>>8);hdr[3]=char(len);}
			}
			else printf("header error\n");

			// fetch frame sequence value
			int frm_seq = 0;
			pmt::pmt_t d_k = pmt::intern("pdu_id");
			pmt::pmt_t d_v = pmt::dict_ref(meta,d_k,pmt::PMT_NIL);
			if(pmt::is_dict(meta) && dict_has_key(meta,d_k))
			{
				//printf("is_dict=%i\n",int(pmt::is_dict(meta)));			// is meta a dictionary?
				//printf("dict_has_key=%i\n",int(dict_has_key(meta,d_k)));	// does the dict. have key d_k?
				//printf("pdu_id="); int(pmt::print(d_v)); printf("\n");		// print to stdout
				//printf("pdu_id="); pmt::print(d_v); printf("\n");		// print to stdout
				//printf("pdu_id=%i\n", int(pmt::to_double(d_v)));
				frm_seq = int(pmt::to_double(d_v));
			}
			else printf("pdu error\n");
			hdr[4] = char(frm_seq);
			//////////////////////

			/////// fill ////////
			int fill_max = d_fill_max;
			size_t fill_len = size_t(int(fill_max)-int(len));
			if(int(fill_len)<0) fill_len=fill_len*-1;
			if(int(fill_len)>6) {fill_len=0; printf("error: -1 < fill_size < 7\n");}
			uint8_t fill[6] = {'0','1','0','1','0','1'};	// alternating sequence that's max 6 bytes
			/////////////////////
			
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

//int test = 1024;
//if(int(test)>-1 && int(test)<1024) {
	//if(int(test)<512) hdr[3]=char(test);
	//else {hdr[2]=char(test>>8);hdr[3]=char(test);}
//}
//else printf("error\n");

/*
// pull a key value
//pmt::pmt_t d_k = pmt::intern("packet_len");
pmt::pmt_t d_k = pmt::intern("pdu_id");
//pmt::pmt_t d_k = pmt::intern("pdu_len");
pmt::pmt_t d_v = pmt::dict_ref(meta,d_k,pmt::PMT_NIL);

printf("is_dict=%i\n",int(pmt::is_dict(meta)));			// is meta a dictionary?
printf("dict_has_key=%i\n",int(dict_has_key(meta,d_k)));	// does the dict. have key d_k?
printf("pdu_id=%i\n", int(pmt::to_double(d_v)));
*/

