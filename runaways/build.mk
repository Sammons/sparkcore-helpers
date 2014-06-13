ifeq ($(APP),custom)
    CPPSRC += applications/custom/custom.cpp     				# the main application
    CPPSRC += libraries/sparkcore-helpers/sparkcore-helpers.cpp # the sensor library
    CPPSRC += libraries/sparkcore-helpers/TCPLogger.cpp

endif