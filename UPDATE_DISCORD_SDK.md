# Discord SDK Update Scripts

This directory contains scripts to automatically update Discord SDK files from the `discord_social_sdk` directory to the `lib/discord` directory.

## Usage

### Method 1: Python Script (Recommended)
```bash
./update_discord_sdk.py
```

### Method 2: Bash Script  
```bash
./update_discord_sdk.sh
```

## How it works

When you drag and drop a new `discord_social_sdk` folder into the project root, run either script to automatically:

1. Copy all platform-specific libraries to the correct locations
2. Update the license file
3. Handle the iOS framework directory structure
4. Provide detailed logging of all operations

## File Mappings

The scripts copy files according to this structure:

```
discord_social_sdk/                 →  lib/discord/
├── License-Notices.txt             →  License-Notices.txt
├── lib/release/                    
│   ├── discord_partner_sdk.aar     →  android/discord_partner_sdk.aar
│   ├── libdiscord_partner_sdk.dylib→  darwin/libdiscord_partner_sdk.dylib  
│   ├── libdiscord_partner_sdk.so   →  linux/libdiscord_partner_sdk.so
│   ├── discord_partner_sdk.lib     →  win32/discord_partner_sdk.lib
│   └── discord_partner_sdk.xcframework → ios/discord_partner_sdk.xcframework
└── bin/release/
    └── discord_partner_sdk.dll     →  win32/discord_partner_sdk.dll
```

## Requirements

- Python 3.6+ (for Python script)
- Bash (for shell script)
- The `discord_social_sdk` directory must exist in the project root

Both scripts will create the necessary directory structure automatically.