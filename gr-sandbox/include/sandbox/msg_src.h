/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_SANDBOX_MSG_SRC_H
#define INCLUDED_SANDBOX_MSG_SRC_H

#include <sandbox/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace sandbox {

    /*!
     * \brief <+description of block+>
     * \ingroup sandbox
     *
     */
    class SANDBOX_API msg_src : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<msg_src> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of sandbox::msg_src.
       *
       * To avoid accidental use of raw pointers, sandbox::msg_src's
       * constructor is in a private implementation
       * class. sandbox::msg_src::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace sandbox
} // namespace gr

#endif /* INCLUDED_SANDBOX_MSG_SRC_H */

