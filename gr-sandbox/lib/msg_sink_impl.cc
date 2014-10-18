#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "msg_sink_impl.h"
#include <cstdio>
#include <iostream>

namespace gr {
  namespace sandbox {

    msg_sink::sptr
    msg_sink::make()
    {
      return gnuradio::get_initial_sptr
        (new msg_sink_impl());
    }

    /*
     * The private constructor
     */
    msg_sink_impl::msg_sink_impl()
      : gr::block("msg_sink",
                 	io_signature::make(0, 0, 0),
                 	io_signature::make(0, 0, 0))
    		{
      			message_port_register_in(pmt::mp("print_pdu"));
      			set_msg_handler(pmt::mp("print_pdu"), boost::bind(&msg_sink_impl::print_pdu, this, _1));
    		}


    /*
     * Our virtual destructor.
     */
    msg_sink_impl::~msg_sink_impl()
    {
    }

    		void msg_sink_impl::print_pdu(pmt::pmt_t pdu)
    		{
			pmt::pmt_t meta = pmt::car(pdu);
			pmt::pmt_t vector = pmt::cdr(pdu);
			pmt::print(meta);

			size_t len = pmt::length(vector);
			std::cout << "length = " << len << std::endl;
			std::cout << "data = "; //<< std::endl;
			size_t offset(0);
			const uint8_t* d = (const uint8_t*) pmt::uniform_vector_elements(vector, offset);
			for(size_t i=0; i<len; i+=16)
			{
				//printf("%04x: ", ((unsigned int)i));
				for(size_t j=i; j<std::min(i+16,len); j++) printf("%02x ",d[j] );
				std::cout << std::endl;
      			}
    		}

    		int msg_sink_impl::num_messages()
    		{return (int)d_messages.size();}

    		pmt::pmt_t msg_sink_impl::get_message(int i)
    		{
   			gr::thread::scoped_lock guard(d_mutex);
      			if((size_t)i >= d_messages.size())
			{
        			throw std::runtime_error("msg_sink: index for message out of bounds.\n");
      			}
      			return d_messages[i];
    		}
  } /* namespace sandbox */
} /* namespace gr */

