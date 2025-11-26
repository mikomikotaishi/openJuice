#!/usr/bin/env python3
"""
Discord SDK Update Script

This script automatically copies Discord SDK files from the discord_social_sdk
directory to the lib/discord directory, maintaining the proper structure.
"""

import shutil
import sys
from pathlib import Path
from typing import List, Tuple


def log(message: str) -> None:
    """
    @brief Print a log message with formatting.

    @param message The message to log
    """
    print(f"[UPDATE] {message}")


def copy_file_with_dirs(src: Path, dst: Path) -> bool:
    """
    @brief Copy a file, creating destination directories if needed.

    @param src Source file path
    @param dst Destination file path

    @return True on success, False on failure
    """
    try:
        dst.parent.mkdir(parents = True, exist_ok = True)
        
        shutil.copy2(src, dst)
        log(f"Copied: {src.relative_to(src.parents[2])} -> {dst.relative_to(dst.parents[2])}")
        return True
    except Exception as e:
        log(f"ERROR copying {src}: {e}")
        return False


def update_discord_sdk(project_root: Path) -> int:
    """
    @brief Update Discord SDK files from discord_social_sdk to lib/discord.

    @param project_root Check if source directory existsoot: Path to the project root directory

    @return 0 on success, 1 on error
    """
    source_dir: Path = project_root / "discord_social_sdk"
    target_dir: Path = project_root / "lib" / "discord"

    if not source_dir.exists():
        log(f"ERROR: Source directory '{source_dir}' not found!")
        log("Please ensure discord_social_sdk is in the project root.")
        return 1
    
    log(f"Updating Discord SDK from {source_dir} to {target_dir}")
    
    file_mappings: List[Tuple[str, str]] = [
        # License file
        ("License-Notices.txt", "License-Notices.txt"),
        
        # Android library
        ("lib/release/discord_partner_sdk.aar", "android/discord_partner_sdk.aar"),
        
        # macOS library  
        ("lib/release/libdiscord_partner_sdk.dylib", "darwin/libdiscord_partner_sdk.dylib"),
        
        # Linux library
        ("lib/release/libdiscord_partner_sdk.so", "linux/libdiscord_partner_sdk.so"),
        
        # Windows libraries
        ("lib/release/discord_partner_sdk.lib", "win32/discord_partner_sdk.lib"),
        ("bin/release/discord_partner_sdk.dll", "win32/discord_partner_sdk.dll"),
    ]

    ios_framework_src: Path = source_dir / "lib" / "release" / "discord_partner_sdk.xcframework"
    ios_framework_dst: Path = target_dir / "ios" / "discord_partner_sdk.xcframework"
    
    success_count: int = 0
    total_count: int = len(file_mappings) + (1 if ios_framework_src.exists() else 0)

    for src_rel, dst_rel in file_mappings:
        src_path = source_dir / src_rel
        dst_path = target_dir / dst_rel
        
        if src_path.exists():
            if copy_file_with_dirs(src_path, dst_path):
                success_count += 1
        else:
            log(f"WARNING: Source file not found: {src_rel}")
    
    # Copy iOS framework directory
    if ios_framework_src.exists():
        try:
            # Remove existing iOS framework if it exists
            if ios_framework_dst.exists():
                shutil.rmtree(ios_framework_dst)
            
            # Create parent directory
            ios_framework_dst.parent.mkdir(parents=True, exist_ok=True)
            
            # Copy the entire framework directory
            shutil.copytree(ios_framework_src, ios_framework_dst)
            log(f"Copied: iOS framework -> {ios_framework_dst.relative_to(target_dir.parent)}")
            success_count += 1
        except Exception as e:
            log(f"ERROR copying iOS framework: {e}")
    else:
        log("WARNING: iOS framework not found")
    
    # Summary
    log(f"Update complete: {success_count}/{total_count} files copied successfully")
    
    if success_count == total_count:
        log("All Discord SDK files updated successfully!")
        return 0
    else:
        log(f"Some files failed to copy ({total_count - success_count} failed)")
        return 1


def main() -> int:
    """
    @brief Main entry point.

    @return 0 on success, 1 on error
    """

    script_dir: Path = Path(__file__).parent.absolute()
    
    log("Discord SDK Update Script")
    log(f"Project root: {script_dir}")
    
    try:
        return update_discord_sdk(script_dir)
    except KeyboardInterrupt:
        log("Update cancelled by user")
        return 1
    except Exception as e:
        log(f"Unexpected error: {e}")
        return 1

if __name__ == "__main__":
    sys.exit(main())
