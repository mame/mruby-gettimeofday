mruby-gettimeofday
===

A simple wrapper of `gettimeofday(2)` for mruby

```ruby
p gettimeofday
#=> {:tv_sec=>1500000000, :tv_usec=>500000}
```

This mgem works with `MRB_WITHOUT_FLOAT`.

# Installation

in build_config.rb

```ruby
MRuby::Build.new do |conf|
  conf.gem :github => "mame/mruby-gettimeofday"
end
```

# Supported Methods

## Kernel

- `Kernel#gettimeofday`
