# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra

# Source files directory
SRCDIR := src

# Include files directory
INCDIR := include

# Object files directory
OBJDIR := obj

# Executable file name
TARGET := screenshot_uploader

# Source files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)

# Object files
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

# Include directories
INCLUDES := -I$(INCDIR)

# Build rule
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)
