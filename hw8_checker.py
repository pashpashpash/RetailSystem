# CS104 Spring 2017: Homework 8 Grading Script
# Run with the command: python hw8_checker.py

import sys, os
sys.path.insert(0, '/')

extra_credit = 0

VALGRIND    = 'valgrind --tool=memcheck --leak-check=yes'
GTEST       = '-I /usr/include/gtest/ -l gtest -l gtest_main -pthread'
HEADER      = '\n*++++++++++++++++++++++++++++++++++++++++++++++++*'
FOOTER      = HEADER + '\n\n\n\n\n'
TEXT_EDITOR = 'subl'

def compile_student_code(makefile_provided, 
						 make_command = '', 
						 source_files = '', 
						 compiler = 'g++', 
						 flags = '-g -Wall', 
						 target = 'executable',
						 use_gtest = 0 
						):
	if makefile_provided:
		os.system('make ' + make_command)
	else:
		if use_gtest:
			os.system(compiler + ' ' + flags + ' ' + source_files + ' ' + GTEST + ' -o ' + target)
		else:
			os.system(compiler + ' ' + flags + ' ' + source_files + ' -o ' + target)

def check_file_existence(file_name, 
						 directory = '/'
						):
	return os.path.exists(file_name)

def open_file(file_name, 
			  text_editor = TEXT_EDITOR 
			 ):
	os.system(text_editor + ' ' + file_name)

def write_message(target_file, 
				  message, 
				  write_mode = 'a' 
				 ):
	with open(target_file, write_mode) as target:
		target.write(message)

def write_file_contents(target_file, 
						source_file, 
						write_mode = 'a' 
					   ):
	with open(target_file, write_mode) as target, open(source_file, 'r') as source:
		source_contents = source.read().strip()
		target.write(source_contents)

def read_file_contents(target_file):
	content = ''
	with open(target_file, 'r') as target:
		content = target.read()
	return content

def remove_file(file_name):
	files_to_remove = file_name.split()
	for i in range(0, len( files_to_remove)):
		os.system('rm ' + str(files_to_remove[i]))

def run_executable(executable_path,
				   executable_name,
				   extra_arguments = '', 
				   use_valgrind = 0,
				   valgrind_log_filename = '' 
				  ):
	if use_valgrind:
		os.system(VALGRIND + ' --log-file=\"temp_valgrind_log.txt' + '\" ' + executable_path + executable_name + ' ' + extra_arguments)
		write_file_contents(valgrind_log_filename, 'temp_valgrind_log.txt')
		write_message(valgrind_log_filename, '\n\n')
		remove_file('temp_valgrind_log.txt')
	else:
		os.system(executable_path + executable_name + ' ' + extra_arguments)

def run_gtest(output_file_name_base, source_files, flags, use_valgrind, open_results, clean_files):
	if check_file_existence(output_file_name_base + '_results.txt'):
		remove_file(output_file_name_base + '_results.txt')
	if check_file_existence(output_file_name_base + '_valgrind.txt'):
		remove_file(output_file_name_base + '_valgrind.txt')
	compile_student_code(0, flags = flags, source_files = source_files, target = output_file_name_base + '_gtest', use_gtest = 1)
	run_executable('./', output_file_name_base + '_gtest', ' > ' + output_file_name_base + '_results.txt', use_valgrind, output_file_name_base + '_valgrind.txt')
	if open_results:
		open_file(output_file_name_base + '_results.txt', TEXT_EDITOR)
		if use_valgrind:
			open_file(output_file_name_base + '_valgrind.txt', TEXT_EDITOR)
	if clean_files:
		remove_file(output_file_name_base + '_gtest')

# Problem 2: Update Heap to Support Decrease-key using a Hash Table.
run_gtest(
	output_file_name_base = 'heap',                 # Do not change.
	         source_files = 'gtest_heap.cpp',       # Do not change.
	                flags = '-g -Wall -std=c++11',  # Flags use for compilation.
	         use_valgrind = 1,                      # Change to 0 to turn off valgrind.
	         open_results = 1,                      # Change to 0 to stop result files from opening automatically.
	          clean_files = 1                       # Change to 0 if you don't want intermediary files cleaned up. 
)

# # Problem 3: Product Recommendations.
# run_gtest(
# 	output_file_name_base = 'recommendations',                 # Do not change.
# 	         source_files = 'gtest_recommendations.cpp',       # Do not change.
# 	                flags = '-g -Wall -std=c++11',             # Flags use for compilation.
# 	         use_valgrind = 0,                                 # Don't change
# 	         open_results = 1,                                 # Change to 0 to stop result files from opening automatically.
# 	          clean_files = 1                                  # Change to 0 if you don't want intermediary files cleaned up. 
# )

# if extra_credit:
# 	run_gtest(
# 	output_file_name_base = 'map',                  # Do not change.
# 	         source_files = 'gtest_map.cpp',        # Do not change.
# 	                flags = '-g -Wall -std=c++11',  # Flags use for compilation.
# 	         use_valgrind = 1,                      # Change to 0 to turn off valgrind.
# 	         open_results = 1,                      # Change to 0 to stop result files from opening automatically.
# 	          clean_files = 1                       # Change to 0 if you don't want intermediary files cleaned up. 
# 	)
