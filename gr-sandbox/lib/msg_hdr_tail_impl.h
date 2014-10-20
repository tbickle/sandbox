#ifndef INCLUDED_SANDBOX_MSG_HDR_TAIL_IMPL_H
#define INCLUDED_SANDBOX_MSG_HDR_TAIL_IMPL_H

#include <sandbox/msg_hdr_tail.h>
#include <gnuradio/thread/thread.h>
#include <pmt/pmt.h>

namespace gr {
  namespace sandbox {

    class msg_hdr_tail_impl : public msg_hdr_tail
    {
    			private:
      			pmt::pmt_t d_in_port;
      			pmt::pmt_t d_out_port;
      			void print_pdu(pmt::pmt_t pdu);
      			gr::thread::mutex d_mutex;
      			//std::vector<pmt::pmt_t> d_messages;

    			public:
      			msg_hdr_tail_impl();
      			~msg_hdr_tail_impl();

      			//int num_messages();
      			//pmt::pmt_t get_message(int i);
    };

  } // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_HDR_TAIL_IMPL_H */

