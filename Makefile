# =========================
# Not Illegal Autoclicker
# Cross-Platform Makefile
# =========================

# ---- Color codes and styles ----
BOLD   := \033[1m
GREEN  := \033[0;32m
YELLOW := \033[0;33m
RED    := \033[0;31m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
PURPLE := \033[0;35m
RESET  := \033[0m

# ---- Fancy icons ----
CHECK  := ✔️
CROSS  := ❌
HAMMER := 🔨
LINK   := 🔗
FOLDER := 📁
BROOM  := 🧹
RECYCLE:= ♻️
INFO   := ℹ️
SPARK  := ✨

# ---- Styled message templates ----
MSG_INFO   := $(BOLD)$(BLUE)$(INFO)$(RESET)$(CYAN)
MSG_WARN   := $(BOLD)$(YELLOW)$(BROOM)$(RESET)$(YELLOW)
MSG_ERROR  := $(BOLD)$(RED)$(CROSS)$(RESET)$(RED)
MSG_DIR    := $(BOLD)$(PURPLE)$(FOLDER)$(RESET)$(PURPLE)
MSG_LINK   := $(BOLD)$(GREEN)$(LINK)$(RESET)$(GREEN)
MSG_OK     := $(BOLD)$(GREEN)$(CHECK)$(RESET)$(GREEN)
MSG_REBUILD:= $(BOLD)$(CYAN)$(RECYCLE)$(RESET)$(CYAN)

# ---- OS Detection ----
ifeq ($(OS),Windows_NT)
    CXX := g++
    RM := del /Q /F
    MKDIR := if not exist build mkdir build
    EXE_EXT := .exe
else
    CXX := clang++
    RM := rm -rf
    MKDIR := mkdir -p build
    EXE_EXT :=
endif

# ---- Project settings ----
TARGET := not_illegal_autoclicker$(EXE_EXT)
SRC_DIR := bot
BUILD_DIR := build

CXXFLAGS := -std=c++17 -Wall -Wextra

# ---- Source and object files ----
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# ---- Default target ----
.PHONY: all
all: $(TARGET)
	@echo "$(MSG_OK) Build complete! $(RESET)"

# ---- Linking ----
$(TARGET): $(OBJS)
	@echo "$(MSG_LINK) Linking executable: $(BOLD)$(TARGET)$(RESET)"
	$(CXX) $(CXXFLAGS) $^ -o $@

# ---- Compile user sources ----
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "$(MSG_INFO) Compiling: $(BOLD)$<$(RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Create build directory ----
$(BUILD_DIR):
	@echo "$(MSG_DIR) Creating build directory: $(BOLD)$(BUILD_DIR)$(RESET)"
	$(MKDIR)

# ---- Clean object files ----
.PHONY: clean
clean:
	@echo "$(MSG_WARN) Cleaning object files...$(RESET)"
	$(RM) $(BUILD_DIR)/*

# ---- Full clean ----
.PHONY: fclean
fclean: clean
	@echo "$(MSG_WARN) Removing executable: $(BOLD)$(TARGET)$(RESET)"
	$(RM) $(TARGET)

# ---- Rebuild ----
.PHONY: re
re: fclean
	@echo "$(MSG_REBUILD) Full rebuild initiated!$(RESET)"
	$(MAKE) all

# ---- Submodule update ----
.PHONY: submodules
submodules:
	@echo "$(MSG_INFO) Updating git submodules...$(RESET)"
	@git submodule update --init --recursive

# ---- Help ----
.PHONY: help
help:
	@echo "$(SPARK)$(BOLD) Not Illegal Autoclicker Makefile Help$(RESET)"
	@echo "  $(MSG_OK) $(GREEN)all$(RESET)        Build the executable"
	@echo "  $(MSG_WARN) $(YELLOW)clean$(RESET)      Remove object files"
	@echo "  $(MSG_WARN) $(YELLOW)fclean$(RESET)     Remove object files and executable"
	@echo "  $(MSG_REBUILD) $(CYAN)re$(RESET)          Clean and rebuild"
	@echo "  $(MSG_INFO) $(BLUE)submodules$(RESET)   Update git submodules"
