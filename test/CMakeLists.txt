
# 指定生成目标
add_executable(http_server http_sever_run.c)
# 添加链接库
target_link_libraries(http_server lib)

# 指定生成目标
add_executable(tcp_server_test tcp_server_test.c)
# 添加链接库
target_link_libraries(tcp_server_test lib)

# 指定生成目标
add_executable(http_server_test http_server_test.c)
# 添加链接库
target_link_libraries(http_server_test lib)
