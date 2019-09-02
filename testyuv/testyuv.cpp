#include "pch.h"
#include "test_convert.h"
#include "ffmpeg_scale_test.h"

int testlibyuv_ffmpeg() {
  for (int i = 0; i < 10; i++) {
    printf("===========do index: %d==========\n", i);
    libyuv_swscale();
    ffmpeg_swscale();

    libyuv_I420_to_Rgb();
    ffmpeg_I420_to_Rgb();
  }

  return getchar();
}

int main(int argc, const char* argv[]) {
  //SaveNV12ToRGB24();
  //SaveNV12ToI420();

  //ScaleNV12ToRGB24();
  //ScaleNV12ToRGBA();
  //ScaleNV12ToARGB();

  //SaveI420ToRGB24();
  //SaveRGB24ToI420();
	
	ffmpegI420ToRGB24();

	//testlibyuv_ffmpeg();

  return 0;
}





