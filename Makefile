# =========================
# Not Illegal Autoclicker
# Cross-Platform Makefile
# =========================

# ---- Color codes and styles ----
BOLD   := \x1b[1m
GREEN  := \x1b[0;32m
YELLOW := \x1b[0;33m
RED    := \x1b[0;31m
BLUE   := \x1b[0;34m
CYAN   := \x1b[0;36m
PURPLE := \x1b[0;35m
RESET  := \x1b[0m


# ---- Fancy icons ----
ifeq ($(OS),Windows_NT)
	CHECK  := [OK]
	CROSS  := [X]
	HAMMER := [*]
	LINK   := [LINK]
	FOLDER := [DIR]
	BROOM  := [CLEAN]
	RECYCLE:= [RE]
	INFO   := [i]
	SPARK  := [*]
else
	CHECK  := ✔️
	CROSS  := ❌
	HAMMER := 🔨
	LINK   := 🔗
	FOLDER := 📁
	BROOM  := 🧹
	RECYCLE:= ♻️
	INFO   := ℹ️
	SPARK  := ✨
endif

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
	RM := rm -rf
	MKDIR := if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	EXE_EXT := .exe
	THREAD_FLAG := -pthread
else
	CXX := clang++ -framework ApplicationServices
	RM := rm -rf
	MKDIR := mkdir -p $(BUILD_DIR)
	EXE_EXT :=
	THREAD_FLAG := -pthread
endif

# ---- Project settings ----
TARGET := not_illegal_autoclicker$(EXE_EXT)
SRC_DIR := bot
BUILD_DIR := build

# Add thread flag for both compile and link
CXXFLAGS := -std=c++17 -Wall -Wextra $(THREAD_FLAG)

# ---- Source and object files ----
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# ---- Default target ----
.PHONY: all
all: $(TARGET)
	@printf '%b\n' "$(MSG_OK) Build complete! $(RESET)"

# ---- Linking ----
$(TARGET): $(OBJS)
	@printf '%b\n' "$(MSG_LINK) Linking executable: $(BOLD)$(TARGET)$(RESET)"
	$(CXX) $(CXXFLAGS) $^ -o $@

# ---- Compile user sources ----
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@printf '%b\n' "$(MSG_INFO) Compiling: $(BOLD)$<$(RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ---- Create build directory ----
$(BUILD_DIR):
	@printf '%b\n' "$(MSG_DIR) Creating build directory: $(BOLD)$(BUILD_DIR)$(RESET)"
	$(MKDIR)

# ---- Clean object files ----
.PHONY: clean
clean:
	@printf '%b\n' "$(MSG_WARN) Cleaning object files...$(RESET)"
	$(RM) $(BUILD_DIR)/*

# ---- Full clean ----
.PHONY: fclean
fclean: clean
	@printf '%b\n' "$(MSG_WARN) Removing executable: $(BOLD)$(TARGET)$(RESET)"
	$(RM) $(TARGET)

# ---- Rebuild ----
.PHONY: re
re: fclean
	@printf '%b\n' "$(MSG_REBUILD) Full rebuild initiated!$(RESET)"
	$(MAKE) all

# ---- Submodule update ----
.PHONY: submodules
submodules:
	@printf '%b\n' "$(MSG_INFO) Updating git submodules...$(RESET)"
	@git submodule update --init --recursive

# ---- Help ----
.PHONY: help
help:
	@printf '%b\n' "$(SPARK)$(BOLD) Not Illegal Autoclicker Makefile Help$(RESET)"
	@printf '%b\n' "  $(MSG_OK) $(GREEN)all$(RESET)        Build the executable"
	@printf '%b\n' "  $(MSG_WARN) $(YELLOW)clean$(RESET)      Remove object files"
	@printf '%b\n' "  $(MSG_WARN) $(YELLOW)fclean$(RESET)     Remove object files and executable"
	@printf '%b\n' "  $(MSG_REBUILD) $(CYAN)re$(RESET)          Clean and rebuild"
	@printf '%b\n' "  $(MSG_INFO) $(BLUE)submodules$(RESET)   Update git submodules"
