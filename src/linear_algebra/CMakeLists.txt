FILE(GLOB HDRS *.h ${PROJECT_NAME})
INSTALL(FILES ${HDRS} DESTINATION include/${PROJECT_NAME} COMPONENT headers)

FILE(GLOB SOURCES *.cpp)
ADD_LIBRARY(${PROJECT_NAME} STATIC ${SOURCES})
INSTALL(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib COMPONENT libraries)

ADD_SUBDIRECTORY(detail)
