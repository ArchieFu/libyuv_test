#include "pch.h"
#include "test_convert.h"
#include "ffmpeg_scale_test.h"

#include <stdio.h>
#include <stdlib.h>

int SaveNV12ToI420() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "videotestsrc_1920x1080.nv12";  //"frame_1280_720_index_856.nv12";                                     
  char outputPathname[30] = "dst_1920x1080.I420";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for nv12 */
  int size_i420src = src_w * src_h * 3 / 2;
 
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf = (uint8*)malloc(size_i420src);         // YUV420p == I420

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);

  int ret = NV12_I420(src_buf, src_w, src_h, dst_buf, dst_w, dst_h, fmode);
  if (ret != 0) {
    printf("NV12_I420 error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf, sizeof(uint8), size_i420src, fout);
  printf("SaveNV12ToI420 fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf);

  fclose(fin);
  fclose(fout);

  return ret;
}

int SaveNV12ToRGB24() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "videotestsrc_1920x1080.nv12";
  char outputPathname[30] = "dst_1920x1080.rgb24";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for nv12 */
  int size_i420src = src_w * src_h * 3 / 2;
  int rgb24_srcsize = src_w * src_h * 3;
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf_rgb24 = (uint8*)malloc(rgb24_srcsize);  // RGB24

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);
  int ret = NV12ToRGB24_x(src_buf, src_w, src_h, dst_buf_rgb24, dst_w, dst_h, fmode);
  /* Write the data to file */
  ret = fwrite(dst_buf_rgb24, sizeof(uint8), rgb24_srcsize, fout);
  printf("SaveNV12ToRGB24 fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf_rgb24);

  fclose(fin);
  fclose(fout);

  return ret;
}

int ScaleNV12ToRGB24() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "videotestsrc_1920x1080.nv12";
  char outputPathname[30] = "dst_1280x720.rgb24";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for nv12 */
  int size_i420src = src_w * src_h * 3 / 2;
  int rgb24_dstsize = dst_w * dst_h * 3;
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf_rgb24 = (uint8*)malloc(rgb24_dstsize);  // RGB24

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);
  int ret = NV12ScaleToRGB24(src_buf, src_w, src_h, dst_buf_rgb24, dst_w, dst_h,
                             fmode);
  if (ret != 0) {
    printf("NV12ScaleToRGB24 error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf_rgb24, sizeof(uint8), rgb24_dstsize, fout);
  printf("ScaleNV12ToRGB24 fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf_rgb24);

  fclose(fin);
  fclose(fout);

  return ret;
}

int ScaleNV12ToRGBA() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "videotestsrc_1920x1080.nv12";
  char outputPathname[30] = "dst_1280x720.rgba";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for nv12 */
  int size_i420src = src_w * src_h * 3 / 2;
  int rgba_dstsize = dst_w * dst_h * 4;
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf_rgba = (uint8*)malloc(rgba_dstsize);  // RGB24

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);
  int ret = NV12_RGBA(src_buf, src_w, src_h, 
	  dst_buf_rgba, dst_w, dst_h, fmode);
  if (ret != 0) {
    printf("NV12_RGBA error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf_rgba, sizeof(uint8), rgba_dstsize, fout);
  printf("ScaleNV12ToRGBA fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf_rgba);

  fclose(fin);
  fclose(fout);

  return ret;
}


int ScaleNV12ToARGB() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "videotestsrc_1920x1080.nv12";
  char outputPathname[30] = "dst_1280x720.bgra";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for nv12 */
  int size_i420src = src_w * src_h * 3 / 2;
  int rgba_dstsize = dst_w * dst_h * 4;
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf_rgba = (uint8*)malloc(rgba_dstsize);  // RGB24

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);
  int ret = NV12_ABGR(src_buf, src_w, src_h, dst_buf_rgba, dst_w, dst_h, fmode);
  if (ret != 0) {
    printf("NV12_ABGR error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf_rgba, sizeof(uint8), rgba_dstsize, fout);
  printf("ScaleNV12ToARGB fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf_rgba);

  fclose(fin);
  fclose(fout);

  return ret;
}

int SaveI420ToRGB24() {
  const int src_w = 1920;
  const int src_h = 1080;
  const int dst_w = 1280;
  const int dst_h = 720;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "src_1920x1080.yuv";
  char outputPathname[30] = "dst_1920x1080.rgb24";
  //char outputPathname[30] = "dst_1280x720.yuv";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for yuv420p */
  int size_i420src = src_w * src_h * 3 / 2;
  int rgb24_dstsize = src_w * src_h * 3;
  //int rgb24_dstsize = dst_w * dst_h * 3 / 2;
  
  uint8* src_buf = (uint8*)malloc(size_i420src);
  uint8* dst_buf = (uint8*)malloc(rgb24_dstsize);

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_i420src, fin);
  int ret = I420_RGB24(src_buf, src_w, src_h, dst_buf, libyuv::kFilterBox);
  //int ret = I420_Scale(src_buf, src_w, src_h, dst_buf, dst_w, dst_h, fmode);
  if (ret != 0) {
    printf("NV12_ABGR error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf, sizeof(uint8), rgb24_dstsize, fout);
  printf("ScaleNV12ToARGB fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf);

  fclose(fin);
  fclose(fout);

  return ret;
}

int SaveRGB24ToI420() {
  const int src_w = 1920;
  const int src_h = 1080;

  libyuv::FilterModeEnum fmode = libyuv::kFilterNone;

  char inputPathname[30] = "src_1920x1080.rgb24";
  char outputPathname[30] = "dst_bgr_I420_1920x1080.yuv";

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }

  FILE* fin = fopen(inputPathname, "r+");
  if (fin == nullptr) {
    printf("open dst file error\n");
    return -1;
  }

  /* Allocate memory for yuv420p */
  int size_src = src_w * src_h * 3; 
  int dstsize = src_w * src_h * 3 / 2;
  
  uint8* src_buf = (uint8*)malloc(size_src);
  uint8* dst_buf = (uint8*)malloc(dstsize);

  /* Read file data to buffer */
  fread(src_buf, sizeof(uint8), size_src, fin);
  int ret = RGB24_I420(src_buf, src_w, src_h, dst_buf, libyuv::kFilterBox);
  if (ret != 0) {
    printf("NV12_ABGR error");
  }

  /* Write the data to file */
  ret = fwrite(dst_buf, sizeof(uint8), dstsize, fout);
  printf("ScaleNV12ToARGB fwrite size: %d\n", ret);

  free(src_buf);
  free(dst_buf);

  fclose(fin);
  fclose(fout);

  return ret;
}

int ffmpegI420ToRGB24() {
  const int width_src = 1920, height_src = 1080;
  const int width_dest = 1920, height_dest = 1080;
  

  FILE* src_file = fopen("src_1920x1080.yuv", "r+");
  //FILE* src_file = fopen("videotestsrc_1920x1080.nv12", "r+");
  if (src_file == nullptr) {
    printf("open src file error");
    return -1;
  }
  FILE* dst_file = fopen("ffmpeg_HD.rgb24", "w+");
  if (dst_file == nullptr) {
    printf("open dst file error\n");
    return -1;
  }
  
  uint8_t* src_data[4];
  int src_linesize[4];

  uint8_t* dst_data[4];
  int dst_linesize[4];

  int size_src = width_src * height_src * 3 / 2;
  int size_dest = width_dest * height_dest * 3;
  char* buffer_src = (char*)malloc(size_src);
  char* buffer_dest = (char*)malloc(size_dest);
  fread(buffer_src, 1, size_src, src_file);

  if (av_image_alloc(src_data, src_linesize, width_src, height_src,
                     AV_PIX_FMT_YUV420P, 1) < 0) {
    return -1;
  }
  if (av_image_alloc(dst_data, dst_linesize, width_dest, height_dest,
                     AV_PIX_FMT_RGB24, 1) < 0) {
    return -1;
  }

  struct SwsContext* sws_context = sws_getContext(width_src, height_src, AV_PIX_FMT_YUV420P, 
					width_dest, height_dest, AV_PIX_FMT_RGB24, 
					SWS_FAST_BILINEAR, 0, 0, 0);
  if (!sws_context)
  {
    printf("sws_getContext failed...\n");
    return -5;
  }

  /*AVFrame* rgbFrame = av_frame_alloc();
  if (NULL == rgbFrame) {
    return false;
  }
  rgbFrame->height = width_src;
  rgbFrame->width = height_src;
  rgbFrame->format = AV_PIX_FMT_RGB24;
  if (av_frame_get_buffer(rgbFrame, 0) < 0) {
    fprintf(stderr, "Could not allocate video data buffers\n");
    av_frame_free(&rgbFrame);
    rgbFrame = NULL;
    return -1;
  }*/
  
  memcpy(src_data[0], buffer_src, width_src * height_src);  // Y
  memcpy(src_data[1], buffer_src + width_src * height_src, width_src * height_src / 4);  // U
  memcpy(src_data[2], buffer_src + width_src * height_src * 5 / 4, width_src * height_src / 4);  // V

  //int ret = sws_scale(sws_context, src_data, src_linesize, 0, height_src, rgbFrame->data, rgbFrame->linesize);
  int ret = sws_scale(sws_context, src_data, src_linesize, 0, height_src, dst_data, dst_linesize);
  if (ret < 0) {
    printf("scale yuv420p to rgb24 failed...\n");
  }

  ret = fwrite(dst_data, 1, size_dest, dst_file);
  //ret = fwrite(rgbFrame->data, 1, size_dest, dst_file);
  if (ret < 0) {
    printf("write file failed...\n");
  }
  

  free(buffer_src);
  free(buffer_dest);
  fclose(src_file);
  fclose(dst_file);
  av_freep(&src_data[0]);
  av_freep(&dst_data[0]);

  return 0;
}

//==========================================================
int NV12Scale(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode) {
  uint8* i420_buf1 = (uint8*)malloc(psrc_w * psrc_h * 3 / 2);
  uint8* i420_buf2 = (uint8*)malloc(pdst_w * pdst_h * 3 / 2);
  int ret = -100;
  /* NV12_1920x1080 -> I420_1920x1080 */
  ret = libyuv::NV12ToI420(
      &psrc_buf[0],							psrc_w, 
	  &psrc_buf[psrc_w * psrc_h],			psrc_w, 
	  &i420_buf1[0],						psrc_w, 
	  &i420_buf1[psrc_w * psrc_h],			psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4],  psrc_w / 2, 
	  psrc_w, psrc_h);

  /* I420_1920x1080 -> I420_1280x720 */
  ret = libyuv::I420Scale(
      &i420_buf1[0], psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h,
      &i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h], pdst_w / 2,
      &i420_buf2[pdst_w * pdst_h * 5 / 4], pdst_w / 2, pdst_w, pdst_h, pfmode);

  /* I420_1280x720 -> NV12_1280x720 */
  ret = libyuv::I420ToNV12(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                           pdst_w / 2, &i420_buf2[pdst_w * pdst_h * 5 / 4],
                           pdst_w / 2, &pdst_buf[0], pdst_w,
                           &pdst_buf[pdst_w * pdst_h], pdst_w, pdst_w, pdst_h);

  free(i420_buf1);
  free(i420_buf2);

  return ret;
}

int NV12ScaleToRGB24(uint8* psrc_buf,
                     int psrc_w,
                     int psrc_h,
                     uint8* pdst_buf,
                     int pdst_w,
                     int pdst_h,
                     libyuv::FilterModeEnum pfmode) {
  uint8* i420_buf1 = (uint8*)malloc(psrc_w * psrc_h * 3 / 2);
  uint8* i420_buf2 = (uint8*)malloc(pdst_w * pdst_h * 3 / 2);
  int ret = -100;
  /* NV12_1920x1080 -> I420_1920x1080 */
  ret = libyuv::NV12ToI420(
      &psrc_buf[0], psrc_w, &psrc_buf[psrc_w * psrc_h], psrc_w, &i420_buf1[0],
      psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h);

  /* I420_1920x1080 -> I420_1280x720 */
  ret = libyuv::I420Scale(
      &i420_buf1[0], psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h,
      &i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h], pdst_w / 2,
      &i420_buf2[pdst_w * pdst_h * 5 / 4], pdst_w / 2, pdst_w, pdst_h, pfmode);

  
   ret = libyuv::I420ToRGB24(&i420_buf2[0], pdst_w, 
							&i420_buf2[pdst_w * pdst_h], pdst_w >> 1, 
							&i420_buf2[(pdst_w * pdst_h * 5) >> 2], pdst_w >> 1,  
							&pdst_buf[0], pdst_w * 3, pdst_w, pdst_h);

 /* ret = libyuv::I420ToRGB24(
      (const uint8*)i420_buf2, pdst_w,
      (const uint8*)(i420_buf2 + pdst_w * pdst_h), pdst_w >> 1,
      (const uint8*)(i420_buf2 + pdst_w * pdst_h * 5 / 4), pdst_w >> 1,
      &pdst_buf[0], pdst_w * 3, 
	  pdst_w, pdst_h);*/

  /*
  ret = libyuv::I420ToARGB((const uint8*)i420_buf2, pdst_w,
                           (const uint8*)(i420_buf2 + pdst_w * pdst_h), pdst_w
  >> 1, (const uint8*)(i420_buf2 + pdst_w * pdst_h * 5 / 4), pdst_w >> 1,
                           &pdst_buf[0], pdst_w * 4,
                                                   pdst_w, pdst_h);*/

  free(i420_buf1);
  free(i420_buf2);

  return ret;
}

int NV12ToRGB24_x(uint8* psrc_buf,
                  int psrc_w,
                  int psrc_h,
                  uint8* pdst_buf,
                  int pdst_w,
                  int pdst_h,
                  libyuv::FilterModeEnum pfmode) {
  int ret = -100;
  ret = libyuv::NV12ToRGB24(&psrc_buf[0], psrc_w, 
	  &psrc_buf[psrc_w * psrc_h],  psrc_w, 
	  &pdst_buf[0],	psrc_w * 3, 
	  psrc_w, psrc_h);

  return ret;
}

int NV12_I420(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode) {
  int ret = -100;
  /* NV12_1920x1080 -> I420_1920x1080 */
  ret = libyuv::NV12ToI420(
      &psrc_buf[0], psrc_w, &psrc_buf[psrc_w * psrc_h], psrc_w, &pdst_buf[0],
      psrc_w, &pdst_buf[psrc_w * psrc_h], psrc_w / 2,
      &pdst_buf[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h);

  return ret;
}

int NV12_RGBA(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode) {

  uint8* i420_buf1 = (uint8*)malloc(psrc_w * psrc_h * 3 / 2);
  uint8* i420_buf2 = (uint8*)malloc(pdst_w * pdst_h * 3 / 2);
  int ret = -100;
  /* NV12_1920x1080 -> I420_1920x1080 */
  ret = libyuv::NV12ToI420(
      &psrc_buf[0], psrc_w, &psrc_buf[psrc_w * psrc_h], psrc_w, &i420_buf1[0],
      psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h);

  /* I420_1920x1080 -> I420_1280x720 */
  ret = libyuv::I420Scale(
      &i420_buf1[0], psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h,
      &i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h], pdst_w / 2,
      &i420_buf2[pdst_w * pdst_h * 5 / 4], pdst_w / 2, pdst_w, pdst_h, pfmode);

  ret = libyuv::I420ToRGB24(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                            pdst_w >> 1, &i420_buf2[(pdst_w * pdst_h * 5) >> 2],
                            pdst_w >> 1, &pdst_buf[0], pdst_w * 3, pdst_w,
                            pdst_h);
  
  ret = libyuv::I420ToRGBA(&i420_buf2[0],		pdst_w, 
	  &i420_buf2[pdst_w * pdst_h],				pdst_w >> 1, 
	  &i420_buf2[(pdst_w * pdst_h * 5) >> 2],	pdst_w >> 1, 
	  &pdst_buf[0], pdst_w * 4, 
	  pdst_w, pdst_h);

  free(i420_buf1);
  free(i420_buf2);

  return ret;
}


int NV12_ABGR(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode) {
  uint8* i420_buf1 = (uint8*)malloc(psrc_w * psrc_h * 3 / 2);
  uint8* i420_buf2 = (uint8*)malloc(pdst_w * pdst_h * 3 / 2);
  int ret = -100;
  /* NV12_1920x1080 -> I420_1920x1080 */
  ret = libyuv::NV12ToI420(
      &psrc_buf[0], psrc_w, &psrc_buf[psrc_w * psrc_h], psrc_w, &i420_buf1[0],
      psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h);

  /* I420_1920x1080 -> I420_1280x720 */
  ret = libyuv::I420Scale(
      &i420_buf1[0], psrc_w, &i420_buf1[psrc_w * psrc_h], psrc_w / 2,
      &i420_buf1[psrc_w * psrc_h * 5 / 4], psrc_w / 2, psrc_w, psrc_h,
      &i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h], pdst_w / 2,
      &i420_buf2[pdst_w * pdst_h * 5 / 4], pdst_w / 2, pdst_w, pdst_h, pfmode);

  ret = libyuv::I420ToRGB24(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                            pdst_w >> 1, &i420_buf2[(pdst_w * pdst_h * 5) >> 2],
                            pdst_w >> 1, &pdst_buf[0], pdst_w * 3, pdst_w,
                            pdst_h);
  // 图像下1/4色彩没对上 abgr
  /*ret = libyuv::I420ToABGR(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                         pdst_w >> 1, &i420_buf2[(pdst_w * pdst_h * 5) >> 2],
                         pdst_w >> 1, &pdst_buf[0], pdst_w * 4, pdst_w,
     pdst_h);*/
  
  // 图像下1/4色彩没对上 argb
  /*ret = libyuv::I420ToARGB(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                         pdst_w >> 1, &i420_buf2[(pdst_w * pdst_h * 5) >> 2],
                         pdst_w >> 1, &pdst_buf[0], pdst_w * 4, pdst_w, pdst_h);*/
  // 整幅画面色彩没对上 bgra
  ret = libyuv::I420ToBGRA(&i420_buf2[0], pdst_w, &i420_buf2[pdst_w * pdst_h],
                         pdst_w >> 1, &i420_buf2[(pdst_w * pdst_h * 5) >> 2],
                         pdst_w >> 1, &pdst_buf[0], pdst_w * 4, pdst_w, pdst_h);

  free(i420_buf1);
  free(i420_buf2);

  return ret;
}

int I420_RGB24(uint8* psrc_buf,
               int psrc_w,
               int psrc_h,
               uint8* pdst_buf,
               libyuv::FilterModeEnum pfmode) {
  
	int ret = libyuv::I420ToRGB24(&psrc_buf[0],							psrc_w, 
								&psrc_buf[psrc_w * psrc_h],				(psrc_w + 1) / 2, 
								&psrc_buf[psrc_w * psrc_h * 5 / 4],		(psrc_w + 1) / 2, 
								&pdst_buf[0],	psrc_w * 3, 
								psrc_w, psrc_h);


  /*int ret = libyuv::I420ToRAW(
      &psrc_buf[0],									psrc_w, 
	  &psrc_buf[psrc_w * psrc_h],					psrc_w >> 1,
      &psrc_buf[(psrc_w * psrc_h * 5) >> 2],		psrc_w >> 1,
	  &pdst_buf[0],									psrc_w * 3, 
	  psrc_w, psrc_h);*/

	//I420ToBGRA  I420ToARGB I420ToABGR I420ToRGBA
    /*int ret = libyuv::I420ToBGRA(
		&psrc_buf[0],							psrc_w, 
		&psrc_buf[psrc_w * psrc_h],				psrc_w >> 1,
		&psrc_buf[psrc_w * psrc_h * 5 /4],		psrc_w >> 1, 
		&pdst_buf[0],							psrc_w * 4, 
		psrc_w, psrc_h);*/

  return ret;
}

int I420_Scale(uint8* psrc_buf,
               int psrc_w,
               int psrc_h,
               uint8* pdst_buf,
               int pdst_w,
               int pdst_h,
               libyuv::FilterModeEnum pfmode) {
  int ret = libyuv::I420Scale(
      &psrc_buf[0],							psrc_w, 
	  &psrc_buf[psrc_w * psrc_h],			(psrc_w + 1) / 2,
      &psrc_buf[psrc_w * psrc_h * 5 / 4],	(psrc_w + 1) / 2, 
	  psrc_w, psrc_h,
      &pdst_buf[0],							pdst_w, 
	  &pdst_buf[pdst_w * pdst_h],			(pdst_w + 1) / 2,
      &pdst_buf[pdst_w * pdst_h * 5 / 4],	(pdst_w + 1) / 2,
	  pdst_w, pdst_h, 
	  pfmode);

  return ret;
}

int RGB24_I420(uint8* psrc_buf,
               int psrc_w,
               int psrc_h,
               uint8* pdst_buf,
               libyuv::FilterModeEnum pfmode) {
	//  (RGB24)bgr -> I420 
	int ret = libyuv::RGB24ToI420(&psrc_buf[0],						psrc_w * 3, 
								&pdst_buf[0],						psrc_w,
                                &pdst_buf[psrc_w * psrc_h],			psrc_w / 2,
                                &pdst_buf[psrc_w * psrc_h * 5 / 4], psrc_w / 2,
                                psrc_w, psrc_h);

        return ret;
}

int RAW_I420(uint8* psrc_buf,
             int psrc_w,
             int psrc_h,
             uint8* pdst_buf,
             libyuv::FilterModeEnum pfmode) {
  //  rgb -> I420
  int ret = libyuv::RAWToI420(&psrc_buf[0], psrc_w * 3, &pdst_buf[0], psrc_w,
                              &pdst_buf[psrc_w * psrc_h], psrc_w / 2,
                              &pdst_buf[psrc_w * psrc_h * 5 / 4], psrc_w / 2,
                              psrc_w, psrc_h);

  return ret;
}

int saveNV12ToFile(unsigned char* pdst_buf, int w, int h) {
  static int i = 0;
  char outputPathname[30] = {0};
  sprintf(outputPathname, "frame_%d_%d_index_%d.nv12", w, h, i++);

  FILE* fout = fopen(outputPathname, "w+");
  if (fout == nullptr) {
    printf("open src file error");
    return -1;
  }
  int ret = fwrite(pdst_buf, sizeof(unsigned char), w * h * 3 / 2, fout);

  fclose(fout);
  return ret;
}
