# openJuice Project Makefile
# 
# This Makefile provides convenient targets for building, installing, and managing
# the openJuice project using CMake and Ninja.

# Project configuration
PROJECT_NAME := openJuice
BUILD_DIR ?= build
INSTALL_PREFIX := $(HOME)/.local
BIN_DIR := $(INSTALL_PREFIX)/bin
CMAKE_GENERATOR := Ninja
CMAKE_BUILD_TYPE := Release

# Timing function (uses shell built-ins for efficiency)
define print_time
	@END_TIME=$$(date +%s); \
	ELAPSED=$$(($$END_TIME - $(1))); \
	if [ $$ELAPSED -ge 60 ]; then \
		MINUTES=$$(($$ELAPSED / 60)); \
		SECONDS=$$(($$ELAPSED % 60)); \
		printf "$(GREEN)✓ Completed in $${MINUTES}m $${SECONDS}s$(RESET)\n"; \
	else \
		printf "$(GREEN)✓ Completed in $${ELAPSED}s$(RESET)\n"; \
	fi
endef

# Sanitizer configuration (can be overridden with make SANITIZERS="address undefined")
SANITIZERS ?=
ENABLE_SANITIZERS := OFF
CMAKE_SANITIZER_FLAGS :=

# Process sanitizer flags
ifneq ($(SANITIZERS),)
	ENABLE_SANITIZERS := ON
	CMAKE_BUILD_TYPE := Debug
	
	ifeq ($(findstring address,$(SANITIZERS)),address)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_ADDRESS=ON -DUSE_SANITIZER_LEAK=ON
	endif
	
	ifeq ($(findstring kernel-address,$(SANITIZERS)),kernel-address)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_KERNEL=ON
	endif
	
	ifeq ($(findstring hw-address,$(SANITIZERS)),hw-address)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_HW=ON
	endif
	
	ifeq ($(findstring undefined,$(SANITIZERS)),undefined)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_UNDEFINED=ON
	endif
	
	ifeq ($(findstring thread,$(SANITIZERS)),thread)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_THREAD=ON
	endif
	
	ifeq ($(findstring memory,$(SANITIZERS)),memory)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_MEMORY=ON
	endif
	
	ifeq ($(findstring leak,$(SANITIZERS)),leak)
		CMAKE_SANITIZER_FLAGS += -DUSE_SANITIZER_LEAK=ON
	endif
	
	ifeq ($(SANITIZERS),all)
		CMAKE_SANITIZER_FLAGS := -DUSE_SANITIZER_ADDRESS=ON -DUSE_SANITIZER_UNDEFINED=ON -DUSE_SANITIZER_LEAK=ON
	endif
	
	ifeq ($(SANITIZERS),all-kernel)
		CMAKE_SANITIZER_FLAGS := -DUSE_SANITIZER_KERNEL=ON -DUSE_SANITIZER_UNDEFINED=ON -DUSE_SANITIZER_MEMORY=ON -DUSE_SANITIZER_LEAK=ON
	endif
	
	ifeq ($(SANITIZERS),all-hardware)
		CMAKE_SANITIZER_FLAGS := -DUSE_SANITIZER_HW=ON -DUSE_SANITIZER_UNDEFINED=ON -DUSE_SANITIZER_MEMORY=ON -DUSE_SANITIZER_LEAK=ON
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
	@printf "$(BOLD)Build Options:$(RESET)\n"
	@printf "  $(YELLOW)BUILD_DIR$(RESET)     - Specify build directory (default: build)\n"
	@printf "    Example: make build BUILD_DIR=mybuild\n"
	@printf "\n"
	@printf "$(BOLD)Install Targets:$(RESET)\n"
	@printf "  $(YELLOW)install$(RESET)       - Install to $(INSTALL_PREFIX)/bin\n"
	@printf "  $(YELLOW)uninstall$(RESET)     - Remove installed files\n"
	@printf "\n"
	@printf "$(BOLD)Sanitizer Options:$(RESET)\n"
	@printf "  $(YELLOW)SANITIZERS$(RESET)    - Enable sanitizers (builds in Debug mode)\n"
	@printf "    Values: address, kernel-address, hw-address, undefined, thread, memory, leak\n"
	@printf "    Special: all, all-kernel, all-hardware\n"
	@printf "    Example: make build SANITIZERS=\"address undefined\"\n"
	@printf "    Example: make run SANITIZERS=all\n"
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
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(BLUE)Configuring CMake build system...$(RESET)\n"; \
	if [ "$(ENABLE_SANITIZERS)" = "ON" ]; then \
		printf "$(BOLD)$(MAGENTA)Sanitizers enabled:$(RESET) $(SANITIZERS)\n"; \
		printf "$(YELLOW)Building in Debug mode for sanitizer support$(RESET)\n"; \
	fi; \
	cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
		-DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX) \
		-DENABLE_SANITIZERS=$(ENABLE_SANITIZERS) \
		$(CMAKE_SANITIZER_FLAGS); \
	END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
	printf "$(GREEN)✓ Configuration complete in $${ELAPSED}s$(RESET)\n"

# Build the project
.PHONY: build
build: configure
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(BLUE)Building $(PROJECT_NAME) library...$(RESET)\n"; \
	BUILD_EXIT=0; cmake --build $(BUILD_DIR) || BUILD_EXIT=$$?; \
	END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
	if [ $$ELAPSED -ge 60 ]; then \
		MINUTES=$$(($$ELAPSED / 60)); SECONDS=$$(($$ELAPSED % 60)); \
		if [ $$BUILD_EXIT -ne 0 ]; then \
			printf "$(RED)✗ Build failed in $${MINUTES}m $${SECONDS}s$(RESET)\n"; exit $$BUILD_EXIT; \
		else \
			printf "$(GREEN)✓ Build complete in $${MINUTES}m $${SECONDS}s$(RESET)\n"; \
		fi; \
	else \
		if [ $$BUILD_EXIT -ne 0 ]; then \
			printf "$(RED)✗ Build failed in $${ELAPSED}s$(RESET)\n"; exit $$BUILD_EXIT; \
		else \
			printf "$(GREEN)✓ Build complete in $${ELAPSED}s$(RESET)\n"; \
		fi; \
	fi

# Clean build directory
.PHONY: clean
clean:
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(YELLOW)Cleaning build directory...$(RESET)\n"; \
	if [ -d "$(BUILD_DIR)" ]; then \
		rm -rf $(BUILD_DIR); \
		END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
		printf "$(GREEN)✓ Build directory cleaned in $${ELAPSED}s$(RESET)\n"; \
	else \
		printf "$(YELLOW)Build directory doesn't exist$(RESET)\n"; \
	fi

# Clean and rebuild
.PHONY: rebuild
rebuild:
	@START_TIME=$$(date +%s); \
	$(MAKE) clean; \
	BUILD_EXIT=0; $(MAKE) build || BUILD_EXIT=$$?; \
	END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
	if [ $$ELAPSED -ge 60 ]; then \
		MINUTES=$$(($$ELAPSED / 60)); SECONDS=$$(($$ELAPSED % 60)); \
		if [ $$BUILD_EXIT -ne 0 ]; then \
			printf "$(RED)✗ Rebuild failed in $${MINUTES}m $${SECONDS}s$(RESET)\n"; exit $$BUILD_EXIT; \
		else \
			printf "$(GREEN)✓ Rebuild complete in $${MINUTES}m $${SECONDS}s$(RESET)\n"; \
		fi; \
	else \
		if [ $$BUILD_EXIT -ne 0 ]; then \
			printf "$(RED)✗ Rebuild failed in $${ELAPSED}s$(RESET)\n"; exit $$BUILD_EXIT; \
		else \
			printf "$(GREEN)✓ Rebuild complete in $${ELAPSED}s$(RESET)\n"; \
		fi; \
	fi

# Install the application
.PHONY: install
install: build
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(BLUE)Installing $(PROJECT_NAME) to $(INSTALL_PREFIX)...$(RESET)\n"; \
	mkdir -p $(BIN_DIR); \
	if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ]; then \
		cp $(BUILD_DIR)/bin/$(PROJECT_NAME) $(BIN_DIR)/; \
		chmod +x $(BIN_DIR)/$(PROJECT_NAME); \
		END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
		printf "$(GREEN)✓ Installed $(PROJECT_NAME) to $(BIN_DIR) in $${ELAPSED}s$(RESET)\n"; \
	elif [ -f "./$(PROJECT_NAME)" ]; then \
		cp ./$(PROJECT_NAME) $(BIN_DIR)/; \
		chmod +x $(BIN_DIR)/$(PROJECT_NAME); \
		END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
		printf "$(GREEN)✓ Installed $(PROJECT_NAME) to $(BIN_DIR) in $${ELAPSED}s$(RESET)\n"; \
	else \
		printf "$(RED)✗ Executable not found!$(RESET)\n"; \
		exit 1; \
	fi; \
	printf "$(CYAN)You can now run: $(BIN_DIR)/$(PROJECT_NAME)$(RESET)\n"

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
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(MAGENTA)Building in debug mode...$(RESET)\n"; \
	cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_INSTALL_PREFIX=$(INSTALL_PREFIX); \
	cmake --build $(BUILD_DIR); \
	END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
	if [ $$ELAPSED -ge 60 ]; then \
		MINUTES=$$(($$ELAPSED / 60)); SECONDS=$$(($$ELAPSED % 60)); \
		printf "$(GREEN)✓ Debug build complete in $${MINUTES}m $${SECONDS}s$(RESET)\n"; \
	else \
		printf "$(GREEN)✓ Debug build complete in $${ELAPSED}s$(RESET)\n"; \
	fi; \
	printf "$(BOLD)$(MAGENTA)Running with gdb...$(RESET)\n"; \
	if [ -f "$(BUILD_DIR)/bin/$(PROJECT_NAME)" ]; then \
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
	@START_TIME=$$(date +%s); \
	printf "$(BOLD)$(BLUE)Running tests...$(RESET)\n"; \
	if [ -d "$(BUILD_DIR)" ]; then \
		cd $(BUILD_DIR) && ctest --output-on-failure; \
		END_TIME=$$(date +%s); ELAPSED=$$(($$END_TIME - $$START_TIME)); \
		printf "$(GREEN)✓ Tests complete in $${ELAPSED}s$(RESET)\n"; \
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
	@printf "$(BOLD)Sanitizers:$(RESET)   $(if $(SANITIZERS),$(SANITIZERS),None)\n"
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
