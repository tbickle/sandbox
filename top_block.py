#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Wed Oct 22 18:35:22 2014
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from gnuradio.wxgui import termsink
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import bch
import sandbox
import wx

class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 32000

        ##################################################
        # Message Queues
        ##################################################
        blocks_message_sink_1_msgq_out = wxgui_termsink_1_msgq_in = gr.msg_queue(2)

        ##################################################
        # Blocks
        ##################################################
        self.wxgui_termsink_1 = termsink.termsink(
        	parent=self.GetWin(),
        	msgq=wxgui_termsink_1_msgq_in,
        )
        self.Add(self.wxgui_termsink_1)
        self.sandbox_msg_src_0 = sandbox.msg_src()
        self.sandbox_msg_hdr_fill_0 = sandbox.msg_hdr_fill(6)
        self.sandbox_msg_div_0 = sandbox.msg_div(1017)
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(8)
        self.blocks_uchar_to_float_0 = blocks.uchar_to_float()
        self.blocks_throttle_1 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.byte_t, "packet_len")
        self.blocks_tag_gate_6 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_5 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_4 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_3 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_2 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_1 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_tag_gate_0 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_stream_to_tagged_stream_1 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, 7, "packet_len")
        self.blocks_stream_to_tagged_stream_0 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, 1, "packet_len")
        self.blocks_stream_mux_0 = blocks.stream_mux(gr.sizeof_char*1, (1, 1, 1, 1, 1, 1, 1))
        self.blocks_pdu_to_tagged_stream_1 = blocks.pdu_to_tagged_stream(blocks.byte_t, "packet_len")
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_char*1)
        self.blocks_message_sink_1 = blocks.message_sink(gr.sizeof_char*1, blocks_message_sink_1_msgq_out, False)
        self.blocks_message_debug_1 = blocks.message_debug()
        self.blocks_message_debug_0 = blocks.message_debug()
        self.blocks_float_to_uchar_0 = blocks.float_to_uchar()
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/home/matthew/sandbox/trig.dat", False)
        self.blocks_add_const_vxx_0 = blocks.add_const_vff((48, ))
        self.bch_syn_gen_6356_6 = bch.syn_gen_6356(6)
        self.bch_syn_gen_6356_5 = bch.syn_gen_6356(5)
        self.bch_syn_gen_6356_4 = bch.syn_gen_6356(4)
        self.bch_syn_gen_6356_3 = bch.syn_gen_6356(3)
        self.bch_syn_gen_6356_2 = bch.syn_gen_6356(2)
        self.bch_syn_gen_6356_1 = bch.syn_gen_6356(1)
        self.bch_syn_gen_6356_0 = bch.syn_gen_6356(0)
        self.bch_mask_0 = bch.mask()

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_stream_mux_0, 0), (self.blocks_stream_to_tagged_stream_1, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_stream_to_tagged_stream_0, 0))
        self.connect((self.blocks_stream_to_tagged_stream_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))
        self.connect((self.blocks_file_source_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_tag_gate_0, 0), (self.bch_syn_gen_6356_0, 0))
        self.connect((self.blocks_tag_gate_1, 0), (self.bch_syn_gen_6356_1, 0))
        self.connect((self.blocks_tag_gate_2, 0), (self.bch_syn_gen_6356_2, 0))
        self.connect((self.blocks_tag_gate_3, 0), (self.bch_syn_gen_6356_3, 0))
        self.connect((self.blocks_tag_gate_4, 0), (self.bch_syn_gen_6356_4, 0))
        self.connect((self.blocks_tag_gate_5, 0), (self.bch_syn_gen_6356_5, 0))
        self.connect((self.blocks_tag_gate_6, 0), (self.bch_syn_gen_6356_6, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_0, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_1, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_2, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_3, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_4, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_5, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_tag_gate_6, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.bch_mask_0, 0))
        self.connect((self.blocks_throttle_1, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        self.connect((self.bch_syn_gen_6356_0, 0), (self.blocks_stream_mux_0, 0))
        self.connect((self.bch_syn_gen_6356_1, 0), (self.blocks_stream_mux_0, 1))
        self.connect((self.bch_syn_gen_6356_2, 0), (self.blocks_stream_mux_0, 2))
        self.connect((self.bch_syn_gen_6356_3, 0), (self.blocks_stream_mux_0, 3))
        self.connect((self.bch_syn_gen_6356_4, 0), (self.blocks_stream_mux_0, 4))
        self.connect((self.bch_syn_gen_6356_5, 0), (self.blocks_stream_mux_0, 5))
        self.connect((self.bch_syn_gen_6356_6, 0), (self.blocks_stream_mux_0, 6))
        self.connect((self.blocks_pdu_to_tagged_stream_1, 0), (self.blocks_throttle_1, 0))
        self.connect((self.blocks_stream_to_tagged_stream_1, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.blocks_float_to_uchar_0, 0), (self.blocks_message_sink_1, 0))
        self.connect((self.blocks_uchar_to_float_0, 0), (self.blocks_add_const_vxx_0, 0))
        self.connect((self.blocks_add_const_vxx_0, 0), (self.blocks_float_to_uchar_0, 0))
        self.connect((self.bch_mask_0, 0), (self.blocks_uchar_to_float_0, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.blocks_tagged_stream_to_pdu_0, "pdus", self.sandbox_msg_src_0, "in")
        self.msg_connect(self.sandbox_msg_src_0, "out", self.sandbox_msg_div_0, "in")
        self.msg_connect(self.sandbox_msg_div_0, "out", self.sandbox_msg_hdr_fill_0, "in")
        self.msg_connect(self.sandbox_msg_hdr_fill_0, "out", self.blocks_message_debug_0, "print_pdu")
        self.msg_connect(self.sandbox_msg_hdr_fill_0, "out", self.blocks_pdu_to_tagged_stream_1, "pdus")


    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.blocks_throttle_1.set_sample_rate(self.samp_rate)

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"
    parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
    (options, args) = parser.parse_args()
    tb = top_block()
    tb.Start(True)
    tb.Wait()
