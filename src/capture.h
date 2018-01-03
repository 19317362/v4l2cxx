#pragma once

class capture {

public:

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    capture(std::string device, std::function<void(uint8_t *p_data, size_t len)> callback)
            : callback_(callback) {

        fd_ = util_v4l2::open_device(device, &err_);
        ASSERT_ERR_CODE(err_);

    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    capture(std::string device, uint32_t width, uint32_t height, pixel_format format,
            std::function<void(uint8_t *p_data, size_t len)> callback)
            : callback_(callback) {


        fd_ = util_v4l2::open_device(device, &err_);
        ASSERT_ERR_CODE(err_);

        util_v4l2::set_format(fd_, width, height, format, &err_);
        ASSERT_ERR_CODE(err_);

        util_v4l2::init_mmap(fd_, buffers, &err_);
        ASSERT_ERR_CODE(err_);

        util_v4l2::start_capturing(fd_, NUM_OF_MAP_BUFFER, &err_);
        ASSERT_ERR_CODE(err_);
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void run() {
        util_v4l2::mainloop(fd_, buffers, callback_,&err_);
        ASSERT_ERR_CODE(err_);
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void set_format(int width, int height, pixel_format format){
        util_v4l2::set_format(fd_, width, height, format, &err_);
        ASSERT_ERR_CODE(err_);

        util_v4l2::init_mmap(fd_, buffers, &err_);
        ASSERT_ERR_CODE(err_);

        util_v4l2::start_capturing(fd_, NUM_OF_MAP_BUFFER, &err_);
        ASSERT_ERR_CODE(err_);
    }

private:

    int fd_{};
    constexpr static int NUM_OF_MAP_BUFFER = 4;
    struct util_v4l2::buffer buffers[NUM_OF_MAP_BUFFER];
    error_code err_ = error_code::ERR_NO_ERROR;
    std::function<void(uint8_t *p_data, size_t len)> callback_;
};