headers = ['matrix_old.hpp']
sources = []

lib = library(
  'matrix',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

matrix_dep = declare_dependency(
  include_directories: inc, 
  link_with: lib,
)
