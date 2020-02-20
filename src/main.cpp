#include <iostream>
#include "ap_int.h"
#include<stdint.h>
#include "hls_stream.h"
#include "assert.h"
#include "main.h"
#include "systemc.h"


void RawStreamToFIFO(hls::stream< ap_uint<16> > &streamIn,
		ap_uint<1> fifoIFInFull_n, ap_uint<16> *fifoIFOutData, ap_uint<16> *skippedData)
{
#pragma HLS INTERFACE ap_vld port=fifoIFOutData
#pragma HLS INTERFACE axis register both port=streamIn
#pragma HLS INTERFACE ap_ctrl_hs port=return
#pragma HLS PIPELINE

	ap_uint<16> data = streamIn.read();
	ap_uint<16> swapData;
	swapData.range(15, 8) = data.range(7, 0);
	swapData.range(7, 0) = data.range(15, 8);

	if(fifoIFInFull_n)
	{
		*fifoIFOutData = swapData;
	}
	else
	{
		*skippedData = swapData;
	}
}
