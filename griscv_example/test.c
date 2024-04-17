

long test_rand(long arg1)
{
    return __builtin_griscv_rand(arg1);
}

void *test_get_frame()
{
    return __builtin_griscv_gr_frame(0);
}

void test_flush()
{
    __builtin_griscv_gr_flush();
}

long test_call(long arg)
{
    long tmp = 2;
    return test_rand(arg + tmp) + 7;
}

long test_control_flow(long arg1, long arg2)
{
    long res = 1;

    if (arg1 != arg2)
        res = arg1 * arg2;
    else {
        arg1 += 10;
        res += arg1 / arg2;
    }

    return res * res - res;
}

// Cannot put -1 (0xFFF...FF) to reg (only <=32 bits is supported now)
// Invalid after optimizations
// long test_imm_minus(long arg1)
// {
//     long arg2 = 1;
//     return -arg2;
// }

// Always valid
int test_imm_minus(int arg1)
{
    int arg2 = 1;
    return -arg2;
}

// don't use for cycle with comparison, due to SLT/SLTI/SGE/... instructions are banned
// instead use comparison ops like "==" in condition blocks
long test_for_sum(long n_iters)
{
    long sum = 0;

    while (n_iters) {
        sum += n_iters;
        n_iters -= 1; // -> addi -1, so valid even for long values
        // after optimization shift ops are used, so cannot be compiled
    }

    return sum;
}

long test_for_for(long n_iters1, long n_iters2)
{
    long sum = 0;

    while (n_iters1) {
        while (n_iters2) {
            sum += n_iters2 * n_iters1;
            n_iters2 -= 1;
        }
        n_iters1 -= 1;
    }

    return sum;
}

// Test for immediate numbers with more than 12 bits
// 9000 = 0b0010'0011'0010'1000 -> LUI 0010 (2) + ADDI 0011'0010'1000 (808)
long test_imm_div(long arg)
{
    return arg / 9000;
}

// int value are supported too, addiw/lw help to cast registers due to the fact
// that not all *w instructions are supported now
int test_int_vals(int arg, long arg2)
{
    int kek = arg2;
    int lol = kek * kek;
    return arg2 / arg + arg - lol;
}
