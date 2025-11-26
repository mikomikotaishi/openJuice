#!/bin/bash
#
# Discord SDK Update Script (Bash version)
# 
# This script automatically copies Discord SDK files from discord_social_sdk
# to lib/discord, maintaining the proper directory structure.
#

# Colours for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Colour

# Logging function
log() {
    echo -e "${BLUE}[UPDATE]${NC} $1"
}

error() {
    echo -e "${RED}[ERROR]${NC} $1" >&2
}

warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

# Get script directory (project root)
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SOURCE_DIR="$PROJECT_ROOT/discord_social_sdk"
TARGET_DIR="$PROJECT_ROOT/lib/discord"

# Check if source directory exists
if [[ ! -d "$SOURCE_DIR" ]]; then
    error "Source directory '$SOURCE_DIR' not found!"
    error "Please ensure discord_social_sdk is in the project root."
    exit 1
fi

log "Updating Discord SDK from $SOURCE_DIR to $TARGET_DIR"

# Function to copy a file with directory creation
copy_file() {
    local src="$1"
    local dst="$2"
    
    if [[ -f "$src" ]]; then
        # Create destination directory
        mkdir -p "$(dirname "$dst")"
        
        # Copy the file
        cp "$src" "$dst"
        log "Copied: ${src#$PROJECT_ROOT/} -> ${dst#$PROJECT_ROOT/}"
        return 0
    else
        warning "Source file not found: ${src#$PROJECT_ROOT/}"
        return 1
    fi
}

# Initialise counters
SUCCESS_COUNT=0
TOTAL_COUNT=0

# Copy individual files
((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/License-Notices.txt" "$TARGET_DIR/License-Notices.txt" && ((SUCCESS_COUNT++))

((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/lib/release/discord_partner_sdk.aar" "$TARGET_DIR/android/discord_partner_sdk.aar" && ((SUCCESS_COUNT++))

((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/lib/release/libdiscord_partner_sdk.dylib" "$TARGET_DIR/darwin/libdiscord_partner_sdk.dylib" && ((SUCCESS_COUNT++))

((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/lib/release/libdiscord_partner_sdk.so" "$TARGET_DIR/linux/libdiscord_partner_sdk.so" && ((SUCCESS_COUNT++))

((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/lib/release/discord_partner_sdk.lib" "$TARGET_DIR/win32/discord_partner_sdk.lib" && ((SUCCESS_COUNT++))

((TOTAL_COUNT++))
copy_file "$SOURCE_DIR/bin/release/discord_partner_sdk.dll" "$TARGET_DIR/win32/discord_partner_sdk.dll" && ((SUCCESS_COUNT++))

# Handle iOS framework (entire directory)
IOS_FRAMEWORK_SRC="$SOURCE_DIR/lib/release/discord_partner_sdk.xcframework"
IOS_FRAMEWORK_DST="$TARGET_DIR/ios/discord_partner_sdk.xcframework"

((TOTAL_COUNT++))
if [[ -d "$IOS_FRAMEWORK_SRC" ]]; then
    # Remove existing framework if it exists
    if [[ -d "$IOS_FRAMEWORK_DST" ]]; then
        rm -rf "$IOS_FRAMEWORK_DST"
    fi
    
    # Create parent directory
    mkdir -p "$(dirname "$IOS_FRAMEWORK_DST")"
    
    # Copy the entire framework directory
    cp -r "$IOS_FRAMEWORK_SRC" "$IOS_FRAMEWORK_DST"
    log "Copied: iOS framework -> ${IOS_FRAMEWORK_DST#$PROJECT_ROOT/}"
    ((SUCCESS_COUNT++))
else
    warning "iOS framework not found: $IOS_FRAMEWORK_SRC"
fi

# Summary
log "Update complete: $SUCCESS_COUNT/$TOTAL_COUNT files copied successfully"

if [[ $SUCCESS_COUNT -eq $TOTAL_COUNT ]]; then
    success "All Discord SDK files updated successfully!"
    exit 0
else
    error "Some files failed to copy ($((TOTAL_COUNT - SUCCESS_COUNT)) failed)"
    exit 1
fi