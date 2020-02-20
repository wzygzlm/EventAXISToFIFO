#include "hls_stream.h"
#include "ap_int.h"
#include "ap_axi_sdata.h"

#define SLICE_WIDTH 512

// Change these two together, make SLIC_HEIGHT equal to 512
#define RESHAPE_FACTOR 64
#define SLICE_HEIGHT RESHAPE_FACTOR*8

// Change them together
#define TS_TYPE_BIT_WIDTH 16
#define LOG_TS_TYPE_BIT_WIDTH 4   // Log(TS_TYPE_BIT_WIDTH), used in pix read and pix write

#define col_pix_t ap_uint<RESHAPE_FACTOR * TS_TYPE_BIT_WIDTH>

static col_pix_t glDVSSlice[SLICE_HEIGHT/RESHAPE_FACTOR][SLICE_WIDTH];   // support 512 * 512 resolution, every pixel 16bits data.

struct register_t
{
	uint32_t dvsWidth;
	uint32_t dvsHeight;
	uint32_t sliceDuration;
	uint32_t displayMode;

	ap_uint<32> status;
	uint32_t frameCnt;
};

typedef ap_axiu<24, 2, 1, 1> rgbFrameStream_t;

typedef ap_axiu<32, 4, 1, 1> stream_t;

void testVGAFrame(hls::stream< rgbFrameStream_t > &frameStream);
void EVRawStreamToXYTSStream(ap_uint<16> *eventFIFOIn,
		hls::stream< ap_uint<16> > &xStreamOut, hls::stream< ap_uint<16> > &yStreamOut, hls::stream< ap_uint<16> > &tsStreamOut);
