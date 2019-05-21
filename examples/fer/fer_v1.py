#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Fer V1
# Author: Moses Browne Mwakyanjala
# Generated: Thu Feb 21 14:11:16 2019
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt4 import Qt
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import ccsds
import mapper
import math, numpy
import sys
import tdd
from gnuradio import qtgui


class fer_v1(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Fer V1")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Fer V1")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "fer_v1")
        self.restoreGeometry(self.settings.value("geometry").toByteArray())

        ##################################################
        # Variables
        ##################################################
        self.symbol_rate = symbol_rate = 500e3
        self.sps = sps = 4
        self.value = value = [0,1]
        self.symbol = symbol = [-1,1]
        self.scramble = scramble = 1
        self.samp_rate = samp_rate = symbol_rate*sps
        self.rs = rs = 0
        self.reset = reset = 500
        self.linecode = linecode = 0
        self.intDepth = intDepth = 4
        self.frame_size = frame_size = 500
        self.cfo = cfo = 0.0
        self.bn = bn = 0.07
        self.SNR = SNR = 1000

        ##################################################
        # Blocks
        ##################################################
        self.tdd_ferMsgGen_0 = tdd.ferMsgGen(frame_size, 'msg_len', "packet_len")
        self.tdd_ferMsgCount_0 = tdd.ferMsgCount(0)
        self.mapper_prbs_source_b_0 = mapper.prbs_source_b("PRBS31", reset*8)
        self.mapper_prbs_sink_b_0 = mapper.prbs_sink_b("PRBS31", reset*8)
        self.ccsds_synchronizeCADU_0 = ccsds.synchronizeCADU('1ACFFC1D', 0, "sync")
        self.ccsds_recoverCADU_0 = ccsds.recoverCADU(frame_size + 10, scramble, 'sync')
        self.ccsds_createCADU_0 = ccsds.createCADU(frame_size + 10, '1ACFFC1D', scramble, 'frame_len')
        self.blocks_unpack_k_bits_bb_1 = blocks.unpack_k_bits_bb(8)
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(8)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_tag_gate_0 = blocks.tag_gate(gr.sizeof_char * 1, False)
        self.blocks_stream_to_tagged_stream_1 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, frame_size+10, 'frame_len')
        self.blocks_stream_to_tagged_stream_0 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, frame_size, "packet_len")
        self.blocks_pdu_to_tagged_stream_0 = blocks.pdu_to_tagged_stream(blocks.byte_t, 'packet_len')
        self.blocks_pack_k_bits_bb_0 = blocks.pack_k_bits_bb(8)

        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.ccsds_recoverCADU_0, 'cadu'), (self.tdd_ferMsgCount_0, 'in'))
        self.msg_connect((self.tdd_ferMsgCount_0, 'out'), (self.blocks_pdu_to_tagged_stream_0, 'pdus'))
        self.connect((self.blocks_pack_k_bits_bb_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_pdu_to_tagged_stream_0, 0), (self.blocks_unpack_k_bits_bb_1, 0))
        self.connect((self.blocks_stream_to_tagged_stream_0, 0), (self.tdd_ferMsgGen_0, 0))
        self.connect((self.blocks_stream_to_tagged_stream_1, 0), (self.ccsds_createCADU_0, 0))
        self.connect((self.blocks_tag_gate_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_stream_to_tagged_stream_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.ccsds_synchronizeCADU_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_1, 0), (self.mapper_prbs_sink_b_0, 0))
        self.connect((self.ccsds_createCADU_0, 0), (self.blocks_tag_gate_0, 0))
        self.connect((self.ccsds_synchronizeCADU_0, 0), (self.ccsds_recoverCADU_0, 0))
        self.connect((self.mapper_prbs_source_b_0, 0), (self.blocks_pack_k_bits_bb_0, 0))
        self.connect((self.tdd_ferMsgGen_0, 0), (self.blocks_stream_to_tagged_stream_1, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "fer_v1")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_symbol_rate(self):
        return self.symbol_rate

    def set_symbol_rate(self, symbol_rate):
        self.symbol_rate = symbol_rate
        self.set_samp_rate(self.symbol_rate*self.sps)

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_samp_rate(self.symbol_rate*self.sps)

    def get_value(self):
        return self.value

    def set_value(self, value):
        self.value = value

    def get_symbol(self):
        return self.symbol

    def set_symbol(self, symbol):
        self.symbol = symbol

    def get_scramble(self):
        return self.scramble

    def set_scramble(self, scramble):
        self.scramble = scramble

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_rs(self):
        return self.rs

    def set_rs(self, rs):
        self.rs = rs

    def get_reset(self):
        return self.reset

    def set_reset(self, reset):
        self.reset = reset

    def get_linecode(self):
        return self.linecode

    def set_linecode(self, linecode):
        self.linecode = linecode

    def get_intDepth(self):
        return self.intDepth

    def set_intDepth(self, intDepth):
        self.intDepth = intDepth

    def get_frame_size(self):
        return self.frame_size

    def set_frame_size(self, frame_size):
        self.frame_size = frame_size
        self.blocks_stream_to_tagged_stream_1.set_packet_len(self.frame_size+10)
        self.blocks_stream_to_tagged_stream_1.set_packet_len_pmt(self.frame_size+10)
        self.blocks_stream_to_tagged_stream_0.set_packet_len(self.frame_size)
        self.blocks_stream_to_tagged_stream_0.set_packet_len_pmt(self.frame_size)

    def get_cfo(self):
        return self.cfo

    def set_cfo(self, cfo):
        self.cfo = cfo

    def get_bn(self):
        return self.bn

    def set_bn(self, bn):
        self.bn = bn

    def get_SNR(self):
        return self.SNR

    def set_SNR(self, SNR):
        self.SNR = SNR


def main(top_block_cls=fer_v1, options=None):

    from distutils.version import StrictVersion
    if StrictVersion(Qt.qVersion()) >= StrictVersion("4.5.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.connect(qapp, Qt.SIGNAL("aboutToQuit()"), quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
