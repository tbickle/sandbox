#ifndef INCLUDED_SANDBOX_MSG_SINK_IMPL_H
#define INCLUDED_SANDBOX_MSG_SINK_IMPL_H

#include <sandbox/msg_sink.h>
#include <gnuradio/thread/thread.h>
#include <pmt/pmt.h>

namespace gr {
  namespace sandbox {

    class msg_sink_impl : public msg_sink
    {
     private:
      void print_pdu(pmt::pmt_t pdu);
      gr::thread::mutex d_mutex;
      std::vector<pmt::pmt_t> d_messages;


     public:
      msg_sink_impl();
      ~msg_sink_impl();

      int num_messages();
      pmt::pmt_t get_message(int i);
    };

  } // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_SINK_IMPL_H */

