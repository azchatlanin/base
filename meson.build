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

deps = [ dependency('threads') ]
args = []

tools = subproject('tools')
logger_dep = tools.get_variable('logger_dep')
exception_dep = tools.get_variable('exception_dep')

deps += logger_dep
deps += exception_dep

inc = []
inc += include_directories('subprojects')

subdir('src')
subdir('bin')
subdir('tests')
