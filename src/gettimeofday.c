#include <sys/time.h>
#include "mruby.h"
#include "mruby/hash.h"
#include "mruby/error.h"

static void
hash_setup(mrb_state *mrb, mrb_value hash, mrb_sym sym, time_t val)
{
  mrb_value r_key;
  mrb_value r_val;

  r_key = mrb_symbol_value(sym);
  if (val > MRB_INT_MAX || val < MRB_INT_MIN) {
#ifdef MRB_WITHOUT_FLOAT
    mrb_raise(mrb, E_RUNTIME_ERROR, "time_t is too big (or small) for MRB_WITHOUT_FLOAT");
#else
    r_val = mrb_float_value(mrb, (mrb_float)val);
#endif
  }
  else {
    r_val = mrb_fixnum_value((mrb_int)val);
  }
  mrb_hash_set(mrb, hash, r_key, r_val);
}

static mrb_value
mrb_kernel_gettimeofday(mrb_state *mrb, mrb_value self)
{
  mrb_value ret;
  struct timeval tv;

  if (gettimeofday(&tv, NULL))
    mrb_sys_fail(mrb, "gettimeofday");

  ret = mrb_hash_new(mrb);
  hash_setup(mrb, ret, mrb_intern_lit(mrb, "tv_sec"), tv.tv_sec);
  hash_setup(mrb, ret, mrb_intern_lit(mrb, "tv_usec"), tv.tv_usec);
  
  return ret;
}

void
mrb_mruby_gettimeofday_gem_init(mrb_state* mrb)
{
  mrb_define_method(mrb, mrb->kernel_module, "gettimeofday", mrb_kernel_gettimeofday, MRB_ARGS_NONE());
}

void
mrb_mruby_gettimeofday_gem_final(mrb_state* mrb)
{
}
