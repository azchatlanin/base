args = []
deps = []

deps += dependency('threads')

deps += vendor_dep
deps += hello_dep
deps += ip_filter_dep

executable(
  'base', 'main.cpp', 
  install: true, 
  dependencies : [deps]
)
