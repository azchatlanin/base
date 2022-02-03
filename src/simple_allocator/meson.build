headers = ['simple_allocator.hpp']
sources = []

lib = library(
  'simple_allocator',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

simple_allocator_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib,
)
