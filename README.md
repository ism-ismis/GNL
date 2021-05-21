# GNL
a function and the tester to  read a line from any file descriptors

#### To check prepared test-cases  
Run command "gcc -Wall -Wextra -Werror -D BUFFER_SIZE=[any_buffer_size_you_want] get_next_line.c get_next_line_utils.c test.c"  

#### To check any file which specified in command line argument  
Run command "gcc -Wall -Wextra -Werror -D BUFFER_SIZE=[any_buffer_size_you_want] get_next_line.c get_next_line_utils.c test_each.c" 

#### To check string from stdin  
Run command "gcc -Wall -Wextra -Werror -D BUFFER_SIZE=[any_buffer_size_you_want] get_next_line.c get_next_line_utils.c test_stdin.c"  

#### To check several file descriptors  
Run command "gcc -Wall -Wextra -Werror -D BUFFER_SIZE=[any_buffer_size_you_want] get_next_line_bonus.c get_next_line_utils_bonus.c test_bonus.c"
