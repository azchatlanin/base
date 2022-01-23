vendor_headers = ['logger/logger.hpp', 'tools/tools.hpp']
vendor_sources = []

vendor_lib = library(
  'vendor',
  include_directories : inc,
  install : true,
  sources: [vendor_headers, vendor_sources]
)

vendor_dep = declare_dependency(
  include_directories: inc,
  link_with: vendor_lib
)
