int main()
{
    long width = 1080;
    long height = 720;
    long bytes_per_pixel = 4;
    long seed = 42;
    long n_max_iters = 1000;

    char *frame = (char *) __builtin_griscv_gr_frame(0);
    long index = 0;

    long y = height - 1;
    while (y) {
        long x = width - 1;
        while (x) {
            index = bytes_per_pixel * (width * y + x);
            frame[index + 3] = 0xFF;
            frame[index + 1] = 0xAA * (__builtin_griscv_rand(seed) & 0x1);
            x -= 1;
        }
        y -= 1;
    }

    __builtin_griscv_gr_flush();

    long i = 0, j = 0;

    while (n_max_iters) {
        long y = height - 1;
        while (y) {
            long x = width - 1;
            while (x) {
                long n_neighbours = 0;

                i = 3;
                while (i) {
                    j = 3;
                    while (j) {
                        index = bytes_per_pixel * (((y + (i - 2) + height) % height) * width + ((x + (j - 2) + width) % width));
                        if (frame[index + 1])
                            n_neighbours++;

                        j--;
                    }
                    i--;
                }

                index = bytes_per_pixel * (((y + height) % height) * width + ((x + width) % width));
                if (frame[index + 1]) {
                    n_neighbours--; // drop own pixel
                }

                if (n_neighbours == 3) {
                    if (frame[index + 1] == 0) {
                        frame[index + 1] = 0xAA;
                    }
                } else if (n_neighbours == 2) {
                    frame[index + 1] = frame[index + 1];
                } else {
                    if (frame[index + 1] != 0) {
                        frame[index + 1] = 0x00;
                    }
                }

                x -= 1;
            }
            y -= 1;
        }

        __builtin_griscv_gr_flush();
        n_max_iters -= 1;
    }

    return 0;
}
