headers = ['logger.hpp']
sources = []

lib = library(
  'logger_base',
  include_directories : inc,
  install : true,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

logger_base_dep = declare_dependency(
  include_directories: inc,
  link_with: lib
)
