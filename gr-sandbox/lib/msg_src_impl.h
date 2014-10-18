#ifndef INCLUDED_SANDBOX_MSG_SRC_IMPL_H
#define INCLUDED_SANDBOX_MSG_SRC_IMPL_H

#include <sandbox/msg_src.h>
#include <boost/crc.hpp>

namespace gr {
  namespace sandbox {

    class msg_src_impl : public msg_src
    {
     			private:
      			pmt::pmt_t d_in_port;
      			pmt::pmt_t d_out_port;
      			void calc(pmt::pmt_t msg);

     public:
      msg_src_impl();
      ~msg_src_impl();

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_SRC_IMPL_H */

