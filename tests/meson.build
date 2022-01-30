gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')

test(
  'hello',
  executable(
    'hello',
    'hello.cpp',
    dependencies: [ hello_dep, gtest_dep ]
  )
)

test(
  'ip_filter',
  executable(
    'ip_filter',
    'ip_filter.cpp',
    dependencies: [ ip_filter_dep, gtest_dep ]
  )
)
