project(
  'linkedList',
  'c',
  default_options : ['cpp_std=c++17', 'buildtype=debug'],version : '0.1')

libs = include_directories('lib')

src = ['src/linkedList.c']
src_test = ['src/testing.c']

executable('main_linkedList',src,include_directories : libs)

testing_aco = executable('testing', src_test,include_directories : libs )
