headers = ['allocator.hpp']
sources = []

lib = library(
  'allocator',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

allocator_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib,
)
