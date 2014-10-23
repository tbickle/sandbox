#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Wed Oct 22 17:00:45 2014
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
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
        # Blocks
        ##################################################
        self.sandbox_msg_src_0 = sandbox.msg_src()
        self.sandbox_msg_hdr_fill_0 = sandbox.msg_hdr_fill(2)
        self.sandbox_msg_div_0 = sandbox.msg_div(3)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_tagged_stream_to_pdu_0 = blocks.tagged_stream_to_pdu(blocks.byte_t, "packet_len")
        self.blocks_stream_to_tagged_stream_0 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, 1, "packet_len")
        self.blocks_message_debug_0 = blocks.message_debug()
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/home/matthew/sandbox/trig.dat", False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_stream_to_tagged_stream_0, 0), (self.blocks_tagged_stream_to_pdu_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_stream_to_tagged_stream_0, 0))

        ##################################################
        # Asynch Message Connections
        ##################################################
        self.msg_connect(self.blocks_tagged_stream_to_pdu_0, "pdus", self.sandbox_msg_src_0, "in")
        self.msg_connect(self.sandbox_msg_src_0, "out", self.sandbox_msg_div_0, "in")
        self.msg_connect(self.sandbox_msg_div_0, "out", self.sandbox_msg_hdr_fill_0, "in")
        self.msg_connect(self.sandbox_msg_hdr_fill_0, "out", self.blocks_message_debug_0, "print_pdu")


    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

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
