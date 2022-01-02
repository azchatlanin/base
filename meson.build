project (
  'base', 
  'cpp', 
  version: '0.0.1',
  default_options : [ 'cpp_std=c++2a' ]
)

add_project_arguments (
  '-pedantic', 
  language: 'cpp'
)

dir_incl = [ '/mnt/develop/projects/cpp/logger' ]

#############################################################
deps = [ 
]
args = []
#############################################################

src = [
  'src/main.cpp'
]

executable (
  'base', 
  sources: src, 
  include_directories : dir_incl,
  dependencies: deps, 
  cpp_args: args
)
