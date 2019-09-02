#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include "libyuv.h"
#include "ffmpeg_scale_test.h"

static inline uint64_t get_clockfreq(void) {
  static LARGE_INTEGER clock_freq;
  QueryPerformanceFrequency(&clock_freq);
  return clock_freq.QuadPart;
}

uint64_t os_gettime_ns(void) {
  LARGE_INTEGER current_time;
  double time_val;
  QueryPerformanceCounter(&current_time);
  time_val = (double)current_time.QuadPart;
  time_val *= 1000000000.0;
  time_val /= (double)get_clockfreq();

  return (uint64_t)time_val;
}

//=================libyuv scale===================================
int libyuv_swscale() {
  printf("---begin libyuv scale------\n");
  const int width_src = 1920, height_src = 1080;
  const int width_dest = 1280, height_dest = 720;
  FILE* src_file = fopen("1920x1080.yuv", "rb");
  FILE* dst_file = fopen("libyuv_1905x1071.yuv", "wb");

  int size_src = width_src * height_src * 3 / 2;
  int size_dest = width_dest * height_dest * 3 / 2;
  char* buffer_src = (char*)malloc(size_src);
  char* buffer_dest = (char*)malloc(size_dest);

  
  //while (1) 
  //{
    if (fread(buffer_src, 1, size_src, src_file) != size_src) 
	{
      // fseek(src_file, 0, 0);
      // fread(buffer_src, 1, size_src, src_file);
      //break;
    }
    uint64_t start_time = os_gettime_ns();  
    libyuv::I420Scale(
        (const uint8*)buffer_src, width_src,
        (const uint8*)(buffer_src + width_src * height_src), width_src / 2,
        (const uint8*)(buffer_src + width_src * height_src * 5 / 4), width_src / 2, 
		width_src, height_src, 
		(uint8*)buffer_dest, width_dest,
        (uint8*)(buffer_dest + width_dest * height_dest), width_dest / 2,
        (uint8*)(buffer_dest + width_dest * height_dest * 5 / 4), width_dest / 2, 
		width_dest, height_dest, 
		libyuv::kFilterNone);

    //fwrite(buffer_dest, 1, size_dest, dst_file);
  //}

  uint64_t stop_time = os_gettime_ns();
  printf("------ %lld\n\n", (stop_time - start_time)/1000);
  
  free(buffer_src);
  free(buffer_dest);
  fclose(dst_file);
  fclose(src_file);
  return 0;
}

//==================ffmpeg scale==================================
int ffmpeg_swscale() {
  printf("---begin ffmpeg scale------\n");
  const int width_src = 1920, height_src = 1080;
  const int width_dest = 1280, height_dest = 720;
  FILE* src_file = fopen("1920x1080.yuv", "rb");
  FILE* dst_file = fopen("ffmpeg_1905x1071.yuv", "wb");

  uint8_t* src_data[4];
  int src_linesize[4];

  uint8_t* dst_data[4];
  int dst_linesize[4];

  struct SwsContext* img_convert_ctx;

  int size_src = width_src * height_src * 3 / 2;
  char* buffer_src = (char*)malloc(size_src);

  if (av_image_alloc(src_data, src_linesize, width_src, height_src,
                     AV_PIX_FMT_YUV420P, 1) < 0) {
    return -1;
  }
  if (av_image_alloc(dst_data, dst_linesize, width_dest, height_dest,
                     AV_PIX_FMT_YUV420P, 1) < 0) {
    return -1;
  }

  img_convert_ctx = sws_alloc_context();
  //av_opt_show2(img_convert_ctx, stdout, AV_OPT_FLAG_VIDEO_PARAM, NULL);
  av_opt_set_int(img_convert_ctx, "sws_flags",
                 SWS_FAST_BILINEAR | SWS_PRINT_INFO, NULL);
  av_opt_set_int(img_convert_ctx, "srcw", width_src, NULL);
  av_opt_set_int(img_convert_ctx, "srch", height_src, NULL);
  av_opt_set_int(img_convert_ctx, "src_format", AV_PIX_FMT_YUV420P, NULL);
  av_opt_set_int(img_convert_ctx, "src_range", 1, NULL);
  av_opt_set_int(img_convert_ctx, "dstw", width_dest, NULL);
  av_opt_set_int(img_convert_ctx, "dsth", height_dest, NULL);
  av_opt_set_int(img_convert_ctx, "dst_format", AV_PIX_FMT_YUV420P, NULL);
  av_opt_set_int(img_convert_ctx, "dst_range", 1, NULL);
  sws_init_context(img_convert_ctx, NULL, NULL);

  
  //while (1) 
 // {
    if (fread(buffer_src, 1, size_src, src_file) != size_src) 
	{
      // fseek(src_file, 0, 0);
      // fread(buffer_src, 1, size_src, src_file);
      //break;
    }
    uint64_t start_time = os_gettime_ns();
    memcpy(src_data[0], buffer_src, width_src * height_src);  // Y
    memcpy(src_data[1], buffer_src + width_src * height_src,
           width_src * height_src / 4);  // U
    memcpy(src_data[2], buffer_src + width_src * height_src * 5 / 4,
           width_src * height_src / 4);  // V
    sws_scale(img_convert_ctx, src_data, src_linesize, 0, height_src, dst_data,dst_linesize);

    // fwrite(dst_data[0], 1, width_dest * height_dest, dst_file);
    // fwrite(dst_data[1], 1, width_dest * height_dest / 4, dst_file);
    // fwrite(dst_data[2], 1, width_dest * height_dest / 4, dst_file);
  //}
  uint64_t stop_time = os_gettime_ns();
  printf("------ %lld\n\n", (stop_time - start_time) / 1000);

  sws_freeContext(img_convert_ctx);

  free(buffer_src);
  fclose(src_file);
  fclose(dst_file);
  av_freep(&src_data[0]);
  av_freep(&dst_data[0]);
  return 0;
}

int libyuv_I420_to_Rgb() {
  printf("---begin libyuv I420 to Rgb------\n");

  const int width = 1920, height = 1080;
  FILE* src_file = fopen("1920x1080.yuv", "rb");
  FILE* dst_file = fopen("1280x720.rgb", "wb");

  int size_src = width * height * 3 / 2;
  int size_dest = width * height * 4;
  char* buffer_src = (char*)malloc(size_src);
  char* buffer_dest = (char*)malloc(size_dest);

  
  //while (1) 
  //{
    if (fread(buffer_src, 1, size_src, src_file) != size_src) 
	{
      // fseek(src_file, 0, 0);
      // fread(buffer_src, 1, size_src, src_file);
      //break;
    }
    uint64_t start_time = os_gettime_ns();
    libyuv::I420ToARGB((const uint8*)buffer_src, width,
                       (const uint8*)(buffer_src + width * height), width / 2,
                       (const uint8*)(buffer_src + width * height * 5 / 4),
                       width / 2, (uint8*)buffer_dest, width * 4, width,
                       height);
    // fwrite(buffer_dest, 1, size_dest, dst_file);
  //}
  uint64_t stop_time = os_gettime_ns();
  printf("------ %lld\n\n", (stop_time - start_time) / 1000);

  free(buffer_src);
  free(buffer_dest);
  fclose(dst_file);
  fclose(src_file);
  return 0;
}

int ffmpeg_I420_to_Rgb() {
  printf("---begin ffmpeg I420 to Rgb------\n");

  const int width = 1920, height = 1080;
  FILE* src_file = fopen("1920x1080.yuv", "rb");
  FILE* dst_file = fopen("1280x720.rgb", "wb");

  uint8_t* src_data[4];
  int src_linesize[4];

  uint8_t* dst_data[4];
  int dst_linesize[4];

  struct SwsContext* img_convert_ctx;

  int size_src = width * height * 3 / 2;
  char* buffer_src = (char*)malloc(size_src);

  if (av_image_alloc(src_data, src_linesize, width, height, AV_PIX_FMT_YUV420P,
                     1) < 0) {
    return -1;
  }
  if (av_image_alloc(dst_data, dst_linesize, width, height, AV_PIX_FMT_BGRA,
                     1) < 0) {
    return -1;
  }

  img_convert_ctx = sws_alloc_context();
  //av_opt_show2(img_convert_ctx, stdout, AV_OPT_FLAG_VIDEO_PARAM, NULL);
  av_opt_set_int(img_convert_ctx, "sws_flags",
                 SWS_FAST_BILINEAR | SWS_PRINT_INFO, NULL);
  av_opt_set_int(img_convert_ctx, "srcw", width, NULL);
  av_opt_set_int(img_convert_ctx, "srch", height, NULL);
  av_opt_set_int(img_convert_ctx, "src_format", AV_PIX_FMT_YUV420P, NULL);
  av_opt_set_int(img_convert_ctx, "src_range", 1, NULL);
  av_opt_set_int(img_convert_ctx, "dstw", width, NULL);
  av_opt_set_int(img_convert_ctx, "dsth", height, NULL);
  av_opt_set_int(img_convert_ctx, "dst_format", AV_PIX_FMT_BGRA, NULL);
  av_opt_set_int(img_convert_ctx, "dst_range", 1, NULL);
  sws_init_context(img_convert_ctx, NULL, NULL);

  
  //while (1) 
 // {
    if (fread(buffer_src, 1, size_src, src_file) != size_src) {
      // fseek(src_file, 0, 0);
      // fread(buffer_src, 1, size_src, src_file);
      //break;
    }
    uint64_t start_time = os_gettime_ns();
    memcpy(src_data[0], buffer_src, width * height);                       // Y
    memcpy(src_data[1], buffer_src + width * height, width * height / 4);  // U
    memcpy(src_data[2], buffer_src + width * height * 5 / 4,
           width * height / 4);  // V
    sws_scale(img_convert_ctx, src_data, src_linesize, 0, height, dst_data,
              dst_linesize);
    // fwrite(dst_data[0], 1, width * height * 4, dst_file);
  //}
  uint64_t stop_time = os_gettime_ns();
  printf("------ %lld\n\n", (stop_time - start_time) / 1000);

  sws_freeContext(img_convert_ctx);

  free(buffer_src);
  fclose(src_file);
  fclose(dst_file);
  av_freep(&src_data[0]);
  av_freep(&dst_data[0]);
  return 0;
}









