#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_src_impl.h"
#include <volk/volk.h>
#include <fstream>
#include <iostream>

namespace gr {
  	namespace sandbox {

    		msg_src::sptr msg_src::make()
    		{return gnuradio::get_initial_sptr(new msg_src_impl());}

    		msg_src_impl::msg_src_impl()
      			: gr::block("msg_src",
              		io_signature::make(0, 0, 0),
              		io_signature::make(0, 0, 0))
    		{
      			d_in_port = pmt::mp("in");
      			d_out_port = pmt::mp("out");
      			message_port_register_in(d_in_port);
      			message_port_register_out(d_out_port);
        		set_msg_handler(d_in_port, boost::bind(&msg_src_impl::calc, this ,_1) );
		}

    		msg_src_impl::~msg_src_impl() {}

    		void msg_src_impl::calc(pmt::pmt_t msg)
    		{
			////// importing a file //////
			//char name[7]={'i','n','.','d','a','t','\0'};
			//char name[12]={'i','n','_','n','o','l','f','.','d','a','t','\0'};
			//char name[9]={'t','r','i','g','.','d','a','t','\0'};
			char name[9]={'t','e','s','t','.','b','i','n','\0'};

			std::ifstream fl(&name[0]);
			fl.seekg(0, std::ios::end);
			size_t len1 = fl.tellg();
			char* ret = new char[len1];
			fl.seekg(0, std::ios::beg);
			fl.read(ret, len1);
			fl.close();
			// print file
			//char* temp; temp = ret;
			//printf("\nret=");
			//for(int i=0; i<len1; i++) {printf("%02X ",*ret); ret++;}
			//ret = temp;
			//printf("\nlen1=%i\n",int(len1));
			/////////////////////////////

      			// extract input pdu
      			pmt::pmt_t meta(pmt::car(msg));
      			pmt::pmt_t bytes(pmt::cdr(msg));

			int extra = 0;
      			uint8_t* bytes_out = (uint8_t*)volk_malloc(extra + len1*sizeof(uint8_t), volk_get_alignment());
      			memcpy((void*)bytes_out, (const void*)ret, len1);

      			pmt::pmt_t output = pmt::init_u8vector(len1+extra, bytes_out); // this copies the values from bytes_out into the u8vector
			pmt::pmt_t msg_pair = pmt::cons(meta, output);
			message_port_pub(d_out_port, msg_pair);
			volk_free(bytes_out);
		}

		int msg_src_impl::general_work(int noutput_items,
				gr_vector_int &ninput_items,
				gr_vector_const_void_star &input_items,
				gr_vector_void_star &output_items)
    		{return noutput_items;}

  	} /* namespace sandbox */
} /* namespace gr */

