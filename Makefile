# openJuice Project Makefile
# 
# This Makefile provides convenient targets for building, installing, and managing
# the openJuice project using CMake and Ninja.

# Project configuration
PROJECT_NAME := openJuice
BUILD_DIR := build
INSTALL_PREFIX := $(HOME)/.local
BIN_DIR := $(INSTALL_PREFIX)/bin
CMAKE_GENERATOR := Ninja
CMAKE_BUILD_TYPE := Release

# Sanitiser configuration (can be overridden with make SANITISERS="address undefined")
SANITISERS ?=
ENABLE_SANITISERS := OFF
CMAKE_SANITISER_FLAGS :=

# Process sanitiser flags
ifneq ($(SANITISERS),)
	ENABLE_SANITISERS := ON
	CMAKE_BUILD_TYPE := Debug
	
	ifeq ($(findstring address,$(SANITISERS)),address)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_ADDRESS=ON -DUSE_SANITISER_LEAK=ON
	endif
	
	ifeq ($(findstring kernel-address,$(SANITISERS)),kernel-address)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_KERNEL=ON
	endif
	
	ifeq ($(findstring hw-address,$(SANITISERS)),hw-address)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_HW=ON
	endif
	
	ifeq ($(findstring undefined,$(SANITISERS)),undefined)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_UNDEFINED=ON
	endif
	
	ifeq ($(findstring thread,$(SANITISERS)),thread)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_THREAD=ON
	endif
	
	ifeq ($(findstring memory,$(SANITISERS)),memory)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_MEMORY=ON
	endif
	
	ifeq ($(findstring leak,$(SANITISERS)),leak)
		CMAKE_SANITISER_FLAGS += -DUSE_SANITISER_LEAK=ON
	endif
	
	ifeq ($(SANITISERS),all)
		CMAKE_SANITISER_FLAGS := -DUSE_SANITISER_ADDRESS=ON -DUSE_SANITISER_UNDEFINED=ON -DUSE_SANITISER_LEAK=ON
	endif
	
	ifeq ($(SANITISERS),all-kernel)
		CMAKE_SANITISER_FLAGS := -DUSE_SANITISER_KERNEL=ON -DUSE_SANITISER_UNDEFINED=ON -DUSE_SANITISER_MEMORY=ON -DUSE_SANITISER_LEAK=ON
	endif
	
	ifeq ($(SANITISERS),all-hardware)
		CMAKE_SANITISER_FLAGS := -DUSE_SANITISER_HW=ON -DUSE_SANITISER_UNDEFINED=ON -DUSE_SANITISER_MEMORY=ON -DUSE_SANITISER_LEAK=ON
	endif
endif

# Colors for output
BOLD := \033[1m
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
RESET := \033[0m

# Check if required tools are available
REQUIRED_TOOLS := cmake ninja python3
$(foreach tool,$(REQUIRED_TOOLS),\
	$(if $(shell command -v $(tool) 2> /dev/null),,\
		$(error $(tool) is required but not found in PATH)))

# Default target
.PHONY: all
all: build

# Help target - shows available commands
.PHONY: help
help:
	@printf "$(BOLD)$(CYAN)openJuice Project Makefile$(RESET)\n"
	@printf "\n"
	@printf "$(BOLD)Build Targets:$(RESET)\n"
	@printf "  $(YELLOW)build$(RESET)         - Build the project (default)\n"
	@printf "  $(YELLOW)clean$(RESET)         - Clean build directory\n"
	@printf "  $(YELLOW)rebuild$(RESET)       - Clean and build\n"
	@printf "  $(YELLOW)configure$(RESET)     - Configure CMake build system\n"
	@printf "\n"
	@printf "$(BOLD)Install Targets:$(RESET)\n"
	@printf "  $(YELLOW)install$(RESET)       - Install to $(INSTALL_PREFIX)/bin\n"
	@printf "  $(YELLOW)uninstall$(RESET)     - Remove installed files\n"
	@printf "\n"
	@printf "$(BOLD)Sanitiser Options:$(RESET)\n"
	@printf "  $(YELLOW)SANITISERS$(RESET)    - Enable sanitisers (builds in Debug mode)\n"
	@printf "    Values: address, kernel-address, hw-address, undefined, thread, memory, leak\n"
	@printf "    Special: all, all-kernel, all-hardware\n"
	@printf "    Example: make build SANITISERS=\"address undefined\"\n"
	@printf "    Example: make run SANITISERS=all\n"
	@printf "\n"
	@printf "$(BOLD)Script Targets:$(RESET)\n"
	@printf "  $(YELLOW)update-discord$(RESET) - Update Discord SDK files\n"
	@printf "  $(YELLOW)scripts$(RESET)       - Show available scripts\n"
	@printf "\n"
	@printf "$(BOLD)Development Targets:$(RESET)\n"
	@printf "  $(YELLOW)run$(RESET)           - Build and run the application\n"
	@printf "  $(YELLOW)debug$(RESET)         - Build in debug mode and run with gdb\n"
	@printf "  $(YELLOW)test$(RESET)          - Run tests (if available)\n"
	@printf "\n"
	@printf "$(BOLD)Utility Targets:$(RESET)\n"
	@printf "  $(YELLOW)format$(RESET)        - Format code using clang-format\n"
	@printf "  $(YELLOW)lint$(RESET)          - Run clang-tidy linter\n"
	@printf "  $(YELLOW)deps$(RESET)          - Install/update dependencies\n"
	@printf "  $(YELLOW)info$(RESET)          - Show project information\n"
	@printf "  $(YELLOW)help$(RESET)          - Show this help message\n"

# Configure CMake build system
.PHONY: configure
configure:
	@printf "$(BOLD)$(BLUE)Configuring CMake build system...$(RESET)\n"
	@if [ "$(ENABLE_SANITISERS)" = "ON" ]; then \
		printf "$(BOLD)$(MAGENTA)Sanitisers enabled:$(RESET) $(SANITISERS)\n"; \
		printf "$(YELLOW)Building in Debug mode for sanitiser support$(RESET)\n"; \
	fi
	cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) \
		-DENABLE_SANITISERS=$(ENABLE_SANITISERS) \
		$(CMAKE_SANITISER_FLAGS)
	@printf "$(GREEN)✓ Configuration complete$(RESET)\n"

# Build the project
.PHONY: build
build: configure
	@printf "$(BOLD)$(BLUE)Building $(PROJECT_NAME)...$(RESET)\n"
	cmake --build $(BUILD_DIR)
	@printf "$(GREEN)✓ Build complete$(RESET)\n"

# Clean build directory
.PHONY: clean
clean:
	@printf "$(BOLD)$(YELLOW)Cleaning build directory...$(RESET)\n"
	@if [ -d "$(BUILD_DIR)" ]; then \
		rm -rf $(BUILD_DIR); \
		printf "$(GREEN)✓ Build directory cleaned$(RESET)\n"; \
	else \
		printf "$(YELLOW)Build directory doesn't exist$(RESET)\n"; \
	fi

# Clean and rebuild
.PHONY: rebuild
rebuild: clean build

# Install the application
.PHONY: install
install: build
	@printf "$(BOLD)$(BLUE)Installing $(PROJECT_NAME) to $(INSTALL_PREFIX)...$(RESET)\n"
	@mkdir -p $(BIN_DIR)
	@if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ]; then \
		cp $(BUILD_DIR)/bin/$(PROJECT_NAME) $(BIN_DIR)/; \
		chmod +x $(BIN_DIR)/$(PROJECT_NAME); \
		printf "$(GREEN)✓ Installed $(PROJECT_NAME) to $(BIN_DIR)$(RESET)\n"; \
	elif [ -f "./$(PROJECT_NAME)" ]; then \
		cp ./$(PROJECT_NAME) $(BIN_DIR)/; \
		chmod +x $(BIN_DIR)/$(PROJECT_NAME); \
		printf "$(GREEN)✓ Installed $(PROJECT_NAME) to $(BIN_DIR)$(RESET)\n"; \
	else \
		printf "$(RED)✗ Executable not found!$(RESET)\n"; \
		exit 1; \
	fi
	@printf "$(CYAN)You can now run: $(BIN_DIR)/$(PROJECT_NAME)$(RESET)\n"

# Uninstall the application
.PHONY: uninstall
uninstall:
	@printf "$(BOLD)$(YELLOW)Uninstalling $(PROJECT_NAME)...$(RESET)\n"
	@if [ -f "$(BIN_DIR)/$(PROJECT_NAME)" ]; then \
		rm -f $(BIN_DIR)/$(PROJECT_NAME); \
		printf "$(GREEN)✓ Uninstalled $(PROJECT_NAME)$(RESET)\n"; \
	else \
		printf "$(YELLOW)$(PROJECT_NAME) not found in $(BIN_DIR)$(RESET)\n"; \
	fi

# Update Discord SDK
.PHONY: update-discord
update-discord:
	@printf "$(BOLD)$(MAGENTA)Updating Discord SDK...$(RESET)\n"
	@if [ -f "./update_discord_sdk.py" ]; then \
		./update_discord_sdk.py; \
	elif [ -f "./update_discord_sdk.sh" ]; then \
		./update_discord_sdk.sh; \
	else \
		printf "$(RED)✗ Discord SDK update script not found!$(RESET)\n"; \
		exit 1; \
	fi

# Show available scripts
.PHONY: scripts
scripts:
	@printf "$(BOLD)$(CYAN)Available Scripts:$(RESET)\n"
	@printf "\n"
	@if [ -f "./update_discord_sdk.py" ]; then \
		printf "  $(GREEN)✓$(RESET) update_discord_sdk.py - Update Discord SDK files\n"; \
	fi
	@if [ -f "./update_discord_sdk.sh" ]; then \
		printf "  $(GREEN)✓$(RESET) update_discord_sdk.sh  - Update Discord SDK files (bash)\n"; \
	fi
	@if [ -f "./quick_cmake_build.py" ]; then \
		printf "  $(GREEN)✓$(RESET) quick_cmake_build.py   - Quick CMake build utility\n"; \
	fi
	@if [ -f "./run-clang-tidy.py" ]; then \
		printf "  $(GREEN)✓$(RESET) run-clang-tidy.py     - Run clang-tidy linter\n"; \
	fi
	@printf "\n"
	@printf "$(CYAN)Run scripts directly or use: make update-discord$(RESET)\n"

# Run the application
.PHONY: run
run: build
	@printf "$(BOLD)$(BLUE)Running $(PROJECT_NAME)...$(RESET)\n"
	@if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ]; then \
		$(BUILD_DIR)/bin/$(PROJECT_NAME); \
	elif [ -f "./$(PROJECT_NAME)" ]; then \
		./$(PROJECT_NAME); \
	else \
		printf "$(RED)✗ Executable not found!$(RESET)\n"; \
		exit 1; \
	fi

# Debug build and run with gdb
.PHONY: debug
debug:
	@printf "$(BOLD)$(MAGENTA)Building in debug mode...$(RESET)\n"
	cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX)
	cmake --build $(BUILD_DIR)
	@printf "$(BOLD)$(MAGENTA)Running with gdb...$(RESET)\n"
	@if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ]; then \
		gdb $(BUILD_DIR)/bin/$(PROJECT_NAME); \
	elif [ -f "./$(PROJECT_NAME)" ]; then \
		gdb ./$(PROJECT_NAME); \
	else \
		printf "$(RED)✗ Debug executable not found!$(RESET)\n"; \
		exit 1; \
	fi

# Run tests
.PHONY: test
test: build
	@printf "$(BOLD)$(BLUE)Running tests...$(RESET)\n"
	@if [ -d "$(BUILD_DIR)" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure; \
	else \
		printf "$(YELLOW)No tests configured$(RESET)\n"; \
	fi

# Format code
.PHONY: format
format:
	@printf "$(BOLD)$(BLUE)Formatting code...$(RESET)\n"
	@if [ -f ".clang-format" ]; then \
		find src include -name "*.cpp" -o -name "*.cppm" -o -name "*.hpp" | xargs clang-format -i; \
		printf "$(GREEN)✓ Code formatted$(RESET)\n"; \
	else \
		printf "$(YELLOW).clang-format not found, skipping formatting$(RESET)\n"; \
	fi

# Run linter
.PHONY: lint
lint:
	@printf "$(BOLD)$(BLUE)Running clang-tidy...$(RESET)\n"
	@if [ -f "./run-clang-tidy.py" ]; then \
		./run-clang-tidy.py; \
	elif [ -f "compile_commands.json" ]; then \
		clang-tidy src/**/*.cpp src/**/*.cppm -p .; \
	else \
		printf "$(YELLOW)No linting configuration found$(RESET)\n"; \
	fi

# Install/update dependencies
.PHONY: deps
deps:
	@printf "$(BOLD)$(BLUE)Checking dependencies...$(RESET)\n"
	@printf "$(CYAN)Required tools:$(RESET)\n"
	@for tool in $(REQUIRED_TOOLS); do \
		if command -v $$tool > /dev/null 2>&1; then \
			printf "  $(GREEN)✓$(RESET) $$tool\n"; \
		else \
			printf "  $(RED)✗$(RESET) $$tool (missing)\n"; \
		fi; \
	done
	@printf "\n"
	@printf "$(CYAN)Optional tools:$(RESET)\n"
	@for tool in gdb clang-format clang-tidy; do \
		if command -v $$tool > /dev/null 2>&1; then \
			printf "  $(GREEN)✓$(RESET) $$tool\n"; \
		else \
			printf "  $(YELLOW)○$(RESET) $$tool (optional)\n"; \
		fi; \
	done

# Show project information
.PHONY: info
info:
	@printf "$(BOLD)$(CYAN)Project Information$(RESET)\n"
	@printf "\n"
	@printf "$(BOLD)Project:$(RESET)      $(PROJECT_NAME)\n"
	@printf "$(BOLD)Build Dir:$(RESET)    $(BUILD_DIR)\n"
	@printf "$(BOLD)Install Dir:$(RESET)  $(INSTALL_PREFIX)\n"
	@printf "$(BOLD)Generator:$(RESET)    $(CMAKE_GENERATOR)\n"
	@printf "$(BOLD)Build Type:$(RESET)   $(CMAKE_BUILD_TYPE)\n"
	@printf "$(BOLD)Sanitisers:$(RESET)   $(if $(SANITISERS),$(SANITISERS),None)\n"
	@printf "\n"
	@printf "$(BOLD)Status:$(RESET)\n"
	@if [ -d "$(BUILD_DIR)" ]; then \
		printf "  $(GREEN)✓$(RESET) Build directory exists\n"; \
	else \
		printf "  $(YELLOW)○$(RESET) Build directory needs creation\n"; \
	fi
	@if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ] || [ -f "./$(PROJECT_NAME)" ]; then \
		printf "  $(GREEN)✓$(RESET) Executable built\n"; \
	else \
		printf "  $(YELLOW)○$(RESET) Executable needs building\n"; \
	fi
	@if [ -f "$(BIN_DIR)/$(PROJECT_NAME)" ]; then \
		printf "  $(GREEN)✓$(RESET) Installed to $(BIN_DIR)\n"; \
	else \
		printf "  $(YELLOW)○$(RESET) Not installed\n"; \
	fi

# Prevent make from treating file names as targets
.PHONY: $(BUILD_DIR) src include
