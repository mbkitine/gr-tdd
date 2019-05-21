/* -*- c++ -*- */

#define TDD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "tdd_swig_doc.i"

%{
#include "tdd/ferMsgCount.h"
#include "tdd/ferMsgBlock.h"
#include "tdd/ferMsgGen.h"
#include "tdd/nullMsgSink.h"
#include "tdd/serMsgCnt.h"
%}


%include "tdd/ferMsgCount.h"
GR_SWIG_BLOCK_MAGIC2(tdd, ferMsgCount);
%include "tdd/ferMsgBlock.h"
GR_SWIG_BLOCK_MAGIC2(tdd, ferMsgBlock);
%include "tdd/ferMsgGen.h"
GR_SWIG_BLOCK_MAGIC2(tdd, ferMsgGen);
%include "tdd/nullMsgSink.h"
GR_SWIG_BLOCK_MAGIC2(tdd, nullMsgSink);
%include "tdd/serMsgCnt.h"
GR_SWIG_BLOCK_MAGIC2(tdd, serMsgCnt);
