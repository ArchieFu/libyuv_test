#ifndef _FFMPEG_SCALE_TEST_H__
#define _FFMPEG_SCALE_TEST_H__

extern "C" {
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#include "libavutil/frame.h"
#include "libswscale/swscale.h"
};

uint64_t os_gettime_ns(void);

int ffmpeg_swscale();
int libyuv_swscale();

int libyuv_I420_to_Rgb();
int ffmpeg_I420_to_Rgb();

#endif //_FFMPEG_SCALE_TEST_H__






