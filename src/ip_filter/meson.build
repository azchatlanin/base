headers = ['ip_filter.hpp']
sources = []

lib = library(
  'ip_filter',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

ip_filter_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib,
)
