file(GLOB SOURCE *.h *.cpp)
add_library(ExternalAdd ${SOURCE})

install(FILES ExternalAdd.h DESTINATION include)
install(TARGETS ExternalAdd DESTINATION lib)
