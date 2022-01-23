headers = ['hello.hpp']
sources = ['hello.cpp']

lib = library(
  'hello',
  include_directories : inc,
  install : true,
  sources: [headers, sources]
)

hello_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
