#ifndef INCLUDED_SANDBOX_MSG_DIV_IMPL_H
#define INCLUDED_SANDBOX_MSG_DIV_IMPL_H

#include <sandbox/msg_div.h>
#include <gnuradio/thread/thread.h>
#include <pmt/pmt.h>

namespace gr {
	namespace sandbox {

    		class msg_div_impl : public msg_div
    		{
    			private:
			int d_div;
      			pmt::pmt_t d_in_port;
      			pmt::pmt_t d_out_port;

    			public:
      			msg_div_impl(int div);
      			~msg_div_impl();

      			void print_pdu(pmt::pmt_t pdu);

    		};
  	} // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_DIV_IMPL_H */

