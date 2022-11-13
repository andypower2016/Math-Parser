CC := g++

# directories
SRCFOLDER := $(PWD)
BUILDFOLDER := $(PWD)/build
DIRS = src
SRCDIRS = $(foreach dir,$(DIRS),$(addprefix $(SRCFOLDER)/,$(dir)))
BUILDDIR = $(foreach dir,$(DIRS),$(addprefix $(BUILDFOLDER)/,$(dir)))

# vpath
VPATH = $(SRCDIRS) 


# srcs & objs
TARGET = main
INCLUDES := $(foreach dir,$(SRCDIRS),$(addprefix -I, $(dir)))
SRCS := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.cpp))
OBJS := $(subst $(SRCFOLDER),$(BUILDFOLDER),$(SRCS:.cpp=.o))
DEPS := $(OBJS:.o=.d)

# tools
SEP=/
PSEP = $(strip $(SEP))
ERRIGNORE = 2>/dev/null

define genRules
$(1)/%.o: %.cpp
	@echo Building $$@
	$(CC) -c $$(INCLUDES) -o $$(subst /,$$(PSEP),$$@) $$(subst /,$$(PSEP),$$<) -MMD
endef


.PHONY= createDir TARGET
all: createDir $(TARGET)

output:
	@echo $(INCLUDES)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	
-include $(DEPS)

$(foreach dir,$(BUILDDIR),$(eval $(call genRules, $(dir))))

createDir:
	mkdir -p $(BUILDFOLDER) $(errignore)
	mkdir -p $(BUILDDIR) $(errignore)

clean:
	rm -rf $(BUILDFOLDER)
	rm -rf $(TARGET)
