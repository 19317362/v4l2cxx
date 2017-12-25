#include "v4l2cxx.h"



int main() {

    struct util_v4l2::buffer buffers[4];

    error_code err = error_code ::ERR_NO_ERROR;

    int fd = util_v4l2::open_device("/dev/video0", err);

    auto cap = util_v4l2::query_capabilites(fd,err);

    auto vec = util_v4l2::query_formats(fd,err);

    util_v4l2::set_format(fd,640,480,pixel_format::V4L2CXX_PIX_FMT_YVYU);

    auto vec_format = util_v4l2::get_current_format(fd);

    //util_v4l2::printv4l2_fmt(vec_format);

    util_v4l2::init_mmap(fd, buffers);

    util_v4l2::start_capturing(fd, 4, buffers);

    util_v4l2_b::mainloop(fd,buffers);


    return 0;
}