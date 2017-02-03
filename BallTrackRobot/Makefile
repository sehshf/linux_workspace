#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = arm-linux-gnueabihf-gcc

# define any compile-time flags
CFLAGS = -g -Wall

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
#LFLAGS = -L/home/newhall/lib  -L../lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm -lpthread
#LIBS = -lmylib -lm

# Output executable file
OUTPUTFILE = MultiTask

# Path
RELEASEDIR  = release
EXEDIR      = $(RELEASEDIR)/exe
OBJDIR      = $(RELEASEDIR)/obj
DRIVER		= source/driver
BASIC		= source/basic
APPLICATION = source/application

# define any directories containing header files other than /usr/include
#
INCLUDES =  	 \
-I$(DRIVER) 	 \
-I$(BASIC)		 \
-I$(APPLICATION)

# Specify all paths of source files
VPATH = $(DRIVER) : $(BASIC) : $(APPLICATION)

# define the C source files
# Extract source directories
SRC_DIRS = $(subst :, ,$(VPATH))

SRCS =  		\
main.c			\
rt_tasks.c		\
task1.c 		\
task2.c 		\
task3.c	

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
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)
#$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

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
