project (
  'otus', 
# https://pixorblog.wordpress.com/2019/07/27/a-meson-starter-script-for-c-projects
project(
  'base', 
  'cpp', 
  version : '0.0.1', 
  default_options : ['cpp_std=c++20']
)

add_project_arguments (
  '-pedantic', 
  '-Wno-comment',
  '-Wno-gnu-zero-variadic-macro-arguments',
  '-Wunused-but-set-variable',
  language: 'cpp'
)

inc = []
inc += include_directories('.')

src = [
  'src/main.cpp'
]

executable (
  'otus', 
  sources: src, 
  dependencies: deps, 
)
subdir('vendor')
subdir('src')
subdir('tests')
subdir('bin')
