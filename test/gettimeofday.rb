assert 'gettimeofday' do
  t = gettimeofday
  assert_kind_of Numeric, t[:tv_sec]
  assert_kind_of Numeric, t[:tv_usec]
end
