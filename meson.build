project (
  'otus', 
  'cpp', 
  default_options : [ 'cpp_std=c++20' ]
)

add_project_arguments (
  '-pedantic', 
  '-Wno-comment',
  '-Wno-gnu-zero-variadic-macro-arguments',
  language: 'cpp'
)

#############################################################
deps = [ 
]
args = [
]
#############################################################

src = [
  'src/main.cpp'
]

executable (
  'otus', 
  sources: src, 
  dependencies: deps, 
)
