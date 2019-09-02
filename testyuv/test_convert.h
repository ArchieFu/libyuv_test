#ifndef __CONVERT_H__
#define __CONVERT_H__

#include "libyuv.h"



int SaveNV12ToI420();
int SaveNV12ToRGB24();
int ScaleNV12ToRGB24();

int ScaleNV12ToRGBA();
int ScaleNV12ToARGB();


int SaveI420ToRGB24();

int SaveRGB24ToI420();

int ffmpegI420ToRGB24();

int NV12Scale(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode);

int NV12ScaleToRGB24(uint8* psrc_buf,
                     int psrc_w,
                     int psrc_h,
                     uint8* pdst_buf,
                     int pdst_w,
                     int pdst_h,
                     libyuv::FilterModeEnum pfmode);

int NV12ToRGB24_x(uint8* psrc_buf,
                  int psrc_w,
                  int psrc_h,
                  uint8* pdst_buf,
                  int pdst_w,
                  int pdst_h,
                  libyuv::FilterModeEnum pfmode);

int NV12_I420(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode);

int NV12_RGBA(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode);

int NV12_ABGR(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode);

int I420_RGB24(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              libyuv::FilterModeEnum pfmode);

int I420_Scale(uint8* psrc_buf,
              int psrc_w,
              int psrc_h,
              uint8* pdst_buf,
              int pdst_w,
              int pdst_h,
              libyuv::FilterModeEnum pfmode);

int RGB24_I420(uint8* psrc_buf,
               int psrc_w,
               int psrc_h,
               uint8* pdst_buf,
               libyuv::FilterModeEnum pfmode);

int RAW_I420(uint8* psrc_buf,
               int psrc_w,
               int psrc_h,
               uint8* pdst_buf,
               libyuv::FilterModeEnum pfmode);

#endif	//__CONVERT_H__


