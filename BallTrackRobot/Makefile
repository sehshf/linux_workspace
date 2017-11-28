#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = arm-linux-gnueabihf-g++

# define any compile-time flags
CFLAGS = -g -Wall -std=gnu++11

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L/home/ses/opencv-3.2.0/build/install/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm -lpthread -lrt -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_objdetect -ldl
#LIBS = -lmylib -lm

# Output executable file
OUTPUTFILE = BallTrackRobot.elf

# Path
HOME			= /home/ses
PROJECT 		= $(HOME)/workspace/BallTrackRobot
SOURCE 			= $(PROJECT)/source
RELEASEDIR 		= $(PROJECT)/release
BASIC			= $(SOURCE)/basic
APPLICATION 	= $(SOURCE)/application
APPLIB 			= $(APPLICATION)/applib/
CAMERA 			= $(APPLICATION)/camera
SERVO 			= $(APPLICATION)/servo
VEHICLE			= $(APPLICATION)/vehicle
TASKS 			= $(SOURCE)/tasks
DATAIO 			= $(SOURCE)/dataio
EXEDIR      	= $(RELEASEDIR)/exe
OBJDIR      	= $(RELEASEDIR)/obj
OPENCVINCLUDE 	= $(HOME)/opencv-3.2.0/build/install/include
OPENCV 			= $(OPENCVINCLUDE)/opencv

# define any directories containing header files other than /usr/include
INCLUDES = 			\
-I$(APPLICATION)	\
-I$(APPLIB)			\
-I$(CAMERA)			\
-I$(SERVO)			\
-I$(VEHICLE)		\
-I$(BASIC)			\
-I$(DATAIO)			\
-I$(OPENCVINCLUDE) 	\
-I$(OPENCV)			\
-I$(TASKS)			

# Specify all paths of source files
VPATH = $(BASIC) : $(APPLICATION) : $(APPLIB) : $(CAMERA) : $(SERVO) : $(VEHICLE) : $(TASKS) : $(DATAIO)

# define the C source files
# Extract source directories
SRC_DIRS = $(subst :, ,$(VPATH))

SRCS = 					\
camera.c 				\
computer_vision.c		\
control.c				\
dc_motors.c				\
i2c_smbus.c				\
gpio.c 					\
main.c					\
params.c				\
pca9685.c				\
rt_tasks.c				\
servo.c					\
servo_control.c			\
servo_motors.c			\
signal_processing.c		\
speed_sensor.c			\
vehicle.c				\
vehicle_control.c		\
wheel.c

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

# define the executable file 
MAIN = $(EXEDIR)/$(OUTPUTFILE)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	@echo  *** Make completed ***

$(MAIN): $(OBJS) 
	@echo "--- Linking ..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)
#$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
$(OBJDIR)/%.o: %.c
	@echo "--- Compiling ..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	@echo "--- Cleaning all generated files ..."
	$(RM) $(OBJDIR)/*.o
	$(RM) $(MAIN)
#$(RM) *~

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
