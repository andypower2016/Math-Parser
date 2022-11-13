CC := clang
CXX := clang++
CFLAGS := -g -O -fsanitize=address -fsanitize-coverage=trace-pc-guard
CXXFLAGS := -g -O -fsanitize=address -fsanitize-coverage=trace-pc-guard

# directories
SRCFOLDER := $(PWD)
BUILDFOLDER := $(PWD)/build
DIRS = src cov
SRCDIRS = $(foreach dir,$(DIRS),$(addprefix $(SRCFOLDER)/,$(dir)))
BUILDDIR = $(foreach dir,$(DIRS),$(addprefix $(BUILDFOLDER)/,$(dir)))

# vpath
VPATH = $(SRCDIRS) 


# srcs & objs
TARGET = main
INCLUDES := $(foreach dir,$(SRCDIRS),$(addprefix -I, $(dir)))
SRCS := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
CSRCS :=$(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS := $(subst $(SRCFOLDER),$(BUILDFOLDER),$(SRCS:.cpp=.o))
COBJS := $(subst $(SRCFOLDER),$(BUILDFOLDER),$(CSRCS:.c=.o))
DEPS := $(OBJS:.o=.d)

# tools
SEP=/
PSEP = $(strip $(SEP))
ERRIGNORE = 2>/dev/null

define genRules
$(1)/%.o: %.cpp
	@echo Building $$@
	$(CXX) $(CXXFLAGS) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD

$(1)/%.o: %.c
	@echo Building $$@
	$(CC) $(CFLAGS) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef


.PHONY= createDir TARGET
all: createDir $(TARGET)

output:
	@echo $(INCLUDES)

$(TARGET): $(OBJS) $(COBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(COBJS) -o $(TARGET)
	
-include $(DEPS)

$(foreach dir,$(BUILDDIR),$(eval $(call genRules, $(dir))))

createDir:
	mkdir -p $(BUILDFOLDER) $(errignore)
	mkdir -p $(BUILDDIR) $(errignore)

clean:
	rm -rf $(BUILDFOLDER)
	rm -rf $(TARGET)
