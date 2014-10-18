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
      			pmt::pmt_t d_in_port;
      			pmt::pmt_t d_out_port;
      			void print_pdu(pmt::pmt_t pdu);
      			gr::thread::mutex d_mutex;
      			std::vector<pmt::pmt_t> d_messages;

    			public:
      			msg_div_impl();
      			~msg_div_impl();

      			int num_messages();
      			pmt::pmt_t get_message(int i);
    };

  } // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_DIV_IMPL_H */

