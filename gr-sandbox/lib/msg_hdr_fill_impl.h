#ifndef INCLUDED_SANDBOX_MSG_HDR_FILL_IMPL_H
#define INCLUDED_SANDBOX_MSG_HDR_FILL_IMPL_H

#include <sandbox/msg_hdr_fill.h>
#include <gnuradio/thread/thread.h>
#include <pmt/pmt.h>

namespace gr {
  	namespace sandbox {

    		class msg_hdr_fill_impl : public msg_hdr_fill
    		{
    			private:
			int d_fill_max;
      			pmt::pmt_t d_in_port;
      			pmt::pmt_t d_out_port;

    			public:
      			msg_hdr_fill_impl(int fill_max);
      			~msg_hdr_fill_impl();

      			void print_pdu(pmt::pmt_t pdu);
    		};

  	} // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_HDR_FILL_IMPL_H */

