/* -*- c++ -*- */

#define SANDBOX_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "sandbox_swig_doc.i"

%{
#include "sandbox/msg_src.h"
#include "sandbox/msg_sink.h"
#include "sandbox/msg_hdr_tail.h"
#include "sandbox/msg_div.h"
#include "sandbox/msg_hdr_fill.h"
%}


%include "sandbox/msg_src.h"
GR_SWIG_BLOCK_MAGIC2(sandbox, msg_src);

%include "sandbox/msg_sink.h"
GR_SWIG_BLOCK_MAGIC2(sandbox, msg_sink);


%include "sandbox/msg_hdr_tail.h"
GR_SWIG_BLOCK_MAGIC2(sandbox, msg_hdr_tail);

%include "sandbox/msg_div.h"
GR_SWIG_BLOCK_MAGIC2(sandbox, msg_div);

%include "sandbox/msg_hdr_fill.h"
GR_SWIG_BLOCK_MAGIC2(sandbox, msg_hdr_fill);
